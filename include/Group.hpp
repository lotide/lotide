#ifndef GROUP_HPP
#define GROUP_HPP

#include <cereal/access.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/unordered_map.hpp>
#include <cereal/types/string.hpp>

#include "tsal.hpp"
#include "Phrase.hpp"

namespace lotide {

	class Group {

	public:
		Group();
		Group(std::string name, std::vector<unsigned> songSynths);
		void addPhrase(unsigned synthId, unsigned phraseId);
		std::vector<unsigned>& getPhrases(unsigned synthId);
		void addSynth(unsigned synthId);
		std::string getName() { return mName; }
	private:
		friend class cereal::access;
		template<class Archive>
		void serialize(Archive & ar)
		{
			ar(mName, mSynthPhrases);
		}

		std::string mName;
		std::unordered_map<unsigned, std::vector<unsigned>> mSynthPhrases;
	};

}

#endif
