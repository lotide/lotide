#ifndef SEQUENCER_HPP
#define SEQUENCER_HPP

#include <string>
#include <iostream>
#include <unordered_map>
#include <queue>
#include <chrono>
#include <thread>

#include "tsal.hpp"

namespace lotide {

class Sequencer {

public:
    Sequencer(LoTide& parent);
    void addUpcoming(Note note, tsal::Synth synth);
    void clearAll();
    void start();
    void Sequencer::start(int time);
    void stop();
    void findUpcomingNotes();
    void processNotes();
private:
    int currentTime;
    LoTide loTide;
    bool isPlaying;
    std::unordered_map<tsal::Synth, std::queue<Note>> playing;

    void tick();
};

}

#endif
