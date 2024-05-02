#include "pch.h"

#include "S71200PLCCom.h"
#include <iostream>

S71200PLCCom::S71200PLCCom() 
{
    plc = std::make_shared<TS7Client>(); 

}

S71200PLCCom::~S71200PLCCom() 
{
    if (plc != nullptr) 
    {
        if (plc->Connected())
        {
            plc->Disconnect();
        }
        plc = nullptr;
    }
}

bool S71200PLCCom::Connect(std::string ip, std::string port)
{
    if (plc->Connected())
    {
        std::cout << "Already Connected." << std::endl;

        return true;
    }
    
    int result = plc->ConnectTo(ip.c_str(), 0, 1);
    if (result == 0) 
    {
        std::cout << "Connected to PLC." << std::endl;

        return true;
    }
    else 
    {
        std::cerr << "Failed to connect to PLC. Error code: " << result << std::endl;

        return false;
    }
}

void S71200PLCCom::Disconnect() 
{
    if (plc->Connected()) 
    {
        plc->Disconnect();
        std::cout << "Disconnected from PLC." << std::endl;
    }
}

void S71200PLCCom::ReadBytes(int DBNumber, int StartByteAdr, int Size, void* Buffer) 
{
    if (!plc->Connected()) 
    {
        std::cerr << "Not connected to PLC." << std::endl;
        return;
    }

    int result = plc->DBRead(DBNumber, StartByteAdr, Size, Buffer);

    if (result != 0) 
    {
        std::cerr << "Failed to read data. Error code: " << result << std::endl;
    }
}


void S71200PLCCom::WriteBytes(int DBNumber, int StartByteAdr, int Size, void* Buffer) 
{
    if (!plc->Connected()) 
    {
        std::cerr << "Not connected to PLC." << std::endl;
        return;
    }
    int result = plc->DBWrite(DBNumber, StartByteAdr, Size, Buffer);

    if (result != 0) 
    {
        std::cerr << "Failed to write data. Error code: " << result << std::endl;
    }
}

bool S71200PLCCom::ReadBit(int DBNumber, int ByteAdr, int BitAdr)
{
    if (!plc->Connected())
    {
        std::cerr << "Not connected to PLC." << std::endl;

        return false;
    }

    byte buffer;

    int result = plc->DBRead(DBNumber, ByteAdr, 1, &buffer);

    if (result != 0)
    {
        std::cerr << "Failed to read byte for bit. Error code: " << result << std::endl;

        return false;
    }

    byte mask = 1 << BitAdr;

    return (buffer & mask) != 0;
}

void S71200PLCCom::WriteBit(int DBNumber, int ByteAdr, int BitAdr, bool BitValue)
{  
    if (!plc->Connected()) 
    {
        std::cerr << "Not connected to PLC." << std::endl;
        return;
    }

    byte buffer;

    int result = plc->DBRead(DBNumber, ByteAdr, 1, &buffer);
    if (result != 0) 
    {
        std::cerr << "Failed to read byte: Error " << result << std::endl;
        return;
    }

    byte mask = 1 << BitAdr;
    if (BitValue) 
    {
        buffer |= mask;  // Set the bit
    }
    else 
    {
        buffer &= ~mask; // Clear the bit
    }

    // Write the modified byte back to the PLC
    result = plc->DBWrite(DBNumber, ByteAdr, 1, &buffer);
    if (result != 0) 
    {
        std::cerr << "Failed to write byte: Error " << result << std::endl;
    }
    else 
    {
        std::cout << "Bit write successful." << std::endl;
    }
}

