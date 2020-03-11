#ifndef LOTIDE_HPP
#define LOTIDE_HPP

#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>

#ifndef TSF_IMPLEMENTATION
#define TSF_IMPLEMENTATION
#include "tsal.hpp"
#include "Sequencer.hpp"
#include "Note.hpp"
#include "Song.hpp"

namespace lotide {

    class LoTide {
    public:
        
        LoTide();
        //~LoTide();
        int load(std::string);
        int save(std::string);
        void play();

    private:
        std::string projectName;
        std::vector<tsal::PolySynth> synths;
        std::vector<std::string> midiFiles;
        tsal::Mixer songMixer;
        Sequencer* sequencer;
        std::vector<Song> songs;
    };

}

#endif
#endif
