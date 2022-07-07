/*
** EPITECH PROJECT, 2022
** B-SYN-400-LYN-4-1-abstractVM-florian.kamps
** File description:
** Parser
*/

#include "IOperand.hpp"

#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <array>
#include <tuple>
#include <map>

class Parser {
    public:
        Parser(char *file_path = nullptr);
        void parsefrmfile();
        void parse();

    private:
        char *_file_path;
        std::vector<std::tuple<std::string, eOperandType, std::string>> cmd;
        std::string command;
        eOperandType type;
        std::string value;
        std::map<std::string, eOperandType> _type {
            {"int8", Int8}, {"int16", Int16}, {"int32", Int32}, {"Float", Float}, 
            {"double", Double}, {"BigDecimal", BigDecimal}, {"NONE", Null}
        };
};