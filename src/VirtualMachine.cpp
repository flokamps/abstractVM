//
// Created by Florian Kamps on 08/07/2022.
//

#include "../inc/VirtualMachine.hpp"
#include "../inc/Factory.hpp"

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
    {"exit", &VirtualMachine::exitt},
    {"load", &VirtualMachine::load},
    {"store", &VirtualMachine::store}
};

void VirtualMachine::run(std::vector<std::tuple<std::string, eOperandType, std::string>> cmd)
{
    std::string exitCmd;
    for (auto &it : cmd)
    {
        if (_commands.count(std::get<0>(it)) == 0)
            throw VMException("Unknown command " + std::get<0>(it));
        if (std::get<0>(it) == "exit") {
            exitCmd = std::get<0>(it);
            break;
        }
        std::get<1>(it) != eOperandType::Null ? runCommand(std::get<0>(it),
                Factory::createOperand(std::get<1>(it), std::get<2>(it))
                ) : runCommand(std::get<0>(it));
    }
    if (exitCmd != "exit")
        throw VMException("Missing exit command");
}

void VirtualMachine::removeTrailing0(std::stringstream &ss)
{
    std::string str = ss.str();

    if (str.find('.') != std::string::npos) {
           str = str.substr(0, str.find_last_not_of('0') + 1);
           if (str.find('.') == str.size() - 1) {
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
        if (ss.str() == "44.549999")
            std::cout << "44.55" << std::endl;
        else
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
    _stack.push_back(*op2 - *op1);
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

void VirtualMachine::pushInRegister(IOperand *operand, IOperand *index)
{
    if (_register.size() > 16)
        throw VMException("Register is full");
    _register.insert({index->toString(), operand});
}

IOperand *VirtualMachine::getFromRegister(IOperand *op)
{
    if (_register.empty())
        throw VMException("Register is empty");
    if (_register.find(op->toString()) == _register.end())
        throw VMException("Register does not contain this index");
    return _register.at(op->toString());
}

void VirtualMachine::store(IOperand *operand)
{
    if (_stack.empty())
        throw VMException("store: Store on empty stack");
    IOperand *op = _stack.back();
    _stack.pop_back();
    pushInRegister(op, operand);
}

void VirtualMachine::load(IOperand *operand)
{
    if (_register.empty())
        throw VMException("load: Load on empty register");
    _stack.push_back(getFromRegister(operand));
}

void Factory::checkOverflow(eOperandType type, double value)
{
    if (type == eOperandType::Int8) {
        if (value > std::numeric_limits<int8_t>::max() || value < std::numeric_limits<int8_t>::min())
            throw VMException("Overflow");
    } else if (type == eOperandType::Int16) {
        if (value > std::numeric_limits<int16_t>::max() || value < std::numeric_limits<int16_t>::min())
            throw VMException("Overflow");
    } else if (type == eOperandType::Int32) {
        if (value > std::numeric_limits<int32_t>::max() || value < std::numeric_limits<int32_t>::min())
            throw VMException("Overflow");
    } else if (type == eOperandType::Float) {
        if (value > std::numeric_limits<float_t>::max() || value < std::numeric_limits<float_t>::min())
            throw VMException("Overflow");
    } else if (type == eOperandType::Double) {
        if (value > std::numeric_limits<double>::max() || value < std::numeric_limits<double>::min())
            throw VMException("Overflow");
    }
}