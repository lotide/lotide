#include <iostream>

#include "LoTide.hpp"
#include "LTSynth.hpp"
#include "Group.hpp"
#include "Phrase.hpp"
#include "Note.hpp"
#include <typeinfo>

using namespace lotide;

int main(int argc, char *argv[])
{
	lotide::LoTide lt;

	// make a song
	Song& song = lt.addSong("Song1");

	LTSynth& synth = song.addSynth();

	Group& g = song.makeNewGroup("normal");

	Phrase& p = song.addPhrase("tempPhrase", synth.getId());
	p.addNote(Note(tsal::A5, 100, 0, 45));
	p.addNote(Note(tsal::B5, 100, 45, 45));
	p.addNote(Note(tsal::C6, 100, 90, 45));
	p.addNote(Note(tsal::D6, 100, 135, 45));

	g.addPhrase(synth.getId(), p.getId());

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
