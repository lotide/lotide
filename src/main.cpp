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

	lt.setSong("Song1");
	lt.setGroup("part1");

	char input;

	lt.save("temp.lot");
	

	LoTide lt2;
	lt2.load("Song1", "temp.lot");
	lt2.setGroup("part1");

	std::cout << "Press <enter> to begin:" << std::endl;
	std::cin.get(input);

	lt2.play();


	std::cout << "Press <enter> to quit:" << std::endl;
	std::cin.get(input);

	lt2.stop();
}
