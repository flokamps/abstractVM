#pragma once

#include <string>

enum eOperandType {
    Int8,
    Int16,
    Int32,
    Float,
    Double,
    BigDecimal,
    Null,
    Error
};

class IOperand {
    public:
        virtual std::string toString() const = 0;

        virtual eOperandType getType() const = 0;

        virtual int getPrecision() const = 0;

        virtual IOperand *operator+(const IOperand &rhs) const = 0;
        virtual IOperand *operator-(const IOperand &rhs) const = 0;
        virtual IOperand *operator*(const IOperand &rhs) const = 0;
        virtual IOperand *operator/(const IOperand &rhs) const = 0;
        virtual IOperand *operator%(const IOperand &rhs) const = 0;
        virtual bool operator!=(const IOperand &rhs) const = 0;
        virtual bool operator<(int rhs) const = 0;
        virtual bool operator==(const IOperand &rhs) const = 0;

        virtual ~IOperand() = default;
};