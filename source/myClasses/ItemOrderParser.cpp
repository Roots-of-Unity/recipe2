// Copyright (c) 2016 Jace Thompson
// Please see LICENSE for license or visit https://github.com/Roots-of-Unity/recipe2
#include "ItemOrderParser.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../libraries/utfcpp-master/source/utf8.h"
#include <cstdlib>

//constructor uses an initializer list to
//intialize data member fileName with argument f
ItemOrderParser::ItemOrderParser(std::string f)
	: fileName(f)
{
	
}

void ItemOrderParser::read_row()
{
	
	/*
	std::cout << filePtr->eof() << "\n";
	std::string bigString((std::istreambuf_iterator<char>(*filePtr)), std::istreambuf_iterator<char>());
	std::cout << bigString << "\n";

	//while we haven't reached the end of file
	while (!filePtr->eof())
	{
		std::cout << "hi.\n";
		//getline's paramters:
		//getline( input stream, string to put stuff in, [delimiter character])
		std::cout << filePtr->eof();
		std::cout << myLine << std::endl;
		break;
	}
	//getline works like getline( input stream, string to put stuff in, delimiter character)
	//why does the following for statement work?
	for (; std::getline((*ItemOrderParser::filePtr), ItemOrderParser::myLine);)
	{
		std::cout << myLine << std::endl;
		//this'll probably result in an infinite loop until I put in a condition
		//that goes if(istream says end of file/end of stream return true)
		
	}
	*/
	// Open the test file (contains UTF-8 encoded text)

	//open the ifstream
	//std::ios::in marks it for read only
	std::ifstream myFile(fileName, std::ios::in);
	
	if (!myFile.is_open())
	{
		std::cout << "Could not open " << fileName;
		std::exit(1);
	}
	
	//ok I just spent too much time figuring out why passing by pointer to getline doesn't work in this case.
	//I believe that going out of scope nukes the pointers in function scope. So now that I've figured
	//that out. Let's rewrite this section!
	unsigned line_count = 1;
	std::string line;
	while (std::getline(myFile, line))
	{
		// check for invalid utf-8 (for a simple yes/no check, there is also utf8::is_valid function)
		std::string::iterator end_it = utf8::find_invalid(line.begin(), line.end());
		if (end_it != line.end()) 
		{
			std::cout << "Invalid UTF-8 encoding detected at line " << line_count << "\n";
			std::cout << "This part is fine: " << std::string(line.begin(), end_it) << "\n";
		}
		// Get the line length (at least for the valid part)
		int length = utf8::distance(line.begin(), end_it);
		std::cout << "Length of line " << line_count << " is " << length << "\n";

		// Convert it to utf-16
		std::vector<unsigned short> utf16line;
		utf8::utf8to16(line.begin(), end_it, back_inserter(utf16line));

		// And back to utf-8
		std::string utf8line;
		utf8::utf16to8(utf16line.begin(), utf16line.end(), back_inserter(utf8line));

		// Confirm that the conversion went OK:
		if (utf8line != std::string(line.begin(), end_it))
			std::cout << "Error in UTF-16 conversion at line: " << line_count << "\n";

		line_count++;
	}
}
