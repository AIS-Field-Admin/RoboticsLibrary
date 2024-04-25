#pragma once

#include "IVehicleCommunicationCommandExecutor.h"
#include "S71200PLCCom.h"

class PLCCommandExecutor : public IVehicleCommunicationCommandExecutor
{
	public:

		PLCCommandExecutor();
		~PLCCommandExecutor();

		bool Connect(std::string ip, std::string port = "NoPort") override;
		bool Disconnect()  override;
		bool Ping()  override;

		bool Forward()  override;
		bool Backward()  override;
		bool TurnRight()  override;
		bool TurnLeft()  override;
		bool Stop()  override;

	private:

		std::shared_ptr<IPLCCommunicator> _plcCommunicator;
};

