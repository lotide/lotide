#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>
#include <cstring>
#include <iostream>

#include "LoTide.hpp"
#include <nlohmann/json.hpp>

#ifdef _WIN32
	#include <winsock2.h>
	#include <Ws2tcpip.h>
#else
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <stdlib.h>
	#include <unistd.h>
#endif

#define MAX_BUF_LENGTH 4096;

namespace lotide {
	class Server {
	public:
		Server(int port);
		~Server();
		void init();
		void parseExecute(std::string jsonText);
		void initializeLoTide();
	private:
		int mPort;
		unsigned int new_socket;
		unsigned int valread;
		unsigned int server_fd;

		struct sockaddr_in address;
		int opt = 1;
		int addrlen = sizeof(address);
		char buffer[4096] = {0};
		nlohmann::json j;
		#ifdef _WIN32
			WSADATA wsa_data;
		#endif
		LoTide lt;
	};
}

#endif
