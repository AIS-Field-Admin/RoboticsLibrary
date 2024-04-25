#pragma once

#include "IVehicleCommunicationCommandExecutor.h"

class IAutonomousNavigator
{
	public:
		virtual bool SetNavigatorBoundaries(std::shared_ptr<IVehicleCommunicationCommandExecutor> vehicleBoundary) = 0;

		virtual bool Initialise() = 0;

		virtual bool StartReadingSensorsAndUpdatingStates() = 0;

		virtual bool StopReadingSensorsAndUpdatingStates() = 0;

		virtual bool Navigate(double target_x, double target_y) = 0;

		virtual bool IsNavigationCompleted() = 0;

		virtual std::string GetNavigationStatus() = 0;
};