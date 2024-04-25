#include <string>

// This file contains the string hashing methods

// convert a given string into its equivalent base-10 integer
// when treated as a base-256 ASCII number
int base256conversion(const std::string &s);

// hashes a string by dividing it into a number of substrings ("folds")
// each of which is foldSize-many characters long,
// then converting each fold into a base-256 integer,
// and finally combining everything together
int hashString(const std::string &s, int foldSize);

template<typename Str>
std::string toString(Str);
