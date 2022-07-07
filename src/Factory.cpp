//
// Created by Florian Kamps on 07/07/2022.
//

#include "../inc/Factory.hpp"
#include "../inc/Type.hpp"

Factory::Factory()
{
}

Factory::~Factory()
{
}

IOperand *Factory::createOperand(eOperandType type, const std::string &value)
{
    Factory factory;
    IOperand *(Factory::*op)(const std::string &) = _operands[type];
    return (factory.*op)(value);
}

Factory::Operands Factory::_operands = {
    {eOperandType::Int8, &Factory::createInt8},
    {eOperandType::Int16, &Factory::createInt16},
    {eOperandType::Int32, &Factory::createInt32},
    {eOperandType::Float, &Factory::createFloat},
    {eOperandType::Double, &Factory::createDouble},
    {eOperandType::BigDecimal, &Factory::createBigDecimal}
};

IOperand *Factory::createInt8(const std::string &value)
{
    IOperand *operand = new Type<int8_t>(std::stoi(value), eOperandType::Int8);
    return operand;
}

IOperand *Factory::createInt16(const std::string &value)
{
    return nullptr;
}

IOperand *Factory::createInt32(const std::string &value)
{
    return nullptr;
}

IOperand *Factory::createFloat(const std::string &value)
{
    return nullptr;
}

IOperand *Factory::createDouble(const std::string &value)
{
    return nullptr;
}

IOperand *Factory::createBigDecimal(const std::string &value)
{
    return nullptr;
}
