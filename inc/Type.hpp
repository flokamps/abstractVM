//
// Created by Florian Kamps on 07/07/2022.
//

#ifndef ABSTRACTVM_TYPE_HPP
#define ABSTRACTVM_TYPE_HPP

#include "IOperand.hpp"
#include "Factory.hpp"
#include <cmath>
#include <variant>
#include <iomanip>

template <class T>
class Type : public IOperand {
    private:
        T _value;
        eOperandType _type;
    public:
        Type(T value, eOperandType type) : _value(value), _type(type) {};
        ~Type() override = default;
        std::string toString() const override {
            return std::to_string(_value);
        };
        eOperandType getType() const override {
            return _type;
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
        eOperandType defineNewType(eOperandType other) const {
            std::map<eOperandType, int> types = {
                    {eOperandType::Int8, 1},
                    {eOperandType::Int16, 2},
                    {eOperandType::Int32, 3},
                    {eOperandType::Float, 4},
                    {eOperandType::Double, 5},
                    {eOperandType::BigDecimal, 6}
            };
            if (types[other] > types[_type])
                return other;
            return _type;
        };
        IOperand *makeOperation(eOperandType operandType, const std::string &value, char op) const {
            double res;
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
                    res = fmod(_value, getDoubleFromString(value));
                    break;
                default:
                    res = 0;
                    break;
            }
            eOperandType new_type = defineNewType(operandType);
            return Factory::createOperand(new_type, std::to_string(res));
        };
        bool checkIfEqual(IOperand const &rhs) const {
            return _value == std::stod(rhs.toString());
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
        bool operator!=(const IOperand &rhs) const override {
            return !checkIfEqual(rhs);
        };
        bool operator<(int rhs) const override {
            return _value < rhs;
        };
};

#endif //ABSTRACTVM_TYPE_HPP
