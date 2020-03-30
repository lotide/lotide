#ifndef PHRASE_HPP
#define PHRASE_HPP

#include <boost/serialization/vector.hpp>
#include <string>

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

		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive & ar, const unsigned int version)
		{
			ar & mName;
			ar & mLength;
			ar & mId;
			ar & mNotes;
		}

		std::string mName;
		unsigned mLength;
		unsigned mId;
		std::vector<Note> mNotes;
	};

}

#endif
