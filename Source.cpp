#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include "MyFile.h"
#include <fstream>
#include <ctime>
#include <chrono>
///Prints out the main menu
void menu() {
    std::cout << "1 - Search for passwords\n"
        << "2 - Sort passwords\n"
        << "3 - Add a password\n"
        << "4 - Edit a password\n"
        << "5 - Remove a password\n"
        << "6 - Add a category\n"
        << "7 - Remove a category\n"
        << "8 - See passwords\n"
        << "9 - See categories\n"
        << "10 - Save & exit\n";
}
/// Gets the right file
/// 
/// The function checks if a file, which the user inputted,
/// has been encrypted by the program and, therefore, it is the right file.
/// Unless the file is the one on which the program can operate,
/// the user will be recursively asked to enter the name of an appropriate file.
/// Each time the user makes 3 consecutive mistakes, the program will ask once again
/// if the user ever started the application earlier.
/// @param var count how many consecutive fails have happened
/// @param pass password which has been provided by the user to decrypt a file
/// <returns>The name of the file</returns> 
std::string fileGetter(int var, std::string pass) {
    if (var != 0 && var % 3 == 0) {
        char c;
        std::cout << "Is this the first start of the program?[y/n] ";
        std::cin >> c;
        if (c == 'n');
        else {
            std::cout << "Passwords.txt has been created\n";
            return "";
        }
    }
    for (auto const& dir_entry : std::filesystem::directory_iterator{ "." })
    {
        if (dir_entry.is_regular_file())
            std::cout << dir_entry << '\n';
    }
    std::string file;
    std::cout << "Choose a file: ";
    std::cin >> file;
    //https://en.cppreference.com/w/cpp/filesystem/absolute
    std::filesystem::path p = file;
    std::ifstream f(file.c_str());
    if (p.is_absolute()) {

        std::string sLine;
        getline(f, sLine);
        std::string tmp;
        if (pass.size() > sLine.size()) {
            bool rep = false;
            for (int i2 = 0, passInd = 0; passInd < pass.size(); ++i2) {

                char c;
                if (i2 == sLine.size()) {
                    i2 = 0;
                    rep = true;
                }

                if (sLine.at(i2) == '\n') continue;
                else {
                    if (rep) {
                        tmp[i2] = tmp[i2] - pass.at(passInd);
                    }
                    else {
                        c = (char)(sLine.at(i2) - pass.at(passInd));

                        tmp.push_back(c);
                    }
                    ++passInd;
                }



            }
            if (tmp == "Encrypted") {

                f.close();
                return file;
            }
        }
        else {
            for (int i2 = 0, passInd = 0; i2 < sLine.size(); ++i2) {

                char c;
                if (passInd >= pass.size()) passInd = 0;


                c = (char)(sLine.at(i2) - pass.at(passInd));
                ++passInd;

                tmp.push_back(c);
            }
        }

        if (tmp == "Encrypted") {

            f.close();
            return file;
        }
        std::cout << "Incorrect file\n";
        f.close();
        return fileGetter(++var, pass);
    }
    //https://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exists-using-standard-c-c11-14-17-c

    if (f.good())
        //
    {
        std::string sLine;
        getline(f, sLine);
        std::string tmp;
        if (pass.size() > sLine.size()) {
            bool rep = false;
            for (int i2 = 0, passInd = 0; passInd < pass.size(); ++i2) {

                char c;
                if (i2 == sLine.size()) {
                    i2 = 0;
                    rep = true;
                }

                if (sLine.at(i2) == '\n') continue;
                else {
                    if (rep) {
                        tmp[i2] = tmp[i2] - pass.at(passInd);
                    }
                    else {
                        c = (char)(sLine.at(i2) - pass.at(passInd));

                        tmp.push_back(c);
                    }
                    ++passInd;
                }



            }
            if (tmp == "Encrypted") {

                f.close();
                return file;
            }
        }
        else {
            for (int i2 = 0, passInd = 0; i2 < sLine.size(); ++i2) {

                char c;
                if (passInd >= pass.size()) passInd = 0;


                c = (char)(sLine.at(i2) - pass.at(passInd));
                ++passInd;

                tmp.push_back(c);
            }
            if (tmp == "Encrypted") {

                f.close();
                return file;
            }
        }


    }
    std::cout << "Incorrect file\n";
    f.close();
    return fileGetter(++var, pass);
}

int main() {

    std::cout << "Hello, you have opened Password Manager\n"
        << "The application will help you manage all your passwords\n"
        << "If this is your first start press 'y'. Otherwise, press 'n'\n"
        << "First start?[y/n] ";
    char val;
    std::cin >> val;
    MyFile m = MyFile();
    std::string pass;
    if (val != 'y' && val != 'n') {
        std::cout << "Incorrect value";
        return 0;
    }
    else if (val == 'y') {
        std::ofstream myFile("Passwords.txt");
        std::cout << "Set up a password. Password: ";
        std::cin >> pass;
        std::cout << "Password has been set\n";
        myFile.close();

    }
    else {
        std::cout << "Enter your password: ";
        std::cin >> pass;
        std::string fileV = fileGetter(0, pass);

        if (fileV == "") {
            std::cout << "Set a password. Password: ";
            std::cin >> pass;
            std::cout << "Password has been set\n";
            std::ofstream myFile("Passwords.txt");
            myFile.close();

        }
        else {

            std::ifstream file(fileV);

            if (file.is_open())
            {
                std::string line;
                int i = 0;

                while (getline(file, line)) {
                    if (i == 0) {

                        ++i;
                        continue;
                    }

                    std::string tmp;
                    for (int i2 = 0, passInd = 0; i2 < line.size(); ++i2) {
                        char c;
                        if (passInd >= pass.size()) passInd = 0;
                        c = (char)(line.at(i2) - pass.at(passInd));
                        tmp.push_back(c);
                        ++passInd;
                    }
                    if (tmp.starts_with("Categories")) break;
                    m.setText(tmp);
                }
                std::string subline, sub2line, res, tmp;
                std::istringstream istream;
                istream.str(m.getText());
                while (getline(istream, line)) {
                    if (line.starts_with("Categories")) break;
                    int found = line.find("Category: ");
                    subline = line.substr(found);
                    found = subline.find(" ");
                    sub2line = subline.substr(found);
                    for (int i = 1; sub2line.at(i) != ';'; ++i) {
                        res.push_back(sub2line.at(i));
                    }
                    m.addCategory(res);
                    res = "";
                }
                while (getline(file, line)) {
                    for (int i2 = 0, passInd = 0; i2 < line.size(); ++i2) {
                        char c;
                        if (passInd >= pass.size()) passInd = 0;
                        c = (char)(line.at(i2) - pass.at(passInd));
                        if (c == ';') {
                            m.addCategory(tmp);
                            tmp = "";
                        }
                        else {
                            tmp.push_back(c);
                        }
                        ++passInd;
                    }

                }
            }


            file.close();


        }

    }
    menu();
    int i;
    while (true) {
        std::cout << "Enter a digit: ";
        std::cin >> i;
        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Enter a valid character! ";
            while (!(std::cin >> i)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter a valid character! ";
            }
        }
        switch (i) {
        case 1: {
            m.searchPassword();
            break;
        }
        case 2: {
            std::list<std::string> records = m.sortPasswords();
            std::list<std::string>::iterator it;
            for (it = records.begin(); it != records.end(); ++it) {
                m.setText(*it);
            }
            std::cout << "Records have been sorted\n//\n";
            break;
        }
        case 3: {
            m.addPassword();
            break;
        }
        case 4: {
            m.editPassword();
            break;
        }
        case 5: {
            m.removePassword();
            break;
        }
        case 6: {
            std::string s;
            std::cout << "Enter the name of a category: ";
            std::cin >> s;
            m.addCategory(s);
            std::cout << "Category " << s << " has been added\n//\n";
            break;
        }
        case 7: {
            m.removeCategory();
            break;
        }
        case 8: {
            std::cout << m.getText() << "//\n";
            break;
        }
        case 9: {
            std::cout << "Categories\n";
            m.categories();
            break;
        }
        case 10: {
            m.save(m.getText(), pass);
            std::cout << "Data has been saved";
            return 0;
        }
        default: {
            std::cout << "Invalid input\n//\n";
        }

        }
        menu();
    }

}
