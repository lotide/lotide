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
		mPhrases(std::move(other.mPhrases)),
		groups(std::move(other.groups)),
		activeGroup(std::move(other.activeGroup)),
		mCurrentLength(other.mCurrentLength),
		mNextUniqueSynthId(other.mNextUniqueSynthId) {
		mMixer = other.mMixer;
	}

	Group& Song::makeNewGroup(std::string groupName) {
		Group g(groupName, getSynthIds());
		groups.push_back(std::move(g));

		if (groups.size() == 1) {
			setGroup(groups[0]);
		}

		return groups[groups.size() - 1];
	}

	std::unordered_map<unsigned, std::list<Note>> Song::getUpcoming(unsigned time) {
		std::unordered_map<unsigned, std::list<Note>> notes;

		if (mCurrentLength == 0) {
			return notes;
		}

		unsigned normTime = time % mCurrentLength;

		if (normTime == 0 && nextGroup != NULL) {
			setGroup(*nextGroup);
		}

		for (auto& kv : mSynths) {
			std::vector<unsigned>& phrases = activeGroup->getPhrases(kv->getId());

			if (phrases.size() != 0) {

				int desId = 0;
				Phrase* desired = &mPhrases[phrases[desId]];

				bool noPhrase = false;

				unsigned previousLength = 0;
				while (desired->getLength() + previousLength <= normTime) {
					desId++;

					if (desId >= phrases.size() || phrases[desId] >= mPhrases.size()) {
						noPhrase = true;
						break;
					}

					desired = &mPhrases[phrases[desId]];
					previousLength += desired->getLength();
				}

				if (!noPhrase) {

					unsigned actualTime = normTime - previousLength;

					for (auto& note : desired->getNotes()) {
						if (note.getStartTime() == actualTime) {
							notes[kv->getId()].push_back(note);
						}
					}
				}
			}
		}

		return notes;
	}

	std::vector<LTSynth*> Song::getSynths() {
		std::vector < LTSynth* > synths;

		for (auto& kv : mSynths) {
			LTSynth* ptr = kv.get();
			synths.push_back(ptr);
		}

		return synths;
	}

	std::vector<unsigned> Song::getSynthIds() {
		std::vector<unsigned> synths;

		for (auto& kv : mSynths) {
			synths.push_back(kv->getId());
		}

		return synths;
	}

	LTSynth& Song::addSynth() {
		mSynths.push_back(std::make_unique<LTSynth>(mNextUniqueSynthId));
		LTSynth& newSynth = *mSynths[mNextUniqueSynthId];
		mNextUniqueSynthId++;

		for (Group g : groups) {
			g.addSynth(newSynth.getId());
		}

		mMixer->add(newSynth.getSynth());
		return newSynth;
	}

	void Song::setGroup(std::string name) {
		activeGroupName = name;
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
			std::vector<unsigned> phrases = activeGroup->getPhrases(kv->getId());

			unsigned thisLength = 0;

			for (auto& phrase : phrases) {
				thisLength += mPhrases[phrase].getLength();
			}

			if (thisLength > mCurrentLength) {
				mCurrentLength = thisLength;
			}
		}

		if (g.getNextGroup() == NULL) {
			nextGroup = NULL;
		} else {
			nextGroup = &groups[g.getNextGroup()];
		}
	}

	Phrase& Song::addPhrase(std::string name) {
		Phrase p(name, mNextUniquePhraseId);
		mPhrases.push_back(std::move(p));

		mNextUniquePhraseId++;

		return mPhrases[mPhrases.size() - 1];
	}

	void Song::setNextGroup(std::string name) {
		for (Group& g : groups) {
			if (g.getName() == name) {
				setNextGroup(g);
			}
		}
	}

	void Song::setNextGroup(Group& g) {
		nextGroup = &g;
	}

	Group& Song::getActiveGroup() {
		return *activeGroup;
	}

	Phrase& Song::getPhrase(unsigned phraseId) {
		return mPhrases[phraseId];
	}

	LTSynth& Song::getSynth(unsigned synthId) {
		return *mSynths[synthId];
	}
}
