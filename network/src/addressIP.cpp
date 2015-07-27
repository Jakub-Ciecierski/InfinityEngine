/* 
 * File:   AddressIP.cpp
 * Author: ciecierskij
 * 
 * Created on July 24, 2015, 6:05 PM
 */

#include "addressIP.h"
#include "sock_util.h"

AddressIP::AddressIP(char* address, uint16_t port)
{
	this->sockAddress_ = make_inet_address(address, port);

	this->ipAddress_ = address;
	this->port_ = port;
}

AddressIP::AddressIP(sockaddr_in sockAddress)
{
	this->sockAddress_ = sockAddress;

	// Get IP address
	this->ipAddress_ = get_ip_address(this->sockAddress_);
;
	// get port
	this->port_ = ntohs(this->sockAddress_.sin_port);
}

AddressIP::AddressIP(const AddressIP& orig)
{
}

AddressIP::~AddressIP()
{
	free(ipAddress_);
}

char* AddressIP::ipAddress()
{
	return this->ipAddress_;
}

uint16_t AddressIP::port()
{
	return this->port_;
}

struct sockaddr_in AddressIP::sockAddress()
{
	return this->sockAddress_;
}

std::ostream& operator<<(std::ostream& os, AddressIP& addressIP)
{
	os << "Address: " << addressIP.ipAddress()
			<< ":" << addressIP.port()
			<< std::endl;
	return os;
}
