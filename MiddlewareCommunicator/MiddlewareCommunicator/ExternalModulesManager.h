#pragma once
#include "pch.h"

#include <iostream>
#include <vector>

#include "IExternalModulesManager.h"

#include "..\ExternalModuleCommunicator\IExternalModuleCommunicator.h"
#include "..\OrderStore\IOrderReception.h"

class ExternalModulesManager : public IExternalModulesManager
{
	public: 

		ExternalModulesManager(std::shared_ptr<IOrderReception> orderReception) ;

		void InitialiseExternalModules() override;

		bool PostOrder(std::string& order, std::string& recipientModule) override;

		bool AddModuleCommunicator(std::shared_ptr<IExternalModuleCommunicator> externalModuleCommunicator) override;

	private:

		std::vector<std::shared_ptr<IExternalModuleCommunicator>> _externalModuleCommunicators;

		void notifyNotInitialisedModules(std::vector<std::string>& failedToIntiailiseModules);
};

