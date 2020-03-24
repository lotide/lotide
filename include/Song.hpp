#ifndef SONG_HPP
#define SONG_HPP

#include <vector>
#include <unordered_map>
#include <string>

#include "tsal.hpp"

#include "Phrase.hpp"
#include "Group.hpp"
#include "LTSynth.hpp"

namespace lotide {

    class Song {
        
    public:
        Song(std::string name, tsal::Mixer& m);
        Song(Song&& other) noexcept;
        LTSynth& addSynth();
        std::vector<unsigned> getSynthIds();
        std::unordered_map<unsigned, std::vector<Note>> getUpcoming(unsigned time);
        std::vector<LTSynth*> getSynths();
        void setGroup(Group& g);
        unsigned getLength() { return mCurrentLength; }
        Group& makeNewGroup(std::string groupName);
        std::string getName() { return mName; }
        void setGroup(std::string name);
        Phrase& addPhrase(std::string name, unsigned synthId);
    private:
        std::string mName;
        tsal::Mixer* mMixer;
        std::vector<LTSynth> mSynths;
        std::unordered_map<unsigned, std::vector<Phrase>> mSynthPhrases;
        std::vector<Group> groups;
        Group* activeGroup;
        unsigned mCurrentLength;
        unsigned mNextUniqueId = 0;
    };

}

#endif
