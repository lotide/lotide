#ifndef PHRASE_HPP
#define PHRASE_HPP

#include <cereal/access.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>

#include "Note.hpp"
#include "tsal.hpp"

namespace lotide {

	class Phrase {

	public:
		Phrase();
		Phrase(std::string name, unsigned id);
		Phrase(std::string newName, unsigned id, Phrase& otherPhrase);
		const std::vector<Note>& getNotes() { return mNotes; }
		unsigned getLength() { return mLength; }
		void addNote(Note&& n);
		unsigned getId() { return mId; }
		std::string getName() { return mName; }
	private:
		friend class cereal::access;
		template<class Archive>
		void serialize(Archive & ar)
		{
			ar(mName, mLength, mId, mNotes);
		}

		std::string mName;
		unsigned mLength;
		unsigned mId;
		std::vector<Note> mNotes;
	};

}

#endif
