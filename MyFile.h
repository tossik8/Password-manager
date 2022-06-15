#include <string>
#include <vector>
/// Stores passwords and categories
/// 
/// MyFile class is needed for storing information about the passwords and categories while a user is running the program
class MyFile {
	std::string text;
	std::vector<std::string> category;
public:
	MyFile();
	std::vector<std::string> getVector() const;
	void categories() const;
	void setText(std::string text);
	std::string getText() const;
	void addPassword();
	void addCategory(std::string cate);
	void removeCategory();
	void save(std::string file, std::string key);
	std::string chooseCat();
	void editPassword();
	void removePassword();
	void searchPassword();
	friend int num_of_char();
};

