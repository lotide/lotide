#include <iostream>
#include <regex>

#ifdef _WIN32
	#include <winsock2.h>
	#include <Ws2tcpip.h>
#else
	#include <sys/socket.h>
	#include <arpa/inet.h>
	#include <stdlib.h>
	#include <unistd.h>
	#include <cstring>
#endif

int parseCommand(std::string);
int socketStart(std::string);

int main() {
	std::cout << "Started LoTide CLI.\n" \
			  << "Enter LoTide Commands.\n" \
			  << "Type \"help\" for a list of commands.\n" \
			  << std::endl;

	for(;;) {
		std::string userInput;
		std::cout << "lotide> " << std::flush;
		std::getline(std::cin, userInput);

		if(parseCommand(userInput) == 1) {
			break;
		}
	}

	return 0;
}

int socketStart(std::string response) {
#ifdef _WIN32
	WSADATA wsa_data;
	WSAStartup(MAKEWORD(1,1), &wsa_data);
#endif


	unsigned int sock = 0, valread;
	struct sockaddr_in serv_addr;
	char buffer[1024] = {0};

	// TODO Consider AF_UNIX because it is just a file
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		perror("cannot create socket");
		return -1;
	}

	// NOTE Clear address (basically like null assignment)
	memset(&serv_addr, 0, sizeof serv_addr);

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(8198);

	inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
		perror("connect failed");
		close(sock);
		return -1;
	}

	// TODO Have to handle string length
	send(sock , response.c_str(), response.length(), 0);
	std::cout << "Message sent" << std::endl;
	std::cout << "From socketStart() this is c_str" << response.c_str() << std::endl;

	valread = recv(sock , buffer, 1024, 0);
	std::cout << buffer << std::endl;

#ifdef _WIN32
	closesocket(sock);
	WSACleanup();
#else
	shutdown(sock, SHUT_RDWR);
	close(sock);
#endif

	return 0;
}

int parseCommand(std::string s) {
	std::istringstream commandStream(s);
	int count = 0;
	std::vector<std::string> commands;

	do {
		std::string command;
		commandStream >> command;

		commands.push_back(command);

		++count;
	} while (commandStream);

	std::string command1 = commands[0];

	if(count >= 3) {
		std::regex quote("\"");
		std::string command2 = std::regex_replace(commands[1], quote, "");
	}

	if (command1 == "exit") {
		std::cout << "Exitting..." << std::endl;
		return 1;
	} else {
		if (command1 == "help") {
			std::cout << "load \"[FILEPATH]\"\t Load .lot file by path.\n" \
					  << "play \"[TRACKNAME]\"\t Play listed track.\n"     \
					  << std::endl;
		} else if (command1 == "load") {
			if (count != 3) {
				std::cout << "Enter file name." << std::endl;
			} else {
				std::cout << "Loading file.." \
						  << std::endl;
			}
		} else if (command1 == "play") {
			socketStart("{ \"command\": \"play\", \"paramaters\": \"\" }");
		// } else if (command1 == "json") {
		//	socketStart("{ \"command\": \"json\", \"paramaters\": \"\" }");
		} else if (command1 == "close") {
			socketStart("{ \"command\": \"close\", \"paramaters\": \"\" }");
			exit(EXIT_SUCCESS);
		} else if (command1 == "stop") {
			socketStart("{ \"command\": \"stop\", \"paramaters\": \"\" }");
		} else {
			std::cout << "Command \"" << command1 << "\" is not found!\n" \
					  << "Type \"help\" for a list of commands.\n"    \
					  << std::endl;
		}

		return 0;
	}
}
