#ifndef LOTIDE_HPP
#define LOTIDE_HPP

#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>

#ifndef TSF_IMPLEMENTATION
#define TSF_IMPLEMENTATION
#include "tsal.hpp"
#include "Note.hpp"



namespace lotide {
    class Sequencer;

    class LoTide {
    public:
        
        LoTide();
        //~LoTide();
        int load(std::string);
        int save(std::string);
        void play();

        std::unordered_map<unsigned, std::vector<Note>> getUpcoming(unsigned time);
        unsigned getBPM();
        void setBPM(unsigned newVal) { bpm = newVal; }
        unsigned getStepSize();
        std::vector<tsal::PolySynth>& getAllSynths();

    private:
        unsigned bpm = 100;
        std::string projectName;
        std::vector<tsal::PolySynth> synths;
        std::vector<std::string> midiFiles;
        tsal::Mixer songMixer;

        Sequencer* sequencer;
        Song* activeSong;
    };

}

#endif
#endif
