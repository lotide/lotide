#ifndef LTSYNTH_HPP
#define LTSYNTH_HPP

#include "tsal.hpp";

namespace lotide {
	class LTSynth {

	public:
		LTSynth(unsigned id, tsal::Mixer &mixer);
		LTSynth(LTSynth&& move) noexcept;
		unsigned getId() { return mId; }
		void play(double note, double velocity) { mSynth.play(note, velocity); }
		void stop(double note) { mSynth.stop(note); }

		tsal::PolySynth& getSynth() { return mSynth; }

	private:
		tsal::PolySynth mSynth;
		unsigned mId;
	};
}

#endif