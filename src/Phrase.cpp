#include "Phrase.hpp"

namespace lotide {
	Phrase::Phrase(std::string name, PolySynth& synth, unsigned id) : name(name), mSynth(synth), mId(id) {
	}

	Phrase::Phrase(stdd::string newName, Phrase& otherPhrase, unsigned id, tsal::PolySynth& newSynth) : name(newName), mSynth(newSynth), mId(id) {
		for (Note& note : otherPhrase.getNotes()) {
			mNotes.push_back(Note(note));
		}
	}
}