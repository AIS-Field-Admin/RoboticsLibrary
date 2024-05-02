#include "pch.h"
#include "MainManager.h"

MainManager::MainManager()
{
	
}

void MainManager::ConstructMiddleware(std::string middlewareName,
									  std::vector<std::shared_ptr<OrderHandler>>& orderHandlers,
								      std::vector<std::shared_ptr<IExternalModuleCommunicator>>& externalModuleCommunicators,
	                                  std::shared_ptr<IOrderReception> orderReception,
									  std::shared_ptr<IOrderStorage> orderStorage_ParentModule)
{
	_orderStorage_ParentModule = orderStorage_ParentModule;
	_orderStorage_Middleware = std::make_shared<OrderStorage>(middlewareName);

	_orderReception = orderReception;
	
	_orderReception->SetOrderStorages(_orderStorage_ParentModule, _orderStorage_Middleware);
	_externalModulesManager = std::make_shared<ExternalModulesManager>(_orderReception);

	_internalOrdersCourier = std::make_shared<InternalOrdersCourier>();

	registerOrderHandlers(orderHandlers);

	addExternalModuleCommunicators(externalModuleCommunicators);

	Initialise();

}
	
void MainManager::registerOrderHandlers(std::vector<std::shared_ptr<OrderHandler>>& orderHandlers)
{
	for (std::shared_ptr<OrderHandler> orderHandler : orderHandlers)
	{
		_internalOrdersCourier->RegisterOrderHandler(orderHandler);
	}
}

void MainManager::addExternalModuleCommunicators(std::vector<std::shared_ptr<IExternalModuleCommunicator>>& externalModuleCommunicators)
{
	for (std::shared_ptr<IExternalModuleCommunicator> externalModuleCommunicator : externalModuleCommunicators)
	{
		_externalModulesManager->AddModuleCommunicator(externalModuleCommunicator);
	}
}

bool MainManager::Initialise()
{
	if (!_orderReception)
	{
		std::cerr << "Error: _orderReception is nullptr. (MainManager)" << std::endl;
	}

	_externalModulesManager->InitialiseExternalModules();



	startOrderDistribution();
	
	return true;
}

void MainManager::startOrderDistribution()
{
	if (_orderDistributionHub == nullptr)
	{
		std::cout << "Created Order Distribution Hub" << std::endl;

		_orderDistributionHub = std::make_shared<OrderDistributionHub>(_externalModulesManager,
																	   _orderStorage_Middleware,
																	   _orderStorage_ParentModule,
			                                                           _internalOrdersCourier);
	}

	_orderDistributionHub->Run();

}


std::queue<std::string> MainManager::GetParentModuleOrders()
{
	return _orderStorage_ParentModule->GetOrders();
}

bool MainManager::SetOrder(std::string order)
{
	_orderReception->ProcessOrder(order);

	return true;
}

