#ifndef S71200PLCCOM_H
#define S71200PLCCOM_H

#include <iostream>
#include "snap7.h"

#include "IPLCCommunicator.h"

class S71200PLCCom : public IPLCCommunicator
{
    public:

        S71200PLCCom();   
        ~S71200PLCCom();  

        void Initialize() override;
        void Connect(std::string ip, std::string port = "NoPort") override;
        void Disconnect() override;
        void ReadBytes(int DBNumber, int StartByteAdr, int Count, void* Buffer) override;
        void WriteBytes(int DBNumber, int StartByteAdr, int Size, void* Buffer) override;
        void WriteBit(int DBNumber, int ByteAdr, int BitAdr, bool BitValue) override;


    private:

        static TS7Client* plc;

        void definePLCAddresses();
};

#endif // S71200PLCCOM_H

