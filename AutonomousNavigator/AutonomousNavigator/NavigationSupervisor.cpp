#include "pch.h"
#include "NavigationSupervisor.h"

NavigationSupervisor::NavigationSupervisor(std::shared_ptr<IRotationPlanner> rotationPlanner,
										   std::shared_ptr<IVehicleCommunicationCommandExecutor> vehicleBoundary)
{
	_isTargetReached = false;

	setNavigationStatus("Not Started");

	_rotationPlanner = rotationPlanner;

	_vehicleBoundary = vehicleBoundary;
}

bool NavigationSupervisor::IsTargetReached()
{
	return _isTargetReached;
}

void NavigationSupervisor::Rotate(double targetAngle, std::string direction)
{
	_isTargetReached = false;

	setNavigationStatus("Rotating");

	std::this_thread::sleep_for(std::chrono::milliseconds(5000));

	std::cout << "STARTED ROTATION" << std::endl;

	if (!sendRotationCommand(direction))
	{
		std::cerr << "Problem while sending rotation command" << std::endl;

		_isTargetReached = true;

		return;
	}

	_navigationThread = std::thread(std::bind(&NavigationSupervisor::runRotationFeedbackLoop, this, targetAngle));
}

bool NavigationSupervisor::sendRotationCommand(std::string direction)
{
	if (direction == "Left")
	{
		return _vehicleBoundary->TurnLeft();
	}
	else
	{
		return _vehicleBoundary->TurnRight();
	}
}

void NavigationSupervisor::Navigate(double target_x, double target_y)
{
	_isTargetReached = false;

	setNavigationStatus("Navigating");

	std::this_thread::sleep_for(std::chrono::milliseconds(5000));

	std::cout << "STARTED NAVIGATION" << std::endl;

	if (!sendForwardCommand())
	{
		std::cerr << "Problem while sending forward command" << std::endl;

		_isTargetReached = true;

		return;
	}

	_navigationThread = std::thread(std::bind(&NavigationSupervisor::runNavigationFeedbackLoop, this, target_x, target_y));

}


bool NavigationSupervisor::sendForwardCommand()
{
	return _vehicleBoundary->Forward();
}

void NavigationSupervisor::runRotationFeedbackLoop(double targetAngle)
{
	_isTargetReached = false;

	while (!_isTargetReached)
	{
		if (isRotationAngleReached(targetAngle))
		{
			_isTargetReached = true;
		}		
	}

	setNavigationStatus("Rotation Completed");

	Stop();
}

bool NavigationSupervisor::isRotationAngleReached(double targetAngle)
{
	double currentVehicleAngle = PositionalState::GetInstance().GetAngle();
	double angleTolerence = AutonomousNavigatorGlobals::ROTATION_TOLERENCE_DEGREE;

	bool isReached = std::abs(targetAngle - currentVehicleAngle) < angleTolerence;

	return isReached;
}

void NavigationSupervisor::runNavigationFeedbackLoop(double target_x, double target_y)
{
	_isTargetReached = false;

	while (!_isTargetReached)
	{
		if (isPositionReached(target_x, target_y))
		{
			_isTargetReached = true;
		}
	}

	setNavigationStatus("Navigation Completed");

	Stop();
}

bool NavigationSupervisor::isPositionReached(double target_x, double target_y)
{
	std::pair<double, double> currentVehiclePosition = PositionalState::GetInstance().GetPosition();

	double currentVehiclePosition_x = currentVehiclePosition.first;
	double currentVehiclePosition_y = currentVehiclePosition.second;

	double distance = calculatePositionDistance(target_x, target_y, currentVehiclePosition_x, currentVehiclePosition_y);

	bool isReached = distance < AutonomousNavigatorGlobals::NAVIGATION_TOLERENCE_METERS;

	return isReached;
}

double NavigationSupervisor::calculatePositionDistance(double x_1, double y_1, double x_2, double y_2)
{
	double deltaX = x_2 - x_1;
	double deltaY = y_2 - y_1;

	return std::sqrt(deltaX * deltaX + deltaY * deltaY);
}

void NavigationSupervisor::setNavigationStatus(const std::string& newString)
{
	std::lock_guard<std::mutex> lock(_navigationStatusMutex);
	_navigationStatus = newString;
}


bool NavigationSupervisor::Stop()
{
	if (!_vehicleBoundary->Stop())
	{
		std::cerr << "COULD NOT STOPEED!!" << std::endl;
		
		return false;
	}

	if (_navigationThread.joinable())
	{
		_navigationThread.join();
	}

	_isTargetReached = true;

	return true;
}

std::string NavigationSupervisor::GetNavigationStatus()
{
	std::lock_guard<std::mutex> lock(_navigationStatusMutex);
	return _navigationStatus;
}



