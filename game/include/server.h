/*
 * server.h
 *
 *  Created on: Jul 26, 2015
 *      Author: jakub
 */

#ifndef _GAME_SERVER_H_
#define _GAME_SERVER_H_

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
* The UDP server Socket
*/
Socket* updSocket;

/**********************************/
/************ METHODS *************/
/**********************************/

/**
 * Received Message and Sends a response.
 */
void communicate();

/**
 * Starts main server work
 */
void serverWork();

/**
 * Cleans up server resources
 */
void cleanUp();

/**********************************/
/*********** INITIATORS ***********/
/**********************************/

/*
 * Initiates Socket libraries and creates our UDP socket
 */
void initSocket();

/*
 * Initiates the Signal Handler
 */
void initSignalHandlers();

/**
 * Initiates the entire server
 */
void initServer(uint16_t port);


#endif /* SERVER_H_ */
