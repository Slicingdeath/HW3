#include <iostream>
#include <fstream>
#include <string>
#include "HashTableOpen.hpp"
#include "ArrayListDictionary.hpp"
#include "LinkedQueue.hpp"
#include "COVIDTestOrder.hpp"
#include "USPS.hpp"

// options for dictionary implementations
enum class DictionaryOpt
{
	ARRLIST,
	OPENHT
};

// Define your own Key and Val types
using KeyType = int;
using ValueType = std::string;

// Define a subclass of HashTableOpen with a specific Key type
//class MyHashTable : public HashTableOpen<KeyType, ValueType> {
//public:
//    MyHashTable(int size) : HashTableOpen(size) {}
//
//    // Override hashImpl for the specific key type
//    virtual int hashImpl(const KeyType &k) const override {
//        // Implement your own hashing function here
//        // For example, you can use a simple modulo operation
//        return k % M;
//    }
//};

// function prototypes
void testHashTable();
void getFileData(LinkedQueue<COVIDTestOrder>*, int);
void testUSPS_Sim();
void runMainProgram();
void getUserInput(int&, int&, char&, bool&, DictionaryOpt&);

int main() {
    int userOpt = 0;

    std::cout << "===== Menu =====" << std::endl;
    std::cout << "1 - Test HashTable" << std::endl;
    std::cout << "2 - Test USPS Simulator" << std::endl;
    std::cout << "3 - Run Main Program" << std::endl;
    std::cout << "Enter choice: " << std::endl;
    std::cin >> userOpt;

    // input validation
    while (userOpt < 0 || userOpt > 3)
    {
    	std::cout << "Invalid input. \nEnter choice: ";
    	std::cin >> userOpt;
    }
    switch (userOpt)
    {
		case 1:
			testHashTable();
			break;
		case 2:
			testUSPS_Sim();
			break;
		case 3:
			runMainProgram();
			break;
    }
    return 0;
}

// function definitions
void testHashTable()
{
	std::cout << "=== TESTING HASH TABLE ===\n";
	// Create an instance of your hash table
	HashTableOpen<int, std::string> table(100);

	// Test insert and find operations
	try {
		table.insert(5, "Value1");
		table.insert(105, "Value2");
		std::cout << "Value for key 5: " << table.find(5) << std::endl;
		std::cout << "Value for key 105: " << table.find(105) << std::endl;
	} catch (const std::string &error) {
		std::cerr << "Error: " << error << std::endl;
	}

	// Test remove operation
	try {
		table.remove(5);
		std::cout << "Value for key 5 after removal: " << table.find(5) << std::endl; // This should throw an error
	} catch (const std::string &error) {
		std::cerr << "Error: " << error << std::endl;
	}
}

// reads in order data from excel sheet
void getFileData(LinkedQueue<COVIDTestOrder> *orderQueue, int num)
{
	std::string csvString;
	std::ifstream orderList("homework-3-kate-and-jai-hw3/data/orders100k.csv");

	int linesToRead = num, // lines to read from the file
		totalLines = 0; // lines read so far
	// read specified number of lines from file while there are strings available
	while (totalLines < linesToRead && !orderList.eof())
	{
		getline(orderList, csvString);
		// pass string to overloaded COVIDTestOrder constructor
		COVIDTestOrder incomingOrder(csvString);
		// place order into queue
		orderQueue->enqueue(incomingOrder);
		// increment counter
		totalLines++;
	}
	// close the file
	orderList.close();
}

void testUSPS_Sim()
{
	std::cout << "=== TESTING USPS SIM ===\n";
	// read data from file
	LinkedQueue<COVIDTestOrder> orderQueue;
	int linesToRead = 10; // number of lines to read from the file
	getFileData(&orderQueue, linesToRead);
	int dictionarySize = linesToRead*2;
	USPS ordersToDeliver(true);

	std::cout << "Testing ArrayList Implementation:\n";
	ArrayListDictionary<StreetAddress, int> arrList_Addresses(dictionarySize);
	ordersToDeliver.run(&orderQueue, &arrList_Addresses);

	std::cout << "Testing Open HashTable Implementation:\n";
	HashTableOpen<StreetAddress, int> HTOpen_Addresses(dictionarySize);
	ordersToDeliver.run(&orderQueue, &HTOpen_Addresses);

}

void runMainProgram()
{
	// PART 3: THE MAIN PROGRAM
	LinkedQueue<COVIDTestOrder> orderQueue;
	std::string csvString;
	std::ifstream orderList("orders100k.csv");
	int linesToRead = 0, // lines to read from the file
		userNumOpt = 0;
	char userOpt; // user option for verbose mode
	bool verboseOpt = false; // flag for whether or not to cout actions taken on each order
	// verbose option not yet implementated in the USPS sim
	DictionaryOpt userDictionOpt;

	// GET USER INPUT
	getUserInput(linesToRead, userNumOpt, userOpt, verboseOpt, userDictionOpt);
	std::cin.ignore(); // prevents cin/getline conflict

	// READ IN DATA
	getFileData(&orderQueue, linesToRead);

	// RUNNING USPS SIM ON QUEUE
	int time = 0;
	int dictionarySize = linesToRead*2;
	USPS ordersToDeliver(verboseOpt);
	// make & use appropriate dictionary
	if (userDictionOpt == DictionaryOpt::ARRLIST)
	{
		ArrayListDictionary<StreetAddress, int> arrList_Addresses(dictionarySize);
		// pass queue and dictionary into usps sim timed run
		time = ordersToDeliver.timedRun(&orderQueue, &arrList_Addresses);
	}
	else // userDictionOpt == DictionaryOpt::OPENHT
	{
//		HashTableOpen<StreetAddress, int> HTOpen_Addresses(dictionarySize);
		// pass queue and dictionary into usps sim timed run
//		time = ordersToDeliver.timedRun(&orderQueue, &HTOpen_Addresses);
	}
}

void getUserInput(int& linesToRead, int& userNumOpt, char& userOpt, bool& verboseOpt, DictionaryOpt& userDictionOpt)
{
	std::cout << "Specify number of orders to process: ";
	std::cin >> linesToRead;
	while (linesToRead < 0 || linesToRead > 999999)
	{
		std::cout << "Invalid value. \nSpecify number of orders to process: ";
		std::cin >> linesToRead;
	}

	std::cout << "Choose dictionary implementation: "
				 "\n1 - Array List"
				 "\n2 - Open Hashing"
				 "\nEnter choice: ";
	std::cin >> userNumOpt;
	while (userNumOpt != 1 && userNumOpt != 2)
	{
		std::cout << "Invalid option. \nEnter choice: ";
		std::cin >> userNumOpt;
	}
	if (userNumOpt == 1)
	{
		userDictionOpt = DictionaryOpt::ARRLIST;
	}
	else
	{
		userDictionOpt = DictionaryOpt::OPENHT;
	}
	std::cout << "Use verbose mode? (y/n): ";
	std::cin >> userOpt;
	while (tolower(userOpt) != 'y' && tolower(userOpt) != 'n')
	{
		std::cout << "Invalid option. \nUse verbose mode? (y/n): ";
		std::cin >> userOpt;
	}
	if (tolower(userOpt) == 'y')
	{
		verboseOpt = true;
	}
}

