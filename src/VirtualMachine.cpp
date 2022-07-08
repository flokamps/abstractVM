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
        if (_commands.count(std::get<0>(it)) == 0) {
            throw std::runtime_error("Unknown command");
        }
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

}

void VirtualMachine::add(IOperand *operand)
{

}

void VirtualMachine::sub(IOperand *operand)
{

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
