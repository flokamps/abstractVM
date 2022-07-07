//
// Created by Florian Kamps on 07/07/2022.
//

#ifndef ABSTRACTVM_TYPE_HPP
#define ABSTRACTVM_TYPE_HPP

#include "IOperand.hpp"

template <class T>
class Type : public IOperand {
    private:
        T _value;
        eOperandType type;
    public:
        Type(T value, eOperandType type) : _value(value), type(type) {};
        ~Type() = default;
        std::string toString() const {
            return std::to_string(_value);
        };
        eOperandType getType() const {
            return type;
        };

        IOperand *operator+(const IOperand &rhs) const {
            return nullptr;
        };
        IOperand *operator-(const IOperand &rhs) const {
            return nullptr;
        };
        IOperand *operator*(const IOperand &rhs) const {
            return nullptr;
        };
        IOperand *operator/(const IOperand &rhs) const {
            return nullptr;
        };
        IOperand *operator%(const IOperand &rhs) const {
            return nullptr;
        };
};

#endif //ABSTRACTVM_TYPE_HPP
