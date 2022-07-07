//
// Created by Florian Kamps on 07/07/2022.
//

#include "../inc/Factory.hpp"

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