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
    std::string temptype;

    if (asmFile.is_open() == false) {
        throw ParserException("Error: Impossible to open file");
    }
    while (asmFile && line != "exit") {
        eOperandType t;

        getline(asmFile, line);
        if (line.find(" ") != std::string::npos) {
            command = line.substr(0, line.find(delimiter));
            line.erase(0, line.find(delimiter) + delimiter.length());
            temptype = line.substr(0, line.find("("));
            temptype = typehandling(temptype);
            t = _type[temptype];
            line.erase(0, line.find("(") + delimiter.length());
            value = line.substr(0, line.find(delimiter));
            if (value.back() == '\r')
                value.pop_back();
            value.pop_back();
            instructions.push_back({command, t, value});
            value = ""; t = Null;
        }
        else if (!line.empty()) {
            command = line;
            if (command.back() == '\r')
                command.pop_back();
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
    std::string temptype;
    int exit = 0;

    while (line != ";;" && exit == 0) {
        getline(std::cin, line);
        if (line == "exit") {
            exit = 1;
        }
        if (line.find(" ") != std::string::npos) {
            command = line.substr(0, line.find(delimiter));
            line.erase(0, line.find(delimiter) + delimiter.length());
            temptype = line.substr(0, line.find("("));
            temptype = typehandling(temptype);
            t = _type[temptype];
            line.erase(0, line.find("(") + delimiter.length());
            value = line.substr(0, line.find(delimiter));
            value.pop_back();
            instructions.push_back({command, t, value});
            value = ""; t = Null;
        }
        else if (!line.empty()) {
            command = line;
            instructions.push_back({command, _type["NONE"], ""});
        }
    }
    while (line != ";;") {
        getline(std::cin, line);
    }
}

std::vector<std::tuple<std::string, eOperandType, std::string>> Parser::getInstructions() {
    return (instructions);
}

std::string Parser::typehandling(std::string temptype) {
    int check = 0;

    for (unsigned int i = 0; i < listt.size(); i++) {
        if (temptype == listt[i])
            check = 1;
    }
    if (check == 0)
        return ("Error");
    else
        return (temptype);
}