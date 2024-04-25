#include "pch.h"
#include "ExternalModuleCommunicator.h"


ExternalModuleCommunicator::ExternalModuleCommunicator(std::string externalModuleName,
                                                       std::shared_ptr<IOrderReception> orderReception,
                                                       std::shared_ptr<IExternalModuleBoundary> externalModuleBoundary,
                                                       std::string parentModuleName)
{
    _externalModuleName = externalModuleName;
    _orderReception = orderReception;
    _externalModuleBoundary = externalModuleBoundary;
    _parentModuleName = parentModuleName;
}

ExternalModuleCommunicator::~ExternalModuleCommunicator()
{
    Stop();
}

bool ExternalModuleCommunicator::InitialiseModule()
{
    if (!_externalModuleBoundary->Start())
    {
        return false;
    }

    StartReceivingOrders();

    return true;
}

bool ExternalModuleCommunicator::Stop()
{
    _isReceiving = false;

    if (_retrievalThread.joinable())
    {
        _retrievalThread.join();
    }

    return true;
}

bool ExternalModuleCommunicator::StartReceivingOrders()
{

    _isReceiving = true;

    _retrievalThread = std::thread(&ExternalModuleCommunicator::retrieveOrdersPeriodically, this);

    return true;

}

bool ExternalModuleCommunicator::AddOrder(const std::string& order)
{
    _externalModuleBoundary->SetOrder(order);

    return true;
}

bool ExternalModuleCommunicator::SetOrderReceivalPeriod(int milliseconds)
{
    _orderReceivalPeriod_milliseconds = milliseconds;

    return true;
}

void ExternalModuleCommunicator::retrieveOrdersPeriodically()
{
    while (_isReceiving)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(_orderReceivalPeriod_milliseconds));

        std::cout << "Listening Navigator orders" << std::endl;

        std::queue<std::string> orders = _externalModuleBoundary->GetOrders();

        while (!orders.empty())
        {
            std::cout << "Received order from Navigator: " << orders.front() << std::endl;

            _orderReception->ProcessOrder(orders.front());

            orders.pop();
        }
    }
}

std::string ExternalModuleCommunicator::GetCommunicatorName()
{
    return _externalModuleName;
}
