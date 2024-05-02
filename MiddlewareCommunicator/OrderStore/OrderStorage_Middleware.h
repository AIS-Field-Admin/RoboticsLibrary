#pragma once

#ifndef ORDERSTORAGE_MIDDLEWARE_H
#define ORDERSTORAGE_MIDDLEWARE_H

#include <queue>
#include <string>
#include <mutex>

#include "IOrderStorage.h"

class OrderStorage_Middleware : public IOrderStorage
{
    public:

        OrderStorage_Middleware(std::string storageName);

        void AddOrder(const std::string& order) override;

        std::queue<std::string> GetOrders() override;

        void CleanOrders() override;

        std::string GetStorageName() override;

    private:

        std::queue<std::string> _orders;

        mutable std::mutex _mutex;

        std::string _storageName;
};

#endif // ORDERSTORAGE_MIDDLEWARE_H