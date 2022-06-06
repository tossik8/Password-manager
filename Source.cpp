#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include "MyFile.h"
#include <fstream>
void menu() {
    std::cout << "1 - Search for passwords\n"
        << "2 - Sort passwords\n"
        << "3 - Add a password\n"
        << "4 - Edit a password\n"
        << "5 - Remove a password\n"
        << "6 - Add a category\n"
        << "7 - Remove a category\n";
}
std::string fileGetter(int var, std::string pass) {
    if (var != 0 && var % 3 == 0) {
        char c;
        std::cout << "Is this the first start of the program?[y/n] ";
        std::cin >> c;
        if (c == 'n');
        else {
            std::cout << "Passwords.txt has been created";
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
            
            for (int i2 = 0, passInd = 0; i2 < sLine.size(); ++i2) {
                
                char c;
                if (passInd >= pass.size()) passInd = 0;
                
               
                    c = (char)(sLine.at(i2) - pass.at(passInd));
                    ++passInd;
                
                tmp.push_back(c);
            }
            
            if (tmp== "Encrypted") {
                
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
            for (int i2 = 0, passInd = 0; i2 < sLine.size(); ++i2) {
                if (passInd >= pass.size()) passInd = 0;

                char c = (char)(sLine.at(i2) - pass.at(passInd));
                ++passInd;
                tmp.push_back(c);
            }
            if (tmp == "Encrypted") {
               
                f.close();
                return file;
            }

    }
    std::cout << "Incorrect file\n";
    f.close();
    return fileGetter(++var,pass);
}
int main() {

    std::cout << "Hello, you have opened Password Manager\n"
        << "The application will help you manage all your passwords\n"
        << "If this is your first start press 'y'. Otherwise, press 'n'\n"
        << "First start?[y/n] ";
    char val;
    std::cin >> val;
    MyFile m = MyFile();
    if (val != 'y' && val != 'n') {
        std::cout << "Incorrect value";
        return 0;
    }
    else if(val == 'y'){
        std::ofstream myFile("Passwords.txt");
        std::string pass;
        std::cout << "Set a password. Password: ";
        std::cin >> pass;
        std::cout << "Password has been set\n";
        myFile.close();
        
        m.addPassword();
        std::cout << m.getText();
        m.save(m.getText(), pass);
        std::cout << m.getText();
    }
    else {
        std::string pass;
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
                        m.setText(tmp);
                    }
                    
                    
                }
                
            //std::cout << m.getText();
           
            file.close();
            m.editPassword();
            std::cout << m.getText();
            //m.save(m.getText(), pass);
        }
        
    }
}
