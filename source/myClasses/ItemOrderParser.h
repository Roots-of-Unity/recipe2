// Copyright (c) 2016 Jace Thompson
// Please see LICENSE for license or visit https://github.com/Roots-of-Unity/recipe2

#ifndef ITEMORDERPARSER_H
#define ITEMORDERPARSER_H
#include <fstream>//for ifstream object
#include <string>
#include <vector>

class ItemOrderParser
{

public:
	//takes an ifstream as it's constructor
	//declared explicit to avoid implicit conversions of the argument
	explicit ItemOrderParser(std::string f);
	

	//passing a reference to a private datamember breaks encapsulation, so pass by value
	std::vector< double >       getSequenceOrderVector();

	//passing a reference to a private datamember breaks encapsulation, so pass by value
	std::vector < std::string > getItemVector();


private:
	//string that holds file name
	std::string fileName;
	
	//variables that hold the parsed data

	std::vector< double > sequenceOrder;
	//these 2 I'm leaving unimplemented because they're not necessary for now:
	std::string quantity;
	std::string unit;

	std::vector < std::string > item;

	//function that initializes the class's datamembers to what is in the csv
	void read_file();
	

};

#endif //ITEMORDERPARSER_H