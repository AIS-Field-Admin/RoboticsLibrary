#include "pch.h"
#include "PLCCommandExecutor.h"

PLCCommandExecutor::PLCCommandExecutor()
{
	_plcCommunicator = std::make_shared<S71200PLCCom>();
}

PLCCommandExecutor::~PLCCommandExecutor()
{
	Disconnect();

	_plcCommunicator.~shared_ptr();
}


bool PLCCommandExecutor::Connect(std::string ip, std::string port)
{
	try
	{
		_plcCommunicator->Connect(ip, port);
		return true;
	}
	catch(std::exception& ex)
	{
		std::cerr << "PLC Connection Error: " << ex.what() << std::endl;
		return false;
	}
}

bool PLCCommandExecutor::Disconnect()
{
	try
	{
		_plcCommunicator->Disconnect();
		return true;
	}
	catch (std::exception& ex)
	{
		std::cerr << "PLC Disconnect Error: " << ex.what() << std::endl;

		return false;
	}
}

bool PLCCommandExecutor::Ping()
{
	return true;
}

bool PLCCommandExecutor::Forward()
{
	_plcCommunicator->WriteBit(_plcCommunicator->PC_DB, _plcCommunicator->NAVIGATION_START_BYTE_ADDRESS, _plcCommunicator->FORWARD_ADDRESS, true);
	return true;
}

bool PLCCommandExecutor::Backward()
{
	_plcCommunicator->WriteBit(_plcCommunicator->PC_DB, _plcCommunicator->NAVIGATION_START_BYTE_ADDRESS, _plcCommunicator->BACKWARD_ADDRESS, true);

	return true;
}

bool PLCCommandExecutor::TurnRight()
{
	_plcCommunicator->WriteBit(_plcCommunicator->PC_DB, _plcCommunicator->NAVIGATION_START_BYTE_ADDRESS, _plcCommunicator->TURN_RIGHT_ADDRESS, true);

	return true;
}

bool PLCCommandExecutor::TurnLeft()
{
	_plcCommunicator->WriteBit(_plcCommunicator->PC_DB, _plcCommunicator->NAVIGATION_START_BYTE_ADDRESS, _plcCommunicator->TURN_LEFT_ADDRESS, true);

	return true;
}

bool PLCCommandExecutor::Stop()
{
	_plcCommunicator->WriteBit(_plcCommunicator->PC_DB, _plcCommunicator->NAVIGATION_START_BYTE_ADDRESS, _plcCommunicator->FORWARD_ADDRESS, false);

	_plcCommunicator->WriteBit(_plcCommunicator->PC_DB, _plcCommunicator->NAVIGATION_START_BYTE_ADDRESS, _plcCommunicator->BACKWARD_ADDRESS, false);

	_plcCommunicator->WriteBit(_plcCommunicator->PC_DB, _plcCommunicator->NAVIGATION_START_BYTE_ADDRESS, _plcCommunicator->TURN_RIGHT_ADDRESS, false);

	_plcCommunicator->WriteBit(_plcCommunicator->PC_DB, _plcCommunicator->NAVIGATION_START_BYTE_ADDRESS, _plcCommunicator->TURN_LEFT_ADDRESS, false);

	return true;
}