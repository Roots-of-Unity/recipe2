// Copyright (c) 2016 Jace Thompson
// Please see LICENSE for license or visit https://github.com/Roots-of-Unity/recipe2

#ifndef ITEMORDERPARSER_H
#define ITEMORDERPARSER_H
#include <fstream>//for ifstream object
#include <string>

class ItemOrderParser
{

public:
	//takes an ifstream as it's constructor
	//declared explicit to avoid implicit conversions of the argument
	explicit ItemOrderParser(std::string f);
	
	//function that reads a row and updates the class's datamembers to what is in the row
	//returns false when the end of file has been reached.
	//This way while(csv.read_row()) works as intended.
	void read_row();

private:
	//string that holds file name
	std::string fileName;
	
	//variables that hold the parsed data
	double order;
	std::string quantity;
	std::string unit;
	std::string item;

	//variable that holds the unparsed data from getline()
	std::string myLine;
	

};

#endif //ITEMORDERPARSER_H