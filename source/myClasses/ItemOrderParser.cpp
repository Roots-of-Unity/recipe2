// Copyright (c) 2016 Jace Thompson
// Please see LICENSE for license or visit https://github.com/Roots-of-Unity/recipe2
#include "ItemOrderParser.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../libraries/utfcpp-master/source/utf8.h" //needed for utf8 iterator
#include <cstdlib> //for exit and atof()

//constructor uses an initializer list to
//intialize data member fileName with argument f
ItemOrderParser::ItemOrderParser(std::string f)
	: fileName(f)
{
	//initializes the classes data members from the file
	read_file();
}

void ItemOrderParser::read_file()
{
	
	/* //scrap code from first try at a parser using a pointer to an already existing dynamically allocated ifstream
	   //which as it turns out was out of scope!
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

	//open the ifstream
	//std::ios::in marks it for read only
	std::ifstream myFile(fileName, std::ios::in);
	
	if (!myFile.is_open())
	{
		std::cout << "Could not open " << fileName;
		std::exit(1);
	}
	
	//ok I just spent too much time figuring out why passing by pointer to getline doesn't work in this case.
	//I believe that going out of scope nukes the dynamically allocated memory in function scope. So now that I've figured
	//that out. Let's rewrite this section!
	//unsigned line_count = 1;
	std::string line;
	std::string mySequenceBuffer;//buffer for the sequence field
	double myConversionBuffer;//holds a numeric characters to be saved for conversion with atof
	std::string myItemBuffer;//buffer for the item field
	int commaCounter = 0;
	while (std::getline(myFile, line))
	{
		//reset variables per line:
		mySequenceBuffer.clear();
		myConversionBuffer = 0;
		myItemBuffer.clear();
		commaCounter = 0;

		//std::cout << line;
		//std::string::iterator end_it = utf8::find_invalid(line.begin(), line.end());
		

		//iterators are magnificent! 
		//The following starts a new string iterator at the beginning of
		//my line. While that iterator is not equal to the end iterator
		//I bump the iterator it up by 1 to the next character.

		for (std::string::iterator it = line.begin(); it != line.end(); ++it)
		{
			//if the iterator is a comma
			//hopefully this works with utf8. In theory, it should.
			if( *it == ',')
			{
				++commaCounter;
			}
			if (*it == '"')
			{
				//remove quote marks for neatness
				continue;
			}
			if (commaCounter == 0)//if we're in the first field: fill up Sequence Order
			{
				//fill up the sequence buffer:

				//dereferencing an iterator returns what it points to
				//in this case a character in a string
				mySequenceBuffer.push_back((*it));
			}
			if (commaCounter == 3)//while we're in the fourth field: item (At this point I'm leaving the rest unimplemented until I need it
			{
				if ((*it) == ',')
				{
					//edge condition where the first character that gets loaded is a comma
					continue;
				}
				//fill up the item buffer
				myItemBuffer.push_back((*it));
			}
			
		}
		//after we've just parsed a line, I need to add sequence order and item to their respective vector datamembers

		//I don't think atof is guaranteed to throw errors
		//The error occurs when you try to store a string in a double from a failed atof()
		myConversionBuffer = std::atof(mySequenceBuffer.c_str());
		
		//store the double in the sequenceOrder vector datamember
		(*this).sequenceOrder.push_back(myConversionBuffer);

		//now to store the fourth field: item
		(*this).item.push_back(myItemBuffer);
		

	}
}

//passing a reference to a private datamember breaks encapsulation
std::vector<double> ItemOrderParser::getSequenceOrderVector()
{
	return (*this).sequenceOrder;
}

//passing a reference to a private datamember breaks encapsulation, so pass by value
std::vector<std::string> ItemOrderParser::getItemVector()
{
	return (*this).item;
}
