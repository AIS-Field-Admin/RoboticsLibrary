#include "pch.h"
#include "OrderStorage_ParentModule.h"

OrderStorage_ParentModule::OrderStorage_ParentModule(std::string storageName)
{
    _storageName = storageName;
}

void OrderStorage_ParentModule::AddOrder(const std::string& order) 
{
    std::lock_guard<std::mutex> lock(_mutex);

    _orders.push(order);
}

std::queue<std::string> OrderStorage_ParentModule::GetOrders() 
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

void OrderStorage_ParentModule::CleanOrders() 
{
    std::lock_guard<std::mutex> lock(_mutex);

    _orders = std::queue<std::string>();
}

std::string OrderStorage_ParentModule::GetStorageName()
{
    return _storageName;
}