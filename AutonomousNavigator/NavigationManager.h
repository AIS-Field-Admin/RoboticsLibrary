#pragma once

#include <thread>
#include <chrono>
#include <functional>

#include "RotationPlanner.h"
#include "IVehicleCommunicationCommandExecutor.h"
#include "NavigationSupervisor.h"



class NavigationManager
{
	public:
		
		NavigationManager(std::shared_ptr<IVehicleCommunicationCommandExecutor> vehicleBoundary);

		void Navigate(double target_x, double target_y);

		bool IsNavigating();

		std::string GetNavigationStatus();

	private:

		std::atomic<bool> _isNavigating;

		std::shared_ptr<IRotationPlanner> _rotationPlanner;
		std::shared_ptr<INavigationSupervisor> _navigationSupervisor;

		std::thread _navigationThread;

		void runNavigationLoop(double target_x, double target_y);
		void stopNavigationLoop();
};

