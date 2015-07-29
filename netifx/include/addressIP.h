/* 
 * File:   AddressIP.h
 * Author: ciecierskij
 *
 * AddressIP contains an IPv4 Address and port number
 * 
 * Created on July 24, 2015, 6:05 PM
 */

// TODO (LowP) Introduce IPv6

#ifndef _NETWORK_ADDRESS_IP_H
#define	_NETWORK_ADDRESS_IP_H

#include "sock_util.h"
#include <iostream>

class AddressIP
{
public:
    AddressIP(char* address, uint16_t port);
    AddressIP(sockaddr_in sockAddress);

    AddressIP(const AddressIP& orig);

    virtual ~AddressIP();
    
    char* ipAddress();
    uint16_t port();
    struct sockaddr_in sockAddress();

    friend std::ostream& operator<<(std::ostream& os,
    								AddressIP& addressIP);
private:

    // IPv4 Address
    char* ipAddress_;
    // Port
    uint16_t port_;

    // The socket address structure
    struct sockaddr_in sockAddress_;
};

#endif	/* _NETWORK_ADDRESS_IP_H */

