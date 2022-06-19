#pragma once
#include <string>
class recordscompare
{
public:
	bool operator()(const std::string& s1, const std::string& s2);
};

