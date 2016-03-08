#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <time.h>

#define clearScreen() printf("\033[H\033[J")

void handleTCPTimeClient(int clientSocket){
	time_t rawtime;
  	struct tm * timeinfo;
  	time ( &rawtime );
  	timeinfo = localtime ( &rawtime );
    char *timeString = asctime(timeinfo);
    size_t timeStringLength = strlen(timeString);
    ssize_t numBytes = send(clientSocket,timeString, timeStringLength, 0);   
	close(clientSocket);
}

int main(){
	clearScreen();
	int serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	struct sockaddr_in serverAddress; 
	memset(&serverAddress, 0, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY); 
	serverAddress.sin_port = htons(5000);
	bind(serverSocket, (struct sockaddr*) &serverAddress, sizeof(serverAddress));
	listen(serverSocket, SOMAXCONN);
	for(;;){
		struct sockaddr_in clientAddress;
		socklen_t clientAddrLen = sizeof(clientAddress);
		int clientSocket = accept(serverSocket,(struct sockaddr*) &clientAddress, &clientAddrLen);
		char clientIP[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &clientAddress.sin_addr.s_addr, clientIP, sizeof(clientIP));
		printf("SOURCE IP   : %s \n", clientIP);
		printf("SOCKET USED : %d \n",ntohs(clientAddress.sin_port));
		printf("Date and Time\n\n");
		handleTCPTimeClient(clientSocket);
	}

	return 0;
}
