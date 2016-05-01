// Copyright (c) 2016 Jace Thompson
// Please see LICENSE for license or visit https://github.com/Roots-of-Unity/recipe2
#include "ItemOrderParser.h"
#include <iostream>//for debugging in this file. remove later
//the fun begins.

//constructor uses an initializer list for class' data members
ItemOrderParser::ItemOrderParser(std::ifstream *ptrToFileStream)
	: filePtr(ptrToFileStream)
{
	
}

bool ItemOrderParser::read_row()
{
	//getline works like getline( input stream, string to put stuff in, delimiter character)
	//why does the following for statement work?
	for (; std::getline((*ItemOrderParser::filePtr), ItemOrderParser::myLine;)
	{
		std::cout << myLine << std::endl;
	}
	return false;
}
