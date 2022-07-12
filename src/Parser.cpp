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
    std::string tempvalue;
    std::string tempRegisterKey;
    eOperandType t;

    if (asmFile.is_open() == false)
        throw ParserException("Error: Impossible to open file");
    while (asmFile && line != "exit") {
        getline(asmFile, line);
        line = trim(line);
        line = removet(line);
        if (line.length() >= 2) {
            if (line.at(0) == ';' && line.at(1) == ';')
                continue;
            if (line.at(0) == ';' && line.at(1) != ';')
                continue;
        }
        if (line.find("\t") != std::string::npos)
            replace(line.begin(), line.end(), '\t' , ' ');
        if (line.find(" ") != std::string::npos) {
            command = line.substr(0, line.find(delimiter));
            line.erase(0, line.find(delimiter) + delimiter.length());
            temptype = line.substr(0, line.find("("));
            if (command == "load" || command == "store")
                tempRegisterKey = line.substr(0, line.find("("));
            temptype.erase(remove_if(temptype.begin(), temptype.end(), isspace), temptype.end());
            temptype = typehandling(temptype);
            t = _type[temptype];
            line.erase(0, line.find("(") + delimiter.length());
            tempvalue = line;
            tempvalue.erase(remove_if(tempvalue.begin(), tempvalue.end(), isspace), tempvalue.end());
            value = tempvalue;
            if (value.back() == '\r')
                value.pop_back();
            value.pop_back();
            if (command == "load" || command == "store")
                instructions.emplace_back(command, t, tempRegisterKey);
            else
                instructions.emplace_back(command, t, value);
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
    std::string tempvalue;
    std::string tempRegisterKey;
    int exit = 0;

    while (line != ";;" && exit == 0) {
        getline(std::cin, line);
        line = trim(line);
        line = removet(line);
        if (line.length() >= 2) {
            if (line.at(0) == ';' && line.at(1) == ';')
                continue;
            if (line.at(0) == ';' && line.at(1) != ';')
                continue;
        }
        if (line.find("\t") != std::string::npos)
            replace(line.begin(), line.end(), '\t' , ' ');
        if (line == "exit")
            exit = 1;
        if (line.find(" ") != std::string::npos) {
            command = line.substr(0, line.find(delimiter));
            line.erase(0, line.find(delimiter) + delimiter.length());
            temptype = line.substr(0, line.find("("));
            if (command == "load" || command == "store")
                tempRegisterKey = line.substr(0, line.find("("));
            temptype.erase(remove_if(temptype.begin(), temptype.end(), isspace), temptype.end());
            temptype = typehandling(temptype);
            t = _type[temptype];
            line.erase(0, line.find("(") + delimiter.length());
            tempvalue = line;
            tempvalue.erase(remove_if(tempvalue.begin(), tempvalue.end(), isspace), tempvalue.end());
            value = tempvalue;
            value.pop_back();
            if (command == "load" || command == "store")
                instructions.emplace_back(command, t, tempRegisterKey);
            else
                instructions.emplace_back(command, t, value);
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

std::string Parser::trim(const std::string &s)
{
    size_t start = s.find_first_not_of(" ");
    return (start == std::string::npos) ? "" : s.substr(start);
}

std::string Parser::removet(const std::string &s)
{
    size_t start = s.find_first_not_of("\t");
    return (start == std::string::npos) ? "" : s.substr(start);
}