#include "LTSynth.hpp"

namespace lotide {
	LTSynth::LTSynth() {}
	// LTSynth::LTSynth(unsigned id, tsal::Mixer &mixer) : mSynth(&mixer), mId(id) {
	LTSynth::LTSynth(unsigned id, tsal::Mixer &mixer) : mId(id) {
	}

	LTSynth::LTSynth(LTSynth&& move) noexcept :
		mId(move.getId()),
		mSynth(std::move(move.mSynth)) {}
}
