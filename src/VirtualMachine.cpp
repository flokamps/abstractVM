//
// Created by Florian Kamps on 08/07/2022.
//

#include "../inc/VirtualMachine.hpp"
#include "../inc/Factory.hpp"
#include <algorithm>

void VirtualMachine::runCommand(const std::string& command, IOperand *operand)
{
   void (VirtualMachine::*func)(IOperand *) = _commands[command];
    return (this->*func)(operand);
}

Commands VirtualMachine::_commands = {
    {"push", &VirtualMachine::push},
    {"pop", &VirtualMachine::pop},
    {"dump", &VirtualMachine::dump},
    {"assert", &VirtualMachine::assertt},
    {"add", &VirtualMachine::add},
    {"sub", &VirtualMachine::sub},
    {"mul", &VirtualMachine::mul},
    {"div", &VirtualMachine::div},
    {"mod", &VirtualMachine::mod},
    {"print", &VirtualMachine::print},
    {"exit", &VirtualMachine::exit}
};

void VirtualMachine::run(std::vector<std::tuple<std::string, eOperandType, std::string>> cmd)
{
    for (auto &it : cmd)
    {
        if (_commands.count(std::get<0>(it)) == 0)
            throw VMException("Unknown command " + std::get<0>(it));
        std::get<1>(it) != eOperandType::Null ? runCommand(std::get<0>(it),
                Factory::createOperand(std::get<1>(it), std::get<2>(it))
                ) : runCommand(std::get<0>(it));
    }
}

void VirtualMachine::push(IOperand *operand)
{
    _stack.push_back(operand);
}

void VirtualMachine::pop(IOperand *operand)
{
    if (_stack.empty())
        throw VMException("Pop on empty stack");
    _stack.pop_back();
}

void VirtualMachine::dump(IOperand *operand)
{
    for (auto &it : _stack)
    {
        std::cout << it->toString() << std::endl;
    }
}

void VirtualMachine::assertt(IOperand *operand)
{
    if (_stack.empty())
        throw VMException("Assert on empty stack");
    if (*_stack.back() != *operand)
        throw VMException("Assert failed");
}

void VirtualMachine::add(IOperand *operand)
{
    if (_stack.size() < 2)
        throw VMException("Add on empty stack");
    IOperand *op1 = _stack.back();
    _stack.pop_back();
    IOperand *op2 = _stack.back();
    _stack.pop_back();
    _stack.push_back(*op1 + *op2);
}

void VirtualMachine::sub(IOperand *operand)
{
    if (_stack.size() < 2)
        throw VMException("Sub on empty stack");
    IOperand *op1 = _stack.back();
    _stack.pop_back();
    IOperand *op2 = _stack.back();
    _stack.pop_back();
    IOperand *res = *op2 - *op1;
    *res < 2 ? throw VMException("Subtraction result is < 2") : _stack.push_back(res);
}

void VirtualMachine::mul(IOperand *operand)
{

}

void VirtualMachine::div(IOperand *operand)
{

}

void VirtualMachine::mod(IOperand *operand)
{

}

void VirtualMachine::print(IOperand *operand)
{

}

void VirtualMachine::exit(IOperand *operand)
{

}
