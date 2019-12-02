#ifndef LOTIDE_HPP
#define LOTIDE_HPP

#include <vector>
#include <string>
#include <iostream>

#ifndef TSF_IMPLEMENTATION
#define TSF_IMPLEMENTATION
#include "tsal.hpp"
#include "tinyxml2.h"
#include "libzippp.h"

namespace lotide {

class LoTide {
public:
    // LoTide(std::string);
    LoTide();
    // ~LoTide();
    int load(std::string);
    int save(std::string);
    void play();
    // void pause(Track);
    // void stop(Track);
    // void addC4(Track);


private:
    std::string projectName;
    std::vector<std::string> midiFiles;
    tsal::Mixer *songMixer;
};

}

#endif
#endif
