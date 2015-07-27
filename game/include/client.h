/*
 * client.h
 *
 *  Created on: Jul 26, 2015
 *      Author: jakub
 */

#ifndef _GAME_CLIENT_H_
#define _GAME_CLIENT_H_

// Network
#include <netfx.h>

/**********************************/
/*********** VARIABLES ************/
/**********************************/

/**
 * Whether the server is running.
 */
bool isRunning;


/**
 * UDP Socket of our client
 */
Socket* updSocket;

/**
 * Address of the server
 */
AddressIP* serverAddress;

/**********************************/
/************ METHODS *************/
/**********************************/

void communicate();

void clientWork();

void cleanUp();

/**********************************/
/*********** INITIATORS ***********/
/**********************************/

/*
 * Initiates the Signal Handler
 */
void initSignalHandlers();

/**
 * Initiates connection with the Server
 */
void initConnection(char* serverIPAddress,
		uint16_t serverPort, uint16_t clientPort);

#endif /* CLIENT_H_ */
