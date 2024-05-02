#pragma once

#include "IExternalModuleBoundary.h"
#include "..\OrderStore\OrderStorage.h"

class ExternalModuleBoundary : public IExternalModuleBoundary
{
	public:

		ExternalModuleBoundary(std::string ExternalModuleOrderStorageName,
							   std::string ParentModuleOrderStorageName);

		bool SetOrder(const std::string& order) override;

		std::queue<std::string> GetOrders() override;

		bool Start() override;

	protected:

		bool _isStarted = false;

		std::shared_ptr<IOrderStorage> _orderStorage_ExternalModule;
		std::shared_ptr<IOrderStorage> _orderStorage_ParentModule;
};

