#include "pch.h"
#include "NavigationManager.h"

NavigationManager::NavigationManager(std::shared_ptr<IVehicleCommunicationCommandExecutor> vehicleBoundary)
{
    _isNavigating.store(false);
    _stopRequested = false;

    _rotationPlanner = std::make_shared<RotationPlanner>();
    _navigationSupervisor = std::make_shared<NavigationSupervisor>(_rotationPlanner, vehicleBoundary);
}

NavigationManager::~NavigationManager()
{
    StopNavigationLoop();
}

void NavigationManager::Navigate(double target_x, double target_y)
{
    StopNavigationLoop(); // Ensure previous navigation stops before starting a new one
    
    {
        std::lock_guard<std::mutex> lock(_navigationMutex);

        _isNavigating = true;
    }

    _stopRequested = false; 
    _navigationThread = std::thread(&NavigationManager::runNavigationLoop, this, target_x, target_y);
}
void NavigationManager::runNavigationLoop(double target_x, double target_y)
{
    // Step 1: Rotate to the desired angle
    std::pair<double, std::string> rotationPlan = _rotationPlanner->CreatePlan(target_x, target_y);
    std::cout << "TargetAngle: " << rotationPlan.first << " " << rotationPlan.second << std::endl;

    rotateToTarget(rotationPlan.first, rotationPlan.second);

    // Step 2: Navigate to the target coordinates
    if (!_stopRequested)
    {
        navigateToTarget(target_x, target_y);
    }

    {
        std::lock_guard<std::mutex> lock(_navigationMutex);

        _isNavigating = false;
    }
}

void NavigationManager::StopNavigationLoop()
{

    _stopRequested = true; // Signal the thread to stop early

    if (_navigationThread.joinable())
    {
        _navigationThread.join(); // Wait for the thread to finish execution
    }

    std::lock_guard<std::mutex> lock(_navigationMutex);
    _isNavigating.store(false);
}

void NavigationManager::rotateToTarget(double targetAngle, const std::string& rotationDirection)
{
    _navigationSupervisor->Rotate(targetAngle, rotationDirection);

    while (!_navigationSupervisor->IsTargetReached() && !_stopRequested)
    {
        checkStopAndSleep(50);
    }

    _navigationSupervisor->Stop();
    checkStopAndSleep(5000);
}

void NavigationManager::navigateToTarget(double target_x, double target_y)
{
    _navigationSupervisor->Navigate(target_x, target_y);

    while (!_navigationSupervisor->IsTargetReached() && !_stopRequested)
    {
        checkStopAndSleep(50);
    }

    _navigationSupervisor->Stop();
    checkStopAndSleep(5000);
}

void NavigationManager::checkStopAndSleep(int milliseconds)
{
    if (!_stopRequested)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    }
}

bool NavigationManager::IsNavigating()
{
    bool isNavigating = _isNavigating.load();

    return isNavigating;
}

std::string NavigationManager::GetNavigationStatus()
{
    return _navigationSupervisor->GetNavigationStatus();
}