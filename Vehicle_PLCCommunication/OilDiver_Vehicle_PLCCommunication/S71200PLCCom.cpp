#include "pch.h"

#include "S71200PLCCom.h"
#include <iostream>

S71200PLCCom::S71200PLCCom() {
    plc = new TS7Client(); 
    definePLCAddresses();
}

S71200PLCCom::~S71200PLCCom() {
    if (plc != nullptr) {
        if (plc->Connected())
            plc->Disconnect();
        delete plc;
        plc = nullptr;
    }
}

void S71200PLCCom::Initialize() {
    // Initialization specific code if needed
}

void S71200PLCCom::Connect(std::string ip, std::string port)
{
    // Assume the IP address and rack/slot are set here for example
    int result = plc->ConnectTo(ip.c_str(), 0, 1);
    if (result == 0) {
        std::cout << "Connected to PLC." << std::endl;
    }
    else {
        std::cerr << "Failed to connect to PLC. Error code: " << result << std::endl;
    }
}

void S71200PLCCom::Disconnect() {
    if (plc->Connected()) {
        plc->Disconnect();
        std::cout << "Disconnected from PLC." << std::endl;
    }
}

void S71200PLCCom::ReadBytes(int DBNumber, int StartByteAdr, int Count, void* Buffer) {
    if (!plc->Connected()) {
        std::cerr << "Not connected to PLC." << std::endl;
        return;
    }
    int result = plc->DBRead(DBNumber, StartByteAdr, Count, Buffer);
    if (result != 0) {
        std::cerr << "Failed to read data. Error code: " << result << std::endl;
    }
}

void S71200PLCCom::WriteBytes(int DBNumber, int StartByteAdr, int Size, void* Buffer) {
    if (!plc->Connected()) {
        std::cerr << "Not connected to PLC." << std::endl;
        return;
    }
    int result = plc->DBWrite(DBNumber, StartByteAdr, Size, Buffer);
    if (result != 0) {
        std::cerr << "Failed to write data. Error code: " << result << std::endl;
    }
}

void S71200PLCCom::WriteBit(int DBNumber, int ByteAdr, int BitAdr, bool BitValue) {
    
    if (!plc->Connected()) {
        std::cerr << "Not connected to PLC." << std::endl;
        return;
    }

    byte buffer;

    int result = plc->DBRead(DBNumber, ByteAdr, 1, &buffer);
    if (result != 0) {
        std::cerr << "Failed to read byte: Error " << result << std::endl;
        return;
    }

    byte mask = 1 << BitAdr;
    if (BitValue) {
        buffer |= mask;  // Set the bit
    }
    else {
        buffer &= ~mask; // Clear the bit
    }

    // Write the modified byte back to the PLC
    result = plc->DBWrite(DBNumber, ByteAdr, 1, &buffer);
    if (result != 0) {
        std::cerr << "Failed to write byte: Error " << result << std::endl;
    }
    else {
        std::cout << "Bit write successful." << std::endl;
    }
}

void S71200PLCCom::definePLCAddresses()
{
    FORWARD_ADDRESS = 2;
    BACKWARD_ADDRESS = 3;
    TURN_RIGHT_ADDRESS = 4;
    TURN_LEFT_ADDRESS = 5;

    PC_DB = 17;

    NAVIGATION_START_BYTE_ADDRESS = 10;
}
