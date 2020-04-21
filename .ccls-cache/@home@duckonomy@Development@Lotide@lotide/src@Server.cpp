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
		setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
				   sizeof(opt));

		// NOTE Clear address (basically like null assignment)
		memset(&address, 0, sizeof address);

		// TODO Consider AF_UNIX because it is just a file
		address.sin_family = AF_INET;
		address.sin_addr.s_addr = INADDR_ANY;
		address.sin_port = htons(mPort);

		// Bind to address
		if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) == -1) {
			perror("bind failed");
			close(server_fd);
			exit(EXIT_FAILURE);
		}

		// Listen to address
		if (listen(server_fd, 10) == -1) {
			perror("listen failed");
			close(server_fd);
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
			lt.play();
		} else if (command == "stop") {
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
				close(server_fd);
				exit(EXIT_FAILURE);
			}

			// LOOP should start here

			// TODO Remove this and put struct in header
			// Build Empty Object of Project State [Send State]
			std::string message = "Message from server";

			// START Procedure [Parse Commands]
			// TODO Parse JSON

			valread = recv(new_socket, buffer, 4096, 0);

			std::cout << buffer << std::endl;

			// j.push_back(buffer);
			parseExecute(buffer);

			// END Procedure

			// SEND Project State
			// FIXME Should this "state" be from LoTide
			// (i.e. a serialized LoTide object)? or internal
			send(new_socket, message.c_str(), message.length(), 0);

			// LOOP should end here

			if (shutdown(new_socket, SHUT_RDWR) == -1) {
				perror("shutdown failed");
				close(new_socket);
				close(server_fd);
				exit(EXIT_FAILURE);
			}

			close(new_socket);
		}
	}
}
