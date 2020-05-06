#include "Phrase.hpp"

namespace lotide {
	Phrase::Phrase() {}

	Phrase::Phrase(std::string name, unsigned id) : mName(name), mId(id) {
		mLength = 0;
	}

	Phrase::Phrase(std::string newName, unsigned id, Phrase& otherPhrase) : mName(newName), mId(id) {
		for (Note note : otherPhrase.getNotes()) {
			mNotes.push_back(Note(note));
		}
	}

	void Phrase::setLength(int newLength) {
		if (newLength >= mLength) {
			mLength = newLength;
		}
	}

	void Phrase::addNote(Note&& n) {
		mNotes.push_back(n);

		for (auto& note : mNotes) {
			unsigned noteLength = note.getStartTime() + note.getDuration();

			setLength(noteLength);
		}
	}

	void Phrase::removeNote(double myNote, int startTime) {
		for (auto& note : mNotes) {
			if (note.getNote() == myNote && note.getStartTime() == startTime) {
				mNotes.erase(std::remove(mNotes.begin(), mNotes.end(), note), mNotes.end());

				unsigned noteLength = note.getStartTime() + note.getDuration();

				if (mLength == noteLength) {
					mLength -= note.getDuration();
				}
			}
		}
	}

}
