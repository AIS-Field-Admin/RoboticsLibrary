#include "pch.h"
#include "OrderHandlerCommand.h"

OrderHandlerCommand::OrderHandlerCommand(std::shared_ptr<IOrderStorage> orderStorage) 
{
    _orderStorage = orderStorage;
}

bool OrderHandlerCommand::PostOrder(const Order& order)
{
    std::string orderString = OrderWrapper::SerializeOrder(order);

    return true;
}
