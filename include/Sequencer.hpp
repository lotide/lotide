#ifndef SEQUENCER_HPP
#define SEQUENCER_HPP

#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <chrono>
#include <thread>

#include "tsal.hpp"
#include "LoTide.hpp"

namespace lotide {

    class Sequencer {

    public:
        Sequencer(LoTide& parent);
        void addUpcoming(Note note, unsigned synthId);
        void clearAll();
        void start();
        void start(unsigned time);
        void stop();
        void findUpcomingNotes();
        void processNotes();
        void tick();
    private:
        unsigned currentTime;
        LoTide& loTide;
        bool isPlaying;
        std::unordered_map<unsigned, std::vector<Note>> playing;
    };

}

#endif
