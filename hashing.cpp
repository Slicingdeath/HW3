#include "hashing.hpp"
#include <string>
using namespace std;

template<typename Str>
std::string toString(Str k) {
	return to_string(k);
}


// convert a given string into its equivalent base-10 integer
// when treated as a base-256 ASCII number
int base256conversion(const string &s) {
    // TODO
	int sum = 0;
	int exp = 1;
	for (int i = s.length() - 1; i >= 0; i--)
	{
		sum += static_cast<int>(s[i]) * exp;
		exp *= 256;
	}
	return sum;
}

// hashes a string by dividing it into a number of substrings ("folds")
// each of which is foldSize-many characters long,
// then converting each fold into a base-256 integer,
// and finally combining everything together
int hashString(const string &s, int foldSize) {
    // TODO
	int sum = 0;
	for (unsigned i = 0; i < s.length(); i += foldSize)
	{
		if (s.length() - i < foldSize)
		{
			sum += base256conversion(s.substr(i, s.length() - i));
		}
		else
		{
			sum += base256conversion(s.substr(i, foldSize));
		}
	}
	return sum;
}
