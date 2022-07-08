//
// Created by Florian Kamps on 08/07/2022.
//

#ifndef ABSTRACTVM_VIRTUALMACHINE_HPP
#define ABSTRACTVM_VIRTUALMACHINE_HPP

#include "Parser.hpp"
#include <list>
#include <map>
#include <utility>

class VirtualMachine;

typedef std::map<const std::string, void (VirtualMachine::*)(IOperand *)> Commands;

class VirtualMachine {
    public:
        VirtualMachine() = default;
        ~VirtualMachine() = default;
        void run(std::vector<std::tuple<std::string, eOperandType, std::string>> cmd);
        void runCommand(const std::string& command, IOperand *operand = nullptr);
    private:
        std::list<IOperand*> _stack;
        static Commands _commands;

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
        void exit(IOperand *operand = nullptr);
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

#endif //ABSTRACTVM_VIRTUALMACHINE_HPP