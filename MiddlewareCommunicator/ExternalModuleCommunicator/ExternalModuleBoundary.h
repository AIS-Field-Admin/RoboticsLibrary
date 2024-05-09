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

		virtual bool Start() override;

	protected:

		std::shared_ptr<IOrderStorage> _orderStorage_ExternalModule;
		std::shared_ptr<IOrderStorage> _orderStorage_ParentModule;
};

