#include "pch.h"
#include "ExternalModulesManager.h"

ExternalModulesManager::ExternalModulesManager(std::shared_ptr<IOrderReception> orderReception)
{
	
}

void ExternalModulesManager::InitialiseExternalModules()
{
	std::vector<std::string> failedToIntialiseCommunicators = {};

	for (std::shared_ptr<IExternalModuleCommunicator> externalModuleCommunicator : _externalModuleCommunicators)
	{
		if (!externalModuleCommunicator->InitialiseModule())
		{
			failedToIntialiseCommunicators.push_back(externalModuleCommunicator->GetCommunicatorName());
		}
	}
	
	if (failedToIntialiseCommunicators.size() != 0)
	{
		notifyNotInitialisedModules(failedToIntialiseCommunicators);
	}
}

void ExternalModulesManager::notifyNotInitialisedModules(std::vector<std::string>& failedToIntiailiseModules)
{
	std::cerr << "Following external modules could not be initialised: " << std::endl;

	for (std::string moduleName : failedToIntiailiseModules)
	{
		std::cerr << moduleName << std::endl;
	}
}

bool ExternalModulesManager::AddModuleCommunicator(std::shared_ptr<IExternalModuleCommunicator> externalModuleCommunicator)
{
	_externalModuleCommunicators.push_back(externalModuleCommunicator);

	return true;
}

bool ExternalModulesManager::PostOrder(std::string& order, std::string& recipientModule)
{
	for (std::shared_ptr<IExternalModuleCommunicator> externalModuleCommunicator : _externalModuleCommunicators)
	{
		if (externalModuleCommunicator->GetCommunicatorName() == recipientModule)
		{
			externalModuleCommunicator->AddOrder(order);

			return true;
		}
	}

	return false;
}

