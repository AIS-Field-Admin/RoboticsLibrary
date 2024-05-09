#include "pch.h"
#include "OrderStorage.h"

OrderStorage::OrderStorage(std::string storageName)
{
    _storageName = storageName;
}

void OrderStorage::AddOrder(const std::string order) 
{
    std::lock_guard<std::mutex> lock(_mutex);
    std::cout << "Add Order: " << order << std::endl;
    _orders.push(order);
}

std::queue<std::string> OrderStorage::GetOrders() 
{
    std::lock_guard<std::mutex> lock(_mutex);

    std::queue<std::string> queueToSent;

    while (!_orders.empty()) 
    {
        std::cout << "Order Found" << std::endl;
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