#include "pch.h"
#include "OrderDecoder.h"

OrderDecoder::OrderDecoder()
{

}

Order OrderDecoder::DecodeOrder(const std::string& jsonStr) 
{
    Order order;

    if (jsonStr.empty()) 
    {
        order = CreateAndGetErrorOrder("JSON is Empty");

        return order;
    }

    if (!OrderStructureValidator::Validate(jsonStr)) 
    {
        order = CreateAndGetErrorOrder("Malformed JSON content");

        return order;
    }

    nlohmann::json json = nlohmann::json::parse(jsonStr, nullptr, false); // No exceptions thrown

    if (json.is_discarded()) 
    {
        order = CreateAndGetErrorOrder("Malformed JSON content");

        return order;
    }

    order = CreateAndGetOrderFromJson(json);

    return order;
}

Order OrderDecoder::CreateAndGetErrorOrder(const std::string& errorMessage)
{
    Order order;

    order.OrderId = -1;
    order.SenderModule = "Error";
    order.RecipientModule = "Error";
    order.OrderType = "JSON_Error";
    order.OrderParameters = errorMessage;
    
    return order;
}

Order OrderDecoder::CreateAndGetOrderFromJson(const nlohmann::json& json)
{
    
    Order order;

    order.OrderId = json.value("OrderId", -1);
    order.SenderModule = json.value("SenderModule", "Unknown");
    order.RecipientModule = json.value("RecipientModule", "Unknown");
    order.OrderType = json.value("OrderType", "Unknown");
    order.OrderParameters = json.value("OrderParameters", "Unknown");

    return order;
}