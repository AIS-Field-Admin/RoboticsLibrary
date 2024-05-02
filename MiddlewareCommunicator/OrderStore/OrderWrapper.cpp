#include "pch.h"
#include "OrderWrapper.h"

#include "Order.h"


std::string OrderWrapper::PrepareOrderParameters(const std::map<std::string, std::string>& parameters) 
{
    nlohmann::json jsonParams = nlohmann::json::object();

    for (const auto& p : parameters) 
    {
        jsonParams[p.first] = p.second;
    }

    return jsonParams.dump(); 
}

std::string OrderWrapper::SerializeOrder(const Order& order) 
{
    nlohmann::json j;

    j["OrderId"] = order.OrderId;
    j["SenderModule"] = order.SenderModule;
    j["RecipientModule"] = order.RecipientModule;
    j["OrderType"] = order.OrderType;
    j["OrderParameters"] = order.OrderParameters; 

    return j.dump(); 
}
