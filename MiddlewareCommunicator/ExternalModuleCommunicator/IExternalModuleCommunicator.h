#pragma once

#include <queue>
#include <string>

class IExternalModuleCommunicator
{
public:
    virtual ~IExternalModuleCommunicator() = default;

    virtual bool InitialiseModule() = 0;

    virtual bool Stop() = 0;

    virtual bool StartReceivingOrders() = 0;

    virtual bool AddOrder(const std::string& order) = 0;

    virtual bool SetOrderReceivalPeriod(int milliseconds) = 0;

    virtual std::string GetCommunicatorName() = 0;
};