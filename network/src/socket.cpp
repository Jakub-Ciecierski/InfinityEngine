/* 
 * File:   Socket.cpp
 * Author: ciecierskij
 * 
 * Created on July 24, 2015, 5:52 PM
 */

/// HEADER
#include "socket.h"

/// INCLUDE
#include "smart_console.h"
#include "macros.h"
#include "sock_util.h"

/*********************************/
/******** CONSTRUCTORS ***********/
/*********************************/

Socket::Socket(uint16_t port)
{
	this->port_ = port;
	this->type_ = SOCK_UDP;

	SmartPrint("Creating Socket");
}

Socket::Socket(const Socket& orig)
{
}

Socket::~Socket()
{
	this->Close();
}

/*********************************/
/******* PRIVATE METHODS *********/
/*********************************/

int Socket::initSocket()
{
	SmartPrint("Initiate Socket", 2);

	return 0;
}

/*********************************/
/******* PUBLIC METHODS **********/
/*********************************/

/**
 * Binds socket to INADDR_ANY and specified port
 */
void Socket::Open()
{
	int new_flags;

	SmartPrint("Opening a Socket", 2);

	fd_ = bind_inet_udp_socket(this->port_);

	// Set the non blocking mode
	new_flags = fcntl(fd_, F_GETFL) | O_NONBLOCK;
	fcntl(fd_, F_SETFL, new_flags);
}

/**
 * Closes The socket file descriptor
 */
void Socket::Close()
{
	SmartPrint("Closing Socket", 2);
	if(TEMP_FAILURE_RETRY(close(this->fd_))<0) ERR("close");
}

int Socket::Send(char* msg, int msgSize)
{
	ERR("NOT IMPLEMENTED");
}

/**
 * Input:
 * 		- msg buffer to be sent
 * 		- msgSize the size of the buffer
 * 		- address to where to send the msg
 * Output:
 * 		- bytes sent, -1 if the other end point socket
 * 		was disconnected
 *
 */
int Socket::SendTo(char* msg, int msgSize, AddressIP* address)
{
	int count;
	sockaddr_in addr = address->sockAddress();

	while((count = sendto(fd_, msg, msgSize, 0,
						(struct sockaddr*)&addr,
						sizeof(addr))) < 0 )
	{
			// Critical Error
			if(EINTR!=errno && errno!=EPIPE && errno!=ECONNRESET)
				ERR("recvfrom:");
			// Connection lost
			if(errno==EPIPE || errno==ECONNRESET)
				return -1;
	}

	return count;
}

int Socket::SendTo(char* msg, int msgSize, sockaddr_in addr)
{
	ERR("NOT IMPLEMENTED");
}

int Socket::Receive(char* msg)
{
	ERR("NOT IMPLEMENTED");
}

/**
 * Input:
 * 		- msg buffer to be sent
 * 		- msgSize the size of the buffer
 * 		- address to where to send the msg
 * Output:
 * 		- bytes received, -1 if the other end point socket
 * 		was disconnected
 *
 */
int Socket::ReceiveFrom(char* msg, int msgSize, AddressIP* address)
{
	int count;

	sockaddr_in addr;
	socklen_t len = sizeof(struct sockaddr_in);

	while(( count = recvfrom(fd_,msg, msgSize, 0,
					(struct sockaddr*)&addr, &len)) < 0)
	{
		if(EINTR!=errno && errno!=EPIPE && errno!=ECONNRESET)
			ERR("recvfrom:");
		if(errno==EPIPE || errno==ECONNRESET)
			return -1;
	}

	address = new AddressIP(addr);

	return count;
}

/*********************************/
/****** GETTERS / SETTERS ********/
/*********************************/

uint16_t Socket::port()
{
	return this->port_;
}

int Socket::type()
{
	return this->type_;
}

int Socket::fd()
{
	return this->fd_;
}

/*********************************/
/*********** FRIENDS *************/
/*********************************/

std::ostream& operator<< (std::ostream& os, Socket& socket)
{
	std::string type;

	if(socket.type() == SOCK_UDP)
		type = "UDP";
	else if(socket.type() == SOCK_TCP)
		type = "TCP";
	else
		type = "Unknown";

	os << "Socket " << type
			<< "\n"
			<< "Port: " << socket.port()
			<< std::endl;
	return os;
}
