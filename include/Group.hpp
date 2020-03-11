#ifndef GROUP_HPP
#define GROUP_HPP

#include <vector>
#include <unordered_map>
#include <string>

#include "tsal.hpp"
#include "Phrase.hpp"

namespace lotide {

    class Group {
        
    public:
        Group(std::string name, std::vector<unsigned> songSynths);
        void addPhrase(unsigned synthId, unsigned phraseId);
        unsigned getLength();
    private:
        std::string mName;
        std::unordered_map<unsigned, std::vector<unsigned>> mSynthPhrases;
        unsigned mLength;

        void calculateLength();
    };

}

#endif
