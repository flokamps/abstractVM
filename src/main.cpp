//
// Created by Florian Kamps on 07/07/2022.
//

#include "../inc/Factory.hpp"

int main(int argc, char **argv)
{
    IOperand *int8 = Factory::createOperand(eOperandType::Int32, "1");
    IOperand *int8_2 = Factory::createOperand(eOperandType::Int8, "2");
    IOperand *sum = *int8 % *int8_2;
    return 0;
}