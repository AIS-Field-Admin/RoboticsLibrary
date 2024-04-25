#pragma once

#ifndef IEXTERNALMODULESMANAGER_H
#define IEXTERNALMODULESMANAGER_H

#include "pch.h"

#include "..\ExternalModuleCommunicator\ExternalModuleCommunicator.h"

class IExternalModulesManager
{
	public:

		virtual void InitialiseExternalModules() = 0;

		virtual bool PostOrder(std::string& order, std::string& recipientModule) = 0;

		virtual bool  AddModuleCommunicator(std::shared_ptr<IExternalModuleCommunicator> externalModuleCommunicator) = 0;

};

#endif // IEXTERNALMODULESMANAGER_H