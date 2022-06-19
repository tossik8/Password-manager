#pragma once
#include <string>
/// A string comparator
///
/// A string comparator is needed for sorting records in a file
class recordscompare
{
public:
	/// Sorts strings
	/// @param s1 is the first string which is to be compared
	/// @param s2 is the second string which is to be compared
	/// @return true - if they shouldn't be swapped, false otherwise
	bool operator()(const std::string& s1, const std::string& s2);
};

