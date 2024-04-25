#pragma once

#include "StreetAddress.hpp"
#include "COVIDTestOrder.hpp"
#include "Queue.hpp"
#include "Dictionary.hpp"

class USPS {
private:
    // TODO you can add private variables or auxiliary methods if you think they will be helpful
	bool verboseOn;

public:
    // TODO add a constructor, if you need to initialize variables
	USPS(bool = false);

    // Run the USPS simulation on the given Queue of orders,
    // using the given Dictionary as the data structure in which to track the (address,#order) information
    void run(Queue<COVIDTestOrder> *orders, Dictionary<StreetAddress, int> *counts);

    // Run the simulation, as above, but return the number of milliseconds it takes to complete all the orders
    int timedRun(Queue<COVIDTestOrder> *orders, Dictionary<StreetAddress, int> *counts);
};
