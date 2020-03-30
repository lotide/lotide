#ifndef SONG_HPP
#define SONG_HPP

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/unordered_map.hpp>
#include <boost/serialization/vector.hpp>

#include <string>

#include "tsal.hpp"

#include "Phrase.hpp"
#include "Group.hpp"
#include "LTSynth.hpp"

namespace lotide {

	class Song {

	public:
		Song();
		Song(std::string name, tsal::Mixer& m);
		Song(Song&& other) noexcept;
		Song(Song& other, tsal::Mixer& m);
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

		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive & ar, const unsigned int version)
		{
			ar & mName;
			// Dependent on underlying hardware
			// ar & mMixer;
			// Dependent on underlying hardware
			ar & mSynths;
			ar & mSynthPhrases;
			ar & groups;
			// Dependent on setting group
			// ar & activeGroup;
			// Dependent on phrases and groups
			// ar & mCurrentLength;
			// Dependent on Synth, so meaningless
			// ar & mNextUniqueId;
		}

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
