#include "Group.hpp"

namespace lotide {
	Group::Group() {}
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

	void Group::addNextGroup(int groupId) {
		nextGroup = groupId;
	}

	void Group::setPhrases(int instrId, std::vector<unsigned>& phrases) {
		std::vector<unsigned> copy;

		for (unsigned& val : phrases) {
			copy.push_back(unsigned(val));
		}

		mSynthPhrases[instrId] = std::move(copy);
	}

	void Group::removePhrases(int instrId) {
		mSynthPhrases[instrId] = std::vector<unsigned>();
	}
}
