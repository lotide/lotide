#include "Server.hpp"

namespace lotide {

	Server::Server(int port) : mPort(port) {
		std::cout << "Starting Server!" << std::endl;

#ifdef _WIN32
		if (WSAStartup(MAKEWORD(1,1), &wsa_data) != 0) {
			fprintf(stderr,"WSAStartup failed.\n");
			exit(1);
		}
#endif

		// Create server
		server_fd = socket(AF_INET, SOCK_STREAM, 0);
		if (server_fd == -1) {
			perror("cannot create socket");
			exit(EXIT_FAILURE);
		}

		// Don't really need
		//setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_BROADCAST, &opt,
				   //sizeof(opt));

		// NOTE Clear address (basically like null assignment)
		memset(&address, 0, sizeof address);

		// TODO Consider AF_UNIX because it is just a file
		address.sin_family = AF_INET;
		address.sin_addr.s_addr = INADDR_ANY;
		address.sin_port = htons(mPort);

		// Bind to address
		if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) == -1) {
			perror("bind failed");
#ifdef _WIN32
			closesocket(server_fd);
			WSACleanup();
#else
			close(server_fd);
#endif
			exit(EXIT_FAILURE);
		}

		// Listen to address
		if (listen(server_fd, 10) == -1) {
			perror("listen failed");
#ifdef _WIN32
			closesocket(server_fd);
			WSACleanup();
#else
			close(server_fd);
#endif
			exit(EXIT_FAILURE);
		}
	}

	Server::~Server() {
		std::cout << "Server Closed." << std::endl;

#ifdef _WIN32
		closesocket(new_socket);
		WSACleanup();
#else
		close(new_socket);
#endif
	}

	void Server::initializeLoTide() {
		int q = Sequencer::ppq;

		Song& song = lt.addSong("Song1");

		LTSynth& synth = song.addSynth();

		Group& g = song.makeNewGroup("normal");

		Phrase& p = song.addPhrase("Phrase1", synth.getId());
		p.setLength(4 * q);
		p.addNote(Note(tsal::A4, 100, 0, q/2));
		p.addNote(Note(tsal::B4, 100, q, q/2));
		p.addNote(Note(tsal::C5, 100, 2*q, q/2));
		p.addNote(Note(tsal::D5, 100, 3*q, q/2));

		Phrase& p2 = song.addPhrase("Phrase2", synth.getId());
		p2.setLength(4 * q);
		p2.addNote(Note(tsal::E5, 100, 0, q/2));
		p2.addNote(Note(tsal::D5, 100, q, q/2));
		p2.addNote(Note(tsal::F5, 100, 2 * q, q/2));
		p2.addNote(Note(tsal::E5, 100, 3 * q, q/2));

		g.addPhrase(0, 0);
		g.addPhrase(0, 1);

		lt.setSong("Song1");
		lt.setGroup("normal");
	}

	// Understand states for this project
	void Server::parseExecute(std::string command) {
		if (command == "play") {
			std::string things = "what";
			lt.play();
		} else if (command == "stop") {
			std::string things = "what";
			lt.stop();
		} else if (command == "close") {
			std::cout << "Successfully Closed" << std::endl;
			exit(EXIT_SUCCESS);
		}
	}

	// TODO Filter Message size
	void Server::init() {
		initializeLoTide();
		for (;;) {
			// Open socket to connection [BLOCKING]
			new_socket = accept(server_fd, (struct sockaddr *)&address,
								(socklen_t *)&addrlen);

			if (0 > new_socket) {
				perror("accept failed");
#ifdef _WIN32
				closesocket(server_fd);
				WSACleanup();
#else
				close(server_fd);
#endif
				exit(EXIT_FAILURE);
			}

			// LOOP should start here

			// TODO Remove this and put struct in header
			// Build Empty Object of Project State [Send State]
			// std::string message = "Message from server";

			// START Procedure [Parse Commands]
			// FIXME when buffer is 4 char (For command) ends with two brackets
			valread = recv(new_socket, buffer, sizeof(buffer), 0);

			auto clientJSON = nlohmann::json::parse(buffer);

			// std::cout << "Client: " << clientJSON.dump() << std::endl;

			parseExecute(clientJSON["command"]);

			// END Procedure
			songState = lt.serializeJSON();

			// SEND Project State
			// FIXME Should this "state" be from LoTide
			// (i.e. a serialized LoTide object)? or internal
			send(new_socket, songState.c_str(), songState.length(), 0);
			// send(new_socket, message.c_str(), message.length(), 0);

#ifdef _WIN32
			if (shutdown(new_socket, SD_BOTH)) {
#else
			if (shutdown(new_socket, SHUT_RDWR) == -1) {
#endif
				perror("shutdown failed");
#ifdef _WIN32
				closesocket(new_socket);
				WSACleanup();
#else
				close(new_socket);
#endif
				exit(EXIT_FAILURE);
			}

#ifdef _WIN32
			closesocket(new_socket);
			WSACleanup();
#else
			close(new_socket);
#endif
		}
	}
}
