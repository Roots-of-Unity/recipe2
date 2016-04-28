#include "store.h"
#include <vector>
#include <fstream> //for ifstream object
#include <iostream>


//pass the file vector by reference to avoid copying it.
Store &Store::addtoInventorySequence(const std::vector<std::string> &fileVector)
{
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

			//<DEBUG> 
		}
	}
	catch(...)//catch all. Downside is that details related to specific exceptions can't be retrieved this way.
	{
		std::cout << "Error handling files in Store::addtoInventorySequence(). Verify filenames are inputted correctly.\n";
	}

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
