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
    
    int trialCount = 10;
    int result = plc->ConnectTo(ip.c_str(), 0, 1);

    while (result != 0)
    {
        int result = plc->ConnectTo(ip.c_str(), 0, 1);

        if (result == 0)
        {
            std::cout << "Connected to PLC." << std::endl;

            return true;
        }

        trialCount++;

        if (trialCount == 10)
        {
            std::cerr << "Failed to connect to PLC. Error code: " << result << std::endl;

            return false;
        }
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

bool S71200PLCCom::WriteBit(int DBNumber, int ByteAdr, int BitAdr, bool BitValue)
{
    // Validate Bit Address Range
    if (BitAdr < 0 || BitAdr > 7) 
    {
        std::cerr << "Invalid bit address: " << BitAdr << std::endl;
        return false;
    }

    // Check PLC connection status
    if (!plc->Connected()) 
    {
        std::cerr << "Not connected to the PLC." << std::endl;
        return false;
    }

    // Initialize buffer and constants
    uint8_t buffer = 0;
    const int MaxRetries = 5;
    int readResult = 1, writeResult = 1;

    // Retry reading the byte up to MaxRetries times
    for (int attempt = 0; attempt < MaxRetries; ++attempt) 
    {
        readResult = plc->DBRead(DBNumber, ByteAdr, 1, &buffer);
        if (readResult == 0) break;  // Successful read

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        std::cerr << "Read attempt " << (attempt + 1) << " failed with error: " << readResult << std::endl;
    }

    if (readResult != 0) 
    {
        std::cerr << "Failed to read the byte after " << MaxRetries << " attempts." << std::endl;
        return false;
    }

    // Set or clear the specific bit in the buffer
    uint8_t mask = 1 << BitAdr;
    if (BitValue) 
    {
        buffer |= mask;  // Set the bit to 1
    }
    else 
    {
        buffer &= ~mask; // Clear the bit to 0
    }

    // Retry writing the byte back up to MaxRetries times
    for (int attempt = 0; attempt < MaxRetries; ++attempt) 
    {
        writeResult = plc->DBWrite(DBNumber, ByteAdr, 1, &buffer);
        if (writeResult == 0) break;  // Successful write

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        std::cerr << "Write attempt " << (attempt + 1) << " failed with error: " << writeResult << std::endl;
    }

    if (writeResult != 0) 
    {
        std::cerr << "Failed to write the byte after " << MaxRetries << " attempts." << std::endl;
        return false;
    }

    std::cout << "Bit write successful." << std::endl;
    return true;
}

