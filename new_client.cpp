#include <iostream>
#include <windows.h>
#include <string>
#include "new_calc_new_client.h"

int main(){
	std::cout<<"Hello"<<"\n";
	sockaddr_in service;
	service.sin_family = AF_INET;
	service.sin_addr.s_addr = inet_addr("127.0.0.1");
	service.sin_port = htons(44444);
	char recvbuf[512];
    int recvbuflen = 512;
	WSADATA wsaData;
	std::string var= GetInputFromConsole();
	//sanitize user input
	
	
    if (int startup = WSAStartup(MAKEWORD(2,2), &wsaData); startup != NO_ERROR) {
      std::cout<<"startup error:"<< startup<<"\n";
      return 1;
    }

	else if (SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); sock == INVALID_SOCKET){
		std::cout<<"socket creation error:" << WSAGetLastError()<<"\n";
		return 1;
	}
	else if (int connecting = connect(sock, (SOCKADDR *) &service, sizeof (service)); connecting == SOCKET_ERROR) {
		std::cout<<"connect error:"<< WSAGetLastError()<<"\n";
		closesocket(sock);
		WSACleanup();
		return 1;
	}
	else if (int sending = send( sock, var.data(), var.length(), 0 );sending == SOCKET_ERROR){
		std::cout<<"Send error:"<< WSAGetLastError()<<"\n";
		closesocket(sock);
		WSACleanup();
		return 1;	
	}
    else if (int shut = shutdown(sock, 1); shut == SOCKET_ERROR){
		std::cout<<"Shut error:"<< WSAGetLastError()<<"\n";
		closesocket(sock);
		WSACleanup();
		return 1;	
	}
	else{
		int receive;
		do {
			receive = recv(sock, recvbuf, recvbuflen, 0);
			if ( receive > 0 ){
				std::cout<<"reveive num:"<< receive<<"\n"; 
				for(int i=0; i<receive; i++){
					std::cout<<recvbuf[i];
				}
				std::cout<<"\n";
			}
			else if ( receive == 0 ){
				std::cout<<"receive num:"<< receive<<"\n";
			}
			else{
			   std::cout<<"receive error:"<< WSAGetLastError()<<"\n";		   
			}
		} while( receive > 0 );
		closesocket(sock);
		WSACleanup();
		std::cout<<"sending result:"<<sending<<"\n";
	}
    return 0;
}
