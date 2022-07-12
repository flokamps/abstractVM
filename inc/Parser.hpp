/*
** EPITECH PROJECT, 2022
** B-SYN-400-LYN-4-1-abstractVM-florian.kamps
** File description:
** Parser
*/

#pragma once

#include "IOperand.hpp"

#include <stdexcept>
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
        explicit Parser(char *file_path = nullptr);
        void parsefrmfile();
        void parse();
        void errorHandling(eOperandType t);
        bool is_number(const std::string& s);
        std::string trim(const std::string &s);
        std::string typehandling(std::string temptype);
        std::vector<std::tuple<std::string, eOperandType, std::string>> getInstructions();
        std::string removet(const std::string &s);
    private:
        char *_file_path;
        std::vector<std::tuple<std::string, eOperandType, std::string>> instructions;
        std::string command;
        eOperandType type;
        std::string value;
        std::map<std::string, eOperandType> _type {
            {"int8", Int8}, {"int16", Int16}, {"int32", Int32}, {"float", Float}, 
            {"double", Double}, {"bigdecimal", BigDecimal}, {"NONE", Null}, {"Error", Error}
        };
        std::vector<std::string> listt {
            "int8", "int16", "int32", "float", "double", "bigdecimal"
        };
};

class ParserException : public std::exception
{
    public:
        explicit ParserException(std::string msg) : _msg(std::move(msg)){}
        const char* what() const noexcept override {
            return _msg.c_str();
        }
    private:
        std::string _msg;
};