#include <iostream>

#include "Cli.hpp"

namespace lotide {

LoTide lo;

// TODO: Replace with ncurses
int Cli::launch() {
    // LoTide lotide = new Lotide(filename);
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

int Cli::parseCommand(std::string s) {
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

                lo.load(command2);
            }
        }
        else if (command1 == "save") {
                if (count != 3) {
                    std::cout << "Enter file name." << std::endl;
                } else {
                    std::cout << "Saving.." \
                              << std::endl;

                    lo.save(command2);
                }
        } else if (command1 == "list") {
            std::cout << "track1\n" \
                      << "track2\n" \
                      << "track3\n" \
                      << std::endl;
        }
        else if (command1 == "track") {
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
}

}
