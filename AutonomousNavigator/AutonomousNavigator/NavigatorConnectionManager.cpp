#include "pch.h"
#include "NavigatorConnectionManager.h"

NavigatorConnectionManager::NavigatorConnectionManager()
{
	_isConnected = false;
}

bool NavigatorConnectionManager::Connect()
{   
    if (_isConnected) 
    {
        std::cerr << "Already connected." << std::endl;
        return true;
    }
    
    std::string ipAddress = AutonomousNavigatorGlobals::IP_ADDRESS;
    std::string port = AutonomousNavigatorGlobals::PORT;

    if (NavigatorConnectionEstablisher::GetInstance().InitializeConnection(ipAddress, port))
    {
        _isConnected = true;
        std::cout << "Connection established successfully." << std::endl;
        return true;
    }
    else 
    {
        std::cerr << "Connection failed." << std::endl;
        return false;
    }
}

bool NavigatorConnectionManager::Disconnect()
{
    if (_isConnected) 
    {
        NavigatorConnectionEstablisher::GetInstance().Cleanup();
        _isConnected = false;
        std::cout << "Disconnected successfully." << std::endl;
    }
    return true;
}

bool NavigatorConnectionManager::IsConnected()
{
    std::cout << "IsConnected to navigator: " << _isConnected << std::endl;
	return _isConnected;
}
