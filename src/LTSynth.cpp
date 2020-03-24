#include "LTSynth.hpp"

namespace lotide {
	LTSynth::LTSynth(unsigned id, tsal::Mixer &mixer) : mSynth(&mixer), mId(id) {
		mixer.add(mSynth);
	}

	LTSynth::LTSynth(LTSynth&& move) noexcept :
		mId(move.getId()),
		mSynth(std::move(move.mSynth)) {}
}