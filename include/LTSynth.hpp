#ifndef LTSYNTH_HPP
#define LTSYNTH_HPP

/* #include <boost/serialization/serialization.hpp> */

#include "tsal.hpp"

namespace lotide {
	class LTSynth {

	public:
		LTSynth();
		LTSynth(unsigned id, tsal::Mixer &mixer);
		LTSynth(LTSynth&& move) noexcept;
		unsigned getId() { return mId; }
		void play(double note, double velocity) { mSynth.play(note, velocity); }
		void stop(double note) { mSynth.stop(note); }

		tsal::PolySynth& getSynth() { return mSynth; }
	private:

/* 		friend class boost::serialization::access; */
/* 		template<class Archive> */
/* 		void serialize(Archive & ar, const unsigned int version) */
/* 		{ */
/* 			ar & mSynth; */
/* 			ar & mId; */
/* 		} */

		tsal::PolySynth mSynth;
		unsigned mId;
	};
}

#endif
