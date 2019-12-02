#ifndef CLI_HPP
#define CLI_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <regex>

#include "LoTide.hpp"

class Cli {
public:
    int launch();
private:
    int parseCommand(std::string);
};

#endif
