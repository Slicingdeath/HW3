#pragma once

#include <string>

// A struct representing a (simplified) street address
struct StreetAddress {
    int number;
    std::string street;
    std::string city;
    int zip;

    bool operator==(const StreetAddress &sa) const {
        return this->number == sa.number && this->street == sa.street && this->city == sa.city && this->zip == sa.zip;
    }

    std::string toString() const {
        return std::to_string(number) + " " + street + ", " + city + " " + std::to_string(zip);
    }
};




