#include "Group.hpp"

namespace lotide {
	Group::Group(std::string name, std::vector<unsigned> songSynths) : mName(name) {
		for (unsigned id : songSynths) {
			mSynthPhrases[id] = std::vector<unsigned>();
		}
	}

	void Group::addPhrase(unsigned synthId, unsigned phraseId) {
		mSynthPhrases[synthId].push_back(phraseId);
	}

	std::vector<unsigned>& Group::getPhrases(unsigned synthId) {
		return mSynthPhrases[synthId];
	}

	void Group::addSynth(unsigned synthId) {
		mSynthPhrases[synthId] = std::vector<unsigned>();
	}
}
