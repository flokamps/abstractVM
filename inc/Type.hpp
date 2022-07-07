//
// Created by Florian Kamps on 07/07/2022.
//

#ifndef ABSTRACTVM_TYPE_HPP
#define ABSTRACTVM_TYPE_HPP

#include "IOperand.hpp"
#include "Factory.hpp"
#include <cmath>

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
        double getDoubleFromString(std::string const &value) const {
            size_t next;
            double conv;

            conv = std::stod(value, &next);
            if (next > value.length() || value[next] != '\0')
                //throw exception
                return 0;
            return conv;
        };
        IOperand *makeOperation(eOperandType operandType, const std::string &value, char op) const {
            double res;
            IOperand *new_op;
            switch (op) {
                case '+':
                    res = getDoubleFromString(value) + _value;
                    break;
                case '-':
                    res = _value - getDoubleFromString(value);
                    break;
                    case '*':
                    res = _value * getDoubleFromString(value);
                    break;
                case '/':
                    res = _value / getDoubleFromString(value);
                    break;
                case '%':
                    res = fmod(_value,getDoubleFromString(value));
                    break;
                default:
                    res = 0;
                    break;
            }
            new_op = Factory::createOperand(operandType, std::to_string(res));
            return new_op;
        };

        IOperand *operator+(const IOperand &rhs) const override {
            IOperand *new_op = makeOperation(rhs.getType(), rhs.toString(), '+');
            return new_op;
        };
        IOperand *operator-(const IOperand &rhs) const override {
            IOperand *new_op = makeOperation(rhs.getType(), rhs.toString(), '-');
            return new_op;
        };
        IOperand *operator*(const IOperand &rhs) const override {
            IOperand *new_op = makeOperation(rhs.getType(), rhs.toString(), '*');
            return new_op;
        };
        IOperand *operator/(const IOperand &rhs) const override {
            IOperand *new_op = makeOperation(rhs.getType(), rhs.toString(), '/');
            return new_op;
        };
        IOperand *operator%(const IOperand &rhs) const override {
            IOperand *new_op = makeOperation(rhs.getType(), rhs.toString(), '%');
            return new_op;
        };
};

#endif //ABSTRACTVM_TYPE_HPP
