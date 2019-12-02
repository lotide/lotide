#include "LoTideServer.hpp"

namespace lotide {

LoTide loty;

Status LoTideServer::GetCommand(ServerContext* context, const Request* request,
              Response* response) {
    response->set_message(request->name());
    std::cout << request->name() << std::endl;

    /* if (request->name() == "test") { */
    /*     std::cout << "Hello\n" << std::endl; */
    /* } else { */
    /*     std::cout << "Wut\n" << std::endl; */
    /* } */
    /* if(parseCommand(request->name()) == 1) { */
    /*     return Status::OK; */
    /* } */

    return Status::OK;
}

void LoTideServer::launch() {
  std::string server_address("0.0.0.0:50051");
  LoTideServer service;

  ServerBuilder builder;
  // Listen on the given address without any authentication mechanism.
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  server->Wait();
}

// Unite with cli
int LoTideServer::parseCommand(std::string s) {
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
    std::string command2 = "";

    if(count >= 2) {
        std::regex quote("\"");
        command2 = std::regex_replace(commands[1], quote, "");
    }

    if (command1 == "exit") {
        std::cout << "Exitting..." << std::endl;
        return 1;
    } else {
        if (command1 == "help") {
            std::cout << "load \"[FILEPATH]\"\t Load .lot file by path.\n" \
                      << "list\t\t\t List tracks.\n" \
                      << "play \"[TRACKNAME]\"\t Play listed track.\n" \
                      << "pause \"[TRACKNAME]\"\t Pause listed track.\n" \
                      << "stop \"[TRACKNAME]\"\t Stop listed track.\n" \
                      << std::endl;
        } else if (command1 == "load") {
            if (count != 3) {
                std::cout << "Enter file name." << std::endl;
            } else {
                std::cout << "Loading file.." \
                          << std::endl;

                loty.load(command2);
            }
        }
        else if (command1 == "save") {
                if (count != 3) {
                    std::cout << "Enter file name." << std::endl;
                } else {
                    std::cout << "Saving.." \
                              << std::endl;

                    loty.save(command2);
                }
        } else if (command1 == "list") {
            std::cout << "track1\n" \
                      << "track2\n" \
                      << "track3\n" \
                      << "track4\n" \
                      << std::endl;
        } else if (command1 == "play") {
            loty.play();
        } else if (command1 == "track") {
            if (count != 3) {
                std::cout << "Enter track name" << std::endl;
            } else {
                std::cout << "Loading track..."   \
                          << std::endl;
            }
        } else {
            std::cout << "Command " << command1 << " is not found!\n" \
                      << "Type \"help\" for a list of commands.\n" \
                      << std::endl;
        }

        return 0;
    }

    return 1;

}

}
