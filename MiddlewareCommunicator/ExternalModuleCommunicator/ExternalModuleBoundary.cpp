#include "pch.h"
#include "ExternalModuleBoundary.h"

ExternalModuleBoundary::ExternalModuleBoundary(std::string ExternalModuleOrderStorageName,
											   std::string ParentModuleOrderStorageName)
{
	_orderStorage_ExternalModule = std::make_shared<OrderStorage>(ExternalModuleOrderStorageName);
	_orderStorage_ParentModule = std::make_shared<OrderStorage>(ParentModuleOrderStorageName);
}

bool ExternalModuleBoundary::SetOrder(const std::string& order)
{
	if (!_isStarted)
	{
		return false;
	}

	_orderStorage_ExternalModule->AddOrder(order);

	return true;
}

std::queue<std::string> ExternalModuleBoundary::GetOrders()
{

	if (!_isStarted)
	{
		return {}; // Returns empty queue
	}

	return _orderStorage_ParentModule->GetOrders();
}

bool ExternalModuleBoundary::Start()
{
	_isStarted = true;

	return true;
}