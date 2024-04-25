#include "pch.h"
#include "OrderReception.h"
 
OrderReception::OrderReception()                                               
{
 
}

void OrderReception::SetOrderStorages(std::shared_ptr<IOrderStorage> orderStorage_ParentModule, std::shared_ptr<IOrderStorage> orderStorage_Middleware)
{
    _orderStorage_ParentModule = orderStorage_ParentModule;
    _orderStorage_Middleware = orderStorage_Middleware;
}

void OrderReception::ProcessOrder(const std::string& order)
{
    std::lock_guard<std::mutex> guard(_mutex);

    Order decodedOrder = OrderDecoder::DecodeOrder(order);

    std::cout << "Order Parameters after decoding: " << decodedOrder.OrderParameters << std::endl;
    std::cout << order << std::endl;

    if (decodedOrder.RecipientModule == _orderStorage_ParentModule->GetStorageName())
    {
        storeOrder_ParentModule(order);
    }
    else if (decodedOrder.RecipientModule == _orderStorage_Middleware->GetStorageName())
    {
        storeOrder_Middleware(order);
    }
}

bool OrderReception::storeOrder_ParentModule(const std::string& order)
{
    try
    {
        _orderStorage_ParentModule->AddOrder(order);

        return true;
    }
    catch (const std::exception& ex)
    {
        std::cout << "Order could not be added to ParentModule: " << ex.what() << std::endl;

        return false;
    }
}

bool OrderReception::storeOrder_Middleware(const std::string& order)
{
    try
    {
        _orderStorage_Middleware->AddOrder(order);

        return true;
    }
    catch (const std::exception& ex)
    {
        std::cout << "Order could not be added to Middleware: " << ex.what() << std::endl;

        return false;
    }
}



