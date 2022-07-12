//
// Created by Florian Kamps on 08/07/2022.
//

#ifndef ABSTRACTVM_VIRTUALMACHINE_HPP
#define ABSTRACTVM_VIRTUALMACHINE_HPP

#include "Parser.hpp"
#include <list>
#include <map>
#include <utility>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <limits>

class VirtualMachine;

typedef std::map<const std::string, void (VirtualMachine::*)(IOperand *)> Commands;

class VirtualMachine {
    public:
        VirtualMachine() = default;
        ~VirtualMachine() = default;
        void run(std::vector<std::tuple<std::string, eOperandType, std::string>> cmd);
        void runCommand(const std::string& command, IOperand *operand = nullptr);
        static void removeTrailing0(std::stringstream &ss);
    private:
        std::list<IOperand*> _stack;
        std::map<std::string,IOperand*> _register;
        static Commands _commands;

        void pushInRegister(IOperand *operand, IOperand *index);
        IOperand *getFromRegister(IOperand *);
        void push(IOperand *operand = nullptr);
        void pop(IOperand *operand = nullptr);
        void dump(IOperand *operand = nullptr);
        void assertt(IOperand *operand = nullptr);
        void add(IOperand *operand = nullptr);
        void sub(IOperand *operand = nullptr);
        void mul(IOperand *operand = nullptr);
        void div(IOperand *operand = nullptr);
        void mod(IOperand *operand = nullptr);
        void print(IOperand *operand = nullptr);
        void dup(IOperand *operand = nullptr);
        void clear(IOperand *operand = nullptr);
        void swap(IOperand *operand = nullptr);
        void exitt(IOperand *operand = nullptr);
        void load(IOperand *operand = nullptr);
        void store(IOperand *operand = nullptr);
};

class VMException : public std::exception {
    public:
        explicit VMException(std::string msg) : _msg(std::move(msg)) {}
        const char *what() const noexcept override {
            return _msg.c_str();
        }
    private:
        std::string _msg;
};

int main(int ac, char **av);

#endif //ABSTRACTVM_VIRTUALMACHINE_HPP