#pragma once

#include <iostream>
#include <thread>


#include "IAutonomousNavigator.h"
#include "OrderStorage.h"

#include "NavigatorSettingsReader.h"
#include "NavigatorStateManager.h"
#include "NavigatorDataReader.h"
#include "NavigatorConnectionManager.h"
#include "NavigatorSensorConstructor.h"
#include "PositionalStateManager.h"
#include "NavigationManager.h"

class AutonomousNavigator_MainManager : public IAutonomousNavigator
{
	public:

		AutonomousNavigator_MainManager();
		~AutonomousNavigator_MainManager();

		bool SetNavigatorBoundaries(std::shared_ptr<IVehicleCommunicationCommandExecutor> vehicleBoundary) override;

		bool Initialise() override;

		bool StartReadingSensorsAndUpdatingStates() override;
		
		bool StopReadingSensorsAndUpdatingStates() override;
		
		bool Navigate(double target_x, double target_y) override;

		bool IsNavigationCompleted() override;

		std::string GetNavigationStatus() override;

	private:

		std::shared_ptr<IVehicleCommunicationCommandExecutor> _vehicleBoundary;
		std::shared_ptr<IConnectionManager> _navigatorConnectionManager;
		std::shared_ptr<INavigatorStateManager> _navigatorStateManager;
		std::shared_ptr<IPositionalStateManager> _positionalStateManager;
		std::shared_ptr<NavigationManager> _navigationManager;

		NavigatorDataReader _navigatorDataReader;

		std::atomic<bool> _isInitialised = false;
		bool _isSettingsRead = false;

		std::thread _sensorThread;
		std::atomic<bool> _isReadingSensors = false;

		bool connectToSensors();
		void readSensorsAndUpdateStates();


};

