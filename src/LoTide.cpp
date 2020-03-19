#include "LoTide.hpp"
#include "Sequencer.hpp"

/*
Groups are settings for how the song is played
They are discrete
They contain all instruments and information
on what tracks those instruments play

------

Chains are an implementation which allow for 
pathing through the graph in defined ways

*/

namespace lotide {

    LoTide::LoTide() : sequencer(100) {
    }

    /*LoTide::~LoTide() {
    }*/

    void LoTide::play() {
        Song s("TempSong", songMixer);

        //songs.push_back(s);

        sequencer.setSong(s);
        sequencer.start();

        std::cout << "Length of Song: " << s.getLength() << std::endl;

        char input;
        std::cout << "Press <enter> to quit:" << std::flush;
        std::cin.get(input);

        /*tsal::PolySynth synth(&songMixer);
        songMixer.add(synth);
        synth.play(tsal::C4);
        char input;
        std::cout << "Press <enter> to quit:" << std::flush;
        std::cin.get(input);*/
    }
}