#ifndef PHRASE_HPP
#define PHRASE_HPP

#include <vector>
#include <string>

#include "Note.hpp"
#include "tsal.hpp"

namespace lotide {

    class Phrase {
        Phrase(std::string name, tsal::PolySynth& synth, unsigned id);
        Phrase(std::string newName, Phrase& otherPhrase, unsigned id, tsal::PolySynth& newSynth);
    public:
        const std::vector<Note> getNotes() { return mNotes; }
    private:
        std::string name;
        unsigned mId;
        tsal::PolySynth& mSynth;
        std::vector<Note> mNotes;
    };

}

#endif
