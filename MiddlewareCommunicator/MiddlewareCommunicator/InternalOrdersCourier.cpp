#include "pch.h"
#include "InternalOrdersCourier.h"

bool InternalOrdersCourier::RegisterOrderHandler(std::shared_ptr<OrderHandler> orderHandler) 
{
    std::vector<std::string> orderTypes = orderHandler->GetOrderTypes();

    for (std::string orderType : orderTypes)
    {
        if (_orderHandlers.find(orderType) != _orderHandlers.end())
        {
            std::cerr << "DUPLICATE ORDER TYPE: " << orderType << std::endl;

            throw;
        }

        _orderHandlers[orderType] = orderHandler;
    }

    return true;
}

bool InternalOrdersCourier::PostOrder(const Order& order) 
{
    auto iterator = _orderHandlers.find(order.OrderType);

    if (iterator != _orderHandlers.end()) 
    {
        return iterator->second->HandleOrder(order);
    }

    return false;
}
