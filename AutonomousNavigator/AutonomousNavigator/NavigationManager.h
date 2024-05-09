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
		~NavigationManager();

		void Navigate(double target_x, double target_y);
		void StopNavigationLoop();

		bool IsNavigating();

		std::string GetNavigationStatus();

	private:

		std::atomic<bool> _isNavigating;
		std::atomic<bool> _stopRequested;

		std::shared_ptr<IRotationPlanner> _rotationPlanner;
		std::shared_ptr<INavigationSupervisor> _navigationSupervisor;

		std::thread _navigationThread;
		std::mutex _navigationMutex;

		void runNavigationLoop(double target_x, double target_y);

		void rotateToTarget(double targetAngle, const std::string& rotationDirection);
		void navigateToTarget(double target_x, double target_y);
		void checkStopAndSleep(int milliseconds);

};

