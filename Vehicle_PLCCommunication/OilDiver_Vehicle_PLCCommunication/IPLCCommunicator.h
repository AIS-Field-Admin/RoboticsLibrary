#pragma once
#ifndef IPCLCCOMMUNICATOR_H
#define IPCLCCOMMUNICATOR_H

class IPLCCommunicator
{
	public:

		virtual void Initialize() = 0;
		virtual void Connect(std::string ip, std::string port = "NoPort") = 0;
		virtual void Disconnect() = 0;
		virtual void ReadBytes(int DBNumber, int StartByteAdr, int Count, void* Buffer) = 0;
		virtual void WriteBytes(int DBNumber, int StartByteAdr, int Size, void* Buffer) = 0;
		virtual void WriteBit(int DBNumber, int ByteAdr, int BitAdr, bool BitValue) = 0;

		int FORWARD_ADDRESS;
		int BACKWARD_ADDRESS;
		int TURN_RIGHT_ADDRESS;
		int TURN_LEFT_ADDRESS;

		int PC_DB;

		int NAVIGATION_START_BYTE_ADDRESS;

};

#endif // IPCLCCOMMUNICATOR_H