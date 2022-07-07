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
        ~Type() override = default;
        std::string toString() const override {
            return std::to_string(_value);
        };
        eOperandType getType() const override {
            return type;
        };
        double getDoubleFromString(std::string const &value) const;
        IOperand *makeOperation(eOperandType operandType, const std::string &value) const;

        IOperand *operator+(const IOperand &rhs) const override {
            IOperand *new_op = makeOperation(rhs.getType(), rhs.toString());
            return new_op;
        };
        IOperand *operator-(const IOperand &rhs) const override {
            return nullptr;
        };
        IOperand *operator*(const IOperand &rhs) const override {
            return nullptr;
        };
        IOperand *operator/(const IOperand &rhs) const override {
            return nullptr;
        };
        IOperand *operator%(const IOperand &rhs) const override {
            return nullptr;
        };
};

#endif //ABSTRACTVM_TYPE_HPP
