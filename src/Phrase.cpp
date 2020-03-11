#include "Phrase.hpp"

namespace lotide {
	Phrase::Phrase(std::string name, tsal::PolySynth& synth, unsigned id) : mName(name), mSynth(synth), mId(id) {
	}

	Phrase::Phrase(std::string newName, Phrase& otherPhrase, unsigned id, tsal::PolySynth& newSynth) : mName(newName), mSynth(newSynth), mId(id) {
		for (Note note : otherPhrase.getNotes()) {
			mNotes.push_back(Note(note));
		}
	}
}