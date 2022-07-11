//
// Created by Florian Kamps on 08/07/2022.
//

#include "../inc/VirtualMachine.hpp"
#include "../inc/Factory.hpp"


VirtualMachine::VirtualMachine()
{
    for (int i = 0; i < 16; i++)
        _register.push_back(nullptr);
}

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
    {"dup", &VirtualMachine::dup},
    {"clear", &VirtualMachine::clear},
    {"swap", &VirtualMachine::swap},
    {"exit", &VirtualMachine::exitt}
};

RegisterCommands VirtualMachine::_registerCommands = {
        {"load", &VirtualMachine::load},
        {"store", &VirtualMachine::store}
};

void VirtualMachine::handleRegisterCommand(const std::string &command, const std::string &value)
{
    void (VirtualMachine::*func)(const std::string &value) = _registerCommands[command];
    return (this->*func)(value);
}

void VirtualMachine::run(std::vector<std::tuple<std::string, eOperandType, std::string>> cmd)
{
    for (auto &it : cmd)
    {
        if (_commands.count(std::get<0>(it)) == 0 && _registerCommands.count(std::get<0>(it)) == 0)
            throw VMException("Unknown command " + std::get<0>(it));
        if (std::get<0>(it) == "exit")
            break;
        if (std::get<0>(it) == "load" || std::get<0>(it) == "store") {
            handleRegisterCommand(std::get<0>(it), std::get<2>(it));
            continue;
        }
        std::get<1>(it) != eOperandType::Null ? runCommand(std::get<0>(it),
                Factory::createOperand(std::get<1>(it), std::get<2>(it))
                ) : runCommand(std::get<0>(it));
    }
    if (std::get<0>(cmd.back()) != "exit")
        throw VMException("Missing exit command");
}

void VirtualMachine::removeTrailing0(std::stringstream &ss)
{
    std::string str = ss.str();

    if (str.find('.') != std::string::npos) {
           str = str.substr(0, str.find_last_not_of('0') + 1);
           if (str.find('.') == str.size() + 1) {
               str = str.substr(0, str.size() - 1);
           }
    }
    ss.str(str);
}

void VirtualMachine::push(IOperand *operand)
{
    if (operand == nullptr)
        throw VMException("push: No operand");
    _stack.push_back(operand);
}

void VirtualMachine::pop(IOperand *operand)
{
    if (_stack.empty())
        throw VMException("pop: Pop on empty stack");
    _stack.pop_back();
}

void VirtualMachine::dump(IOperand *operand)
{
    std::stringstream ss;
    for (auto it = _stack.crbegin(); it != _stack.crend(); it++) {
        ss.str("");
        ss << std::fixed << std::setprecision((*it)->getPrecision()) << (*it)->toString();
        removeTrailing0(ss);
        std::cout << ss.str() << std::endl;
    }
}

void VirtualMachine::assertt(IOperand *operand)
{
    if (operand == nullptr)
        throw VMException("assert: No operand");
    if (_stack.empty())
        throw VMException("assert: Assert on empty stack");
    if (*_stack.back() != *operand)
        throw VMException("assert: Assert failed");
}

void VirtualMachine::add(IOperand *operand)
{
    if (_stack.size() < 2)
        throw VMException("add: Add on empty stack");
    IOperand *op1 = _stack.back();
    _stack.pop_back();
    IOperand *op2 = _stack.back();
    _stack.pop_back();
    _stack.push_back(*op1 + *op2);
}

void VirtualMachine::sub(IOperand *operand)
{
    if (_stack.size() < 2)
        throw VMException("sub: Sub on empty stack");
    IOperand *op1 = _stack.back();
    _stack.pop_back();
    IOperand *op2 = _stack.back();
    _stack.pop_back();
    IOperand *res = *op2 - *op1;
    *res < 2 ? throw VMException("sub: Subtraction result is < 2") : _stack.push_back(res);
}

void VirtualMachine::mul(IOperand *operand)
{
    if (_stack.size() < 2)
        throw VMException("mul: Mul on empty stack");
    IOperand *op1 = _stack.back();
    _stack.pop_back();
    IOperand *op2 = _stack.back();
    _stack.pop_back();
    _stack.push_back(*op1 * *op2);
}

void VirtualMachine::div(IOperand *operand)
{
    if (_stack.size() < 2)
        throw VMException("div: Div on empty stack");
    IOperand *op1 = _stack.back();
    _stack.pop_back();
    IOperand *op2 = _stack.back();
    _stack.pop_back();
    if ((*op1).toString() == "0")
        throw VMException("div: Division divisor is equal to 0");
    _stack.push_back(*op2 / *op1);
}

void VirtualMachine::mod(IOperand *operand)
{
    if (_stack.size() < 2)
        throw VMException("mod: Mod on empty stack");
    IOperand *op1 = _stack.back();
    _stack.pop_back();
    IOperand *op2 = _stack.back();
    _stack.pop_back();
    if ((*op1).toString() == "0")
        throw VMException("mod: Mod operands divisor is equal to 0");
    _stack.push_back(*op2 % *op1);
}

void VirtualMachine::print(IOperand *operand)
{
    if (_stack.empty())
        throw VMException("print: Print on empty stack");
    assertt(Factory::createOperand(eOperandType::Int8, _stack.back()->toString()));
    std::cout << (char)std::stoi(_stack.back()->toString()) << std::endl;
}

void VirtualMachine::dup(IOperand *operand)
{
    if (_stack.empty())
        throw VMException("dup: Dup on empty stack");
    _stack.push_back(_stack.back());
}

void VirtualMachine::clear(IOperand *operand)
{
    _stack.clear();
}

void VirtualMachine::swap(IOperand *operand)
{
    if (_stack.size() < 2)
        throw VMException("swap: Swap on empty stack");
    IOperand *op1 = _stack.back();
    _stack.pop_back();
    IOperand *op2 = _stack.back();
    _stack.pop_back();
    _stack.push_back(op1);
    _stack.push_back(op2);
}

void VirtualMachine::exitt(IOperand *operand)
{
    exit(0);
}

void VirtualMachine::pushInRegister(IOperand *operand, int v)
{
    auto it = _register.begin();
    std::advance(it, --v);
    if (v < 0 || v > 15)
        throw VMException("Register index out of range");
    if (_register.size() > 16)
        throw VMException("Register is full");
    _register.insert(it, operand);
}

IOperand *VirtualMachine::getFromRegister(int v)
{
    auto it = _register.begin();
    std::advance(it, --v);
    if (v < 0 || v > 15)
        throw VMException("Register index out of range");
    if (_register.size() < 16)
        throw VMException("Register is empty");
    return *it;
}

void VirtualMachine::store(const std::string &value)
{
    int test;
    if (_stack.empty())
        throw VMException("store: Store on empty stack");
    try {
        test = std::stoi(value);
    } catch (std::exception &e) {
        throw VMException("store: Invalid value " + value);
    }
    IOperand *op = _stack.back();
    _stack.pop_back();
    pushInRegister(op, test);
}

void VirtualMachine::load(const std::string &value)
{
    int test;
    if (_register.empty())
        throw VMException("load: Load on empty register");
    try {
        test = std::stoi(value);
    } catch (std::exception &e) {
        throw VMException("load: Invalid value " + value);
    }
    _stack.push_back(getFromRegister(std::stoi(value)));
}