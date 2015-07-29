#include "client.h"
#include "msg_protocol.h"
#include <string.h>

void usage(char * name){
	fprintf(stderr,"USAGE: %s Server_IPv4 Server_port client_port \n",name);
}

int main(int argc, char** argv) {

	uint16_t serverPort;
	uint16_t clientPort;

	if(argc!=4) {
		usage(argv[0]);
		return EXIT_FAILURE;
	}
	serverPort = atoi(argv[2]);
	clientPort = atoi(argv[3]);
	if(serverPort < 0 || clientPort < 0){
		usage(argv[0]);
		exit(EXIT_FAILURE);
	}

	initSignalHandlers();

	initConnection(argv[1], serverPort, clientPort);

	isRunning = true;

	clientWork();

	cleanUp();

	return EXIT_SUCCESS;
}

/**********************************/
/************ METHODS *************/
/**********************************/

void communicate()
{
	char bufferRecv[CMP_BUFFER_SIZE];
	char bufferSend[CMP_BUFFER_SIZE];
	int count;
	AddressIP* addressFrom = NULL;

	if(snprintf(bufferSend, CMP_BUFFER_SIZE, "Hello From Client!") < 0)
		ERR("snprintf");

	count = udpSocket->SendTo(bufferSend , CMP_BUFFER_SIZE, serverAddress);

	std::cout << "Sent: " << count << " bytes\n" << std::endl;

	count = udpSocket->ReceiveFrom(bufferRecv, CMP_BUFFER_SIZE, &addressFrom);

	std::cout << "Recevied: " << count << " bytes from:\n"
			<< *addressFrom
			<< "Message:\n"
			<< bufferRecv
			<< std::endl;
}

void clientWork()
{
	SmartPrint("Starting work");
	std::string str;

	while(isRunning)
	{
		SmartPrint("Press Enter to send msg");
		std::cin >> str;

		communicate();
	}
}

void cleanUp()
{
	udpSocket->Close();
}

/**********************************/
/*********** INITIATORS ***********/
/**********************************/

void initSignalHandlers()
{
	SmartPrint("initSignalHandlers");

	if(sethandler(SIG_IGN, SIGPIPE)<0) ERR("sethandler");
}

void initConnection(char* serverIPAddress,
		uint16_t serverPort, uint16_t clientPort)
{
	SmartPrint("initConnection");

	udpSocket = new Socket(clientPort);
	serverAddress = new AddressIP(serverIPAddress, serverPort);

	udpSocket->Open();
}
