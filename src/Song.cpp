#include "Song.hpp"

namespace lotide {
	Song::Song(std::string name, tsal::Mixer& mixer) : mName(name), mMixer(mixer) {
		activeGroup = NULL;
		mCurrentLength = 0;

		tsal::PolySynth polySynth(&mixer);
		addSynth(std::move(polySynth));
		
		std::vector<Phrase> synthPhrase;

		Phrase p("tempPhrase", 0);
		p.addNote(Note(tsal::A5, 50, 1, 5));

		synthPhrase.push_back(p);
		mSynthPhrases[0] = synthPhrase;

		auto allSynths = getSynthIds();

		makeNewGroup("tempGroup");
		groups[0].addPhrase(0, 0);
	}

	void Song::makeNewGroup(std::string groupName) {
		Group g(groupName, getSynthIds());
		groups.push_back(g);

		if (groups.size() == 1) {
			setGroup(g);
		}
	}

	std::unordered_map<unsigned, std::vector<Note>> Song::getUpcoming(unsigned time) {
		std::unordered_map<unsigned, std::vector<Note>> notes;

		if (mCurrentLength == 0) {
			return notes;
		}

		unsigned normTime = time % mCurrentLength;

		for (auto& kv : mSynths) {
			std::vector<unsigned>& phrases = activeGroup->getPhrases(kv.first);
			Phrase* desired = &mSynthPhrases[kv.first][0];

			unsigned previousLength = 0;

			while (desired->getLength() + previousLength <= normTime) {
				desired++;
				previousLength += desired->getLength();
			}

			unsigned actualTime = normTime - previousLength;

			for (auto &note : desired->getNotes()) {
				if (note.getStartTime() == actualTime) {
					notes[kv.first].push_back(note);
				}
			}
		}

		return notes;
	}

	std::vector<tsal::PolySynth*> Song::getSynths() {
		std::vector<tsal::PolySynth*> synths;

		for (auto& kv : mSynths) {
			tsal::PolySynth* ptr = &(kv.second);
			synths.push_back(ptr);
		}

		return synths;
	}

	std::vector<unsigned> Song::getSynthIds() {
		std::vector<unsigned> synths;

		for (auto& kv : mSynths) {
			synths.push_back(kv.first);
		}

		return synths;
	}

	void Song::addSynth(tsal::PolySynth&& synth) {
		//mSynths[mSynths.size()] = synth;
	}

	void Song::setGroup(Group& g) {
		activeGroup = &g;

		mCurrentLength = 0;

		for (auto& kv : mSynths) {
			std::vector<unsigned>& phrases = activeGroup->getPhrases(kv.first);

			unsigned thisLength = 0;

			for (auto& phrase : phrases) {
				thisLength += mSynthPhrases[kv.first][phrase].getLength();
			}

			if (thisLength > mCurrentLength) {
				mCurrentLength = thisLength;
			}
		}
	}
}