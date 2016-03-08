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

int main (){   
        clearScreen();   
        int sock = socket(AF_INET, SOCK_STREAM,IPPROTO_TCP);
        struct sockaddr_in server_address ; 
        memset(&server_address, 0, sizeof(server_address));     
        int ip = inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr.s_addr) ;
        server_address.sin_family = AF_INET;
        server_address.sin_port = htons(5000);
        if(connect(sock, (struct sockaddr *) &server_address, sizeof(server_address))<0) 
        	exit(1);
        char buffer[BUFSIZ];
        int counter = 0; 
        ssize_t numBytes = recv(sock, buffer, BUFSIZ -1 , 0);
       	buffer[numBytes] = '\0';
        fputs(buffer, stdout);
        printf("\n");  
    	
        close(sock);  
    return 0;
}


//ss -t :informacion d elos sockets ; ps: informacion del proceso ; fuser: ver el proceso del socket
