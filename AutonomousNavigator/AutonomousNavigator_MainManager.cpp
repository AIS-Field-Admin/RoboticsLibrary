#include "pch.h"
#include "AutonomousNavigator_MainManager.h"

AutonomousNavigator_MainManager::AutonomousNavigator_MainManager() 
{
	_navigatorConnectionManager = std::make_shared<NavigatorConnectionManager>();
	_navigatorStateManager = std::make_shared<NavigatorStateManager>();
	_positionalStateManager = std::make_shared<PositionalStateManager>();

	_navigatorDataReader = NavigatorDataReader();

	_isSettingsRead = NavigatorSettingsReader::ReadSettings("../Settings/settings.json");
}

AutonomousNavigator_MainManager::~AutonomousNavigator_MainManager()
{
	StopReadingSensorsAndUpdatingStates();
}

bool AutonomousNavigator_MainManager::SetNavigatorBoundaries(std::shared_ptr<IVehicleCommunicationCommandExecutor> vehicleBoundary)
{
	_vehicleBoundary = vehicleBoundary;

	return true;
}

bool AutonomousNavigator_MainManager::Initialise()
{
	if (_vehicleBoundary == nullptr)
	{
		std::cout << "Vehicle Boundary for Autonomous Navigator is not set!" << std::endl;

		return false;
	}

	if (!_isSettingsRead)
	{
		return false;
	}

	connectToSensors();

	if (!_navigatorConnectionManager->IsConnected())
	{
		return false;
	}

	NavigatorSensorConstructor::GetInstance().ConstructSensors();
	_positionalStateManager->SetEncoders(NavigatorSensorConstructor::GetInstance().GetEncoders());
	StartReadingSensorsAndUpdatingStates();

	_navigationManager = std::make_shared<NavigationManager>(_vehicleBoundary);

	_isInitialised = true;

	return true;
}

bool AutonomousNavigator_MainManager::connectToSensors()
{
	if (!_navigatorConnectionManager->Connect())
	{
		// Handle if error occurs
	}

	return true;
}

bool AutonomousNavigator_MainManager::StartReadingSensorsAndUpdatingStates()
{
	_sensorThread = std::thread(&AutonomousNavigator_MainManager::readSensorsAndUpdateStates, this);

	return true;
}

bool AutonomousNavigator_MainManager::StopReadingSensorsAndUpdatingStates()
{
	_isReadingSensors = false;

	if (_sensorThread.joinable())
		_sensorThread.join();

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

void AutonomousNavigator_MainManager::readSensorsAndUpdateStates()
{
	_isReadingSensors = true;

	while (_isReadingSensors)
	{
		const char* data = _navigatorDataReader.ReadData();  
		
		_navigatorStateManager->UpdateStates(data);
		
		_positionalStateManager->UpdateState();

		std::this_thread::sleep_for(std::chrono::milliseconds(10)); 
	}
}