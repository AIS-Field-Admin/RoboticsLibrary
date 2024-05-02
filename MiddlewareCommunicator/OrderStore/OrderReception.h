#pragma once

#ifndef ORDERRECEPTION_H
#define ORDERRECEPTION_H

#include <memory>
#include <mutex>

#include "IOrderReception.h"

#include "Order.h" 
#include "OrderDecoder.h"
#include "IOrderStorage.h"

class OrderReception : public IOrderReception
{
    public:

        OrderReception();

        void SetOrderStorages(std::shared_ptr<IOrderStorage> orderStorage_ParentModule, std::shared_ptr<IOrderStorage> orderStorage_Middleware) override;

        void ProcessOrder(const std::string& order) override;

    private:

        std::shared_ptr<IOrderStorage> _orderStorage_ParentModule;
        std::shared_ptr<IOrderStorage> _orderStorage_Middleware;

        std::mutex _mutex;

        bool storeOrder_ParentModule(const std::string& order);
        bool storeOrder_Middleware(const std::string& order);
};

#endif //ORDERRECEPTION_H

