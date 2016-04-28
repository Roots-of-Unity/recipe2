//My Copyright Notice: Jace Thompson


#include <iostream>
#include "./myClasses/store.h" //that's store: as in the place where you buy things

//let's me parse input fed from the commandline easily. see rational for use in
//"./documentation/parseInput.txt"
#include "./libraries/cxxopts-master/src/cxxopts.hpp"

int main(int argc, char* argv[])
{
	//This variable stores the list of files from what the user input into the commandline.
	//An example fileVector might be: { thisIngredientList.txt, thatIngredientList.txt, ingredientList }
	//This variable gets used later in the program, after the following 
	//try block (which is where the library cxxopts) finishes parsing and doing
	//some of the required validations on the user's input.
	std::vector< std::string > fileVector;

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
			("s,shoppingList", "generates an optimized shopping list from [FILE...]")
			("h,help", "display this help text and exit")
			//("r,recursive", "enable to parse directories recursively")//probably get rid of this one
			("f,file", "Positional argument. Can be entered without --file flag. Supports file(s) in the local directory.", cxxopts::value<std::vector<std::string>>());//

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

		//after defining the options, tell the cxxopts to parse command line parameters

		//parse positional (arguments that are entered without an option)
		myCommandlineOptions.parse_positional("file");

		myCommandlineOptions.parse(argc, argv);
		

		//count( option ) returns the number of the times the argument was found
		//so logically, if ( an argument is present )
		if (myCommandlineOptions.count("help"))
		{
			std::cout << myCommandlineOptions.help();
			exit(0);
		}
		//<DEBUG>
		if (myCommandlineOptions.count("shoppingList"))
		{
			std::cout << "shoppingList is present.\n";
		}
		
		//<DEBUG>
		//if (myCommandlineOptions.count("recursive"))
		//{
		//	std::cout << "recursive is present.\n";
		//}
		//<DEBUG>

		if (myCommandlineOptions.count("file"))
		{
			std::cout << "file = {";
			auto& v = myCommandlineOptions["file"].as<std::vector<std::string>>();
			for (const auto& s : v)
			{
				std::cout << s << ", ";
			}
			std::cout << "}" << std::endl;

			//store the fileVector for use later use in the program
			fileVector = myCommandlineOptions["file"].as<std::vector<std::string>>();
		}
	}
	//catches errors relating to command line parameters
	catch (const cxxopts::OptionException& e)
	{
		std::cout << "error parsing options: " << e.what() << std::endl;
		exit(1);
	}
	
	//<DEBUG> the Jace Thompson proving grounds below:
	Store myStore;
	
	//fileVector is from the "file" commmand line parameter of the program.
	myStore.addtoInventorySequence(fileVector);

	return 0;
}//end of main