//
// Created by Florian Kamps on 07/07/2022.
//

#ifndef ABSTRACTVM_TYPE_HPP
#define ABSTRACTVM_TYPE_HPP

#include "IOperand.hpp"

template <class T>
class Type : public IOperand {
    private:
        T value;
        eOperandType type;
    public:
        Type(T value, eOperandType type) : value(value), type(type) {};
        ~Type();
};

#endif //ABSTRACTVM_TYPE_HPP
