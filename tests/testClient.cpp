#include "LoTide.hpp"
#include "iostream"

#ifdef _WIN32
  #ifndef _WIN32_WINNT
    #define _WIN32_WINNT 0x0501 /* For Windows XP. */
  #endif
  #include <winsock2.h>
  #include <Ws2tcpip.h>
#else
	#include <sys/socket.h>
	#include <arpa/inet.h>
#endif

int main() {

	#ifdef _WIN32
        WSADATA wsa_data;
        WSAStartup(MAKEWORD(1,1), &wsa_data);
	#endif

	unsigned int sock = 0, valread;
	struct sockaddr_in serv_addr;
	char buffer[1024] = {0};

	sock = socket(AF_INET, SOCK_STREAM, 0);

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(5928);

	inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
	connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

	std::string message = "Message from client";

	send(sock , message.c_str(), message.length(), 0);
	std::cout << "Message sent" << std::endl;

	// valread = read( sock , buffer, 1024);
	valread = recv(sock, buffer, 1024, 0);
	std::cout << buffer << std::endl;

    #ifdef _WIN32
		closesocket(sock);
        WSACleanup();
    #else
		close(sock);
    #endif

	return 0;
}
