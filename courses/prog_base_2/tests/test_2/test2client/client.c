#include"client.h"

SOCKET newSocket(){
    SOCKET recvSocket;
    recvSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(recvSocket == INVALID_SOCKET)
	{
		printf("ERROR: socket unsuccessful\r\n");
		exit(EXIT_FAILURE);
	}
	return recvSocket;
}

SOCKADDR_IN newSockAddr(const char * host_name){
     char * ip;
     struct hostent * remoteHost;
     remoteHost = gethostbyname(host_name);
     ip = inet_ntoa(*(struct in_addr *)*remoteHost->h_addr_list);
     SOCKADDR_IN recvSockAddr;
     memset(&recvSockAddr, 0, sizeof(recvSockAddr));
     recvSockAddr.sin_port=htons(PORT);
     recvSockAddr.sin_family=AF_INET;
     recvSockAddr.sin_addr.s_addr= inet_addr(ip);
     return recvSockAddr;
}

void connectToTheServer(SOCKADDR_IN recvSockAddr, SOCKET recvSocket){
    if(connect(recvSocket,(SOCKADDR*)&recvSockAddr,sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
    {
        printf("ERROR: socket could not connect\r\n");
        closesocket(recvSocket);
        WSACleanup();
        exit(EXIT_FAILURE);
    }
}

void sendRequest(SOCKET recvSocket, const char * host_name, char * content){
    char request[200];
    sprintf(request, "GET test/var/24?format=xml%s HTTP/1.1\r\nHost:%s\r\n\r\n", content, host_name);  // add Host header with host_name value
    send(recvSocket, request, strlen(request), 0);
}

void recieveResponse(SOCKET recvSocket, char * buffer, int status){
    int numrcv = 0;
    numrcv = recv(recvSocket, buffer, MAXBUFLEN, NO_FLAGS_SET);
    if (numrcv == SOCKET_ERROR)
    {
        printf("ERROR: recvfrom unsuccessful\r\n");
        status = closesocket(recvSocket);
        if(status == SOCKET_ERROR)
			printf("ERROR: closesocket unsuccessful\r\n");
        status = WSACleanup();
        if (status == SOCKET_ERROR)
			printf("ERROR: WSACleanup unsuccessful\r\n");
        exit(EXIT_FAILURE);
    }
}
