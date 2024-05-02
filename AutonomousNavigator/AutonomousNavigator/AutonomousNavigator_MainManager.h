#pragma once

#include <iostream>
#include <thread>


#include "IAutonomousNavigator.h"

#include "NavigatorSettingsReader.h"
#include "PositionalStateManager.h"
#include "NavigationManager.h"

class AutonomousNavigator_MainManager : public IAutonomousNavigator
{
	public:

		AutonomousNavigator_MainManager();
		~AutonomousNavigator_MainManager();

		bool SetExternalBoundaries(std::shared_ptr<IVehicleCommunicationCommandExecutor> vehicleBoundary,
								   std::shared_ptr<IPositionalStateProvider_2D> positionalStateProviderBoundary
								   ) override;

		bool Initialise() override;

		bool SetStartingPosition(double position_mm_x, double position_mm_y) override;
		bool SetStartingAngle(double angle) override;

		bool StartUpdatingStates() override;
		bool StopUpdatingStates() override;
		
		bool Navigate(double target_x, double target_y) override;

		bool IsNavigationCompleted() override;
		std::string GetNavigationStatus() override;

	private:

		std::shared_ptr<IPositionalStateManager> _positionalStateManager;
		std::shared_ptr<NavigationManager> _navigationManager;

		std::shared_ptr<IVehicleCommunicationCommandExecutor> _vehicleBoundary;
		std::shared_ptr<IPositionalStateProvider_2D> _positionalStateProviderBoundary;

		std::atomic<bool> _isInitialised = false;
		bool _isSettingsRead = false;

		std::thread _stateProviderThread;
		std::atomic<bool> _isUpdatingStates = false;

		bool isInitialisable();
		bool isPositionalStateManagerConstructed();

		void runStateUpdateLoop();
};

