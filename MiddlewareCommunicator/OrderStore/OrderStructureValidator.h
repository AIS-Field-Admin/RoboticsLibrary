#ifndef ORDERSTRUCTUREVALIDATOR_H
#define ORDERSTRUCTUREVALIDATOR_H

#pragma once

#include <nlohmann/json.hpp>

#include "Order.h"
#include <string>


class OrderStructureValidator {
public:
    static bool Validate(const std::string& orderJson);
};

#endif // ORDERSTRUCTUREVALIDATOR_H

