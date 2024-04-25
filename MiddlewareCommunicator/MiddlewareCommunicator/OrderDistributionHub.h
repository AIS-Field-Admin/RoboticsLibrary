#pragma once
#include "pch.h"

#include <iostream>

#include "IExternalModulesManager.h"
#include "..\OrderStore\Order.h"
#include "..\OrderStore\OrderDecoder.h"
#include "..\OrderStore\IOrderStorage.h"
#include "IOrderDistributionHub.h"
#include "IInternalOrdersCourier.h"

class OrderDistributionHub : public IOrderDistributionHub
{
	public:

		OrderDistributionHub(std::shared_ptr<IExternalModulesManager>& externalModulesManager,
								   std::shared_ptr<IOrderStorage>& orderStorage_middleware,
			                       std::shared_ptr<IOrderStorage>& orderStorage_parentModule,
								   std::shared_ptr<IInternalOrdersCourier>& internalOrdersCourier);

		~OrderDistributionHub();

		bool Run() override;

		bool Stop() override;

	private:

		void distributeOrders();
		
		std::queue<std::string> collectReceivedOrders();
		
		bool processOrder(std::string& order);

		bool postExternalOrder(std::string& order, std::string& recipientModule);

		bool postInternalOrder(Order& order);

		std::shared_ptr<IExternalModulesManager> _externalModulesManager;
		std::shared_ptr<IOrderStorage> _orderStorage_Middleware;
		std::shared_ptr<IOrderStorage> _orderStorage_ParentModule;
		std::shared_ptr<IInternalOrdersCourier> _internalOrdersCourier;

		bool _isProcessingOrders;

		std::thread _processingThread;
};

