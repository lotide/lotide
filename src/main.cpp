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
	p.addNote(Note(tsal::A5, 100, 0, q));
	p.addNote(Note(tsal::B5, 100, q, q));
	p.addNote(Note(tsal::C6, 100, 2*q, q));
	p.addNote(Note(tsal::D6, 100, 3*q, q));

	Phrase& p2 = song.addPhrase("Phrase2", synth.getId());
	p2.addNote(Note(tsal::E6, 100, 0, q));
	p2.addNote(Note(tsal::D6, 100, q, q));
	p2.addNote(Note(tsal::F6, 100, 2 * q, q));
	p2.addNote(Note(tsal::E6, 100, 3 * q, q));

	g.addPhrase(0, 0);
	g.addPhrase(0, 1);
	g.addPhrase(0, 0);

	lt.setSong("Song1");
	lt.setGroup("normal");

	char input;
	std::cout << "Press <enter> to begin:" << std::endl;
	std::cin.get(input);

	lt.play();

	std::cout << "Press <enter> to quit:" << std::endl;
	std::cin.get(input);

	lt.stop();

	// Test saving
	lt.save("test.txt");

	// Test loading
	lt.load("Song1", "test.txt");

	lt.setSong("Song1");
	lt.setGroup("normal");

	// Should have list songs (in names)
	std::cout << "Press <enter> to begin:" << std::endl;
	std::cin.get(input);

	lt.play();

	std::cout << "Press <enter> to quit:" << std::endl;
	std::cin.get(input);

	lt.stop();
}
