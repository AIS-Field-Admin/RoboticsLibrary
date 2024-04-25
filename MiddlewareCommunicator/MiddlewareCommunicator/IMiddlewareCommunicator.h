#pragma once

#ifndef IMIDDLEWARECOMMUNICATOR_H
#define IMIDDLEWARECOMMUNICATOR_H

#include "pch.h"
#include <iostream>
#include <queue>

#include "..\OrderHandler\OrderHandler.h"
#include "..\OrderStore\IOrderReception.h"
#include "..\OrderStore\IOrderStorage.h"
#include "..\ExternalModuleCommunicator\ExternalModuleCommunicator.h"

#include "..\OrderStore\OrderStorage.h"


class IMiddlewareCommunicator
{
public:

	virtual ~IMiddlewareCommunicator() = default;

	virtual bool Construct(std::string middlewareName,
						   std::vector<std::shared_ptr<OrderHandler>>& orderHandlers,
						   std::vector<std::shared_ptr<IExternalModuleCommunicator>>& externalModuleCommunicators,
						   std::shared_ptr<IOrderReception> orderReception,
		                   std::shared_ptr<IOrderStorage> orderStorage_ParentModule) = 0;

	virtual bool SetOrder(std::string order) = 0;

	virtual std::queue<std::string> GetOrders() = 0;

	virtual bool Start() = 0;

};

#endif // IMIDDLEWARECOMMUNICATOR_H
