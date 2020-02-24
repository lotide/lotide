#include "LoTide.hpp"

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

// LoTide::LoTide(std::string filePath) {
//     load(filePath);
// }

LoTide::LoTide() {
    // synth = new tsal::PolySynth(&mixer);
    // tsal::Mixer mixer;
}

// LoTide::~LoTide() {
    // delete &midiFiles;
// }

// TODO: Add different file types
// TODO: Confirm load when load exists
// TODO: Compare size

void LoTide::play() {
    tsal::Mixer mixer;
    tsal::PolySynth synth(&mixer);
    mixer.add(synth);
    synth.play(tsal::C4);
    char input;
    std::cout << "Press <enter> to quit:" << std::flush;
    std::cin.get(input);
}

/* std::unordered_map<tsal::Synth, std::queue<Note>> getUpcoming(int time) { */
    
/* } */

// LoTide::pause(Track t) {

// }

// LoTide::stop (Track t) {
//     synth.stop(C4);
// }

// LoTide::addC4(Track t) {

// }

// std::string LoTide::unzipXML(std::string filePath) {


// }


} // end of namespace lotide
