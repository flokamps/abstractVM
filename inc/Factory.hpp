//
// Created by Florian Kamps on 07/07/2022.
//

#ifndef ABSTRACTVM_FACTORY_H
#define ABSTRACTVM_FACTORY_H

#include "IOperand.hpp"
#include <array>
#include <map>
#include <cmath>

class Factory {
    public:
        Factory();
        ~Factory();

        static IOperand* createOperand(eOperandType type, const std::string& value);
    private:
        IOperand* createInt8(const std::string& value);
        IOperand* createInt16(const std::string& value);
        IOperand* createInt32(const std::string& value);
        IOperand* createFloat(const std::string& value);
        IOperand* createDouble(const std::string& value);
        IOperand* createBigDecimal(const std::string& value);

        static void checkOverflow(eOperandType type, double value);
        static bool isFloatingPoint(const std::string &);

       typedef std::map<eOperandType, IOperand *(Factory::*)(const std::string&)> Operands;
       static Operands _operands;
};

#endif //ABSTRACTVM_FACTORY_H