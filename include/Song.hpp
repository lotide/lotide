#ifndef SONG_HPP
#define SONG_HPP

#include <vector>
#include <unordered_map>
#include <string>

#include "tsal.hpp"

#include "Phrase.hpp"
#include "Group.hpp"

namespace lotide {

    class Song {
        
    public:
        Song(std::string name, tsal::Mixer& mixer);
        void addSynth(tsal::PolySynth&& synth);
        std::vector<unsigned> getSynthIds();

        std::unordered_map<unsigned, std::vector<Note>> getUpcoming(unsigned time);
        std::vector<tsal::PolySynth*> getSynths();
    private:
        std::string mName;
        tsal::Mixer& mMixer;
        std::unordered_map<unsigned, tsal::PolySynth> mSynths;
        std::unordered_map<unsigned, std::vector<Phrase>> mSynthPhrases;
        std::vector<Group> groups;
        Group* activeGroup;
    };

}

#endif
