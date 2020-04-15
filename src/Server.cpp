#ifdef _WIN32
#else

#include "Server.hpp"

namespace lotide {

	Server::Server(int port) : mPort(port) {
        // #ifdef _WIN32
            // WSAStartup(MAKEWORD(1,1), &wsa_data);
            // WSADATA wsa_data;
        // #else
        // #endif
	}

	// Server::~Server() {
        // #ifdef _WIN32
		// 	closesocket(new_socket;)
        //     WSACleanup();
        // #else
		// 	close(new_socket);
        // #endif
	// }

	// TODO Add Checks and make it C++ Style
	void Server::init() {
        #ifdef _WIN32
            WSAStartup(MAKEWORD(1,1), &wsa_data);
		#endif

		server_fd = socket(AF_INET, SOCK_STREAM, 0);
		setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

		address.sin_family = AF_INET;
		address.sin_addr.s_addr = INADDR_ANY;
		address.sin_port = htons(mPort);

		bind(server_fd, (struct sockaddr *)&address, sizeof(address));
		listen(server_fd, 3);
		new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);

		std::string message = "Message from server";

		// valread = read(new_socket , buffer, 1024);
		valread = recv(new_socket, buffer, 1024, 0);
		std::cout << buffer << std::endl;
		send(new_socket , message.c_str() , message.length() , 0 );
		std::cout << "Message sent!" << std::endl;
		printf("Message sent\n");

        #ifdef _WIN32
			closesocket(new_socket);
            WSACleanup();
        #else
			close(new_socket);
        #endif
	}
}

#endif
