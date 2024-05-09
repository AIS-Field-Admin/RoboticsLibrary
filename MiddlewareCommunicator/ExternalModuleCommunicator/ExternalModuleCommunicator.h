#ifndef EXTERNALMODULECOMMUNICATOR_H
#define EXTERNALMODULECOMMUNICATOR_H

#pragma once

#include <atomic>
#include <thread>
#include <mutex>
#include <queue>
#include <string>
#include <chrono>

#include "IExternalModuleCommunicator.h"
#include "..\OrderStore\IOrderReception.h"
#include "IExternalModuleBoundary.h"

class ExternalModuleCommunicator : public IExternalModuleCommunicator {

    public:

        ExternalModuleCommunicator(std::string externalModuleName,
                                   std::shared_ptr<IOrderReception> orderReception, 
                                   std::shared_ptr<IExternalModuleBoundary> externalModuleBoundary,
                                   std::string parentModuleName);

        virtual ~ExternalModuleCommunicator();

        bool InitialiseModule() override;

        bool Stop() override;

        bool StartReceivingOrders() override;

        bool AddOrder(const std::string& order) override;

        bool SetOrderReceivalPeriod(int milliseconds) override;

        std::string GetCommunicatorName() override;

    protected:

        std::string _externalModuleName;
        std::shared_ptr<IExternalModuleBoundary> _externalModuleBoundary;
        std::shared_ptr<IOrderReception> _orderReception;
        std::string _parentModuleName;

        std::atomic<bool> _isReceiving{ false };

        int _orderReceivalPeriod_milliseconds = 100;

        std::thread _retrievalThread;
        std::mutex _mutex;

        std::queue<std::string> _orders;

        void retrieveOrdersPeriodically();
};

#endif // EXTERNALMODULECOMMUNICATOR_H
