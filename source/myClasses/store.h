#include <map>
#include <string>
#include <vector>

class Store
{
public:
	//reads the file vector and adds contents to the store's inventorySequence
	//const because I'm reading the fileVector, not modifying it
	//cascadable
	Store &addtoInventorySequence(const std::vector<std::string> &fileVector );

	void saveInventorySequence(std::string storeName, std::string path);


private:
	//takes doubles as the key values and string as the value type
	//This datamember represents a sequence of known items in the store along 
	//the human shopper's fastest/preferred route
	std::multimap< double, std::string > inventorySequence;
};