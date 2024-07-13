#include <iostream>
#include <windows.h>
#include <print>
#include <string>
#include "new_calc_new_server.h"

int main(){
	std::println("Hello");
	sockaddr_in service;
	service.sin_family = AF_INET;
	service.sin_addr.s_addr = inet_addr("127.0.0.1");
	service.sin_port = htons(44444);
	char recvbuf[512];
    int recvbuflen = 512;
	WSADATA wsaData;
	SOCKET sock{};
	
	
		
    if (int startup = WSAStartup(MAKEWORD(2,2), &wsaData); startup != NO_ERROR) {
      std::cout<<"startup error:"<< startup<<"\n";
      return 1;
    }

	else if (sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); sock == INVALID_SOCKET){
		std::cout<<"socket creation error:" << WSAGetLastError()<<"\n";
		return 1;
	}
	else if (int binder = bind(sock, (SOCKADDR *) &service, sizeof (service)); binder == SOCKET_ERROR) {
		std::cout<<"binder error:"<< WSAGetLastError()<<"\n";
		closesocket(sock);
		WSACleanup();
		return 1;
	}
	else if (listen(sock, SOMAXCONN) == SOCKET_ERROR){
		std::cout<<"listen error:"<< WSAGetLastError()<<"\n";
		closesocket(sock);
		WSACleanup();
		return 1;	
	}
	while(true){
		if (SOCKET clientsocket= accept(sock, NULL, NULL); clientsocket== INVALID_SOCKET){
			std::cout<<"accept error:"<< WSAGetLastError()<<"\n";
			closesocket(sock);
			WSACleanup();
			return 1;	
		}

		else{
			int receive{};
			std::string res{};
			do {
				receive = recv(clientsocket, recvbuf, recvbuflen, 0);
				if ( receive > 0 ){
					std::cout<<"reveive num:"<< receive<<"\n"; 
					for(int i=0; i<receive; i++){
						std::cout<<recvbuf[i];
					}
					std::cout<<"\n";
					try{
						int result = eval(recvbuf, receive);
						res = std::to_string(result);
					}
					catch(std::exception ex){
						res = ex.what();
					}
				}
				else if ( receive == 0 ){
					std::cout<<"receive num:"<< receive<<"\n";
				}
				else{
				   std::cout<<"receive error:"<< WSAGetLastError()<<"\n";		   
				}
			} while( receive > 0 );
			
			if (int sending = send( clientsocket, res.data(), res.length(), 0 );sending == SOCKET_ERROR){
				std::cout<<"Send error:"<< WSAGetLastError()<<"\n";
				closesocket(sock);
				WSACleanup();
				closesocket(sock);
				closesocket(clientsocket);
				WSACleanup();
				return 1;	
			}
			else if (int shut = shutdown(clientsocket, 1); shut == SOCKET_ERROR){
				std::cout<<"Shut error:"<< WSAGetLastError()<<"\n";
				closesocket(sock);
				WSACleanup();
				closesocket(sock);
				closesocket(clientsocket);
				WSACleanup();
				return 1;	
			}
			closesocket(clientsocket);
		}
	}
	closesocket(sock);	
	WSACleanup();
    return 0;
	
}
