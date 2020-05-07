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


	Song& song = lt.addSong("Song1", 150);

	LTSynth& synth3 = song.addSynth();
	int synth3Id = synth3.getId();

	synth3.setParameter(tsal::PolySynth::ENV_ATTACK, 0.01);
	synth3.setParameter(tsal::PolySynth::ENV_SUSTAIN, .15);
	synth3.setParameter(tsal::PolySynth::ENV_DECAY, .01);
	synth3.setParameter(tsal::PolySynth::ENV_RELEASE, .01);

	synth3.setParameter(tsal::PolySynth::MODULATION_MODE, tsal::Oscillator::AM);
	synth3.setParameter(tsal::PolySynth::OSC1_MODE, tsal::Oscillator::SQUARE);
	synth3.setParameter(tsal::PolySynth::OSC2_MODE, tsal::Oscillator::SAW);
	synth3.setParameter(tsal::PolySynth::OSC2_OFFSET, 0.3);
	synth3.setParameter(tsal::PolySynth::VOLUME, 22);

	LTSynth& synth2 = song.addSynth();
	int synth2Id = synth2.getId();

	synth2.setParameter(tsal::PolySynth::ENV_ATTACK, 0.15);
	synth2.setParameter(tsal::PolySynth::ENV_SUSTAIN, 0.2);
	synth2.setParameter(tsal::PolySynth::ENV_DECAY, .05);
	synth2.setParameter(tsal::PolySynth::ENV_RELEASE, .25);

	synth2.setParameter(tsal::PolySynth::MODULATION_MODE, tsal::Oscillator::MIX);
	synth2.setParameter(tsal::PolySynth::OSC1_MODE, tsal::Oscillator::SINE);
	synth2.setParameter(tsal::PolySynth::OSC2_MODE, tsal::Oscillator::SQUARE);
	synth2.setParameter(tsal::PolySynth::OSC2_OFFSET, 0.3);


	LTSynth& synth = song.addSynth(); 
	int synth1Id = synth.getId();

	synth.setParameter(tsal::PolySynth::ENV_ATTACK, .05);
	synth.setParameter(tsal::PolySynth::ENV_SUSTAIN, .1);
	synth.setParameter(tsal::PolySynth::ENV_DECAY, .6);
	synth.setParameter(tsal::PolySynth::ENV_RELEASE, .8);

	synth.setParameter(tsal::PolySynth::MODULATION_MODE, tsal::Oscillator::AM);
	synth.setParameter(tsal::PolySynth::OSC1_MODE, tsal::Oscillator::SAW);
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

	Phrase& bass1 = song.addPhrase("LoruleBass");
	int bass1Id = bass1.getId();
	bass1.setLength(64);
	bass1.addNote(Note(tsal::C2, 67, 0, 6));
	bass1.addNote(Note(tsal::C2, 67, 8, 6));
	bass1.addNote(Note(tsal::C2, 67, 16, 6));
	bass1.addNote(Note(tsal::C2, 67, 28, 4));

	bass1.addNote(Note(tsal::C2, 67, 32, 6));
	bass1.addNote(Note(tsal::C2, 67, 40, 6));
	bass1.addNote(Note(tsal::C2, 67, 48, 6));
	bass1.addNote(Note(tsal::C2, 67, 60, 4));

	Phrase& bass3 = song.addPhrase("LoruleBass3");
	int bass3Id = bass3.getId();
	bass3.setLength(128);
	bass3.addNote(Note(tsal::C2, 67, 0, 6));
	bass3.addNote(Note(tsal::C2, 67, 8, 6));
	bass3.addNote(Note(tsal::C2, 67, 16, 6));
	bass3.addNote(Note(tsal::C2, 67, 28, 4));

	bass3.addNote(Note(tsal::C2, 67, 32, 6));
	bass3.addNote(Note(tsal::C2, 67, 40, 6));
	bass3.addNote(Note(tsal::C2, 67, 48, 6));
	bass3.addNote(Note(tsal::C2, 67, 60, 4));

	bass3.addNote(Note(tsal::C2, 67, 64, 6));
	bass3.addNote(Note(tsal::C2, 67, 72, 6));
	bass3.addNote(Note(tsal::C2, 67, 80, 6));
	bass3.addNote(Note(tsal::C2, 67, 92, 4));

	bass3.addNote(Note(tsal::C2, 67, 96, 6));
	bass3.addNote(Note(tsal::C2, 67, 104, 6));
	bass3.addNote(Note(tsal::C2, 67, 112, 6));

	Phrase& bass2 = song.addPhrase("LoruleBass2");
	int bass2Id = bass2.getId();
	bass2.setLength(128);
	bass2.addNote(Note(tsal::C2, 67, 0, 6));
	bass2.addNote(Note(tsal::C2, 67, 8, 6));
	bass2.addNote(Note(tsal::C2, 67, 16, 6));
	bass2.addNote(Note(tsal::C2, 67, 28, 4));

	bass2.addNote(Note(tsal::F2, 67, 32, 6));
	bass2.addNote(Note(tsal::F2, 67, 40, 6));
	bass2.addNote(Note(tsal::F2, 67, 48, 6));
	bass2.addNote(Note(tsal::F2, 67, 60, 4));

	bass2.addNote(Note(tsal::Gs2, 67, 64, 6));
	bass2.addNote(Note(tsal::Gs2, 67, 72, 6));
	bass2.addNote(Note(tsal::Gs2, 67, 80, 6));
	bass2.addNote(Note(tsal::Gs2, 67, 92, 4));

	bass2.addNote(Note(tsal::As2, 67, 96, 6));
	bass2.addNote(Note(tsal::As2, 67, 104, 6));
	bass2.addNote(Note(tsal::As2, 67, 112, 6));

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
	lorule4.addNote(Note(tsal::Ds5, 100, 60, 2));
	lorule4.addNote(Note(tsal::F5, 100, 62, 2));

	Phrase& lorule6 = song.addPhrase("LoruleMelody6");
	int lorule6Id = lorule6.getId();
	lorule6.setLength(64);
	lorule6.addNote(Note(tsal::C5, 100, 0, 32));

	Group& g = song.makeNewGroup("part1");

	g.addPhrase(synth1Id, loruleId);
	g.addPhrase(synth1Id, lorule2Id);
	g.addPhrase(synth1Id, lorule4Id);
	g.addPhrase(synth1Id, lorule3Id);
	g.addPhrase(synth1Id, lorule5Id);
	g.addPhrase(synth1Id, lorule6Id);

	g.addPhrase(synth2Id, bass2Id);
	g.addPhrase(synth2Id, bass1Id);
	g.addPhrase(synth2Id, bass2Id);
	g.addPhrase(synth2Id, bass1Id);

	g.addPhrase(synth3Id, guitar1Id);
	g.addPhrase(synth3Id, guitar1Id);
	g.addPhrase(synth3Id, guitar1Id);
	g.addPhrase(synth3Id, guitar1Id);
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
