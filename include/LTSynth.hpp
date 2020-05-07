#ifndef LTSYNTH_HPP
#define LTSYNTH_HPP

#include <cereal/access.hpp>
#include <cereal/archives/xml.hpp>
#include <cereal/archives/json.hpp>

#include "tsal.hpp"

namespace lotide {
	class LTSynth {

	public:
		LTSynth();
		LTSynth(unsigned id);
		unsigned getId() { return mId; }
		void play(double note, double velocity) { mSynth.play(note, velocity); }
		void stop(double note) { mSynth.stop(note); }

		tsal::PolySynth& getSynth() { return mSynth; }
		void setParameter(tsal::PolySynth::Parameters param, double val) {
			mParams.push_back(param);
			mVals.push_back(val);
			mSynth.setParameter(param, val);
		}
	private:
		friend class cereal::access;

		template<class Archive>
		void save(Archive & ar) const
		{
			// ar & mSynth;
			ar(
				cereal::make_nvp("id", mId),
				cereal::make_nvp("vals", mVals),
				cereal::make_nvp("params", mParams)
			);
		}

		template<class Archive>
		void load(Archive& ar)
		{
			// ar & mSynth;
			ar(
				cereal::make_nvp("id", mId),
				cereal::make_nvp("vals", mVals),
				cereal::make_nvp("params", mParams)
			);

			for (int i = 0; i < mParams.size(); i++) {
				mSynth.setParameter(mParams[i], mVals[i]);
			}
		}

		tsal::PolySynth mSynth;
		unsigned mId;

		std::vector<tsal::PolySynth::Parameters> mParams;
		std::vector<double> mVals;
	};
}

#endif
