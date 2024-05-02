#pragma once
#include "pch.h"

#include <unordered_map>
#include <memory>
#include <string>

#include "IInternalOrdersCourier.h"
#include "..\OrderHandler\OrderHandler.h"
#include "..\OrderStore\Order.h"

class InternalOrdersCourier : public IInternalOrdersCourier
{
    public:

        bool RegisterOrderHandler(std::shared_ptr<OrderHandler> orderHandler) override;

        bool PostOrder(const Order& order) override;

    private:

        std::unordered_map<std::string, std::shared_ptr<OrderHandler>> _orderHandlers;
};

