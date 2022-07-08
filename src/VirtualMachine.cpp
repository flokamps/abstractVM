//
// Created by Florian Kamps on 08/07/2022.
//

#include "../inc/VirtualMachine.hpp"


VirtualMachine::VirtualMachine(std::vector<std::tuple<std::string, eOperandType, std::string>> cmd)
{
}

void VirtualMachine::runCommand(const std::string& command)
{
   void (VirtualMachine::*func)(void) = _commands[command];
    return (this->*func)();
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

void VirtualMachine::run()
{

}