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
        std::vector<unsigned>& getPhrases(unsigned synthId);
        void addSynth(unsigned synthId);
        std::string getName() { return mName; }
    private:
        std::string mName;
        std::unordered_map<unsigned, std::vector<unsigned>> mSynthPhrases;
    };

}

#endif
