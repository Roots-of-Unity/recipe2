#include "store.h"
#include <vector>
#include <fstream> //for ifstream object
#include <iostream>
#include "../libraries/utfcpp-master/source/utf8.h" //for utf8 support


//pass the file vector by reference to avoid copying it.
Store &Store::addtoInventorySequence(const std::vector<std::string> &fileVector)
{
	//this function should probably be split up into smaller functions
	//at a later date. I'll go ahead and mark what each part does
	//with a label;

	///////////////////////////////////////////////
	//Open files given to the fileVector parameter:
	///////////////////////////////////////////////

	//As it turns out: enumerating files in a directory is a task specific to the OS
	//So at this moment I'm changing the support level to single files in the local directory.
	//It looks like C++17 might have a standard filesystem library:
	//http://en.cppreference.com/w/cpp/experimental/fs

	//vector of pointers to ifstreams
	//more tips on vector of pointers:
	//http://stackoverflow.com/questions/2853438/c-vector-of-pointers
	std::vector< std::ifstream * > inputFileVector;

	//I have limited knowledge of how well the following dynamic ifstream manipulation will go.
	//I also have only a little knowledge on exception handling. I must read more!
	//So I'm going to mix the two limited knowledges together,
	//And if my code breaks, at least it can std::cout where it broke.

	//For each "file" (or for each string) in the fileVector
	try
	{
		for (auto &fileName : fileVector)
		{
			//make some input streams!
			//<DEBUG>Be sure to deallocate stuff allocated by the new keyword. Deitel pg 452.
			inputFileVector.push_back(new std::ifstream(fileName, std::ios::in));
			//In the above, ios::in marks those input streams as being used for input only.
		}
	}
	catch(...)//catch all. Downside is that details related to specific exceptions can't be retrieved this way.
	{
		std::cout << "Error handling files in Store::addtoInventorySequence(). Verify filenames are inputted correctly.\n";
	}

	//test if each files in the filevector were opened successfully
	for (size_t i = 0; i < inputFileVector.size(); ++i)
	{
		//below translates to: if the file is not open
		//-> operator because vector stores pointers
		if (!inputFileVector.at(i)->is_open())
		{
			//if this conditions occurs, I don't want the program to continue
			//even though it technically could.
			//I'd still want the user to know a file wasn't processed, before running
			//the program on a large set of data
			//only to find at the end a file wasn't inputted.
			std::cout <<
				"Could not open file: " <<
				//This next parts gets tricky. ifstreams don't store the filename they're constructed with.
				//But I already have the data from the fileVector parameter. So I just have to cross reference
				//using indexes.
				//I figure this is better than a helper class as mentioned here:
				//http://stackoverflow.com/questions/31100249/can-i-get-the-name-of-file-used-from-ifstream-ofstream/31100271
				//because I already have the required data as an argument in this function.
				fileVector.at(i) << "\n\n"<<
				"Terminating program." << "\n" <<
				"Make sure the file exists in the same directory as recipe2." << "\n" <<
				"Be sure to pass only the exact name of the file\n" <<
				"with no symbols related to the filesystem\n" <<
				"examples: . / :" << std::endl;
			std::exit(1);

	
		}
	}

	//Now that the files are validated(not all the way)->
	//Only because ifstream was able to open them:

	/////////////////////////////////////////////////////////////
	//Take the opened streams and validate their encoding (UTF-8)
	/////////////////////////////////////////////////////////////

	//the following is adapted from the introductory example
	//found here:
	//https://github.com/nemtrif/utfcpp

	//for each file in the inputFileVector
	for (size_t i = 0; i < inputFileVector.size(); ++i)
	{
		//separating this into it's own line for
		//readabilites sake
		//copy pointer to ifstream into it's own variable
		std::ifstream *filePtr = inputFileVector.at(i);
		//if file is not valid utf8
		if (!valid_utf8_file(filePtr))
		{
			std::cout << "Error file: " << fileVector.at(i) << "\n" <<
				"is not valid UTF-8. " << "Please input only UTF-8 valid files." << std::endl;
			exit(1);
		}
	}
	std::cout << "\nAll files are valid UTF-8. Continuing.\n";
	
	//now that all the files are UTF-8 encoded, I can move onto parsing the csv format


	//<RESUME>
	//
	//Feed the validated files into the map 
	//Stuff is going to collide here if multiple files fed
	//into the program, (does x come before y)
	//so get ready for that
	//

	///////////////////////////////////////
	//Clean up dynamically allocated memory
	///////////////////////////////////////
	//<DEBUG> deallocate memory from the inputFileVector
	//pass by value here, because I'm just copying pointers. This is the same as what passing by reference does. It just
	//copies address locations. If I did: auto& inputFileStreamPtr I'd be passing a reference to a pointer which is weird.
	for (auto inputFileStreamPtr : inputFileVector)
	{
		//delete calls the destructor of the object that the pointer points to:
		delete inputFileStreamPtr;
		//Deitel page 451. Set the ptr to nullptr immediate after you called delete on it.
		//This prevents undefied behavior if you were to mistakenly call delete on the pointer again.
		inputFileStreamPtr = nullptr;

	}
	return (*this);
}

void Store::saveInventorySequence(std::string storeName, std::string path)
{

}

bool Store::valid_utf8_file(std::ifstream *filePtr)
{
	//if file not open
	if (!(*filePtr))
	{
		std::cout << "\nError file is not open in UTF-8 checker\n";
		return false;
	}

	//iterate through the file buffer without copying into
	//memory first
	std::istreambuf_iterator<char> it((*filePtr).rdbuf());
	std::istreambuf_iterator<char> eos;

	return utf8::is_valid(it, eos);
}
