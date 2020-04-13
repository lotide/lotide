#ifndef SERVER_HPP
#define SERVER_HPP

// TODO Check for WIN32 for WinSock
#ifdef _WIN32
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
		void init();
	private:
		int mPort;
		int server_fd, new_socket, valread;
		struct sockaddr_in address;
		int opt = 1;
		int addrlen = sizeof(address);
		char buffer[1024] = {0};
	};
}

#endif
#endif
