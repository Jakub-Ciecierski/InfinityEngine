#include "sockets.h"

/**
 * Creates an endpoint for communication.
 * After successfully calling this function.
 * The socket will exist in name space but will have
 * no address assigned to it.
 * 
 * For more information refer to the man page:
 *      man 2 socket
 * 
 * @param domain
 *      The communication domain. describing either local
 *      or certain IP internet protocols. The domain should be of
 *      protocol family. e.g. PF_LOCAL.
 *      see the man page for more options.
 *  
 * @param type
 *      The type of the communication: e.g.
 *      SOCK_STREAM, SOCK_DGRAM
 *      
 * @return 
 *      Socket descriptor on success.
 *      On failure -1 and errno indicating the error.
 */
int make_socket(int domain, int type){
    int sock;
    sock = socket(domain,type,0);
    if(sock < 0) ERR("socket");
    return sock;
}

/**
 * Prepares a structure for LOCAL address i.e. the name of the socket
 * 
 * @param name
 *      Name of local socket
 * @return 
 *      The LOCAL socket address structure.
 */
struct sockaddr_un make_local_address(char *name){
    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path,name,sizeof(addr.sun_path)-1);
    return addr;
}

/**
 * Prepares a structure for IPv4 INET address
 * 
 * @param address
 *      The IPv4 Address
 * @param port
 *      Port
 * @return 
 *      The INET socket address structure.
 */
struct sockaddr_in make_inet_address(char *address, uint16_t port){
    struct sockaddr_in addr;
    struct hostent *hostinfo;
    addr.sin_family = AF_INET;
    addr.sin_port = htons (port);
    hostinfo = gethostbyname(address);
    if(hostinfo == NULL)HERR("gethostbyname");
    addr.sin_addr = *(struct in_addr*) hostinfo->h_addr;
    return addr;
}

/**
 * Makes new socket, makes proper address structure,
 * binds the socket to that address and finally call listen() in 
 * order to make this socket listen for new connections.
 * 
 * @param name
 *      Name of the socket
 * @param type
 *      Type of the socket. refer to: man 2 socket
 * @param backlog
 *      Hint to the limit of outstanding connections in the socket's
 *      listen queue.
 * @return 
 */
int bind_local_socket(char *name, int type, int backlog){
    struct sockaddr_un addr;
    int socketfd;
    if(unlink(name) <0&&errno!=ENOENT) ERR("unlink");

    socketfd = make_socket(PF_UNIX,type);
    addr = make_local_address(name);

    if(bind(socketfd,(struct sockaddr*) &addr,SUN_LEN(&addr)) < 0)  
        ERR("bind");
    if(listen(socketfd, backlog) < 0) ERR("listen");
    return socketfd;
}

/**
 * 
 * Makes a socket, sets a socket option(*) using setsockopt(), 
 * binds and finally if it is a SOCK_STREAM socket, makes it a listening socket.
 * 
 * (*)  For more info refer to: man setsockopt
 *      or see the section:
 *      http://www.gnu.org/software/libc/manual/html_node/Socket-Options.html
 * 
 *      SOL_SOCKET:
 *      Use this constant as the level argument to getsockopt or setsockopt to 
 *      manipulate the socket-level options described in this section.
 * 
 *      SO_REUSEADDR:
 *      This option controls whether bind should permit reuse of local 
 *      addresses for this socket. If you enable this option, 
 *      you can actually have two sockets with the same Internet port number
 * 
 *      The value has type int; a nonzero value means "yes". 
 * 
 * @param port
 * @param type
 * @param backlog
 * @return 
 */
int bind_inet_socket(uint16_t port,int type, int backlog){
    struct sockaddr_in addr;
    int socketfd,t=1;
    socketfd = make_socket(PF_INET,type);
    memset(&addr, 0, sizeof(struct sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR,&t, sizeof(t))) 
        ERR("setsockopt");
    if(bind(socketfd,(struct sockaddr*) &addr,sizeof(addr)) < 0)  
        ERR("bind");
    if(SOCK_STREAM==type)
        if(listen(socketfd, backlog) < 0) ERR("listen");
    return socketfd;
}

/**
 * Makes a socket, makes an address structure and finally connects
 * to given socket.
 * @param name
 *      Name of the socket
 * @return 
 *      Socket descriptor
 */
int connect_local_socket(char *name){
    struct sockaddr_un addr;
    int socketfd;
    socketfd = make_socket(PF_UNIX,SOCK_STREAM);
    addr = make_local_address(name);
    if(connect(socketfd,(struct sockaddr*) &addr,SUN_LEN(&addr)) < 0){
        if(errno!=EINTR) ERR("connect");
        else { 
            fd_set wfds;
            int status;
            socklen_t size = sizeof(int);
            FD_ZERO(&wfds);
            FD_SET(socketfd, &wfds);
            if(TEMP_FAILURE_RETRY(select(socketfd+1,NULL,&wfds,NULL,NULL))<0) 
                    ERR("select");
            if(getsockopt(socketfd,SOL_SOCKET,SO_ERROR,&status,&size)<0) 
                    ERR("getsockopt");
            if(0!=status) ERR("connect");
        }
    }
    return socketfd;
}

/**
 * Makes a socket, makes an address structure and finally connects
 * to given socket.
 * @param address
 *      IPv4 Address
 * @param port
 *      Port
 * @return 
 *      The socket descriptor
 */
int connect_inet_socket(char *address, uint16_t port){
    struct sockaddr_in addr;
    int socketfd;
    socketfd = make_socket(PF_INET,SOCK_STREAM);
    addr=make_inet_address(address,port);
    if(connect(socketfd,(struct sockaddr*) &addr,sizeof(struct sockaddr_in)) < 0){
        if(errno!=EINTR) ERR("connect");
        else { 
            fd_set wfds;
            int status;
            socklen_t size = sizeof(int);
            FD_ZERO(&wfds);
            FD_SET(socketfd, &wfds);
            if(TEMP_FAILURE_RETRY(select(socketfd+1,NULL,&wfds,NULL,NULL))<0) 
                ERR("select");
            if(getsockopt(socketfd,SOL_SOCKET,SO_ERROR,&status,&size)<0) 
                ERR("getsockopt");
            if(0!=status) ERR("connect");
        }
    }
    return socketfd;
}
