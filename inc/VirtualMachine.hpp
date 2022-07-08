//
// Created by Florian Kamps on 08/07/2022.
//

#ifndef ABSTRACTVM_VIRTUALMACHINE_HPP
#define ABSTRACTVM_VIRTUALMACHINE_HPP

#include "Parser.hpp"
#include <list>
#include <map>

class VirtualMachine;

typedef std::map<const std::string, void (VirtualMachine::*)(void)> Commands;

class VirtualMachine {
    public:
        VirtualMachine(std::vector<std::tuple<std::string, eOperandType, std::string>> cmd);
        ~VirtualMachine() = default;
        void run();
        void runCommand(const std::string& command);
    private:
        std::list<IOperand*> _stack;
        static Commands _commands;

        void push(void);
        void pop(void);
        void dump(void);
        void assertt(void);
        void add(void);
        void sub(void);
        void mul(void);
        void div(void);
        void mod(void);
        void print(void);
        void exit(void);
};

#endif //ABSTRACTVM_VIRTUALMACHINE_HPP