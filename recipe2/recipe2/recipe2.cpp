//My Copyright Notice: Jace Thompson


#include <iostream>

//let's me parse input fed from the commandline easily. see rational for use in
//"./documentation/parseInput.txt"
#include "./libraries/cxxopts-master/src/cxxopts.hpp"

int main(int argc, char* argv[])
{
	//this try block catches errors related to the library I'm using for command line parameters: cxxopts
	try
	{
		//declare an object from class cxxopts::Options. This is the object that has all the functionality
		//for processing user input from command line parameters.
		cxxopts::Options myCommandlineOptions(argv[0], 
		" [FILE...]");//example usage string
		//In the above, "argv[0]" is the argument vector of the system. According to Deitel, this C feature
		//isn't guaranteed portable to every C/C++ implementation, but it covers the
		//usual suspects mainstream users are on. Certain operating systems (OpenVMS) have their own
		//way of getting arguments from the commandline.
		//
		//Also, the cxxopts::Options object takes the argv[0] during construction and is able to parse
		//what was passed in that vector.

		//Below, the options I want for my project are declared. This function makes use of 
		//overloaded operator() and maybe even operator*. I have no idea how ()() is interpretted by C
		//I assume multiplication. <TO BE READ UP ON DURING ANOTHER DAY>
		myCommandlineOptions.add_options()
			("s,shoppingList", "generates a shopping list from [FILE...]")
			("h,help", "display this help text and exit");

		//after defining the options, tell the cxxopts to parse command line parameters
		myCommandlineOptions.parse(argc, argv);
		
		//if there was only 1 argument given (the program's name)
		//details here: 
		//http://stackoverflow.com/questions/17007557/c-how-to-check-if-an-arguement-was-given-or-not
		if (argc == 1)
		{
			//display a tiny help message
			std::cout <<
			"Usage: recipe2 [OPTION...] [FILE...]\n" <<
			"Try 'recipe2 --help' for more information.\n";
		}
		//count( option ) returns the number of the times the argument was found
		//so logically, if ( an argument is present )
		if (myCommandlineOptions.count("help"))
		{
			std::cout << myCommandlineOptions.help();
		}
		if (myCommandlineOptions.)

	}
	//catches errors relating to command line parameters
	catch (const cxxopts::OptionException& e)
	{
		std::cout << "error parsing options: " << e.what() << std::endl;
		exit(1);
	}
	
	return 0;
}//end of main