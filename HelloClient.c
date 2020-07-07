
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
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#endif
#define PORT 8080 
#pragma comment(lib, "Ws2_32.lib")
   
int main(int argc, char const *argv[]) 
{ 
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    char *hello = "Hello from client"; 
    char buffer[1024] = {0}; 

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
	 
    if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
   /* if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } */
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 
    send(sock , hello , strlen(hello) , 0 ); 
    printf("Hello message sent\n"); 
    valread = read( sock , buffer, 1024); 
    printf("%s\n",buffer ); 
    closesocket(sock);
    WSACleanup();
    return 0; 
} 

