#include "pch.h"
#include "OrderCreator.h"

OrderCreator::OrderCreator()
{
	_orderId = 0;

	_recipientName = "";

	_senderModuleName = "";
}

bool OrderCreator::ConstructOrderCreator(std::string recipientName, std::string senderName)
{
	_recipientName = recipientName;
	_senderModuleName = senderName;

	return true;
}

std::string OrderCreator::CreateOrder(std::string orderType, const std::map<std::string, std::string>& parameters)
{
	if (_recipientName == "" || _senderModuleName == "")
	{
		return "Error";
	}

	Order newOrder;

	newOrder.OrderId = _orderId;
	newOrder.SenderModule = _senderModuleName;
	newOrder.RecipientModule = _recipientName;
	newOrder.OrderType = orderType;
	newOrder.OrderParameters = OrderWrapper::PrepareOrderParameters(parameters);

	std::string orderString = OrderWrapper::SerializeOrder(newOrder);

	_orderId++;

	return orderString;
}
