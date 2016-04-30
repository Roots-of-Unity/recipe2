#include "store.h"
#include <vector>
#include <fstream> //for ifstream object
#include <iostream>
#include <string>
#include "../libraries/utfcpp-master/source/utf8.h" //for utf8 validator. requires cpp
#include "../libraries/fast-cpp-csv-parser-master/csv.h" //for csv parsing abilities. requires c


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
			inputFileVector.push_back( new std::ifstream(fileName, std::ios::in));
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
			
			//<del>
			//Decided to not let this entire function have exit points. It's better to just guarantee that
			//the function reaches the end and returns dynamically allocated memory.
			//</del>
		
			//Unique_ptrs are great for small tasks, but I require more reading to get them to work properly
			//with operator new and within vectors. So I'll just require that before every exit point in this function I 
			//deallocate my pointers.

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
			std::exit(1);
			//<del>^Since I'm using std::exit(). It's worth noting that I need to make sure the stack gets "unwound".
			//As exit doesn't take care of this. source:
			//http://en.cppreference.com/w/cpp/utility/program/exit
			//The stack is where dynamic memory allocation takes place. So I need to use a ptr that guarantees that on 
			//exit it destructs it's object and deallocates the memory. That would be unique_ptr. I'm going to 
			//go back and fix my ptr vector of ifstreams.
			//</del>
			

	
		}//end if
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

			///////////////////////////////////////////////////
			//Clean up dynamically allocated memory before exit
			///////////////////////////////////////////////////
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

			exit(1);
		}//end if
	}
	std::cout << "\nAll files are valid UTF-8. Continuing.\n";
	
	//now that all the files are UTF-8 encoded, I can move onto parsing the csv format

	//Here, I'm using the fast cpp cvs parser found here:
	//https://github.com/ben-strasser/fast-cpp-csv-parser
	//Now that I can guarantee the encoding of the files are valid UTF 8 for the csv parser
	//I can discard my input file streams, since the parser has it's own way of 
	//getting input from the file. 
	
	//<code here>
	
	//Then, I just pass the names of the files that have been validated
	//and are good to go.

	//<RESUME>
	//
	//Feed the validated files into the map 
	//Stuff is going to collide here if multiple files fed
	//into the program, (does x come before y)
	//so get ready for that
	//

	//the following is adapted from these examples:
	//https://github.com/ben-strasser/fast-cpp-csv-parser
	//^Edit: It turns out that this uses so much new ~~c++11~~, (lol, it's actually uses
	//C++14 threads woops:
	//https://www.reddit.com/r/cpp/comments/3lrsbt/whats_your_go_to_modern_c_csv_reader/cv95b3u
	//that it exposes
	//bugs in mingw. Visual Studio won't compile it of course. So while it may work on
	//*nix OS's with a nice gcc implementation: I have to pitch it for cross platform reasons,
	//Until windows gets a fully compliant ~~c++11~~ c++14 compiler.
	//So I lost some time debugging this issue, but no worries. I pick the following as my
	//next library to try out:

	//I'm just rolling my own custom file parser. I'm making it the minimum component that can possibly get
	//the job done. Also, CSV has no formal standard (I learned a ton from the entire thread):
	//https://www.reddit.com/r/cpp/comments/3lrsbt/whats_your_go_to_modern_c_csv_reader/cv8wwuh
	//I shall call it ItemOrderParser

	//4 columns in the style I want my csv files to be in.
	//This standard is described in the /documentation directory of
	//this project
	const unsigned int column_count = 4;
	//for each file in the file vector
	for (auto fileString : fileVector)
	{
		//create a CSVReader object named csv
		io::CSVReader<column_count> csv(fileString);
		
		//Next, I name the columns in the .csv file
		//ignore_no_column outputs an error if there are more columns in the *.csv file
		csv.read_header( io::ignore_no_column, "order", "quantity", "unit", "item");
		//define the types of each column:
		double order;
		//because unicode symbols are used in the quantity
		//I'm leaving it as a string and not actually using this data.
		std::string quantity;
		std::string unit;
		std::string item;
		//loops through the csv row by row and puts the
		//row data into the above variables
		while (csv.read_row(order, quantity, unit, item))
		{
			//<DEBUG>
			std::cout << order << " " <<
				quantity << " " <<
				unit << " " <<
				item << std::endl;
			//</DEBUG>
		}
	}



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
