#ifndef GROUP_HPP
#define GROUP_HPP

#include <vector>
#include <unordered_map>
#include <string>

#include "tsal.hpp"
#include "Phrase.hpp"

namespace lotide {

    class Group {
        Group(std::string name);
    public:

    private:
        std::string name;
        std::unordered_map<tsal::PolySynth, std::vector<unsigned>> mSynthPhrases;
        unsigned mLength;
    };

}

#endif
