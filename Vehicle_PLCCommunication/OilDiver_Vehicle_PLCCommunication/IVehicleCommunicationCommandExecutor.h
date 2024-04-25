#pragma once
#ifndef IVEHICLECOMMUNICATIONCOMMANDEXECUTOR_H
#define IVEHICLECOMMUNICATIONCOMMANDEXECUTOR_H

#include<iostream>
#include "IVehicleCommunicationCommandExecutor.h"

class IVehicleCommunicationCommandExecutor
{
	public:
		virtual bool Connect(std::string ip, std::string port = "NoPort") = 0;
		virtual bool Disconnect() = 0;
		virtual bool Ping() = 0;

		virtual bool Forward() = 0;
		virtual bool Backward() = 0;
		virtual bool TurnRight() = 0;
		virtual bool TurnLeft() = 0;
		virtual bool Stop() = 0;

};

#endif // IVEHICLECOMMUNICATIONCOMMANDEXECUTOR_H
