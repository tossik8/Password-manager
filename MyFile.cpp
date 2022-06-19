#include "MyFile.h"
#include "recordscompare.h"
#include <string>
#include <vector>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <regex>
#include <sstream>
#include <list>
#include <iterator>

//! Constructs an object needed for manipulating data
MyFile::MyFile() : text(""), category({}) {}
/// <summary>
/// Returns the content of MyFile object
/// </summary>
/// <returns>All passwords</returns>
std::string MyFile::getText() const{
	return text;
}
/// <summary>
/// Returns a vector with all categories
/// </summary>
/// <returns>All categories</returns>
std::vector<std::string> MyFile::getVector() const{
	return category;
}
//! Updates the content of the class
//! @param text is the text which should be added to the existing records
void MyFile::setText(std::string text) {
	this->text = this->text.append(text).append("\n");
}
/// <summary>
/// Sorts passwords in ascending order by the name of a platform and its' category
/// </summary>
/// <returns>List of sorted passwords</returns>
std::list<std::string> MyFile::sortPasswords() {
	std::list<std::string> records;
	std::istringstream is;
	is.str(text);
	std::string line;
	while (getline(is, line)) {
		records.push_back(line);
	}
	recordscompare rcd;
	records.sort(rcd);
	text = "";
	return records;
}
//! Adds a new category to the existing ones
//! @param cate is a category which should be added to the existing ones
void MyFile::addCategory(std::string cate) {
	
	for (int i = 0; i < category.size(); ++i) {
		if (category.at(i) == cate) {
			return;
		}
	}
	category.push_back(cate);
}
/// <summary>
/// Invoked from addPassword method when a user is asked how many characters a random passwords should contain
/// </summary>
/// <returns>The number of symbols a password will comprise</returns>
/// @see MyFile::addPassword()
int num_of_char(){
	int num;
	std::cout << "Number of characters: ";
	//https://stackoverflow.com/questions/20709633/what-do-i-do-with-throw-to-handle-wrong-data-type-in-c
	while (!(std::cin >> num) || num <= 0)
	{
		std::cout << "Number of characters: ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}//
	return num;

}
//!Adds a new password to the currently existing ones
void MyFile::addPassword() {
	using std::string;
	string platform, pass,cate, log, url, res,ch;
	std::cout << "Name of the platform: ";
	std::cin >> platform;
	res.append(platform).append(": ");
	std::cout << "Would you like a randomly generated password?[y/n]: ";
		std::cin >> ch;
		if (ch == "y") {
			int num;
			string ULCase, spChar;
			num = num_of_char();
			std::cout << "Should it include both upper and lower case letters?[y/n]: ";
			std::cin >> ULCase;
			std::cout << "Should it include special characters?[y/n]: ";
			std::cin >> spChar;
			if (spChar == "y" && ULCase == "y") {
				srand(time(0));
				for (int i = 0; i < num; ++i) {
					char c = (char)(rand() % 93 + 33);
					pass.push_back(c);
				}
			}
			else if (spChar == "y" && ULCase != "y") {
				srand(time(0));
				for (int i = 0; i < num; ++i) {
					char c = (char)(rand() % 93 + 33);
					if (c >= 'a' && c <= 'z') {
						c = (char)c - 26;
					}
					pass.push_back(c);
				}
			}
			else if (spChar != "y" && ULCase == "y") {
				srand(time(0));
				for (int i = 0; i < num; ++i) {
					char c = (char)(rand() % 93 + 33);
					if (c < 'A') c = c + 32;
					else if (c > 'z') c = (char)c - 26;
					if (c > 'Z' && c < 'a') c = (char)c - 26;
					pass.push_back(c);
				}
			}
			else {
				//https://www.geeksforgeeks.org/rand-and-srand-in-ccpp/
				srand(time(0));
				for (int i = 0; i < num; ++i) {
					char c = (char)(rand() % 26 + 65);

					pass.push_back(c);
				}
			}
		
		}
		else {
			std::cout << "Password: ";
			std::cin >> pass;
		}
		
	res.append(pass).append("; ");
	std::cout << "The password for " << platform<< " is " << pass << "\n";
	if (category.empty()) {
		std::cout << "You don't have any categories yet\n"
			<< "Name of a new category: ";
		std::cin >> cate;
		category.push_back(cate);

	}
	else {
		string answ;
		std::cout << "Would you like to create a new category?[y/n]: ";
		std::cin >> answ;
		if ("y" == answ) {
			std::cout<<"Name of a new category: ";
			std::cin >> cate;
		}
		else {
			cate = chooseCat();
		}
	}
	addCategory(cate);
	res.append("Category: ").append(cate).append("; ");
	std::cout << "Login(optional - 0 to skip): ";
	std::cin >> log;
	if (log != "0") {
		res.append("Login: ").append(log).append("; ");
	}
	std::cout << "URL(optional - 0 to skip): ";
	std::cin >> url;
	if (url != "0") {
		res.append("URL: ").append(url).append(";");
	}
	
	setText(res);
	std::cout << "Password has been added\n//\n";
}

/// Saves data
/// 
/// Overrides the currently existing file with new data.
/// Categories inside the vecor are encrypted and written to the file as well.
/// @param text text which must be saved
/// @param key is the key which is going to be used for encryption
void MyFile::save(std::string text, std::string key) const {
	//https://www.delftstack.com/howto/cpp/how-to-append-text-to-a-file-in-cpp/
	std::ofstream myFile;
	myFile.open("Passwords.txt");
	
	//
	const std::string key2 = "Encrypted\n";
	std::string res;
	if (key2.size() < key.size()) {
		bool rep = false;
		for (int i = 0, keyInd = 0; keyInd < key.size(); ++i) {
			if (i == key2.size()) {
				i = 0;
				rep = true;
			}
			if (key2.at(i) == '\n') continue;
			else {
				if (rep) {
					
					res[i] = res[i] + key.at(keyInd);
				
				}
				else {
					res.push_back(key.at(keyInd) + key2.at(i));
				
				}
				++keyInd;
			}
		}
		
		res.push_back('\n');
		myFile << res;
	}
	else {
		for (int i = 0, keyInd = 0; i < key2.size(); ++i) {

			if (key.size() <= keyInd) keyInd = 0;
			if (key2.at(i) == '\n') myFile << '\n';
			else {
				myFile << (char)(key.at(keyInd) + key2.at(i));
				++keyInd;
			}
		}
	}
	
	for (int i = 0, keyInd = 0; i < text.size(); ++i) {
		if (key.size() <= keyInd) keyInd = 0;
		if (text.at(i) == '\n') {
			myFile << '\n';
			keyInd = 0;
		}
		else {
			myFile << (char)(text.at(i) + key.at(keyInd));
			++keyInd;
		}
	}
	
	const std::string s = "Categories\n";
	for (int i = 0, keyInd = 0; i < s.size(); ++i) {
		if (key.size() <= keyInd) keyInd = 0;
		if (s.at(i) == '\n') {
			myFile << '\n';
			keyInd = 0;
		}
		else {
			myFile << (char)(s.at(i) + key.at(keyInd));
			++keyInd;
		}
	}
	for (int j = 0; j < category.size(); ++j) {
		for (int i = 0, keyInd = 0; i < category.at(j).size() + 1; ++i) {
			if (key.size() <= keyInd) keyInd = 0;
			if (i == category.at(j).size()) myFile << (char)(';' + key.at(keyInd));
			else myFile << (char)(category.at(j).at(i) + key.at(keyInd));
			++keyInd;
		}
		myFile << '\n';
	}
}
/// <summary>
/// Invoked from addPassword method when the user is asked to which category the record should be assigned to
/// </summary>
/// <returns>A category that has been chosen</returns>
/// @see addPassword()
std::string MyFile::chooseCat() const {
	std::cout << "Choose a category\n";
	int c;
	categories();
	std::cin >> c;
	if (c <= 0 || c > category.size() || !std::cin) {
		std::cout << "Wrong value\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return chooseCat();
	}	
	return category.at(c - 1);
	}
	
///Removes a category from the vector with categories
///As well as removes all records associated with that category
void MyFile::removeCategory() {
	int i;
	std::cout << "REMEMBER that removing a category means deleting all the records which fall into that category!!!\n"
			  <<"Choose a category to remove: \n";
	categories();
	std::cin >> i;
	if (std::cin) {
		if (i <= 0) {
			std::cout << "Wrong input\n";
			return removeCategory();
		}
		else if (i > category.size()) {
			std::cout << "Wrong input\n";
			return removeCategory();
		}
	}
	else {
		std::cout << "Wrong input\n";
		return removeCategory();
	}
	std::string cat = category.at(i - 1);
	std::istringstream istream;
	istream.str(getText());
	std::string line;
	text = "";
	while (getline(istream, line)) {
		if (line.find(cat) != std::string::npos) {
			continue;
		}
		setText(line);
	}
	std::cout << category.at(i-1) << " has been removed as well as all the records associated with it\n//\n";
	category.erase(category.begin() + i -1);
	
}
//!Searches for passwords according to the name of the platform that a user provides
void MyFile::searchPassword() const{
	std::string name;
	std::cout << "Enter the name of a platform: ";
	std::cin >> name;
	//https://www.codeproject.com/Articles/811387/Cplusplus-New-Text-Streams
	std::istringstream istream;
	istream.str(getText());
	std::string line;
	bool found = false;
	while (getline(istream, line))/**/ {
		//https://www.techiedelight.com/check-if-a-string-contains-another-string-in-cpp/#:~:text=Using%20basic_string%3A%3Acontains,specif
		//ied%20substring%2C%20and%20false%20otherwise.&text=That's%20all%20about%20checking%20if,another%20string%20in%20C%2B%2B.
		if (line.find(name) != std::string::npos) {
			found = true;
			std::cout << line << '\n';
			
		}
	}
	if (!found) std::cout << "No such password\n//\n";
	else std::cout << "//\n";
}
/// Removes passwords from a file.
///The user is asked to confirm the changes
void MyFile::removePassword() {
	std::string modified = text;
	while (true) {
		int num = 0,i=0;
		std::istringstream istream;
		std::string line;
		istream.str(modified);
		while (getline(istream,line)) {
			std::cout << ++num << " - " << line << "\n";
		}
		std::cout << "Choose a record to remove(0 to quit): ";
		std::cin >> i;
		if (std::cin) {
			if (i == 0) break;
			else if (i < 0) {
				std::cout << "Wrong input\n";
				continue;
			}
			else if (i > num) {
				std::cout << "Wrong input\n";
				continue;
			}
		}
		else {
			std::cout << "Wrong input\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		num = 1;
		istream.clear();
		istream.str(modified);
		modified = "";
		while (getline(istream, line)) {
			if (num == i) {
				++num;
				continue;
			}
			++num;
			modified.append(line);
		}
		std::cout << "After removal\n";
		std::cout << modified << '\n';
		std::cin.clear();
			

	}
	std::string conf;
	std::cout << "Are you sure you want to commit changes?[y/n] ";
	std::cin >> conf;
	if (conf == "y") { 
		std::cout << "Changes have been saved\n//\n";
		text = "";
		if (modified == "");
		else {
			setText(modified);
		}

	}
	
	else{
		std::cout << "Nothing has been changed\n//\n";
	}
	
}
/// Edits the user's passwords one at a time
void MyFile::editPassword() {
	std::cout << "Choose a password which you want to update\n";
	int num = 0, i;
	std::istringstream istream;
	std::string line, pass;
	istream.str(text);
	while (getline(istream, line)) {
		std::cout << ++num << " - " << line << "\n";
	}
		std::cin >> i;
		
		if ((i <= 0 || i > num) || std::cin.fail()) {
			std::cout << "Wrong input. Enter a new number\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin >> i;
			while (!(i > 0 && i <= num)) {
				std::cout << "Wrong input. Enter a new number\n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
				std::cin >> i;
			}
		}
	num = 1;
	istream.clear();
	istream.str(text);
	text = "";
	while (getline(istream, line)) {
		if (num != i) {
			setText(line);
			++num;
			continue;
		}
		std::cout << "Enter your new password: ";
		std::cin >> pass;
		int found = line.find(": "), found2 = line.find("; Category");
		std::string cpy = line.substr(found2),cpy2 = line.substr(0,found+2);
		cpy2.append(pass).append(cpy);
		setText(cpy2);
		++num;
		
	}
	std::cout << "Password has been modified\n//\n";

}

//! Lists all categories
void MyFile::categories() const {
	if (category.size() == 0) {
		std::cout << "There are no categories\n//\n";
		return;
	}
	for (int i = 0; i < category.size(); ++i) {
		std::cout << i+1 << " - " << category.at(i) << "\n";
	}
	std::cout << "//\n";
}
