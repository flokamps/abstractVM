//
// Created by Florian Kamps on 07/07/2022.
//

#ifndef ABSTRACTVM_FACTORY_H
#define ABSTRACTVM_FACTORY_H

#include "IOperand.hpp"

class Factory {
    public:
        Factory();
        ~Factory();

        static IOperand* createOperand(eOperandType type, const std::string& value);

        IOperand* createInt8(const std::string& value);
        IOperand* createInt16(const std::string& value);
        IOperand* createInt32(const std::string& value);
        IOperand* createFloat(const std::string& value);
        IOperand* createDouble(const std::string& value);
        IOperand* createBigDecimal(const std::string& value);
};

#endif //ABSTRACTVM_FACTORY_H