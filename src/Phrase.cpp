#include "Phrase.hpp"

namespace lotide {
	Phrase::Phrase(std::string name, unsigned id) : mName(name), mId(id) {
		mLength = 0;
	}

	Phrase::Phrase(std::string newName, unsigned id, Phrase& otherPhrase) : mName(newName), mId(id) {
		for (Note note : otherPhrase.getNotes()) {
			mNotes.push_back(Note(note));
		}
	}

	void Phrase::addNote(Note&& n) {
		mNotes.push_back(n);

		for (auto& note : mNotes) {
			unsigned noteLength = note.getStartTime() + note.getDuration();
			if (noteLength > mLength) {
				mLength = noteLength;
			}
		}
	}
}