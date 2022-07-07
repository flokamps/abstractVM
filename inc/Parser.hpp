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

class Parser {
    public:
        Parser(char *file_path = nullptr);
        void parsefrmfile();
        void parse();

    private:
        char *_file_path;
        std::vector<std::tuple<std::string, IOperand::eOperandType, std::string>> cmd;
}