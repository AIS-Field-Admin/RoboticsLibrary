#include "pch.h"
#include "NavigatorConnectionEstablisher.h"
#include <iostream>

NavigatorConnectionEstablisher& NavigatorConnectionEstablisher::GetInstance()
{
    static NavigatorConnectionEstablisher instance;
    
    return instance;
}
NavigatorConnectionEstablisher::NavigatorConnectionEstablisher() : _sock(INVALID_SOCKET), _result(nullptr), _ptr(nullptr) 
{
    ZeroMemory(&_hints, sizeof(_hints));
    _hints.ai_family = AF_UNSPEC;    // Both IPv4 and IPv6
    _hints.ai_socktype = SOCK_STREAM;
    _hints.ai_protocol = IPPROTO_TCP;
}

NavigatorConnectionEstablisher::~NavigatorConnectionEstablisher() 
{
    Cleanup();
}

bool NavigatorConnectionEstablisher::InitializeConnection(const std::string& ip, const std::string& port)
{
    if (!_setupWinsock()) {
        return false;
    }

    if (!_resolveServerAddress(ip, port)) {
        WSACleanup();
        return false;
    }

    if (!_attemptConnection()) {
        Cleanup();
        return false;
    }

    return true;
}

SOCKET NavigatorConnectionEstablisher::GetSocket() const
{
    return _sock;
}

bool NavigatorConnectionEstablisher::_setupWinsock() 
{
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        std::cerr << "WSAStartup failed with error: " << result << std::endl;
        return false;
    }
    return true;
}

bool NavigatorConnectionEstablisher::_resolveServerAddress(const std::string& ip, const std::string& port) 
{
    int result = getaddrinfo(ip.c_str(), port.c_str(), &_hints, &_result);
    if (result != 0) {
        std::cerr << "getaddrinfo failed with error: " << result << std::endl;
        return false;
    }
    return true;
}

bool NavigatorConnectionEstablisher::_attemptConnection() 
{
    for (_ptr = _result; _ptr != NULL; _ptr = _ptr->ai_next) {
        _sock = socket(_ptr->ai_family, _ptr->ai_socktype, _ptr->ai_protocol);
        if (_sock == INVALID_SOCKET) {
            std::cerr << "Socket creation failed with error: " << WSAGetLastError() << std::endl;
            continue;
        }

        int iResult = connect(_sock, _ptr->ai_addr, (int)_ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(_sock);
            _sock = INVALID_SOCKET;
            continue;
        }
        break;
    }

    if (_sock == INVALID_SOCKET) {
        std::cerr << "Unable to connect to server!" << std::endl;
        return false;
    }
    return true;
}

void NavigatorConnectionEstablisher::Cleanup()
{
    if (_result != nullptr) {
        freeaddrinfo(_result);
        _result = nullptr;
    }
    if (_sock != INVALID_SOCKET) {
        closesocket(_sock);
        _sock = INVALID_SOCKET;
    }
    WSACleanup();
}
