#ifndef SONG_HPP
#define SONG_HPP

#include <vector>
#include <unordered_map>

#include "tsal.hpp"

#include "Phrase.hpp"
#include "Group.hpp"

namespace lotide {

    class Song {
        Song();
    public:

    private:
        std::unordered_map<tsal::PolySynth, std::vector<Phrase>> mSynths;
        std::vector<Group> groups;
    };

}

#endif
