#include "pch.h"
#include "OrderDistributionHub.h"

OrderDistributionHub::OrderDistributionHub(std::shared_ptr<IExternalModulesManager>& externalModulesManager,
										   std::shared_ptr<IOrderStorage>& orderStorage_middleware,
										   std::shared_ptr<IOrderStorage>& orderStorage_parentModule,
										   std::shared_ptr<IInternalOrdersCourier>& internalOrdersCourier)

{
	_externalModulesManager = externalModulesManager;
	_orderStorage_Middleware = orderStorage_middleware;
	_orderStorage_ParentModule = orderStorage_parentModule;
	_internalOrdersCourier = internalOrdersCourier;

	_isProcessingOrders = false;
}

OrderDistributionHub::~OrderDistributionHub()
{
	Stop(); 
}

bool OrderDistributionHub::Run()
{
	_isProcessingOrders = true;

	_processingThread = std::thread(&OrderDistributionHub::distributeOrders, this);

	return true;
}

bool OrderDistributionHub::Stop()
{
	_isProcessingOrders = false;

	if (_processingThread.joinable())
	{
		_processingThread.join(); 
	}
	
	return true;
}

void OrderDistributionHub::distributeOrders()
{
	while (_isProcessingOrders)
	{
		std::queue<std::string> orders = collectReceivedOrders();

		while (!orders.empty())
		{
			processOrder(orders.front());

			orders.pop();
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(100)); 
	}
}

std::queue<std::string> OrderDistributionHub::collectReceivedOrders()
{
	std::queue<std::string> orders = _orderStorage_Middleware->GetOrders();

	return orders;
}

bool OrderDistributionHub::processOrder(std::string& order)
{
	Order decodedOrder = OrderDecoder::DecodeOrder(order);

	if (decodedOrder.RecipientModule == _orderStorage_Middleware->GetStorageName())
	{
		if(!postInternalOrder(decodedOrder))
		{
			return false;
		}
	}
	else
	{
		if (!postExternalOrder(order, decodedOrder.RecipientModule))
		{
			return false;
		}
	}

	return true;

}

bool OrderDistributionHub::postExternalOrder(std::string& order, std::string& recipientModule)
{
	if (recipientModule == "DeepDive")
	{
		_orderStorage_ParentModule->AddOrder(order);

	}
	else if (!_externalModulesManager->PostOrder(order, recipientModule))
	{
		return false;
	}

	return true;
}

bool OrderDistributionHub::postInternalOrder(Order& order)
{
	_internalOrdersCourier->PostOrder(order);

	return true;
}

