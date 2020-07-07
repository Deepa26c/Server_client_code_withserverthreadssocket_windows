
#ifdef __WIN32__
#include <windows.h>

    #include <stdio.h>
    #include <winsock2.h>
    #include <ws2tcpip.h>
	#include <iphlpapi.h>
    #include <stdlib.h>

#else
  #include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#endif
#define PORT 8080 
#pragma comment(lib, "Ws2_32.lib")
   
int main(int argc, char const *argv[]) 
{ 
   int server_fd, new_socket, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[1024] = {0}; 
    char *hello = "Hello from server"; 

	typedef struct WSAData {
	WORD wVersion;
	WORD wHighVersion;
	char szDescription[WSADESCRIPTION_LEN+1];
	char szSystemStatus[WSASYS_STATUS_LEN+1];
	unsigned short iMaxSockets;
	unsigned short iMaxUdpDg;
	char FAR * lpVendorInfo;
	} WSADATA; 
    
	 WSADATA wsaData; 
     int iResult;
     iResult = WSAStartup(MAKEWORD(2, 0),&wsaData);

    if (iResult != 0)
    {
        printf("WSAStartup failed: %d\n", iResult);
        return 1;
     }
   if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        return -1; 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 

    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        perror("bind failed"); 
        return -1; 
    } 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
   /* if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } */
   
    if (listen(server_fd, 3) < 0) 
    { 
        perror("listen"); 
        return -1; 
    } 
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  
                       (socklen_t*)&addrlen))<0) 
    { 
        perror("accept"); 
        return -1; 
    } 
    valread = read( new_socket , buffer, 1024); 
    printf("%s\n",buffer ); 
    send(new_socket , hello , strlen(hello) , 0 ); 
    printf("Hello message sent\n");  
    closesocket(server_fd);
    WSACleanup();
    return 0; 
}