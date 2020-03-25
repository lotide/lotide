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
        void stop();
        Song& addSong(std::string name);
        void setSong(std::string name);
        void setGroup(std::string name);
    private:
        tsal::Mixer masterMixer;
        Sequencer sequencer;
        std::vector<Song> songs;
    };

}

#endif
#endif
