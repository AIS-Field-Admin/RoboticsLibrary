#pragma once
#ifndef IPCLCCOMMUNICATOR_H
#define IPCLCCOMMUNICATOR_H

class IPLCCommunicator
{
	public:

		virtual bool Connect(std::string ip, std::string port = "NoPort") = 0;
		virtual void Disconnect() = 0;

		virtual void WriteBytes(int DBNumber, int StartByteAdr, int Size, void* Buffer) = 0;
		virtual void ReadBytes(int DBNumber, int StartByteAdr, int Count, void* Buffer) = 0;

		virtual bool ReadBit(int DBNumber, int ByteAdr, int BitAdr) = 0;
		virtual bool WriteBit(int DBNumber, int ByteAdr, int BitAdr, bool BitValue) = 0;

};

#endif // IPCLCCOMMUNICATOR_H