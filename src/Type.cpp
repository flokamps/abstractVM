//
// Created by Florian Kamps on 07/07/2022.
//

#include "../inc/Type.hpp"

template <typename T>
double Type<T>::getDoubleFromString(std::string const &value) const
{
    size_t next;
    double conv;

    conv = std::stod(value, &next);
    if (next > value.length() || value[next] != '\0')
        //throw exception
        return 0;
    return conv;
}