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
	// make a song
	Song& song = lt.addSong("Song1");

	LTSynth& synth = song.addSynth();

	Group& g = song.makeNewGroup("normal");

	Phrase& p = song.addPhrase("Phrase1", synth.getId());
	p.setLength(4 * q);
	p.addNote(Note(tsal::A4, 100, 0, q/2));
	p.addNote(Note(tsal::E3, 100, 0, 4 * q));
	p.addNote(Note(tsal::B4, 100, q, q/2));
	p.addNote(Note(tsal::C5, 100, 2*q, q/2));
	p.addNote(Note(tsal::D5, 100, 3*q, q/2));

	Phrase& p2 = song.addPhrase("Phrase2", synth.getId());
	p2.setLength(4 * q);
	p2.addNote(Note(tsal::C3, 100, 0, 4 * q));
	p2.addNote(Note(tsal::E5, 100, 0, q/2));
	p2.addNote(Note(tsal::D5, 100, q, q/2));
	p2.addNote(Note(tsal::F5, 100, 2 * q, q/2));
	p2.addNote(Note(tsal::E5, 100, 3 * q, q/2));

	g.addPhrase(0, 0);
	g.addPhrase(0, 1);

	lt.setSong("Song1");
	lt.setGroup("normal");

	char input;

	std::cout << "Press <enter> to begin:" << std::endl;
	std::cin.get(input);

	lt.play();

	std::cout << "Press <enter> to quit:" << std::endl;
	std::cin.get(input);

	lt.stop();
}
