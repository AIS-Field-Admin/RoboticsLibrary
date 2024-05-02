#include "pch.h"
#include "AutonomousNavigator_MainManager.h"

AutonomousNavigator_MainManager::AutonomousNavigator_MainManager() 
{
	_isSettingsRead = NavigatorSettingsReader::ReadSettings("../Settings/settings.json");
}

AutonomousNavigator_MainManager::~AutonomousNavigator_MainManager()
{
	StopUpdatingStates();
}

bool AutonomousNavigator_MainManager::SetExternalBoundaries(
										std::shared_ptr<IVehicleCommunicationCommandExecutor> vehicleBoundary,
										std::shared_ptr<IPositionalStateProvider_2D> positionalStateProviderBoundary
										)
{
	_vehicleBoundary = vehicleBoundary;
	_positionalStateProviderBoundary = positionalStateProviderBoundary;
	
	return true;
}

bool AutonomousNavigator_MainManager::Initialise()
{
	if (!isInitialisable())
	{
		std::cout << "Autonomous navigator could not be initialised" << std::endl;

		return false;
	}

	_navigationManager = std::make_shared<NavigationManager>(_vehicleBoundary);
	_positionalStateManager = std::make_shared<PositionalStateManager>(_positionalStateProviderBoundary);

	StartUpdatingStates();

	_isInitialised = true;

	return true;
}

bool AutonomousNavigator_MainManager::isInitialisable()
{
	if (_vehicleBoundary == nullptr)
	{
		std::cout << "Vehicle Boundary for Autonomous Navigator is not set!" << std::endl;

		return false;
	}

	if (_positionalStateProviderBoundary == nullptr)
	{
		std::cout << "Positional State Provider Boundary for Autonomous Navigator is not set!" << std::endl;

		return false;
	}

	if (!_isSettingsRead)
	{
		std::cout << "Autonomous Navigator settings are not read!" << std::endl;

		return false;
	}

	return true;
}

bool AutonomousNavigator_MainManager::SetStartingPosition(double position_mm_x, double position_mm_y)
{
	if (!isPositionalStateManagerConstructed())
	{
		return false;
	}

	_positionalStateManager->SetStartingPositions(position_mm_x, position_mm_y);

	return true;
}

bool AutonomousNavigator_MainManager::SetStartingAngle(double angle)
{
	if (!isPositionalStateManagerConstructed())
	{
		return false;
	}

	_positionalStateManager->SetStartingAngle(angle);

	return true;
}

bool AutonomousNavigator_MainManager::isPositionalStateManagerConstructed()
{
	if (_positionalStateManager == nullptr)
	{
		std::cout << "Positional State Manager is not constructed yet" << std::endl;

		return false;
	}
	else
	{
		return true;
	}
}


bool AutonomousNavigator_MainManager::StartUpdatingStates()
{
	_stateProviderThread = std::thread(&AutonomousNavigator_MainManager::runStateUpdateLoop, this);

	return true;
}

bool AutonomousNavigator_MainManager::StopUpdatingStates()
{
	_isUpdatingStates = false;

	if (_stateProviderThread.joinable())
		_stateProviderThread.join();

	return true;
}

bool AutonomousNavigator_MainManager::Navigate(double target_x, double target_y)
{
	if (_navigationManager->IsNavigating())
	{
		std::cout << "Already Navigating" << std::endl;

		return false;
	}
	_navigationManager->Navigate(target_x, target_y);

	return true;
}

bool AutonomousNavigator_MainManager::IsNavigationCompleted()
{
	if (_navigationManager == nullptr)
	{
		std::cout << "Navigation Manager is not created" << std::endl;

		return false;
	}

	bool isCompleted = !(_navigationManager->IsNavigating());

	return isCompleted;
}

std::string AutonomousNavigator_MainManager::GetNavigationStatus()
{
	if (_navigationManager == nullptr)
	{
		std::cout << "Navigation Manager is not created" << std::endl;

		return "Not Started";
	}

	return _navigationManager->GetNavigationStatus();
}

void AutonomousNavigator_MainManager::runStateUpdateLoop()
{
	_isUpdatingStates = true;

	while (_isUpdatingStates)
	{
		_positionalStateManager->UpdateState();

		std::this_thread::sleep_for(std::chrono::milliseconds(10)); 
	}
}