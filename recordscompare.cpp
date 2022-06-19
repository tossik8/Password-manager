#include "recordscompare.h"
bool recordscompare::operator()(const std::string& s1, const std::string& s2) {
	int nameS = s1.find(": "), cateS = s1.find("Category: ");
	std::string help = s1.substr(cateS + 10);
	int cate = help.find(" ");
	std::string cpy1 = s1.substr(0,nameS), cpy2 = help.substr(0,cate-1);
	int nameS2 = s2.find(": "), cateS2 = s2.find("Category: ");
	help = s2.substr(cateS2 + 10);
	int cate2 = help.find(" ");
	std::string cpy3 = s2.substr(0, nameS2), cpy4 = help.substr(0, cate2 - 1);
	if (cpy1 > cpy3 && cpy2 >= cpy4) {
		return false;
	}
	else if (cpy2 < cpy4 && cpy1 <= cpy3) return true;
	else if (cpy1 > cpy3 && cpy2 <= cpy4) return !true;
	else if (cpy1 == cpy3 && cpy2 == cpy4) return false;
	else return !false;
}
