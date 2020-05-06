#ifndef SONG_HPP
#define SONG_HPP

#include <cereal/access.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/unordered_map.hpp>

#include <string>
#include <list>
#include <memory>
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
		/*Song(Song& other, tsal::Mixer& m);*/
		LTSynth& addSynth();
		std::vector<unsigned> getSynthIds();
		std::unordered_map<unsigned, std::list<Note>> getUpcoming(unsigned time);
		std::vector<LTSynth*> getSynths();
		Phrase& addPhrase(std::string name);
		unsigned getLength() { return mCurrentLength; }
		Group& makeNewGroup(std::string groupName);
		std::string getName() { return mName; }
		void setGroup(std::string name);
		void setGroup(Group& g);
		void setNextGroup(std::string name);
		void setNextGroup(Group& g);

		void init(tsal::Mixer& m) {
			mMixer = &m;

			for (auto const& s : mSynths) {
				m.add(s->getSynth());
			}
		}
	private:
		friend class cereal::access;
		template<class Archive>
		void serialize(Archive & ar)
		{
			ar( mName,
				mSynths,
				mPhrases,
				groups,
				// activeGroup,
				mCurrentLength,
				mNextUniqueSynthId,
				mNextUniquePhraseId);
		}

		std::string mName;
		tsal::Mixer* mMixer;
		std::vector<std::unique_ptr<LTSynth>> mSynths;
		//std::unordered_map<unsigned, std::vector<Phrase>> mSynthPhrases;
		std::vector<Phrase> mPhrases;
		std::vector<Group> groups;
		Group* activeGroup;
		Group* nextGroup = NULL;
		unsigned mCurrentLength;
		unsigned mNextUniqueSynthId = 0;
		unsigned mNextUniquePhraseId = 0;
	};

}

#endif
