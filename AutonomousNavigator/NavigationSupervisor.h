#pragma once

#include <thread>
#include <chrono>
#include <functional>
#include <mutex>

#include "INavigationSupervisor.h"
#include "IRotationPlanner.h"
#include "IVehicleCommunicationCommandExecutor.h"
#include "PositionalState.h"
#include "AutonomousNavigatorGlobals.h"



class NavigationSupervisor : public INavigationSupervisor
{
	public:

		NavigationSupervisor(std::shared_ptr<IRotationPlanner> rotationPlanner,
							 std::shared_ptr<IVehicleCommunicationCommandExecutor> vehicleBoundary);

		bool IsTargetReached() override;

		void Rotate(double targetAngle, std::string direction) override;
		void Navigate(double target_x, double target_y) override;
		bool Stop() override;

		std::string GetNavigationStatus() override;

	private:

		std::atomic<bool> _isTargetReached;
		std::string _navigationStatus;

		std::thread _navigationThread;

		std::shared_ptr<IRotationPlanner> _rotationPlanner;
		std::shared_ptr<IVehicleCommunicationCommandExecutor> _vehicleBoundary;

		std::mutex _navigationStatusMutex;

		void runRotationFeedbackLoop(double targetAngle);
		bool sendRotationCommand(std::string direction);
		bool isRotationAngleReached(double targetAngle);

		void runNavigationFeedbackLoop(double target_x, double target_y);
		bool sendForwardCommand();
		bool isPositionReached(double target_x, double target_y);

		double calculatePositionDistance(double x_1, double y_1, double x_2, double y_2);

		void setNavigationStatus(const std::string& newString);
};

