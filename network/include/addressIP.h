/* 
 * File:   AddressIP.h
 * Author: ciecierskij
 *
 * AddressIP contains an IPv4 Address and port number
 * 
 * Created on July 24, 2015, 6:05 PM
 */

// TODO (LP) Introduce IPv6

#ifndef ADDRESS_IP_H
#define	ADDRESS_IP_H

class AddressIP {
public:
    AddressIP(char* address, unsigned int port);
    AddressIP(const AddressIP& orig);

    virtual ~AddressIP();
    
    char* address();
    int port();
private:

    char* address_;
    unsigned int port_;
};

#endif	/* ADDRESS_IP_H */

