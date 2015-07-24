/* 
 * File:   Socket.h
 * Author: ciecierskij
 *
 * Encapsulates all low level socket functions
 * to create an easy to use interface.
 * 
 * Created on July 24, 2015, 5:52 PM
 */

#ifndef NETWORK_SOCKET_H
#define	NETWORK_SOCKET_H

#include "addressIP.h"

// The Socket Types
#define SOCK_UDP 0
#define SOCK_TCP 1

class Socket {
public:
    Socket(int sockType);
    Socket(const Socket& orig);
    
    virtual ~Socket();
    
    int Open();
    int Close();
    
    int Send(char* msg, int msgSize);
    int SendTo(char* msg, int msgSize, AddressIP address);
    int Receive(char* msg);
    int ReceiveFrom(char* msg, AddressIP address);
    
    int sockType();
private:

    int sockType_;
};

#endif	/* NETWORK_SOCKET_H */

