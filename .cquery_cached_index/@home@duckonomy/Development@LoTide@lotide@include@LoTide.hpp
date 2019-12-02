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
     // Pass in object reference
    LoTide(std::string);
    LoTide();
    // ~LoTide();
    int load(std::string);
    int save(std::string);
    // void play(Track);
    // void pause(Track);
    // void stop(Track);
    // void addC4(Track);


private:
    std::string projectName;
    std::vector<std::string> midiFiles;
    // std::vector<std::string> sf2Files;
    // tsal::Mixer mixer;
    // tsal::PolySynth synth(tsal::Mixer);
    // tsal::MidiParser mp;

    // std::string unzip(std::string);
    // FileOperations *fo;
};

}

#endif
#endif
