#pragma once

#ifndef ORDERSTORAGE_PARENTMODULE_H
#define ORDERSTORAGE_PARENTMODULE_H

#include <queue>
#include <string>
#include <mutex>

#include "IOrderStorage.h"

class OrderStorage_ParentModule : public IOrderStorage
{
    public:

        OrderStorage_ParentModule(std::string storageName);

        void AddOrder(const std::string& order) override;

        std::queue<std::string> GetOrders() override;

        void CleanOrders() override;

        std::string GetStorageName() override;

    private:

        std::queue<std::string> _orders;

        mutable std::mutex _mutex;

        std::string _storageName;
};

#endif // ORDERSTORAGE_PARENTMODULE_H