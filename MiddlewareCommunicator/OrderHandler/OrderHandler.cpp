#include "pch.h"
#include "OrderHandler.h"

void OrderHandler::SetOrderTypes(std::vector<std::string> orderTypes)
{
	_orderTypes = orderTypes;
}

void OrderHandler::SetOrderStorage(std::shared_ptr<IOrderStorage> orderStorage)
{
	_orderStorage = orderStorage;
}

std::vector<std::string> OrderHandler::GetOrderTypes()
{
	return _orderTypes;
}