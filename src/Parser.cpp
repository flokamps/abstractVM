/*
** EPITECH PROJECT, 2022
** B-SYN-400-LYN-4-1-abstractVM-florian.kamps
** File description:
** Parse
*/

#include "../inc/Parser.hpp"
#include <algorithm>

Parser::Parser(char *file_path) {
    this->_file_path = file_path;
}

void Parser::parsefrmfile()
{
    std::ifstream asmFile(_file_path);
    std::string delimiter = " ";
    std::string line;

    if (asmFile.is_open() == false) {
        throw ParserException("Error: Impossible to open file");
    }
    while (asmFile && line != "exit") {
        eOperandType t;

        getline(asmFile, line);
        if (line.find(" ") != std::string::npos) {
            command = line.substr(0, line.find(delimiter));
            line.erase(0, line.find(delimiter) + delimiter.length());
            t = _type[line.substr(0, line.find("("))];
            line.erase(0, line.find("(") + delimiter.length());
            value = line.substr(0, line.find(delimiter));
            value.pop_back();
            instructions.push_back({command, t, value});
        }
        else if (!line.empty()) {
            command = line;
            instructions.push_back({command, _type["NONE"], ""});
        }
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
        }
        if (line.find(" ") != std::string::npos) {
            command = line.substr(0, line.find(delimiter));
            line.erase(0, line.find(delimiter) + delimiter.length());
            t = _type[line.substr(0, line.find("("))];
            line.erase(0, line.find("(") + delimiter.length());
            value = line.substr(0, line.find(delimiter));
            value.pop_back();
           // errorHandling(t);
            instructions.push_back({command, t, value});
        }
        else if (!line.empty()) {
            command = line;
          //  errorHandling(t);
            instructions.push_back({command, _type["NONE"], ""});
        }
    }
    while (line != ";;") {
        getline(std::cin, line);
    }
    for(auto& tuple: instructions) {
        std::cout << std::get<0>(tuple) << " " << std::get<1>(tuple) << " " << std::get<2>(tuple) << std::endl;   
    }
}

std::vector<std::tuple<std::string, eOperandType, std::string>> Parser::getInstructions() {
    return (instructions);
}

bool Parser::is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(), 
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

void Parser::errorHandling(eOperandType t)
{
    int check = 0;

    for (unsigned int i = 0; i < cmd.size(); i++) {
        if (command == cmd[i])
            check = 1;
    }
    if (check == 0) {
        for (unsigned int i = 0; i < cmdv.size(); i++) {
            if (command == cmdv[i])
                check = 2;
        }
    }
    switch (check) {
        case 0:
            throw ParserException("Error: bad command");
            break;
        case 1: {
            if (t == 0)
                throw ParserException("Error: bad type");
            if (value != "")
                throw ParserException("Error: bad value");
            break;
        } 
        case 2: {
            if (t == 0)
                throw ParserException("Error: bad type");
            if (!is_number(value))
                throw ParserException("Error: bad value");
            break;
        }
    }
}