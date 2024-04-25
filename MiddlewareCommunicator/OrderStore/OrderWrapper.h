#ifndef ORDERWRAPPER_H
#define ORDERWRAPPER_H


#include <iostream>

#include "nlohmann/json.hpp"

#include "Order.h"


class OrderWrapper 
{
    public:

        static std::string SerializeOrder(const Order& order);
        static std::string PrepareOrderParameters(const std::map<std::string, std::string>& parameters);
};

#endif // !ORDERWRAPPER_H

