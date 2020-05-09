#include "Server.hpp"

namespace lotide {

	Server::Server(int port) : mPort(port) {
		std::cout << "Starting Server!" << std::endl;

#ifdef _WIN32
		if (WSAStartup(MAKEWORD(1,1), &wsaData) != 0) {
			std::cerr << "WSAStartup failed." << std::endl;
			exit(EXIT_FAILURE);
		}
#endif

#ifdef WIN32
		// Initialize Winsock
		WSAData wsaData;
		iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
		if (iResult != 0) {
			std::cout << "WSAStartup failed: " << iResult << std::endl;
			return;
		}
#endif
		// Create server
		listen_socket = socket(AF_INET, SOCK_STREAM, 0);
		if (listen_socket == -1) {
			std::cerr << "Cannot create socket." << std::endl;
			exit(EXIT_FAILURE);
		}

		// NOTE Clear address (basically like null assignment)
		memset(&address, 0, sizeof address);

		// TODO Consider AF_UNIX because it is just a file
		address.sin_family = AF_INET;
		address.sin_addr.s_addr = INADDR_ANY;
		address.sin_port = htons(mPort);

#ifdef WIN32
		// Initialize Winsock
		iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
		if (iResult != 0) {
			std::cout << "WSAStartup failed: " << iResult << std::endl;
			return;
		}
#endif
		// Bind to address
		if (bind(listen_socket, (struct sockaddr *)&address, sizeof(address)) == -1) {
			std::cerr << "Bind failed." << std::endl;
#ifdef _WIN32
			closesocket(listen_socket);
			WSACleanup();
#else
			close(listen_socket);
#endif
			std::cerr << "Exit failed." << std::endl;
			exit(EXIT_FAILURE);
		}

		// Listen to address
		if (listen(listen_socket, 10) == -1) {
			std::cerr << "Listen failed." << std::endl;
#ifdef _WIN32
			closesocket(listen_socket);
			WSACleanup();
#else
			close(listen_socket);
#endif
			std::cerr << "Exit failed." << std::endl;
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
			std::this_thread::sleep_for(std::chrono::microseconds(300000));
			synth.stop(std::stod(params[0]));
		} else if (command == "setAttack") {
			Song& song = lt.getActiveSong();
			LTSynth& synth = song.getSynth(activeSynthId);
			synth.getSynth().setParameter(tsal::PolySynth::ENV_ATTACK, std::stod(params[0]));
		} else if (command == "setSustain") {
			Song& song = lt.getActiveSong();
			LTSynth& synth = song.getSynth(activeSynthId);
			synth.getSynth().setParameter(tsal::PolySynth::ENV_SUSTAIN, std::stod(params[0]));
		} else if (command == "setDecay") {
			Song& song = lt.getActiveSong();
			LTSynth& synth = song.getSynth(activeSynthId);
			synth.getSynth().setParameter(tsal::PolySynth::ENV_DECAY, std::stod(params[0]));
		} else if (command == "setRelease") {
			Song& song = lt.getActiveSong();
			LTSynth& synth = song.getSynth(activeSynthId);
			synth.getSynth().setParameter(tsal::PolySynth::ENV_RELEASE, std::stod(params[0]));
		} else if (command == "setVolume") {
			Song& song = lt.getActiveSong();
			LTSynth& synth = song.getSynth(activeSynthId);
			synth.getSynth().setParameter(tsal::PolySynth::VOLUME, std::stod(params[0]));
		} else if (command == "setModulationMode") {
			Song& song = lt.getActiveSong();
			LTSynth& synth = song.getSynth(activeSynthId);
			synth.getSynth().setParameter(tsal::PolySynth::MODULATION_MODE, std::stod(params[0]));
		} else if (command == "setOSC1Mode") {
			Song& song = lt.getActiveSong();
			LTSynth& synth = song.getSynth(activeSynthId);
			synth.getSynth().setParameter(tsal::PolySynth::OSC1_MODE, std::stod(params[0]));
		} else if (command == "setOSC2Mode") {
			Song& song = lt.getActiveSong();
			LTSynth& synth = song.getSynth(activeSynthId);
			synth.getSynth().setParameter(tsal::PolySynth::OSC2_MODE, std::stod(params[0]));
		} else if (command == "setOSC2Offset") {
			Song& song = lt.getActiveSong();
			LTSynth& synth = song.getSynth(activeSynthId);
			synth.getSynth().setParameter(tsal::PolySynth::OSC2_OFFSET, std::stod(params[0]));
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
			activeInstanceGroup = params[0];
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
		} else if (command == "setActiveSynth") {
			activeSynthId = std::stoul(params[0]);
		} else if (command == "setActiveSong") {
			lt.setSong(params[0]);
		} else if (command == "setLength") {
			Song& song = lt.getActiveSong();
			Phrase& phrase = song.getPhrase(activePhraseId);
			phrase.setLength(stoi(params[0]));
		} else if (command == "load") {
			lt.load(params[0], params[1]);
		} else if (command == "setInstrumentPlay") {	// replaces instrument param[1]'s phrases in active group to whatever is in group param[0]
			lt.setInstrumentPlay(params[0], std::stoi(params[1]));
			activeInstanceGroup = "generated";
		} else if (command == "removeInstrument") {
			lt.removeInstrument(std::stoi(params[0]));
			activeInstanceGroup = "generated";
		} else if (command == "setTempo") {
			lt.setTempo(std::stoi(params[0]));
		} else {
			std::cout << "Wrong input" << std::endl;
		}
	}

	// TODO Filter Message size
	void Server::init() {
		for (;;) {
			// Open socket to connection [BLOCKING]
#ifdef WIN32
			// Initialize Winsock
			iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
			if (iResult != 0) {
				std::cout << "WSAStartup failed: " << iResult << std::endl;
				return;
		}
#endif

			client_socket = accept(listen_socket, NULL, NULL);
			// client_socket = accept(listen_socket, (struct sockaddr *)&address,
			//					(socklen_t *)&addrlen);

			if (client_socket == -1) {
#ifdef _WIN32
				std::cerr << "Accept failed with error: " << WSAGetLastError() << std::endl;
				closesocket(listen_socket);
				WSACleanup();
#else
				close(listen_socket);
#endif
				exit(EXIT_FAILURE);
			}

			// char recvbuf[4096];
			// std::vector<char> buffer(4096);

			std::vector<char> buf(4096); // create buffer with preallocated size

#ifdef WIN32
			iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
			if (iResult != 0) {
				std::cout << "WSAStartup failed: " << iResult << std::endl;
				return;
		}
#endif
			valread = recv(client_socket, &buf[0], buf.size(), 0);
			// valread = recv(client_socket, recvbuf, 4096, 0);
			buf.resize(valread);
			if (valread == -1) {
				std::cerr << "Receive failed." << std::endl;
				exit(EXIT_FAILURE);
			}

			// std::string receivedData(buffer.begin(), buffer.end());

			std::cout << buf.data() << std::endl;
			auto clientJSON = nlohmann::json::parse(buf.data());

			parseExecute(clientJSON["command"], clientJSON["parameters"]);
			std::cout << clientJSON["parameters"] << std::endl;

			songState = lt.serializeJSON();

#ifdef WIN32
			// Initialize Winsock
			iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
			if (iResult != 0) {
				std::cout << "WSAStartup failed: " << iResult << std::endl;
				return;
		}
#endif
			send(client_socket, songState.c_str(), songState.length(), 0);

#ifdef _WIN32
			if (shutdown(client_socket, SD_BOTH)) {
#else
			if (shutdown(client_socket, SHUT_RDWR) == -1) {
#endif
				std::cerr << "Shutdown failed." << std::endl;
#ifdef _WIN32
				closesocket(client_socket);
				WSACleanup();
#else
				close(client_socket);
#endif
				std::cerr << "Close failed." << std::endl;
				exit(EXIT_FAILURE);
			}

#ifdef _WIN32
			closesocket(client_socket);
			WSACleanup();
#else
			close(client_socket);
#endif
		}
	}
}
