#include <iostream>

#include "LoTide.hpp"
#include "LTSynth.hpp"
#include "Group.hpp"
#include "Phrase.hpp"
#include "Sequencer.hpp"
#include "Note.hpp"

#include "Server.hpp"

using namespace lotide;

int main(int argc, char *argv[])
{
	lotide::LoTide lt;
	int q = Sequencer::ppq;


	Song& song = lt.addSong("Song1", 138);

	LTSynth& synth3 = song.addSynth();
	int synth3Id = synth3.getId();

	synth3.setParameter(tsal::PolySynth::ENV_ATTACK, 0.04);
	synth3.setParameter(tsal::PolySynth::ENV_SUSTAIN, .15);
	synth3.setParameter(tsal::PolySynth::ENV_DECAY, .2);
	synth3.setParameter(tsal::PolySynth::ENV_RELEASE, .2);

	synth3.setParameter(tsal::PolySynth::MODULATION_MODE, tsal::Oscillator::MIX);
	synth3.setParameter(tsal::PolySynth::OSC1_MODE, tsal::Oscillator::SQUARE);
	synth3.setParameter(tsal::PolySynth::OSC2_MODE, tsal::Oscillator::SAW);
	synth3.setParameter(tsal::PolySynth::OSC2_OFFSET, 0.3);
	//synth3.setParameter(tsal::PolySynth::VOLUME, .3);

	LTSynth& synth2 = song.addSynth();
	int synth2Id = synth2.getId();

	synth2.setParameter(tsal::PolySynth::ENV_ATTACK, 0.05);
	synth2.setParameter(tsal::PolySynth::ENV_SUSTAIN, 0.4);
	synth2.setParameter(tsal::PolySynth::ENV_DECAY, .25);
	synth2.setParameter(tsal::PolySynth::ENV_RELEASE, .8);

	synth2.setParameter(tsal::PolySynth::MODULATION_MODE, tsal::Oscillator::PM);
	synth2.setParameter(tsal::PolySynth::OSC1_MODE, tsal::Oscillator::SINE);
	synth2.setParameter(tsal::PolySynth::OSC2_MODE, tsal::Oscillator::SQUARE);
	synth2.setParameter(tsal::PolySynth::OSC2_OFFSET, 0.4);


	LTSynth& synth = song.addSynth();
	int synth1Id = synth.getId();

	synth.setParameter(tsal::PolySynth::ENV_ATTACK, .05);
	synth.setParameter(tsal::PolySynth::ENV_SUSTAIN, .1);
	synth.setParameter(tsal::PolySynth::ENV_DECAY, .6);
	synth.setParameter(tsal::PolySynth::ENV_RELEASE, .8);

	synth.setParameter(tsal::PolySynth::MODULATION_MODE, tsal::Oscillator::MIX);
	synth.setParameter(tsal::PolySynth::OSC1_MODE, tsal::Oscillator::SINE);
	synth.setParameter(tsal::PolySynth::OSC2_MODE, tsal::Oscillator::SAW);
	synth.setParameter(tsal::PolySynth::OSC2_OFFSET, 0.5);

	Phrase& guitar1 = song.addPhrase("LoruleGuitar1");
	int guitar1Id = guitar1.getId();
	guitar1.setLength(64);
	guitar1.addNote(Note(tsal::Ds3, 44, 4, 4));
	guitar1.addNote(Note(tsal::G3, 44, 4, 4));
	guitar1.addNote(Note(tsal::Ds3, 44, 8, 4));
	guitar1.addNote(Note(tsal::G3, 44, 8, 4));
	guitar1.addNote(Note(tsal::Ds3, 44, 12, 2));
	guitar1.addNote(Note(tsal::G3, 44, 12, 2));
	guitar1.addNote(Note(tsal::Ds3, 44, 14, 2));
	guitar1.addNote(Note(tsal::G3, 44, 14, 2));
	guitar1.addNote(Note(tsal::Ds3, 44, 16, 4));
	guitar1.addNote(Note(tsal::G3, 44, 16, 4));
	guitar1.addNote(Note(tsal::F3, 44, 20, 4));
	guitar1.addNote(Note(tsal::A3, 44, 20, 4));

	guitar1.addNote(Note(tsal::G3, 44, 36, 4));
	guitar1.addNote(Note(tsal::As3, 44, 36, 4));
	guitar1.addNote(Note(tsal::G3, 44, 40, 4));
	guitar1.addNote(Note(tsal::As3, 44, 40, 4));
	guitar1.addNote(Note(tsal::G3, 44, 44, 2));
	guitar1.addNote(Note(tsal::As3, 44, 44, 2));
	guitar1.addNote(Note(tsal::G3, 44, 46, 2));
	guitar1.addNote(Note(tsal::As3, 44, 46, 2));
	guitar1.addNote(Note(tsal::G3, 44, 48, 4));
	guitar1.addNote(Note(tsal::As3, 44, 48, 4));
	guitar1.addNote(Note(tsal::A3, 44, 52, 4));
	guitar1.addNote(Note(tsal::C4, 44, 52, 4));

	Phrase& guitar2 = song.addPhrase("LoruleGuitar1");
	int guitar2Id = guitar2.getId();
	guitar2.setLength(128);
	guitar2.addNote(Note(tsal::Ds3, 44, 4, 4));
	guitar2.addNote(Note(tsal::G3, 44, 4, 4));
	guitar2.addNote(Note(tsal::Ds3, 44, 8, 4));
	guitar2.addNote(Note(tsal::G3, 44, 8, 4));
	guitar2.addNote(Note(tsal::Ds3, 44, 12, 2));
	guitar2.addNote(Note(tsal::G3, 44, 12, 2));
	guitar2.addNote(Note(tsal::Ds3, 44, 14, 2));
	guitar2.addNote(Note(tsal::G3, 44, 14, 2));
	guitar2.addNote(Note(tsal::Ds3, 44, 16, 4));
	guitar2.addNote(Note(tsal::G3, 44, 16, 4));
	guitar2.addNote(Note(tsal::Ds3, 44, 20, 4));
	guitar2.addNote(Note(tsal::G3, 44, 20, 4));

	guitar2.addNote(Note(tsal::F3, 44, 36, 4));
	guitar2.addNote(Note(tsal::A3, 44, 36, 4));
	guitar2.addNote(Note(tsal::F3, 44, 40, 4));
	guitar2.addNote(Note(tsal::A3, 44, 40, 4));
	guitar2.addNote(Note(tsal::F3, 44, 44, 2));
	guitar2.addNote(Note(tsal::A3, 44, 44, 2));
	guitar2.addNote(Note(tsal::F3, 44, 46, 2));
	guitar2.addNote(Note(tsal::A3, 44, 46, 2));
	guitar2.addNote(Note(tsal::F3, 44, 48, 4));
	guitar2.addNote(Note(tsal::A3, 44, 48, 4));
	guitar2.addNote(Note(tsal::F3, 44, 52, 4));
	guitar2.addNote(Note(tsal::A3, 44, 52, 4));

	guitar2.addNote(Note(tsal::Gs3, 44, 68, 4));
	guitar2.addNote(Note(tsal::Ds3, 44, 68, 4));
	guitar2.addNote(Note(tsal::Gs3, 44, 72, 4));
	guitar2.addNote(Note(tsal::Ds3, 44, 72, 4));
	guitar2.addNote(Note(tsal::Gs3, 44, 76, 2));
	guitar2.addNote(Note(tsal::Ds3, 44, 76, 2));
	guitar2.addNote(Note(tsal::Gs3, 44, 78, 2));
	guitar2.addNote(Note(tsal::Ds3, 44, 78, 2));
	guitar2.addNote(Note(tsal::Gs3, 44, 80, 4));
	guitar2.addNote(Note(tsal::Ds3, 44, 80, 4));
	guitar2.addNote(Note(tsal::Gs3, 44, 84, 4));
	guitar2.addNote(Note(tsal::Ds3, 44, 84, 4));

	guitar2.addNote(Note(tsal::D3, 44, 64 + 36, 4));
	guitar2.addNote(Note(tsal::F3, 44, 64 + 36, 4));
	guitar2.addNote(Note(tsal::D3, 44, 64 + 40, 4));
	guitar2.addNote(Note(tsal::F3, 44, 64 + 40, 4));
	guitar2.addNote(Note(tsal::D3, 44, 64 + 44, 2));
	guitar2.addNote(Note(tsal::F3, 44, 64 + 44, 2));
	guitar2.addNote(Note(tsal::D3, 44, 64 + 46, 2));
	guitar2.addNote(Note(tsal::F3, 44, 64 + 46, 2));
	guitar2.addNote(Note(tsal::D3, 44, 64 + 48, 4));
	guitar2.addNote(Note(tsal::F3, 44, 64 + 48, 4));
	guitar2.addNote(Note(tsal::D3, 44, 64 + 52, 4));
	guitar2.addNote(Note(tsal::F3, 44, 64 + 52, 4));

	Phrase& bass1 = song.addPhrase("LoruleBass");
	int bass1Id = bass1.getId();
	bass1.setLength(64);
	bass1.addNote(Note(tsal::C2, 33, 0, 6));
	bass1.addNote(Note(tsal::C2, 33, 8, 6));
	bass1.addNote(Note(tsal::C2, 33, 16, 6));
	bass1.addNote(Note(tsal::C2, 33, 28, 4));

	bass1.addNote(Note(tsal::C2, 33, 32, 6));
	bass1.addNote(Note(tsal::C2, 33, 40, 6));
	bass1.addNote(Note(tsal::C2, 33, 48, 6));
	bass1.addNote(Note(tsal::C2, 33, 60, 4));

	Phrase& bass2 = song.addPhrase("LoruleBass2");
	int bass2Id = bass2.getId();
	bass2.setLength(128);
	bass2.addNote(Note(tsal::C2, 33, 0, 6));
	bass2.addNote(Note(tsal::C2, 33, 8, 6));
	bass2.addNote(Note(tsal::C2, 33, 16, 6));
	bass2.addNote(Note(tsal::C2, 33, 28, 4));

	bass2.addNote(Note(tsal::F2, 33, 32, 6));
	bass2.addNote(Note(tsal::F2, 33, 40, 6));
	bass2.addNote(Note(tsal::F2, 33, 48, 6));
	bass2.addNote(Note(tsal::F2, 33, 60, 4));

	bass2.addNote(Note(tsal::Gs2, 33, 64, 6));
	bass2.addNote(Note(tsal::Gs2, 33, 72, 6));
	bass2.addNote(Note(tsal::Gs2, 33, 80, 6));
	bass2.addNote(Note(tsal::Gs2, 33, 92, 4));

	bass2.addNote(Note(tsal::As2, 33, 96, 6));
	bass2.addNote(Note(tsal::As2, 33, 104, 6));
	bass2.addNote(Note(tsal::As2, 33, 112, 6));

	Phrase& loruleSilence = song.addPhrase("LoruleMelodySilence");
	int loruleSilenceId = loruleSilence.getId();
	loruleSilence.setLength(64);

	Phrase& loruleMelodyIntro = song.addPhrase("LoruleMelodySilence");
	int loruleMelodyIntroId = loruleMelodyIntro.getId();
	loruleMelodyIntro.setLength(64);
	loruleMelodyIntro.addNote(Note(tsal::C4, 100, 62, 2));

	Phrase& lorule = song.addPhrase("LoruleMelody1");
	int loruleId = lorule.getId();
	lorule.setLength(64);
	lorule.addNote(Note(tsal::G4, 100, 0, 20));
	lorule.addNote(Note(tsal::C4, 85, 20, 4));
	lorule.addNote(Note(tsal::G4, 88, 24, 4));
	lorule.addNote(Note(tsal::C5, 92, 28, 4));
	lorule.addNote(Note(tsal::A4, 98, 32, 2));
	lorule.addNote(Note(tsal::As4, 100, 34, 2));
	lorule.addNote(Note(tsal::A4, 95, 36, 28));
	lorule.addNote(Note(tsal::F4, 86, 62, 2));

	Phrase& lorule2 = song.addPhrase("LoruleMelody2");
	int lorule2Id = lorule2.getId();
	lorule2.setLength(64);
	lorule2.addNote(Note(tsal::G4, 100, 0, 8));
	lorule2.addNote(Note(tsal::C4, 100, 8, 16));
	lorule2.addNote(Note(tsal::F4, 100, 24, 8));
	lorule2.addNote(Note(tsal::D4, 100, 32, 2));
	lorule2.addNote(Note(tsal::Ds4, 100, 34, 2));
	lorule2.addNote(Note(tsal::D4, 100, 36, 26));
	lorule2.addNote(Note(tsal::As3, 100, 62, 2));

	Phrase& lorule3 = song.addPhrase("LoruleMelody3");
	int lorule3Id = lorule3.getId();
	lorule3.setLength(64);
	lorule3.addNote(Note(tsal::G5, 100, 0, 20));
	lorule3.addNote(Note(tsal::C5, 85, 20, 4));
	lorule3.addNote(Note(tsal::G5, 88, 24, 4));
	lorule3.addNote(Note(tsal::C6, 92, 28, 4));
	lorule3.addNote(Note(tsal::A5, 98, 32, 2));
	lorule3.addNote(Note(tsal::As5, 100, 34, 2));
	lorule3.addNote(Note(tsal::A5, 95, 36, 28));
	lorule3.addNote(Note(tsal::F5, 86, 62, 2));

	Phrase& lorule5 = song.addPhrase("LoruleMelody5");
	int lorule5Id = lorule5.getId();
	lorule5.setLength(64);
	lorule5.addNote(Note(tsal::G5, 100, 0, 8));
	lorule5.addNote(Note(tsal::C5, 100, 8, 16));
	lorule5.addNote(Note(tsal::F5, 100, 24, 8));
	lorule5.addNote(Note(tsal::D5, 100, 32, 2));
	lorule5.addNote(Note(tsal::Ds5, 100, 34, 2));
	lorule5.addNote(Note(tsal::D5, 100, 36, 26));
	lorule5.addNote(Note(tsal::As4, 100, 62, 2));

	Phrase& lorule4 = song.addPhrase("LoruleMelody4");
	int lorule4Id = lorule4.getId();
	lorule4.setLength(64);
	lorule4.addNote(Note(tsal::C4, 100, 0, 32));
	lorule4.addNote(Note(tsal::C5, 100, 62, 2));

	Phrase& lorule6 = song.addPhrase("LoruleMelody6");
	int lorule6Id = lorule6.getId();
	lorule6.setLength(64);
	lorule6.addNote(Note(tsal::C5, 100, 0, 32));

	Group& g = song.makeNewGroup("part1");

	g.addPhrase(synth1Id, loruleSilenceId);
	g.addPhrase(synth1Id, loruleMelodyIntroId);
	g.addPhrase(synth1Id, loruleId);
	g.addPhrase(synth1Id, lorule2Id);
	g.addPhrase(synth1Id, lorule4Id);
	g.addPhrase(synth1Id, lorule3Id);
	g.addPhrase(synth1Id, lorule5Id);
	g.addPhrase(synth1Id, lorule6Id);

	g.addPhrase(synth2Id, bass1Id);
	g.addPhrase(synth2Id, bass1Id);
	g.addPhrase(synth2Id, bass2Id);
	g.addPhrase(synth2Id, bass1Id);
	g.addPhrase(synth2Id, bass2Id);
	g.addPhrase(synth2Id, bass1Id);

	g.addPhrase(synth3Id, guitar1Id);
	g.addPhrase(synth3Id, guitar1Id);
	g.addPhrase(synth3Id, guitar2Id);
	g.addPhrase(synth3Id, guitar1Id);
	g.addPhrase(synth3Id, guitar2Id);
	g.addPhrase(synth3Id, guitar1Id);

	Group& g2 = song.makeNewGroup("part2");
	Phrase& sunflower = song.addPhrase("Sunflower");
	int sunflowerId = sunflower.getId();
	sunflower.setLength(514);
	// measure 1
	sunflower.addNote(Note(tsal::G4, 100, 0, 32));
	sunflower.addNote(Note(tsal::C5, 100, 0, 32));
	sunflower.addNote(Note(tsal::E5, 100, 0, 32));
	// measure 2
	sunflower.addNote(Note(tsal::A4, 100, 32, 16));
	sunflower.addNote(Note(tsal::D5, 100, 32, 16));
	sunflower.addNote(Note(tsal::F5, 100, 32, 16));
	sunflower.addNote(Note(tsal::G5, 100, 48, 12));
	sunflower.addNote(Note(tsal::F5, 100, 60, 4));
	// measure 3
	sunflower.addNote(Note(tsal::A4, 100, 64, 16));
	sunflower.addNote(Note(tsal::C5, 100, 64, 16));
	sunflower.addNote(Note(tsal::E5, 100, 64, 16));
	sunflower.addNote(Note(tsal::A4, 100, 80, 4));
	sunflower.addNote(Note(tsal::B4, 100, 84, 4));
	sunflower.addNote(Note(tsal::C5, 100, 88, 4));
	sunflower.addNote(Note(tsal::D5, 100, 92, 4));
	// measure 4
	sunflower.addNote(Note(tsal::Gs4, 100, 96, 8));
	sunflower.addNote(Note(tsal::C5, 100, 96, 8));
	sunflower.addNote(Note(tsal::G5, 100, 96, 8));
	sunflower.addNote(Note(tsal::F5, 100, 104, 12));
	sunflower.addNote(Note(tsal::C5, 100, 116, 8));
	sunflower.addNote(Note(tsal::D5, 100, 124, 4));
	// measure 5
	sunflower.addNote(Note(tsal::A4, 100, 128, 16));
	sunflower.addNote(Note(tsal::C5, 100, 128, 16));
	sunflower.addNote(Note(tsal::E5, 100, 128, 16));
	sunflower.addNote(Note(tsal::A5, 100, 144, 16));
	// measure 5
	sunflower.addNote(Note(tsal::E5, 100, 160, 16));
	sunflower.addNote(Note(tsal::Gs5, 100, 160, 16));
	sunflower.addNote(Note(tsal::B5, 100, 160, 16));
	sunflower.addNote(Note(tsal::C6, 100, 176, 8));
	sunflower.addNote(Note(tsal::D6, 100, 184, 8));
	// measure 6
	sunflower.addNote(Note(tsal::B5, 100, 192, 24));
	sunflower.addNote(Note(tsal::C6, 100, 192, 24));
	sunflower.addNote(Note(tsal::E6, 100, 192, 24));
	sunflower.addNote(Note(tsal::C6, 100, 216, 8));
	// measure 7
	sunflower.addNote(Note(tsal::C5, 100, 224, 32));
	sunflower.addNote(Note(tsal::E5, 100, 224, 32));
	sunflower.addNote(Note(tsal::A5, 100, 224, 32));
	// measure 8
	sunflower.addNote(Note(tsal::A4, 100, 256, 24));
	sunflower.addNote(Note(tsal::C5, 100, 256, 24));
	sunflower.addNote(Note(tsal::F5, 100, 256, 24));
	sunflower.addNote(Note(tsal::A5, 100, 280, 8));
	// measure 9
	sunflower.addNote(Note(tsal::D5, 100, 288, 8));
	sunflower.addNote(Note(tsal::F5, 100, 288, 8));
	sunflower.addNote(Note(tsal::A5, 100, 288, 8));
	sunflower.addNote(Note(tsal::G5, 100, 296, 8));
	sunflower.addNote(Note(tsal::B4, 100, 304, 8));
	sunflower.addNote(Note(tsal::D5, 100, 304, 8));
	sunflower.addNote(Note(tsal::G5, 100, 304, 8));
	sunflower.addNote(Note(tsal::F5, 100, 312, 8));
	// measure 10
	sunflower.addNote(Note(tsal::B4, 100, 320, 24));
	sunflower.addNote(Note(tsal::D5, 100, 320, 24));
	sunflower.addNote(Note(tsal::G5, 100, 320, 24));
	sunflower.addNote(Note(tsal::D5, 100, 344, 8));
	// measure 11
	sunflower.addNote(Note(tsal::G4, 100, 352, 16));
	sunflower.addNote(Note(tsal::A4, 100, 352, 16));
	sunflower.addNote(Note(tsal::Cs5, 100, 352, 16));
	sunflower.addNote(Note(tsal::D5, 100, 368, 8));
	sunflower.addNote(Note(tsal::E5, 100, 376, 8));
	// measure 12
	sunflower.addNote(Note(tsal::A4, 100, 384, 32));
	sunflower.addNote(Note(tsal::D5, 100, 384, 32));
	sunflower.addNote(Note(tsal::F5, 100, 384, 32));
	// measure 13
	sunflower.addNote(Note(tsal::Gs4, 100, 416, 32));
	sunflower.addNote(Note(tsal::Cs5, 100, 416, 32));
	sunflower.addNote(Note(tsal::F5, 100, 416, 32));
	// loop point
	// measure 14 outro
	sunflower.addNote(Note(tsal::G4, 100, 448, 16));
	sunflower.addNote(Note(tsal::C5, 100, 448, 16));
	sunflower.addNote(Note(tsal::E5, 100, 448, 16));
	sunflower.addNote(Note(tsal::G4, 100, 468, 4));
	sunflower.addNote(Note(tsal::B4, 100, 472, 4));
	sunflower.addNote(Note(tsal::C5, 100, 476, 4));
	// measure 15 outro
	sunflower.addNote(Note(tsal::D5, 100, 480, 6));
	sunflower.addNote(Note(tsal::E5, 100, 486, 28));

	Phrase& sunflowerBass = song.addPhrase("SunflowerBass");
	int sunflowerBassId = sunflowerBass.getId();
	sunflowerBass.setLength(514);

	Group& g3 = song.makeNewGroup("part3");
	Phrase& kkRestMeasure = song.addPhrase("KKRestMeasure");
	int kkRestMeasureId = kkRestMeasure.getId();
	kkRestMeasure.setLength(128);

	Phrase& kkHouseIntro = song.addPhrase("KKHouseIntro");
	int kkHouseIntroId = kkHouseIntro.getId();
	kkHouseIntro.setLength(128);
	kkHouseIntro.addNote(Note(tsal::D3, 44, 0, 6));
	kkHouseIntro.addNote(Note(tsal::A3, 44, 6, 6));
	kkHouseIntro.addNote(Note(tsal::D4, 44, 12, 8));
	kkHouseIntro.addNote(Note(tsal::D3, 44, 20, 4));
	kkHouseIntro.addNote(Note(tsal::A3, 44, 24, 4));
	kkHouseIntro.addNote(Note(tsal::D3, 44, 28, 2));
	kkHouseIntro.addNote(Note(tsal::Ds3, 44, 30, 2));

	kkHouseIntro.addNote(Note(tsal::E3, 44, 32, 6));
	kkHouseIntro.addNote(Note(tsal::B3, 44, 38, 6));
	kkHouseIntro.addNote(Note(tsal::E4, 44, 44, 8));
	kkHouseIntro.addNote(Note(tsal::E3, 44, 52, 4));
	kkHouseIntro.addNote(Note(tsal::B3, 44, 56, 4));
	kkHouseIntro.addNote(Note(tsal::G2, 44, 60, 2));
	kkHouseIntro.addNote(Note(tsal::Gs2, 44, 62, 2));

	kkHouseIntro.addNote(Note(tsal::A2, 44, 64, 6));
	kkHouseIntro.addNote(Note(tsal::E3, 44, 70, 6));
	kkHouseIntro.addNote(Note(tsal::A3, 44, 76, 8));
	kkHouseIntro.addNote(Note(tsal::A2, 44, 84, 4));
	kkHouseIntro.addNote(Note(tsal::E3, 44, 88, 4));
	kkHouseIntro.addNote(Note(tsal::G2, 44, 92, 2));
	kkHouseIntro.addNote(Note(tsal::Gs2, 44, 94, 2));

	kkHouseIntro.addNote(Note(tsal::A2, 44, 96, 6));
	kkHouseIntro.addNote(Note(tsal::E3, 44, 102, 6));
	kkHouseIntro.addNote(Note(tsal::As3, 44, 106, 2));
	kkHouseIntro.addNote(Note(tsal::B3, 44, 108, 8));
	kkHouseIntro.addNote(Note(tsal::A3, 44, 116, 4));
	kkHouseIntro.addNote(Note(tsal::E3, 44, 120, 4));
	kkHouseIntro.addNote(Note(tsal::Ds3, 44, 124, 4));

	Phrase& kkHouseBass = song.addPhrase("KKHouseBass");
	int kkHouseBassId = kkHouseBass.getId();
	kkHouseBass.setLength(128);
	kkHouseBass.addNote(Note(tsal::D2, 44, 0, 6));
	kkHouseBass.addNote(Note(tsal::A2, 44, 6, 6));
	kkHouseBass.addNote(Note(tsal::D3, 44, 12, 8));
	kkHouseBass.addNote(Note(tsal::D2, 44, 20, 4));
	kkHouseBass.addNote(Note(tsal::A2, 44, 24, 4));
	kkHouseBass.addNote(Note(tsal::D2, 44, 28, 2));
	kkHouseBass.addNote(Note(tsal::Ds3, 44, 30, 2));

	kkHouseBass.addNote(Note(tsal::E2, 44, 32, 6));
	kkHouseBass.addNote(Note(tsal::B2, 44, 38, 6));
	kkHouseBass.addNote(Note(tsal::E3, 44, 44, 8));
	kkHouseBass.addNote(Note(tsal::E2, 44, 52, 4));
	kkHouseBass.addNote(Note(tsal::B2, 44, 56, 4));
	kkHouseBass.addNote(Note(tsal::G1, 44, 60, 2));
	kkHouseBass.addNote(Note(tsal::Gs1, 44, 62, 2));

	kkHouseBass.addNote(Note(tsal::A1, 44, 64, 6));
	kkHouseBass.addNote(Note(tsal::E2, 44, 70, 6));
	kkHouseBass.addNote(Note(tsal::A2, 44, 76, 8));
	kkHouseBass.addNote(Note(tsal::A1, 44, 84, 4));
	kkHouseBass.addNote(Note(tsal::E2, 44, 88, 4));
	kkHouseBass.addNote(Note(tsal::G1, 44, 92, 2));
	kkHouseBass.addNote(Note(tsal::Gs1, 44, 94, 2));

	kkHouseBass.addNote(Note(tsal::A1, 44, 96, 6));
	kkHouseBass.addNote(Note(tsal::E2, 44, 102, 6));
	kkHouseBass.addNote(Note(tsal::As2, 44, 106, 2));
	kkHouseBass.addNote(Note(tsal::B2, 44, 108, 8));
	kkHouseBass.addNote(Note(tsal::A2, 44, 116, 4));
	kkHouseBass.addNote(Note(tsal::E2, 44, 120, 4));
	kkHouseBass.addNote(Note(tsal::Ds2, 44, 124, 4));

	Phrase& kkHouseRhythm = song.addPhrase("KKHouseRhythm");
	int kkHouseRhythmId = kkHouseRhythm.getId();
	kkHouseRhythm.setLength(128);

	kkHouseRhythm.addNote(Note(tsal::D3, 44, 0, 8));

	kkHouseRhythm.addNote(Note(tsal::A3, 44, 8, 8));
	kkHouseRhythm.addNote(Note(tsal::C4, 44, 8, 8));
	kkHouseRhythm.addNote(Note(tsal::E4, 44, 8, 8));

	kkHouseRhythm.addNote(Note(tsal::A3, 44, 16, 4));
	kkHouseRhythm.addNote(Note(tsal::C4, 44, 16, 4));
	kkHouseRhythm.addNote(Note(tsal::E4, 44, 16, 4));

	kkHouseRhythm.addNote(Note(tsal::F3, 44, 20, 2));

	kkHouseRhythm.addNote(Note(tsal::A3, 44, 22, 4));
	kkHouseRhythm.addNote(Note(tsal::C4, 44, 22, 4));
	kkHouseRhythm.addNote(Note(tsal::E4, 44, 22, 4));

	kkHouseRhythm.addNote(Note(tsal::F3, 44, 26, 2));

	kkHouseRhythm.addNote(Note(tsal::A3, 44, 28, 4));
	kkHouseRhythm.addNote(Note(tsal::C4, 44, 28, 4));
	kkHouseRhythm.addNote(Note(tsal::E4, 44, 28, 4));

	kkHouseRhythm.addNote(Note(tsal::E3, 44, 32, 8));

	kkHouseRhythm.addNote(Note(tsal::B3, 44, 40, 8));
	kkHouseRhythm.addNote(Note(tsal::D4, 44, 40, 8));
	kkHouseRhythm.addNote(Note(tsal::Fs4, 44, 40, 8));

	kkHouseRhythm.addNote(Note(tsal::B3, 44, 48, 4));
	kkHouseRhythm.addNote(Note(tsal::D4, 44, 48, 4));
	kkHouseRhythm.addNote(Note(tsal::Fs4, 44, 48, 4));

	kkHouseRhythm.addNote(Note(tsal::G3, 44, 52, 2));

	kkHouseRhythm.addNote(Note(tsal::B3, 44, 54, 4));
	kkHouseRhythm.addNote(Note(tsal::D4, 44, 54, 4));
	kkHouseRhythm.addNote(Note(tsal::Fs4, 44, 54, 4));

	kkHouseRhythm.addNote(Note(tsal::G3, 44, 58, 2));

	kkHouseRhythm.addNote(Note(tsal::B3, 44, 60, 4));
	kkHouseRhythm.addNote(Note(tsal::D4, 44, 60, 4));
	kkHouseRhythm.addNote(Note(tsal::Fs4, 44, 60, 4));

	kkHouseRhythm.addNote(Note(tsal::A2, 44, 64, 8));

	kkHouseRhythm.addNote(Note(tsal::E3, 44, 72, 8));
	kkHouseRhythm.addNote(Note(tsal::Gs3, 44, 72, 8));
	kkHouseRhythm.addNote(Note(tsal::Cs4, 44, 72, 8));

	kkHouseRhythm.addNote(Note(tsal::E3, 44, 80, 4));
	kkHouseRhythm.addNote(Note(tsal::Gs3, 44, 80, 4));
	kkHouseRhythm.addNote(Note(tsal::Cs4, 44, 80, 4));

	kkHouseRhythm.addNote(Note(tsal::E3, 44, 84, 2));

	kkHouseRhythm.addNote(Note(tsal::E3, 44, 86, 4));
	kkHouseRhythm.addNote(Note(tsal::Gs3, 44, 86, 4));
	kkHouseRhythm.addNote(Note(tsal::Cs4, 44, 86, 4));

	kkHouseRhythm.addNote(Note(tsal::E3, 44, 90, 2));

	kkHouseRhythm.addNote(Note(tsal::E3, 44, 92, 4));
	kkHouseRhythm.addNote(Note(tsal::Gs3, 44, 92, 4));
	kkHouseRhythm.addNote(Note(tsal::Cs4, 44, 92, 4));

	kkHouseRhythm.addNote(Note(tsal::A2, 44, 96, 4));

	kkHouseRhythm.addNote(Note(tsal::Gs3, 44, 100, 4));
	kkHouseRhythm.addNote(Note(tsal::Cs4, 44, 100, 4));
	kkHouseRhythm.addNote(Note(tsal::E4, 44, 100, 4));

	kkHouseRhythm.addNote(Note(tsal::E3, 44, 104, 2));

	kkHouseRhythm.addNote(Note(tsal::Gs3, 44, 106, 4));
	kkHouseRhythm.addNote(Note(tsal::Cs4, 44, 106, 4));
	kkHouseRhythm.addNote(Note(tsal::E4, 44, 106, 4));

	kkHouseRhythm.addNote(Note(tsal::E3, 44, 110, 2));

	kkHouseRhythm.addNote(Note(tsal::G3, 44, 112, 4));
	kkHouseRhythm.addNote(Note(tsal::As3, 44, 112, 4));
	kkHouseRhythm.addNote(Note(tsal::Cs4, 44, 112, 4));
	kkHouseRhythm.addNote(Note(tsal::F4, 44, 112, 4));

	kkHouseRhythm.addNote(Note(tsal::Ds3, 44, 116, 2));

	kkHouseRhythm.addNote(Note(tsal::Ds3, 44, 118, 4));
	kkHouseRhythm.addNote(Note(tsal::G3, 44, 118, 4));
	kkHouseRhythm.addNote(Note(tsal::As3, 44, 118, 4));
	kkHouseRhythm.addNote(Note(tsal::Cs4, 44, 118, 4));
	kkHouseRhythm.addNote(Note(tsal::F4, 44, 118, 4));

	kkHouseRhythm.addNote(Note(tsal::Ds3, 44, 122, 2));

	kkHouseRhythm.addNote(Note(tsal::Ds3, 44, 124, 4));
	kkHouseRhythm.addNote(Note(tsal::G3, 44, 124, 4));
	kkHouseRhythm.addNote(Note(tsal::As3, 44, 124, 4));
	kkHouseRhythm.addNote(Note(tsal::Cs4, 44, 124, 4));
	kkHouseRhythm.addNote(Note(tsal::F4, 44, 124, 4));

	Phrase& kkHouseMelody1 = song.addPhrase("KKHouseMelody1");
	int kkHouseMelody1Id = kkHouseMelody1.getId();
	kkHouseMelody1.setLength(128);
	kkHouseMelody1.addNote(Note(tsal::E5, 44, 0, 4));
	kkHouseMelody1.addNote(Note(tsal::A4, 44, 4, 4));
	kkHouseMelody1.addNote(Note(tsal::C5, 44, 8, 2));
	kkHouseMelody1.addNote(Note(tsal::D5, 44, 10, 4));
	kkHouseMelody1.addNote(Note(tsal::E5, 44, 14, 10));

	kkHouseMelody1.addNote(Note(tsal::A4, 44, 36, 4));
	kkHouseMelody1.addNote(Note(tsal::C5, 44, 40, 2));
	kkHouseMelody1.addNote(Note(tsal::G5, 44, 42, 4));
	kkHouseMelody1.addNote(Note(tsal::E5, 44, 46, 10));

	kkHouseMelody1.addNote(Note(tsal::E5, 44, 68, 4));
	kkHouseMelody1.addNote(Note(tsal::G5, 44, 72, 2));
	kkHouseMelody1.addNote(Note(tsal::A5, 44, 74, 4));
	kkHouseMelody1.addNote(Note(tsal::E5, 44, 78, 18));

	Phrase& kkHouseMelody2 = song.addPhrase("KKHouseMelody2");
	int kkHouseMelody2Id = kkHouseMelody2.getId();
	kkHouseMelody2.setLength(128);
	kkHouseMelody2.addNote(Note(tsal::E5, 44, 0,  4));
	kkHouseMelody2.addNote(Note(tsal::A4, 44, 4, 4));
	kkHouseMelody2.addNote(Note(tsal::C5, 44, 8, 2));
	kkHouseMelody2.addNote(Note(tsal::D5, 44, 10, 4));
	kkHouseMelody2.addNote(Note(tsal::E5, 44, 14, 10));

	kkHouseMelody2.addNote(Note(tsal::A4, 44, 36, 4));
	kkHouseMelody2.addNote(Note(tsal::C5, 44, 40, 2));
	kkHouseMelody2.addNote(Note(tsal::D5, 44, 42, 4));
	kkHouseMelody2.addNote(Note(tsal::E5, 44, 46, 10));

	kkHouseMelody2.addNote(Note(tsal::A4, 44, 68, 4));
	kkHouseMelody2.addNote(Note(tsal::A4, 44, 72, 2));
	kkHouseMelody2.addNote(Note(tsal::G5, 44, 74, 4));
	kkHouseMelody2.addNote(Note(tsal::E5, 44, 78, 18));

	Phrase& kkHouseMelody3 = song.addPhrase("KKHouseMelody3");
	int kkHouseMelody3Id = kkHouseMelody3.getId();
	kkHouseMelody3.setLength(128);
	kkHouseMelody3.addNote(Note(tsal::E5, 44, 0, 4));
	kkHouseMelody3.addNote(Note(tsal::A4, 44, 4, 4));
	kkHouseMelody3.addNote(Note(tsal::C5, 44, 8, 2));
	kkHouseMelody3.addNote(Note(tsal::D5, 44, 10, 4));
	kkHouseMelody3.addNote(Note(tsal::E5, 44, 14, 10));

	kkHouseMelody3.addNote(Note(tsal::A4, 44, 36, 4));
	kkHouseMelody3.addNote(Note(tsal::C5, 44, 40, 2));
	kkHouseMelody3.addNote(Note(tsal::D5, 44, 42, 4));
	kkHouseMelody3.addNote(Note(tsal::Ds5, 44, 46, 6));
	kkHouseMelody3.addNote(Note(tsal::D5, 44, 52, 4));
	kkHouseMelody3.addNote(Note(tsal::C5, 44, 56, 4));
	kkHouseMelody3.addNote(Note(tsal::A4, 44, 60, 4));

	g2.addPhrase(synth1Id, sunflowerId);
	g2.addPhrase(synth2Id, sunflowerBassId);

	g3.addPhrase(synth1Id, kkHouseIntroId);
	g3.addPhrase(synth2Id, kkRestMeasureId);
	g3.addPhrase(synth3Id, kkRestMeasureId);

	g3.addPhrase(synth1Id, kkHouseMelody1Id);
	g3.addPhrase(synth1Id, kkHouseMelody2Id);
	g3.addPhrase(synth1Id, kkHouseMelody3Id);

	g3.addPhrase(synth2Id, kkHouseBassId);
	g3.addPhrase(synth2Id, kkHouseBassId);
	g3.addPhrase(synth2Id, kkHouseBassId);

	g3.addPhrase(synth3Id, kkHouseRhythmId);
	g3.addPhrase(synth3Id, kkHouseRhythmId);
	g3.addPhrase(synth3Id, kkHouseRhythmId);

	lt.setSong("Song1");
	lt.setGroup("part3");

	char input;

	lt.save("temp.lot");


	LoTide lt2;
	lt2.load("Song1", "temp.lot");
	lt2.setGroup("part3");

	std::cout << "Press <enter> to begin:" << std::endl;
	std::cin.get(input);

	lt2.play();


	std::cout << "Press <enter> to quit:" << std::endl;
	std::cin.get(input);

	lt2.stop();
}
