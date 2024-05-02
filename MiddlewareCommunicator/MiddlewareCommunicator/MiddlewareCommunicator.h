#pragma once

#ifndef MIDDLEWARECOMMUNICATOR_H
#define MIDDLEWARECOMMUNICATOR_H

#include "pch.h"

#include <iostream>
#include <queue>

#include "IMiddlewareCommunicator.h"
#include "MainManager.h"


class MiddlewareCommunicator : public IMiddlewareCommunicator
{
	public:

		MiddlewareCommunicator();

		bool Construct(std::string middlewareName,
					   std::vector<std::shared_ptr<OrderHandler>>& orderHandlers,
					   std::vector<std::shared_ptr<IExternalModuleCommunicator>>& externalModuleCommunicators,
					   std::shared_ptr<IOrderReception> orderReception,
			           std::shared_ptr<IOrderStorage> orderStorage_ParentModule) override;

		bool SetOrder(std::string order) override;

		std::queue<std::string> GetOrders() override;

		bool Start() override;

	private:

		std::shared_ptr<MainManager> _mainManager;

		bool _isStarted = false;

};

#endif //MIDDLEWARECOMMUNICATOR_H

