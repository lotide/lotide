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

	void Server::parseExecute(std::string command, std::vector<std::string> params) {
		if (command == "play") {
			// Need this to increment and refresh current length according to added phrases
			lt.setGroup(activeInstanceGroup);
			lt.play();
		} else if (command == "stop") {
			lt.stop();
		} else if (command == "playNote") {
			Song& song = lt.getActiveSong();
			LTSynth& synth = song.getSynth(activeSynthId);
			synth.play(std::stod(params[0]), std::stod(params[1]));
			usleep(300000);
			synth.stop(std::stod(params[0]));
		} else if (command == "close") {
			std::cout << "Successfully Closed" << std::endl;
			exit(EXIT_SUCCESS);
		} else if (command == "addSong") {
			// FIXME No way to display active song
			lt.addSong(params[0]);
			lt.setSong(params[0]);
		} else if (command == "addSynth") {
			Song& song = lt.getActiveSong();
			LTSynth& synth = song.addSynth();
			activeSynthId = synth.getId();
		} else if (command == "addGroup") {
			Song& song = lt.getActiveSong();
			song.makeNewGroup(params[0]);
			lt.setGroup(params[0]);
		} else if (command == "addPhrase") {
			Song& song = lt.getActiveSong();
			Group& group = song.getActiveGroup();
			song.addPhrase(params[0]);
			group.addPhrase(activeSynthId, phraseIncrement);
			++phraseIncrement;
		} else if (command == "addNote") {
			Song& song = lt.getActiveSong();
			Phrase& phrase = song.getPhrase(activePhraseId);
			phrase.addNote(Note(std::stod(params[0]), std::stod(params[1]), std::stoi(params[2]), std::stoi(params[3])));
		} else if (command == "removeNote") {
			Song& song = lt.getActiveSong();
			Phrase& phrase = song.getPhrase(activePhraseId);
			phrase.removeNote(std::stod(params[0]), std::stod(params[1]));
		} else if (command == "setActivePhrase") {
			activePhraseId = std::stoul(params[0]);
		} else if (command == "setActiveGroup") {
			activeInstanceGroup = params[0];
			lt.setGroup(params[0]);
		} else if (command == "setActiveSong") {
			lt.setSong(params[0]);
		} else if (command == "setLength") {
			Song& song = lt.getActiveSong();
			Phrase& phrase = song.getPhrase(activePhraseId);
			phrase.setLength(stoi(params[0]));
		} else {
			std::cout << "Wrong input" << std::endl;
		}
	}

	// TODO Filter Message size
	void Server::init() {
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

			std::vector<unsigned char> buffer(4096);
			valread = recv(new_socket, buffer.data(), buffer.size(), 0);
			if (valread != -1) {
				buffer.resize(valread);
			} else {
				exit(1);
			}

			std::string receivedData(buffer.begin(), buffer.end());

			std::cout << receivedData << std::endl;
			auto clientJSON = nlohmann::json::parse(buffer);

			parseExecute(clientJSON["command"], clientJSON["parameters"]);
			std::cout << clientJSON["parameters"] << std::endl;

			songState = lt.serializeJSON();
			send(new_socket, songState.c_str(), songState.length(), 0);

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
