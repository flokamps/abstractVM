/*
** EPITECH PROJECT, 2022
** B-SYN-400-LYN-4-1-abstractVM-florian.kamps
** File description:
** Parse
*/

#include "../inc/Parser.hpp"

Parser::Parser(char *file_path) {
    this->_file_path = file_path;
}

void Parser::parsefrmfile()
{
    std::ifstream asmFile(_file_path);
    std::string delimiter = " ";
    std::string line;

    while (asmFile && line != "exit") {
        eOperandType t;

        getline(asmFile, line);
        if (line == "exit")
            continue;
        if (line.find(" ") != std::string::npos) {
            command = line.substr(0, line.find(delimiter));
            line.erase(0, line.find(delimiter) + delimiter.length());
            t = _type[line.substr(0, line.find("("))];
            line.erase(0, line.find("(") + delimiter.length());
            value = line.substr(0, line.find(delimiter));
            value.pop_back();
            cmd.push_back({command, t, value});
        }
        else if (!line.empty()) {
            command = line;
            cmd.push_back({command, _type["NONE"], ""});
        }
    }
    for(auto& tuple: cmd) {
        std::cout << std::get<0>(tuple) << " " << std::get<1>(tuple) << " " << std::get<2>(tuple) << std::endl;   
    }
    asmFile.close();
}

void Parser::parse()
{
    std::string line;
    std::string delimiter = " ";
    eOperandType t;
    int exit = 0;

    while (line != ";;" && exit == 0) {
        getline(std::cin, line);
        if (line == "exit") {
            exit = 1;
            continue;
        }
        if (line.find(" ") != std::string::npos) {
            command = line.substr(0, line.find(delimiter));
            line.erase(0, line.find(delimiter) + delimiter.length());
            t = _type[line.substr(0, line.find("("))];
            line.erase(0, line.find("(") + delimiter.length());
            value = line.substr(0, line.find(delimiter));
            value.pop_back();
            cmd.push_back({command, t, value});
        }
        else if (!line.empty() && line != "exit") {
            command = line;
            cmd.push_back({command, _type["NONE"], ""});
        }
    }
    while (line != ";;") {
        getline(std::cin, line);
    }
    for(auto& tuple: cmd) {
        std::cout << std::get<0>(tuple) << " " << std::get<1>(tuple) << " " << std::get<2>(tuple) << std::endl;   
    }
}
