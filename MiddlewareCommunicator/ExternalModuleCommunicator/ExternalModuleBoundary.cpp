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
	try
	{
		_orderStorage_ExternalModule->AddOrder(order);

		return true;
	}
	catch (std::exception& ex)
	{
		std::cerr << "Exception occured while trying to add order: " << std::endl;

		std::cerr << ex.what() << std::endl;

		return false;
	}

}

std::queue<std::string> ExternalModuleBoundary::GetOrders()
{
	try
	{
		return _orderStorage_ParentModule->GetOrders();
	}
	catch (std::exception& ex)
	{
		std::cerr << "Exception occured while trying to get orders: " << std::endl;

		std::cerr << ex.what() << std::endl;

		return {};
	}

}

bool ExternalModuleBoundary::Start()
{
	// Implementation left for derived classes if needed

	return true;
}