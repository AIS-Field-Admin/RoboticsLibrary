#pragma once

#ifndef IORDERRECEPTION_H
#define IORDERRECEPTION_H

#include <iostream>

#include "IOrderStorage.h"

class IOrderReception
{
public:
    virtual ~IOrderReception() = default; 

    virtual void SetOrderStorages(std::shared_ptr<IOrderStorage> orderStorage_ParentModule, std::shared_ptr<IOrderStorage> orderStorage_Middleware) = 0;

    virtual void ProcessOrder(const std::string& order) = 0;
};

#endif // IORDERRECEPTION_H
