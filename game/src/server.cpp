#include "server.h"
#include "msg_protocol.h"

void usage(char * name)
{
	fprintf(stderr,"USAGE: %s port \n",name);
}

int main(int argc, char** argv)
{
	uint16_t port;

	if(argc != 2) {
		usage(argv[0]);
		exit(EXIT_FAILURE);
	}

	port = atoi(argv[1]);
	if(port < 0){
		usage(argv[0]);
		exit(EXIT_FAILURE);
	}

	initServer(port);

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

	count = udpSocket->ReceiveFrom(bufferRecv, CMP_BUFFER_SIZE, &addressFrom);

	std::cout << "Recevied: " << count << " bytes from:\n"
			<< *addressFrom
			<< "Message:\n"
			<< bufferRecv
			<< std::endl;

	if(snprintf(bufferSend, CMP_BUFFER_SIZE, "Hello From Server!") < 0)
		ERR("snprintf");

	count = udpSocket->SendTo(bufferSend , CMP_BUFFER_SIZE, addressFrom);

	std::cout << "Response sent" << std::endl;
}

void serverWork()
{
	SmartPrint("Starting work");

	fd_set base_rfds, rfds;
	sigset_t mask, oldmask;

	FD_ZERO(&base_rfds);

	FD_SET(udpSocket->fd(), &base_rfds);

	sigemptyset (&mask);
	sigaddset (&mask, SIGINT);
	sigprocmask (SIG_BLOCK, &mask, &oldmask);

	while(isRunning)
	{
		rfds=base_rfds;
		SmartPrint("Starting pselect", 3);
		if(pselect(udpSocket->fd()+1,&rfds,NULL,NULL,NULL,&oldmask)>0)
		{
			if(FD_ISSET(udpSocket->fd(),&rfds))
			{
				SmartPrint("Received message", 3);
				communicate();
			}
			// Console input
			else if(FD_ISSET(STDIN_FILENO, &rfds)){
				SmartPrint("Received console input");
			}
		}
		else
		{
			if(EINTR==errno) continue;
			ERR("pselect");
		}
	}

	sigprocmask (SIG_UNBLOCK, &mask, NULL);

}

void cleanUp()
{
	SmartPrint("cleanUp()");

	udpSocket->Close();

	// Wait for all children.
	//while (TEMP_FAILURE_RETRY(wait(NULL)) > 0);
}

/**********************************/
/*********** INITIATORS ***********/
/**********************************/

void initSocket(uint16_t port)
{
	SmartPrint("TODO [Windows] Init Socket Libraries");
	udpSocket = new Socket(port);

	udpSocket->Open();
}

void initSignalHandlers()
{
	SmartPrint("Initating Signal Handlers");
	if(sethandler(SIG_IGN, SIGPIPE)<0) ERR("sethandler");
}

/**
 * Used to initilize the server and all its components
 * */
void initServer(uint16_t port)
{
	isRunning = true;

	// Init socket
	initSocket(port);

	// Init signals
	initSignalHandlers();

	serverWork();

	// Clean Up
	cleanUp();

	SmartPrint("Server has terminated");
}
