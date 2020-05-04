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
	// make a song

	Song& song = lt.addSong("Song1");
	LTSynth& synth = song.addSynth(); 

	synth.getSynth().setParameter(tsal::PolySynth::ENV_ATTACK, 20);
	synth.getSynth().setParameter(tsal::PolySynth::ENV_SUSTAIN, 1);
	synth.getSynth().setParameter(tsal::PolySynth::ENV_DECAY, 4);
	synth.getSynth().setParameter(tsal::PolySynth::ENV_RELEASE, 2);

	synth.getSynth().setParameter(tsal::PolySynth::MODULATION_MODE, tsal::Oscillator::AM);
	synth.getSynth().setParameter(tsal::PolySynth::OSC1_MODE, tsal::Oscillator::SAW);
	synth.getSynth().setParameter(tsal::PolySynth::OSC2_MODE, tsal::Oscillator::SINE);
	synth.getSynth().setParameter(tsal::PolySynth::OSC2_OFFSET, 0.1);

	Phrase& lorule = song.addPhrase("Lorule", synth.getId());
	lorule.addNote(Note(tsal::G4, 100, 0, 24));
	lorule.addNote(Note(tsal::C4, 100, 24, 4));
	lorule.addNote(Note(tsal::G4, 100, 28, 4));
	lorule.addNote(Note(tsal::C5, 100, 32, 4));
	lorule.addNote(Note(tsal::A4, 100, 36, 2));
	lorule.addNote(Note(tsal::As4, 100, 38, 2));
	lorule.addNote(Note(tsal::A4, 100, 40, 20));
	lorule.addNote(Note(tsal::G4, 100, 60, 2));
	lorule.addNote(Note(tsal::F4, 100, 62, 2));

	Phrase& lorule2 = song.addPhrase("Lorule2", synth.getId());
	lorule2.addNote(Note(tsal::G4, 100, 0, 8));
	lorule2.addNote(Note(tsal::C4, 100, 8, 16));
	lorule2.addNote(Note(tsal::F4, 100, 24, 8));
	lorule2.addNote(Note(tsal::D4, 100, 32, 2));
	lorule2.addNote(Note(tsal::Ds4, 100, 34, 2));
	lorule2.addNote(Note(tsal::D4, 100, 36, 28));

	Phrase& lorule3 = song.addPhrase("Lorule3", synth.getId());

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

	g.addPhrase(0, 2);
	g.addPhrase(0, 1);

	Group& g2 = song.makeNewGroup("part2");

	g2.addPhrase(0, 0);
	g2.addPhrase(0, 1);

	lt.setSong("Song1");
	lt.setGroup("part1");

	char input;

	std::cout << "Press <enter> to begin:" << std::endl;
	std::cin.get(input);

	lt.play();

	std::cout << "Press <enter> to change to next group" << std::endl;
	std::cin.get(input);
	lt.setNextGroup("part2");

	std::cout << "Press <enter> to quit:" << std::endl;
	std::cin.get(input);

	lt.stop();
}
