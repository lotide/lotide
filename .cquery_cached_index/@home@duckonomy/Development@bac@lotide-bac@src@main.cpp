#include <iostream>

// TEMP: Get proper argument parser
#include "cstring"

#include "Server.hpp"
#include "Cli.hpp"
#include "LoTideConfig.hpp"

int main(int argc, char *argv[])
{
    // TEMP: Handle this in argument parser
    bool verbose = true;

    // TEMP: Use better parser to get catch cases (Hard coded for now)
    if (argc < 4) {
        std::cout << "Invalid arguments\n\n"
                  << "Usage: lotide [OPTION]...\n"
                  << "OPTIONS:\n"
                  << "\t-d, --daemon\t Run the daemon.\n"
                  // << "\t-v, --verbose\t Enable verbose output.\n"
                  << std::endl;
        // TODO correct error return
        return 0;
    }

    // TEMP: Handle this is argument parser
    // TODO: gracefully terminate (inside each server/cli or here)
    if (argc == 1) { // cli
        Cli cli;
        cli.launch();
    } else { // daemon
        Server server;
        server.launch();
    }

    return 0;
}
