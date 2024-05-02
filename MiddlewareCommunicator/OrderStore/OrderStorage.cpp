#include "pch.h"
#include "OrderStorage.h"

OrderStorage::OrderStorage(std::string storageName)
{
    _storageName = storageName;
}

void OrderStorage::AddOrder(const std::string order) 
{
    std::lock_guard<std::mutex> lock(_mutex);

    _orders.push(order);
}

std::queue<std::string> OrderStorage::GetOrders() 
{
    std::cout << "Getting Orders From: " << _storageName << std::endl;

    std::lock_guard<std::mutex> lock(_mutex);

    std::queue<std::string> queueToSent;

    while (!_orders.empty()) 
    {
        queueToSent.push(_orders.front());
        _orders.pop();
    }

    return queueToSent;
}

void OrderStorage::CleanOrders() 
{
    std::lock_guard<std::mutex> lock(_mutex);

    _orders = std::queue<std::string>();
}

std::string OrderStorage::GetStorageName()
{
    return _storageName;
}