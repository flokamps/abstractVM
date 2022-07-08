//
// Created by Florian Kamps on 07/07/2022.
//

#include "../inc/Factory.hpp"

int main(int argc, char **argv)
{
    IOperand *int8 = Factory::createOperand(eOperandType::Float, "2.0");
    IOperand *int8_2 = Factory::createOperand(eOperandType::Double, "3.0");
    IOperand *sum = *int8 / *int8_2;
    return 0;
}