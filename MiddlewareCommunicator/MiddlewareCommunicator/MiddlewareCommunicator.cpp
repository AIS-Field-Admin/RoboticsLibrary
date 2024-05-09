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
	try
	{
		_mainManager->SetOrder(order);

		return true;
	}
	catch (std::exception& ex)
	{
		std::cout << "An error occured while trying to add orders: " << ex.what() << std::endl;

		return false;
	}
}

std::queue<std::string> MiddlewareCommunicator::GetOrders()
{

	try
	{
		std::queue<std::string> orderQueue = _mainManager->GetParentModuleOrders();

		return orderQueue;
	}
	catch (std::exception& ex)
	{
		std::cout << "An error occured while trying to get orders: " << ex.what() << std::endl;

		return { };
	}

}


