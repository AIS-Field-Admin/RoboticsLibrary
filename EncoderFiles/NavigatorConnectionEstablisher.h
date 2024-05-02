// NavigatorConnectionEstablisher.h

#ifndef NAVIGATOR_CONNECTION_ESTABLISHER_H
#define NAVIGATOR_CONNECTION_ESTABLISHER_H

#include <Winsock2.h>
#include <Ws2tcpip.h>
#include <string>
#include <memory>

class NavigatorConnectionEstablisher {
public:
    static NavigatorConnectionEstablisher& GetInstance();
    NavigatorConnectionEstablisher(const NavigatorConnectionEstablisher&) = delete;
    void operator=(const NavigatorConnectionEstablisher&) = delete;

    bool InitializeConnection(const std::string& ip, const std::string& port);
    void Cleanup();
    SOCKET GetSocket() const;

private:
    NavigatorConnectionEstablisher();
    ~NavigatorConnectionEstablisher();

    SOCKET _sock;
    struct addrinfo* _result;
    struct addrinfo* _ptr;
    struct addrinfo _hints;

    bool _setupWinsock();
    bool _resolveServerAddress(const std::string& ip, const std::string& port);
    bool _attemptConnection();
};

#endif // NAVIGATOR_CONNECTION_ESTABLISHER_H