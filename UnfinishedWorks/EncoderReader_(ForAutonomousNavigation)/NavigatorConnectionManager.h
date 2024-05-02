#pragma once
#include "IConnectionManager.h"
#include "AutonomousNavigatorGlobals.h"
#include "NavigatorConnectionEstablisher.h"
#include <iostream>

class NavigatorConnectionManager : public IConnectionManager
{
	public:
		
		NavigatorConnectionManager();

		bool Connect() override;
		
		bool Disconnect() override;
		
		bool IsConnected() override;
	
};

