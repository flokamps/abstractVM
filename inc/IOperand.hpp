#include <string>
#include "Factory.hpp"

enum eOperandType {
    Int8,
    Int16,
    Int32,
    Float,
    Double
};

class IOperand {
    public:
        virtual std::string toString() const = 0;

        virtual eOperandType getType() const = 0;

        virtual IOperand *operator+(const IOperand &rhs) const = 0;
        virtual IOperand *operator-(const IOperand &rhs) const = 0;
        virtual IOperand *operator*(const IOperand &rhs) const = 0;
        virtual IOperand *operator/(const IOperand &rhs) const = 0;
        virtual IOperand *operator%(const IOperand &rhs) const = 0;

        virtual ~IOperand() {}
};