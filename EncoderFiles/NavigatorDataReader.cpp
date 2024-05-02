#include "pch.h"
#include "NavigatorDataReader.h"

NavigatorDataReader::NavigatorDataReader()
{
    _socket = NavigatorConnectionEstablisher::GetInstance().GetSocket();
}

const char* NavigatorDataReader::ReadData() 
{
    
    const int recvbuflen = AutonomousNavigatorGlobals::DEFAULT_BUFFER_LENGTH;
    char recvbuf[recvbuflen];
    int iResult;
    std::string data;

    // Receive data from the socket
    do {
        iResult = recv(_socket, recvbuf, recvbuflen, 0);
        if (iResult > 0) 
        {
            data.append(recvbuf, iResult);
        }
        else if (iResult == 0) 
        {
            std::cerr << "Connection closed\n";
            break;
        }
        else 
        {
            std::cerr << "recv failed with error: " << WSAGetLastError() << std::endl;
            break;
        }
    } while (iResult > 0);

    return data.c_str();
}