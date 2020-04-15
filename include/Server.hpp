#ifndef SERVER_HPP
#define SERVER_HPP

// TODO Check for WIN32 for WinSock
#ifdef _WIN32
  #ifndef _WIN32_WINNT
    #define _WIN32_WINNT 0x0501 /* For Windows XP. */
  #endif
  #include <winsock2.h>
  #include <Ws2tcpip.h>
#else

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>

#include <string>
#include <iostream>

#include "LoTide.hpp"

namespace lotide {
	class Server {
	public:
		Server(int port);
		// ~Server();
		void init();
	private:
		int mPort;
		unsigned int new_socket;
		int server_fd, valread;
		struct sockaddr_in address;
		int opt = 1;
		int addrlen = sizeof(address);
		char buffer[1024] = {0};
        #ifdef _WIN32
            WSADATA wsa_data;
		#endif
	};
}

#endif
#endif
