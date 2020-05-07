#ifndef SONG_HPP
#define SONG_HPP

#include <cereal/access.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/unordered_map.hpp>
#include <cereal/archives/xml.hpp>
#include <cereal/archives/json.hpp>

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
		Song(std::string name, tsal::Mixer& m, int tempo);
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
		Phrase& getPhrase(unsigned phraseId);
		LTSynth& getSynth(unsigned synthId);
		Group& getActiveGroup();
		Group& getGroup(std::string groupName) {
			for (Group& g : groups) {
				if (g.getName() == groupName) {
					return g;
				}
			}
		}
		Group& getGroup(int id) {
			return groups[id];
		}
		void init(tsal::Mixer& m) {
			mMixer = &m;

			for (auto const& s : mSynths) {
				m.add(s->getSynth());
			}
		}
		void setTempo(int bpm) {
			mTempo = bpm;
		}
		int getTempo() { return mTempo; }
	private:
		friend class cereal::access;
		template<class Archive>
		void serialize(Archive & ar)
		{
			ar(cereal::make_nvp("name", mName),
				cereal::make_nvp("synths", mSynths),
				cereal::make_nvp("phrases", mPhrases),
				cereal::make_nvp("groups", groups),
				cereal::make_nvp("active_group", activeGroupName),
				cereal::make_nvp("current_length", mCurrentLength),
				cereal::make_nvp("next_unique_synth_id", mNextUniqueSynthId),
				cereal::make_nvp("next_unique_phrase_id", mNextUniquePhraseId),
				cereal::make_nvp("tempo", mTempo)
			);
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
		std::string activeGroupName;
		int mTempo;
	};

}

#endif
