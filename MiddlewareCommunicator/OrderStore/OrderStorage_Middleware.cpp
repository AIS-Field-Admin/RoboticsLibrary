#include "pch.h"
#include "OrderStorage_Middleware.h"

OrderStorage_Middleware::OrderStorage_Middleware(std::string storageName)
{
    _storageName = storageName;
}

void OrderStorage_Middleware::AddOrder(const std::string& order) 
{
    std::lock_guard<std::mutex> lock(_mutex);

    _orders.push(order);
}

std::queue<std::string> OrderStorage_Middleware::GetOrders() 
{
    std::lock_guard<std::mutex> lock(_mutex);

    std::queue<std::string> queueToSent;

    while (!_orders.empty()) 
    {
        queueToSent.push(_orders.front());
        _orders.pop();
    }

    return queueToSent;
}

void OrderStorage_Middleware::CleanOrders() 
{
    std::lock_guard<std::mutex> lock(_mutex);

    _orders = std::queue<std::string>();
}

std::string OrderStorage_Middleware::GetStorageName()
{
    return _storageName;
}