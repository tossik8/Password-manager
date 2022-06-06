#include "MyFile.h"
#include <string>
#include <vector>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <regex>

MyFile::MyFile() : text(""), category({}) {}
std::string MyFile::getText() {
	return text;
}
void MyFile::setText(std::string text) {
	this->text = this->text.append(text).append("\n");
}
void MyFile::addCategory(std::string cate) {
	
	for (int i = 0; i < category.size(); ++i) {
		if (category.at(i) == cate) {
			std::cout << cate << " already exists\n";
			return;
		}
	}
	category.push_back(cate);
	std::cout << cate << " has been added\n";
}

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
}
int num_of_char() {
	int num;
	std::cout << "Number of characters: ";
	//https://stackoverflow.com/questions/20709633/what-do-i-do-with-throw-to-handle-wrong-data-type-in-c
	while (!(std::cin >> num))
	{
		std::cout << "Number of characters: " << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}//
	return num;

}
void MyFile::save(std::string text, std::string key) {
	//https://www.delftstack.com/howto/cpp/how-to-append-text-to-a-file-in-cpp/
	std::ofstream myFile;
	
	myFile.open("Passwords.txt");
	
	//
	const std::string key2 = "Encrypted\n";

	for (int i = 0, keyInd = 0; i < key2.size(); ++i) {
		
		if (key.size() <= keyInd) keyInd = 0;
		if (key2.at(i) == '\n') myFile << '\n';
		else {
			myFile << (char)(key.at(keyInd) + key2.at(i));
			++keyInd;
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
}
std::string MyFile::chooseCat() {
	std::cout << "Choose a category\n";
	int c;
	categories();
	try {
		std::cin >> c;
		if (c <= 0) {
			std::cout << "Wrong value\n";
			return chooseCat();
		}
		else if (c >= category.size()) {
			std::cout << "Wrong value\n";
			return chooseCat();
		}
		return category.at(c - 1);
	}
	catch (std::exception e) {
		std::cout << "Wrong symbol\n";
		return chooseCat();
	}
}
void MyFile::searchPassword() {

}
void MyFile::removePassword() {
	int line = 1;
	for (int i = 0; i < this->text.size() - 1; ++i) {
		if (line == 1) {
			std::cout << line << " - ";
			++line;
		}
		if (text.at(i) == '\n') {
			std::cout << '\n' << line << " - ";
			++line;
		}
		else {
			std::cout << text.at(i);
		}
	}
	int res;
	std::cout << "\nChoose a line which you want to remove: ";
	std::cin >> res;
}
void MyFile::editPassword() {
	int line = 1;
	for (int i = 0; i < this->text.size() - 1; ++i) {
		if (line == 1) {
			std::cout << line << " - ";
			++line;
		}
		if (text.at(i) == '\n') {
			std::cout << '\n' << line << " - ";
			++line;
		}
		else {
			std::cout << text.at(i);
		}
	}
	int res;
	std::cout << "\nChoose a line where you want to modify a password: ";
	std::cin >> res;
	if (res <= 0) {
		std::cout << "Wrong value\n";
		return editPassword();
	}
	else if (res > line) {
		std::cout << "Wrong value\n";
		return editPassword();
	}
	std::string pass, str;
	for (int i = 0, lineIn = 1; true; ++i) {
		if (text.at(i) == '\n') {
			++lineIn;
			continue;
		}
		if (lineIn == res) {
			for (int j = i; text.at(j) != '\n'; ++j) {
				str.push_back(text.at(j));
			}
			break;
		}
	}
		str.push_back('\n');

		std::regex myReg("\\b.+\\b");

		std::cout << "Enter new password: ";
		std::cin >> pass;
		std::string s = std::regex_replace(str, myReg, pass);
		std::cout << s;
	
}
void MyFile::categories() {
	for (int i = 0; i < category.size(); ++i) {
		std::cout << i++ << " - " << category.at(i) << "\n";
	}
}