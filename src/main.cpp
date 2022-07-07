//
// Created by Florian Kamps on 07/07/2022.
//

#include "../inc/Factory.hpp"

int main(int argc, char **argv)
{
    IOperand *int8 = Factory::createOperand(eOperandType::Int8, "1");
    return 0;
}