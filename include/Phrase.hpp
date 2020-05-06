#ifndef PHRASE_HPP
#define PHRASE_HPP

#include <cereal/access.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>
#include <cereal/archives/xml.hpp>
#include <cereal/archives/json.hpp>

#include "Note.hpp"
#include "tsal.hpp"

namespace lotide {

	class Phrase {

	public:
		Phrase();
		Phrase(std::string name, unsigned id);
		Phrase(std::string newName, unsigned id, Phrase& otherPhrase);
		void setLength(int newLength);
		const std::vector<Note>& getNotes() { return mNotes; }
		unsigned getLength() { return mLength; }
		void addNote(Note&& n);
		void removeNote(double myNote, int startTime);
		unsigned getId() { return mId; }
		std::string getName() { return mName; }
	private:
		friend class cereal::access;
		template<class Archive>
		void serialize(Archive & ar)
		{
			ar(cereal::make_nvp("name", mName),
			   cereal::make_nvp("length", mLength),
			   cereal::make_nvp("id", mId),
			   cereal::make_nvp("notes", mNotes));
		}
		std::string mName;
		unsigned mLength = -1;
		unsigned mId;
		std::vector<Note> mNotes;
	};

}

#endif
