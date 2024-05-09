#ifndef IORDERHANDLER_H
#define IORDERHANDLER_H

#include <iostream>

#include "..\OrderStore\Order.h"
#include "..\OrderStore\IOrderStorage.h"

class OrderHandler
{
    public:

        virtual ~OrderHandler() = default;

        virtual bool HandleOrder(const Order& order) = 0;

        virtual bool ConstructCommands() = 0;

        void SetOrderStorage(std::shared_ptr<IOrderStorage> orderStorage);
        
        std::vector<std::string> GetOrderTypes();

    protected:

        void SetOrderTypes(std::vector<std::string> orderTypes);

        std::shared_ptr<IOrderStorage> _orderStorage;

        std::vector<std::string> _orderTypes = {};


};

#endif // IORDERHANDLER_H
