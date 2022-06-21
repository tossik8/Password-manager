#include "recordscompare.h"
#include <algorithm>
bool recordscompare::operator()(const std::string& s1, const std::string& s2) const {
	int nameS = s1.find(": "), cateS = s1.find("Category: ");
	std::string help = s1.substr(cateS + 10);
	int cate = help.find(" ");
	std::string cpy1 = s1.substr(0, nameS), cpy2 = help.substr(0, cate - 1);
	int nameS2 = s2.find(": "), cateS2 = s2.find("Category: ");
	help = s2.substr(cateS2 + 10);
	int cate2 = help.find(" ");
	std::string cpy3 = s2.substr(0, nameS2), cpy4 = help.substr(0, cate2 - 1);
	//https://stackoverflow.com/questions/735204/convert-a-string-in-c-to-upper-case
	std::transform(cpy3.begin(), cpy3.end(), cpy3.begin(), ::toupper);
	std::transform(cpy4.begin(), cpy4.end(), cpy4.begin(), ::toupper);
	std::transform(cpy2.begin(), cpy2.end(), cpy2.begin(), ::toupper);
	std::transform(cpy1.begin(), cpy1.end(), cpy1.begin(), ::toupper);
	//
	if (cpy1 > cpy3 && cpy2 >= cpy4) {
		return false;
	}
	else if (cpy2 < cpy4 && cpy1 <= cpy3) return true;
	else if (cpy1 > cpy3 && cpy2 <= cpy4) return !true;
	else if (cpy1 == cpy3 && cpy2 == cpy4) return false;
	else return !false;
}
