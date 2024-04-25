#include "pch.h"
#include "NavigationManager.h"

NavigationManager::NavigationManager(std::shared_ptr<IVehicleCommunicationCommandExecutor> vehicleBoundary)
{
	_isNavigating = false;

	_rotationPlanner = std::make_shared<RotationPlanner>();

	_navigationSupervisor = std::make_shared<NavigationSupervisor>(_rotationPlanner, vehicleBoundary);
}

void NavigationManager::Navigate(double target_x, double target_y)
{
	_navigationThread = std::thread(std::bind(&NavigationManager::runNavigationLoop, this, target_x, target_y));
}

void NavigationManager::runNavigationLoop(double target_x, double target_y)
{
	_isNavigating = true;

	std::pair<double, std::string> rotationPlan = _rotationPlanner->CreatePlan(target_x, target_y);

	_navigationSupervisor->Rotate(rotationPlan.first, rotationPlan.second);

	while (!_navigationSupervisor->IsTargetReached())
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(5000));

	_navigationSupervisor->Navigate(target_x, target_y);

	while (!_navigationSupervisor->IsTargetReached())
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(5000));

	stopNavigationLoop();
}

void NavigationManager::stopNavigationLoop()
{
	if (_navigationThread.joinable())
	{
		_navigationThread.join();
	}

	_isNavigating = false;
}

bool NavigationManager::IsNavigating()
{
	return _isNavigating;
}

std::string NavigationManager::GetNavigationStatus()
{
	return _navigationSupervisor->GetNavigationStatus();
}