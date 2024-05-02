#pragma once
#include "IOrderCreator.h"

class OrderCreator : public IOrderCreator
{
	public:

		OrderCreator();

		bool ConstructOrderCreator(std::string recipientName, std::string senderName) override;
		
		std::string CreateOrder(std::string orderType, const std::map<std::string, std::string>& parameters) override;
		std::string CreateOrder(std::string orderType, const std::string& parameters) override;

	private:

		int _orderId;
		std::string _senderModuleName;
		std::string _recipientName;



};

