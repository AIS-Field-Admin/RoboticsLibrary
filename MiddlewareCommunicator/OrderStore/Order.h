#pragma once

#ifndef ORDER_H
#define ORDER_H

#include <string>
#include <vector>

struct Order {
    int OrderId;
    std::string SenderModule;
    std::string RecipientModule;
    std::string OrderType;
    std::string OrderParameters;
};

#endif // ORDER_H