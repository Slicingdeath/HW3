#include "USPS.hpp"
#include <iostream>
#include <ctime>
using namespace std;


USPS::USPS(bool b)
: verboseOn(b) {}
// Run the USPS simulation on the given Queue of orders,
// using the given Dictionary as the data structure in which to track the (address,#order) information.
// If this->verbose is true, cout a message for each order describing the action taken (accepted or rejected);
// otherwise, do not output anything.
void USPS::run(Queue<COVIDTestOrder> *orders, Dictionary<StreetAddress, int> *counts) {
    while (!orders->isEmpty()) {
        // Dequeue an order
        COVIDTestOrder order = orders->front();
        orders->dequeue();

        // Try to find the existing count for the address
        try {
            int existingCount = counts->find(order.sa);

            // Calculate the new total count if this order is accepted
            int newTotal = existingCount + order.num;

            // Check if the new total exceeds the limit of 4 kits
            if (newTotal <= 4)
            {
                // Accept the order and update the count in the dictionary
                counts->remove(order.sa);
                counts->insert(order.sa, newTotal);
                if (this->verboseOn == true)
                {
                	std::cout << "accepted: " << order.num << " kits to " << order.sa.toString() << " (" << newTotal << " total)" << std::endl;
                }
            }
            else
            {
            	if (this->verboseOn == true)
            	{
					// Reject the order
					std::cout << "REJECTED: " << order.num << " kits to " << order.sa.toString() << " (" << existingCount << " already)" << std::endl;
            	}
            }
        } catch (const std::string &error) {
            // If the address is not found, it means this is the first order for this address
            // Since there's no existing count, we can simply accept the order
            if (order.num <= 4) {
                counts->insert(order.sa, order.num);
                if (this->verboseOn == true)
                {
                	std::cout << "accepted: " << order.num << " kits to " << order.sa.toString() << " (" << order.num << " total)" << std::endl;
                }
            }
            else
            {
            	if (this->verboseOn == true)
            	{
            		std::cout << "REJECTED: " << order.num << " kits to " << order.sa.toString() << " (0 already)" << std::endl;
            	}
            }
        }
    }
}


// Run the simulation, as above, but return the number of milliseconds it takes to complete all the orders
int USPS::timedRun(Queue<COVIDTestOrder> *orders,
        Dictionary<StreetAddress, int> *counts) {
    clock_t start, end;

    start = clock(); // get the clock time before running the function
    run(orders, counts);
    end = clock(); // get the clock time after running the function

    // compute the difference and convert it to milliseconds
    int ms = (end - start) / (double) (CLOCKS_PER_SEC / 1000);
    return ms;
}
