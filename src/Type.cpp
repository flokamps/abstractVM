//
// Created by Florian Kamps on 07/07/2022.
//

#include "../inc/Type.hpp"
#include "../inc/Factory.hpp"

template <typename T>
double Type<T>::getDoubleFromString(std::string const &value) const
{
    size_t next;
    double conv;

    conv = std::stod(value, &next);
    if (next > value.length() || value[next] != '\0')
        //throw exception
        return 0;
    return conv;
}

template<class T>
IOperand *Type<T>::makeOperation(eOperandType operandType, const std::string &value) const
{
    double res;
    IOperand *new_op;
    res = getDoubleFromString(value) + _value;
    new_op = Factory::createOperand(operandType, std::to_string(res));
    return new_op;
}