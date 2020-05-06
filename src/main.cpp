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

	synth2.getSynth().setParameter(tsal::PolySynth::ENV_ATTACK, 0.1);
	synth2.getSynth().setParameter(tsal::PolySynth::ENV_SUSTAIN, 0.2);
	synth2.getSynth().setParameter(tsal::PolySynth::ENV_DECAY, .05);
	synth2.getSynth().setParameter(tsal::PolySynth::ENV_RELEASE, .1);

	synth2.getSynth().setParameter(tsal::PolySynth::MODULATION_MODE, tsal::Oscillator::MIX);
	synth2.getSynth().setParameter(tsal::PolySynth::OSC1_MODE, tsal::Oscillator::SINE);
	synth2.getSynth().setParameter(tsal::PolySynth::OSC2_MODE, tsal::Oscillator::SQUARE);
	synth2.getSynth().setParameter(tsal::PolySynth::OSC2_OFFSET, 0.3);


	LTSynth& synth = song.addSynth(); 
	int synth1Id = synth.getId();

	synth.getSynth().setParameter(tsal::PolySynth::ENV_ATTACK, .05);
	synth.getSynth().setParameter(tsal::PolySynth::ENV_SUSTAIN, .1);
	synth.getSynth().setParameter(tsal::PolySynth::ENV_DECAY, .6);
	synth.getSynth().setParameter(tsal::PolySynth::ENV_RELEASE, .8);

	synth.getSynth().setParameter(tsal::PolySynth::MODULATION_MODE, tsal::Oscillator::AM);
	synth.getSynth().setParameter(tsal::PolySynth::OSC1_MODE, tsal::Oscillator::SAW);
	synth.getSynth().setParameter(tsal::PolySynth::OSC2_MODE, tsal::Oscillator::SAW);
	synth.getSynth().setParameter(tsal::PolySynth::OSC2_OFFSET, 0.5);

	Phrase& bass1 = song.addPhrase("LoruleBass");
	int bass1Id = bass1.getId();
	bass1.setLength(128);
	bass1.addNote(Note(tsal::C3, 67, 0, 6));
	bass1.addNote(Note(tsal::C3, 67, 8, 6));
	bass1.addNote(Note(tsal::C3, 67, 16, 6));
	bass1.addNote(Note(tsal::C3, 67, 28, 4));

	bass1.addNote(Note(tsal::C3, 67, 32, 6));
	bass1.addNote(Note(tsal::C3, 67, 40, 6));
	bass1.addNote(Note(tsal::C3, 67, 48, 6));
	bass1.addNote(Note(tsal::C3, 67, 60, 4));

	bass1.addNote(Note(tsal::C3, 67, 64, 6));
	bass1.addNote(Note(tsal::C3, 67, 72, 6));
	bass1.addNote(Note(tsal::C3, 67, 80, 6));
	bass1.addNote(Note(tsal::C3, 67, 92, 4));

	bass1.addNote(Note(tsal::C3, 67, 96, 6));
	bass1.addNote(Note(tsal::C3, 67, 104, 6));
	bass1.addNote(Note(tsal::C3, 67, 112, 6));

	Phrase& bass2 = song.addPhrase("LoruleBass2");
	int bass2Id = bass2.getId();
	bass2.setLength(128);
	bass2.addNote(Note(tsal::C3, 67, 0, 6));
	bass2.addNote(Note(tsal::C3, 67, 8, 6));
	bass2.addNote(Note(tsal::C3, 67, 16, 6));
	bass2.addNote(Note(tsal::C3, 67, 28, 4));

	bass2.addNote(Note(tsal::F3, 67, 32, 6));
	bass2.addNote(Note(tsal::F3, 67, 40, 6));
	bass2.addNote(Note(tsal::F3, 67, 48, 6));
	bass2.addNote(Note(tsal::F3, 67, 60, 4));

	bass2.addNote(Note(tsal::Gs3, 67, 64, 6));
	bass2.addNote(Note(tsal::Gs3, 67, 72, 6));
	bass2.addNote(Note(tsal::Gs3, 67, 80, 6));
	bass2.addNote(Note(tsal::Gs3, 67, 92, 4));

	bass2.addNote(Note(tsal::As3, 67, 96, 6));
	bass2.addNote(Note(tsal::As3, 67, 104, 6));
	bass2.addNote(Note(tsal::As3, 67, 112, 6));

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

	Phrase& lorule4 = song.addPhrase("LoruleMelody4");
	int lorule4Id = lorule4.getId();
	lorule4.setLength(64);
	lorule4.addNote(Note(tsal::C4, 100, 0, 32));

	Group& g = song.makeNewGroup("part1");

	g.addPhrase(synth1Id, loruleId);
	g.addPhrase(synth1Id, lorule2Id);
	g.addPhrase(synth1Id, lorule4Id);

	g.addPhrase(synth2Id, bass2Id);
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
