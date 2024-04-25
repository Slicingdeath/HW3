#include "COVIDTestOrder.hpp"
#include <sstream>
using namespace std;

COVIDTestOrder::COVIDTestOrder(const std::string &csvLine) {
    string temp;

    stringstream ss(csvLine);
    getline(ss, temp, ',');
    sa.number = stoi(temp);
    getline(ss, sa.street, ',');
    getline(ss, sa.city, ',');
    getline(ss, temp, ',');
    sa.zip = stoi(temp);
    getline(ss, temp, ',');
    num = stoi(temp);
}
