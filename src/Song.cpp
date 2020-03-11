#include "Song.hpp"

namespace lotide {
	Song::Song(std::string name, tsal::Mixer& mixer) : mName(name), mMixer(mixer) {
		tsal::PolySynth polySynth();

		auto allSynths = getSynthIds();

		Group g("tempGroup", allSynths);

		//Phrase p("tempPhrase", )

		activeGroup = &g;
	}

	std::unordered_map<unsigned, std::vector<Note>> Song::getUpcoming(unsigned time) {
		std::unordered_map<unsigned, std::vector<Note>> notes;
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
}