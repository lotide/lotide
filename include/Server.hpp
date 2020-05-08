#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>
#include <cstring>
#include <iostream>

#include "LoTide.hpp"
#include <nlohmann/json.hpp>

#ifdef _WIN32
	// #include <winsock2.h>
	// #include <Ws2tcpip.h>
	#undef UNICODE

	#define WIN32_LEAN_AND_MEAN

	#include <windows.h>
	#include <winsock2.h>
	#include <ws2tcpip.h>
	#include <stdlib.h>
	#include <stdio.h>

	// Need to link with Ws2_32.lib
	#pragma comment (lib, "Ws2_32.lib")
	// #pragma comment (lib, "Mswsock.lib")

	#define DEFAULT_BUFLEN 512
	#define DEFAULT_PORT "27015"
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
		void parseExecute(std::string command, std::vector<std::string> params);
		void initializeLoTide();
	private:
		int mPort;
		unsigned int new_socket;
		unsigned int valread;
		unsigned int server_fd;
		unsigned client_socket;
		unsigned listen_socket;
		struct sockaddr_in address;
		int opt = 1;
		int addrlen = sizeof(address);
		nlohmann::json j;
		#ifdef _WIN32
			WSADATA wsaData;
			int iResult;
		#endif
		LoTide lt;
		std::string songState;
		unsigned activeSynthId = 0;
		std::string activeInstanceGroup;
		unsigned phraseIncrement = 0;
		unsigned activePhraseId = 0;
	};
}

#endif
