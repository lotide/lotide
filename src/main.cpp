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
	lt.setTempo(150);
	int q = Sequencer::ppq;


	Song& song = lt.addSong("Song1");


	LTSynth& synth2 = song.addSynth();
	int synth2Id = synth2.getId();

	synth2.getSynth().setParameter(tsal::PolySynth::ENV_ATTACK, .3);
	synth2.getSynth().setParameter(tsal::PolySynth::ENV_SUSTAIN, 0.2);
	synth2.getSynth().setParameter(tsal::PolySynth::ENV_DECAY, .2);
	synth2.getSynth().setParameter(tsal::PolySynth::ENV_RELEASE, .3);

	synth2.getSynth().setParameter(tsal::PolySynth::MODULATION_MODE, tsal::Oscillator::AM);
	synth2.getSynth().setParameter(tsal::PolySynth::OSC1_MODE, tsal::Oscillator::SAW);
	synth2.getSynth().setParameter(tsal::PolySynth::OSC2_MODE, tsal::Oscillator::SINE);
	synth2.getSynth().setParameter(tsal::PolySynth::OSC2_OFFSET, 0.3);


	LTSynth& synth = song.addSynth(); 
	int synth1Id = synth.getId();

	synth.getSynth().setParameter(tsal::PolySynth::ENV_ATTACK, .05);
	synth.getSynth().setParameter(tsal::PolySynth::ENV_SUSTAIN, .1);
	synth.getSynth().setParameter(tsal::PolySynth::ENV_DECAY, .6);
	synth.getSynth().setParameter(tsal::PolySynth::ENV_RELEASE, .8);

	synth.getSynth().setParameter(tsal::PolySynth::MODULATION_MODE, tsal::Oscillator::AM);
	synth.getSynth().setParameter(tsal::PolySynth::OSC1_MODE, tsal::Oscillator::SAW);
	synth.getSynth().setParameter(tsal::PolySynth::OSC2_MODE, tsal::Oscillator::SINE);
	synth.getSynth().setParameter(tsal::PolySynth::OSC2_OFFSET, 0.1);

	

	Phrase& bass1 = song.addPhrase("LoruleBass");
	int bass1Id = bass1.getId();
	bass1.setLength(128);
	bass1.addNote(Note(tsal::C3, 67, 0, 6));
	bass1.addNote(Note(tsal::C3, 67, 8, 6));
	bass1.addNote(Note(tsal::C3, 67, 16, 6));
	bass1.addNote(Note(tsal::C3, 67, 28, 4));

	bass1.addNote(Note(tsal::F3, 67, 32, 6));
	bass1.addNote(Note(tsal::F3, 67, 40, 6));
	bass1.addNote(Note(tsal::F3, 67, 48, 6));
	bass1.addNote(Note(tsal::F3, 67, 60, 4));

	bass1.addNote(Note(tsal::Gs3, 67, 64, 6));
	bass1.addNote(Note(tsal::Gs3, 67, 72, 6));
	bass1.addNote(Note(tsal::Gs3, 67, 80, 6));
	bass1.addNote(Note(tsal::Gs3, 67, 92, 4));

	bass1.addNote(Note(tsal::As3, 67, 96, 6));
	bass1.addNote(Note(tsal::As3, 67, 104, 6));
	bass1.addNote(Note(tsal::As3, 67, 112, 6));

	Phrase& lorule = song.addPhrase("LoruleMelody1");
	int loruleId = lorule.getId();
	lorule.setLength(64);
	lorule.addNote(Note(tsal::G4, 100, 0, 24));
	lorule.addNote(Note(tsal::C4, 85, 24, 4));
	lorule.addNote(Note(tsal::G4, 88, 28, 4));
	lorule.addNote(Note(tsal::C5, 92, 32, 4));
	lorule.addNote(Note(tsal::A4, 98, 36, 2));
	lorule.addNote(Note(tsal::As4, 100, 38, 2));
	lorule.addNote(Note(tsal::A4, 95, 40, 20));
	lorule.addNote(Note(tsal::G4, 94, 60, 2));
	lorule.addNote(Note(tsal::F4, 86, 62, 2));

	Phrase& lorule2 = song.addPhrase("LoruleMelody2");
	int lorule2Id = lorule2.getId();
	lorule2.setLength(64);
	lorule2.addNote(Note(tsal::G4, 100, 0, 8));
	lorule2.addNote(Note(tsal::C4, 100, 8, 16));
	lorule2.addNote(Note(tsal::F4, 100, 24, 8));
	lorule2.addNote(Note(tsal::D4, 100, 32, 2));
	lorule2.addNote(Note(tsal::Ds4, 100, 34, 2));
	lorule2.addNote(Note(tsal::D4, 100, 36, 28));

	Phrase& lorule3 = song.addPhrase("LoruleMelody3");
	int lorule3Id = lorule3.getId();
	lorule3.setLength(64);
	lorule3.addNote(Note(tsal::G5, 100, 0, 24));
	lorule3.addNote(Note(tsal::C5, 100, 24, 4));
	lorule3.addNote(Note(tsal::G5, 100, 28, 4));
	lorule3.addNote(Note(tsal::C6, 100, 32, 4));
	lorule3.addNote(Note(tsal::A5, 100, 36, 2));
	lorule3.addNote(Note(tsal::As5, 100, 38, 2));
	lorule3.addNote(Note(tsal::A5, 100, 40, 20));
	lorule3.addNote(Note(tsal::G5, 100, 60, 2));
	lorule3.addNote(Note(tsal::F5, 100, 62, 2));

	Group& g = song.makeNewGroup("part1");

	g.addPhrase(synth1Id, loruleId);
	g.addPhrase(synth1Id, lorule2Id);

	g.addPhrase(synth2Id, bass1Id);

	lt.setSong("Song1");
	lt.setGroup("part1");

	char input;

	std::cout << "Press <enter> to begin:" << std::endl;
	std::cin.get(input);

	lt.play();


	std::cout << "Press <enter> to quit:" << std::endl;
	std::cin.get(input);

	lt.stop();
}
