/* 
 * File:   Socket.h
 * Author: ciecierskij
 *
 * Encapsulates all low level socket functions
 * to create an easy to use interface.
 * 
 * Created on July 24, 2015, 5:52 PM
 */

// TODO UDP vs TCP

#ifndef _NETWORK_SOCKET_H
#define	_NETWORK_SOCKET_H

#include "addressIP.h"
#include <iostream>

// The Socket Types
#define SOCK_UDP 0
#define SOCK_TCP 1

class Socket {
public:
    Socket(uint16_t port);
    Socket(const Socket& orig);
    
    virtual ~Socket();
    
    void Open();
    void Close();
    
    int Send(char* msg, int msgSize);
    int SendTo(char* msg, int msgSize, AddressIP* address);
    int SendTo(char* msg, int msgSize, sockaddr_in addr);
    int Receive(char* msg);
    int ReceiveFrom(char* msg, int msgSize, AddressIP* address);
    
    uint16_t port();
    int type();
    int fd();

    friend std::ostream& operator<<(std::ostream& os,
    								Socket& socket);

private:

    // Port of the socket
    uint16_t port_;

    // The socket File descriptor
    int fd_;

    // The socket type UDP or TCP
    int type_;

    // Initiates native socket library
    int initSocket();
};

#endif	/* NETWORK_SOCKET_H */

