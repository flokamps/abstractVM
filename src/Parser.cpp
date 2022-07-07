/*
** EPITECH PROJECT, 2022
** B-SYN-400-LYN-4-1-abstractVM-florian.kamps
** File description:
** Parse
*/

#include "inc/Parser.hpp"

Parser::Parser(char *file_path) {
    this->_file_path = file_path;
}

void Parser::parsefrmfile() {
    std::ifstream asmFile(_file_path);
    asmFile.is_open();
    std::string line;
    while (std::getline(asmFile, line)) {
        if (line.find(" ")) {
            strtok(line.c_str(), " ");
        }
    }
}