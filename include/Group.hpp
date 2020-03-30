#ifndef GROUP_HPP
#define GROUP_HPP

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/unordered_map.hpp>
#include <boost/serialization/vector.hpp>

#include <string>

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

		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive & ar, const unsigned int version)
		{
			ar & mName;
			ar & mSynthPhrases;
		}

		std::string mName;
		std::unordered_map<unsigned, std::vector<unsigned>> mSynthPhrases;
	};

}

#endif
