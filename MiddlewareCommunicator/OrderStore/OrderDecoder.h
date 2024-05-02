#pragma once

#ifndef ORDERDECODER_H
#define ORDERDECODER_H

#include <string>
#include <nlohmann/json.hpp>
#include <iostream>

#include "OrderStructureValidator.h"
#include "Order.h" 


static class OrderDecoder
{
    public:

        OrderDecoder();

        static Order DecodeOrder(const std::string& jsonStr);

    private:

        static Order CreateAndGetErrorOrder(const std::string& errorMessage);
        static Order CreateAndGetOrderFromJson(const nlohmann::json& json);

};

#endif // ORDERDECODER_H