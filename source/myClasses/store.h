//include guard
#ifndef STORE_H
#define STORE_H

#include <map>
#include <string>
#include <vector>

class Store
{
public:
	//reads the file vector and adds contents to the store's inventorySequence
	//const because I'm reading the fileVector, not modifying it.
	//cascadable
	Store &addtoInventorySequence(const std::vector<std::string> &fileVector );

	void saveInventorySequence(std::string storeName, std::string path);

private:
	//takes doubles as the key values and string as the value type
	//This datamember represents a sequence of known items in the store along 
	//the human shopper's fastest/preferred route
	std::multimap< double, std::string > inventorySequence;

	//helper function for checking if a file contains valid utf8 text
	//from these examples:
	//https://github.com/nemtrif/utfcpp
	//iterators are amazing!
	bool valid_utf8_file(std::ifstream *filePtr);
};

#endif //STORE_H