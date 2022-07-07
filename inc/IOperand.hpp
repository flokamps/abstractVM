#include <string>

class IOperand {
    enum eOperandType {
        Int8,
        Int16,
        Int32,
        Float,
        Double
    };

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