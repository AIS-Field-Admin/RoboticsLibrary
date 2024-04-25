#include "pch.h"
#include "MiddlewareCommunicator.h"

MiddlewareCommunicator::MiddlewareCommunicator()
{
	_mainManager = std::make_shared<MainManager>();
}

bool MiddlewareCommunicator::Construct(std::string middlewareName,
									   std::vector<std::shared_ptr<OrderHandler>>& orderHandlers,
									   std::vector<std::shared_ptr<IExternalModuleCommunicator>>& externalModuleCommunicators,
									   std::shared_ptr<IOrderReception> orderReception,
	                                   std::shared_ptr<IOrderStorage> orderStorage_ParentModule)
{
	_mainManager->ConstructMiddleware(middlewareName, orderHandlers, externalModuleCommunicators, orderReception, orderStorage_ParentModule);

	return true;
}

bool MiddlewareCommunicator::SetOrder(std::string order)
{
	if (!_isStarted)
	{
		return false;
	}

	_mainManager->SetOrder(order);

	return true;
}

std::queue<std::string> MiddlewareCommunicator::GetOrders()
{
	if (!_isStarted)
	{
		return {};
	}

	std::cout << "Trying to get Orders" << std::endl;

	std::queue<std::string> orderQueue = _mainManager->GetParentModuleOrders();

	std::cout << "Queue Count: " << orderQueue.size() << std::endl;

	return orderQueue;
}

bool MiddlewareCommunicator::Start()
{
	_isStarted = true;

	return true;
}
