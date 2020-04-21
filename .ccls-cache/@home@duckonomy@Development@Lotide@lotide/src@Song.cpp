#include "Song.hpp"

namespace lotide {
	Song::Song() {}

	Song::Song(std::string name, tsal::Mixer& m) : mName(name) {
		mMixer = &m;
		activeGroup = NULL;
		mCurrentLength = 0;
	}

	Song::Song(Song&& other) noexcept :
		mName(std::move(other.mName)),
		mSynths(std::move(other.mSynths)),
		mSynthPhrases(std::move(other.mSynthPhrases)),
		groups(std::move(other.groups)),
		activeGroup(std::move(other.activeGroup)),
		mCurrentLength(other.mCurrentLength),
		mNextUniqueId(other.mNextUniqueId) {
		mMixer = other.mMixer;
	}

	// For Serialization
	Song::Song(Song& other, tsal::Mixer& m) {
		mMixer = &m;

		LTSynth& synth = addSynth();

		mName = other.mName;

		for (auto& kv: other.groups) {
			Group& g = makeNewGroup(kv.getName());

			for (auto& kk: other.mSynthPhrases) {
				for (auto& x: kk.second) {
					Phrase& p = addPhrase(x.getName(), synth.getId());
					for (auto& y: x.getNotes()) {
						p.addNote((Note(y.getNote(), y.getVelocity(),
										y.getStartTime(), y.getDuration())));
					}
					g.addPhrase(synth.getId(), p.getId());
				}
			}
		}
	}

	Group& Song::makeNewGroup(std::string groupName) {
		Group g(groupName, getSynthIds());
		groups.push_back(std::move(g));

		if (groups.size() == 1) {
			setGroup(groups[0]);
		}

		return groups[groups.size() - 1];
	}

	std::unordered_map<unsigned, std::vector<Note>> Song::getUpcoming(unsigned time) {
		std::unordered_map<unsigned, std::vector<Note>> notes;

		if (mCurrentLength == 0) {
			return notes;
		}

		unsigned normTime = time % mCurrentLength;

		for (auto& kv : mSynths) {
			std::vector<unsigned>& phrases = activeGroup->getPhrases(kv.getId());

			int desId = 0;
			Phrase* desired = &mSynthPhrases[kv.getId()][phrases[desId]];
			//Phrase* desired = &mSynthPhrases[kv.getId()][0];

			unsigned previousLength = 0;
			while (desired->getLength() + previousLength <= normTime) {
				desId++;

				desired = &mSynthPhrases[kv.getId()][phrases[desId]];
				//desired = &mSynthPhrases[kv.getId()][0];
				previousLength += desired->getLength();
			}

			unsigned actualTime = normTime - previousLength;

			for (auto &note : desired->getNotes()) {
				if (note.getStartTime() == actualTime) {
					notes[kv.getId()].push_back(note);
				}
			}
		}

		return notes;
	}

	std::vector<LTSynth*> Song::getSynths() {
		std::vector < LTSynth* > synths;

		for (auto& kv : mSynths) {
			LTSynth* ptr = &(kv);
			synths.push_back(ptr);
		}

		return synths;
	}

	std::vector<unsigned> Song::getSynthIds() {
		std::vector<unsigned> synths;

		for (auto& kv : mSynths) {
			synths.push_back(kv.getId());
		}

		return synths;
	}

	LTSynth& Song::addSynth() {
		LTSynth newSynth(mNextUniqueId, *mMixer);
		// int count = mMixer->getMaster().getInstrumentCount();

		mSynths.push_back(std::move(newSynth));
		mNextUniqueId++;

		for (Group g : groups) {
			g.addSynth(newSynth.getId());
		}

		mMixer->add(mSynths[newSynth.getId()].getSynth());
		return mSynths[newSynth.getId()];
	}

	void Song::setGroup(std::string name) {
		for (Group& g : groups) {
			if (g.getName() == name) {
				setGroup(g);
			}
		}
	}

	void Song::setGroup(Group& g) {
		activeGroup = &g;

		mCurrentLength = 0;

		for (auto& kv : mSynths) {
			std::vector<unsigned>& phrases = activeGroup->getPhrases(kv.getId());

			unsigned thisLength = 0;

			for (auto& phrase : phrases) {
				thisLength += mSynthPhrases[kv.getId()][phrase].getLength();
			}

			if (thisLength > mCurrentLength) {
				mCurrentLength = thisLength;
			}
		}
	}

	Phrase& Song::addPhrase(std::string name, unsigned synthId) {
		Phrase p(name, synthId);
		mSynthPhrases[synthId].push_back(std::move(p));

		return mSynthPhrases[synthId][mSynthPhrases[synthId].size() - 1];
	}
}
