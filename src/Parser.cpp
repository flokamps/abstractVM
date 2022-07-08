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
            cmd.push_back({command, t, value});
        }
        else if (!line.empty()) {
            command = line;
            cmd.push_back({command, _type["NONE"], ""});
        }
    }
    while (line != ";;") {
        getline(std::cin, line);
    }
}

std::vector<std::tuple<std::string, eOperandType, std::string>> Parser::getInstructions() {
    return (cmd);
}