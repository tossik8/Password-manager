#include <string>
#include <vector>
class MyFile {
	std::string text;
	std::vector<std::string> category;
public:
	MyFile();
	void categories();
	void setText(std::string text);
	std::string getText();
	void addPassword();
	void addCategory(std::string cate);
	void removeCategory();
	void save(std::string file,std::string key);
	std::string chooseCat();
	void editPassword();
	void removePassword();
	void searchPassword();
};
int num_of_char();
