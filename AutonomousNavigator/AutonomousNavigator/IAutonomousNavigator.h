#pragma once

#include "IVehicleCommunicationCommandExecutor.h"
#include "IPositionalStateProvider_2D.h"

class IAutonomousNavigator
{
	public:
		virtual bool SetExternalBoundaries(std::shared_ptr<IVehicleCommunicationCommandExecutor> vehicleBoundary,
										   std::shared_ptr<IPositionalStateProvider_2D> positionalStateProviderBoundary
										   ) = 0;

		virtual bool Initialise() = 0;

		virtual bool SetStartingPosition(double position_mm_x, double position_mm_y) = 0;
		virtual bool SetStartingAngle(double angle) = 0;

		virtual bool StartUpdatingStates() = 0;
		virtual bool StopUpdatingStates() = 0;

		virtual bool Navigate(double target_x, double target_y) = 0;

		virtual bool IsNavigationCompleted() = 0;
		virtual std::string GetNavigationStatus() = 0;
};