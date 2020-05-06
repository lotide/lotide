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
		void parseExecute(std::string command, std::vector<std::string> params);
		void initializeLoTide();
	private:
		int mPort;
		unsigned int new_socket;
		unsigned int valread;
		unsigned int server_fd;

		struct sockaddr_in address;
		int opt = 1;
		int addrlen = sizeof(address);
		nlohmann::json j;
		#ifdef _WIN32
			WSADATA wsa_data;
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
