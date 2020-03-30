#ifndef SEQUENCER_HPP
#define SEQUENCER_HPP

#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <chrono>
#include <thread>

#include "tsal.hpp"
#include "Song.hpp"

namespace lotide {

    class Sequencer {

    public:
        const static int ppq = 8;

        Sequencer(unsigned bpm);
        void addUpcoming(Note note, unsigned synthId);
        void clearAll();
        void start();
        void start(unsigned time);
        void stop();
        void findUpcomingNotes();
        void processNotes();
        void tick();
        void setSong(Song& s);
        Song& getSong() { return *activeSong; }
    private:
        int mBpm = 90;
        int currentTime;
        Song* activeSong;
        bool isPlaying;
        std::unordered_map<unsigned, std::vector<Note>> playing;
    };

}

#endif
