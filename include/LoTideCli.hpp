#ifndef LOTIDECLI_HPP
#define LOTIDECLI_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <regex>

#include "LoTide.hpp"

namespace lotide {
class LoTideCli {
public:
    int launch();
private:
    int parseCommand(std::string);
};

}

#endif
