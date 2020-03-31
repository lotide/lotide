#ifndef LTSYNTH_HPP
#define LTSYNTH_HPP

#include <cereal/access.hpp>

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

		void init(tsal::Mixer& m) {
			mSynth = tsal::PolySynth(&m);
		}
	private:
		friend class cereal::access;
		template<class Archive>
		void serialize(Archive & ar)
		{
			// ar & mSynth;
			ar(mId);
		}

		tsal::PolySynth mSynth;
		unsigned mId;
	};
}

#endif
