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

        bool Connect(std::string ip, std::string port = "NoPort") override;
        void Disconnect() override;
        void ReadBytes(int DBNumber, int StartByteAdr, int Size, void* Buffer) override;
        void WriteBytes(int DBNumber, int StartByteAdr, int Size, void* Buffer) override;
        void WriteBit(int DBNumber, int ByteAdr, int BitAdr, bool BitValue) override;


    private:

        std::shared_ptr<TS7Client> plc;
};

#endif // S71200PLCCOM_H

