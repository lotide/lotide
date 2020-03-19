#ifndef PHRASE_HPP
#define PHRASE_HPP

#include <vector>
#include <string>

#include "Note.hpp"
#include "tsal.hpp"

namespace lotide {

    class Phrase {
       
    public:
        Phrase(std::string name, unsigned id);
        Phrase(std::string newName, unsigned id, Phrase& otherPhrase);
        const std::vector<Note>& getNotes() { return mNotes; }
        unsigned getLength() { return mLength; }
        void addNote(Note&& n);
    private:
        std::string mName;
        unsigned mLength;
        unsigned mId;
        std::vector<Note> mNotes;
    };

}

#endif
