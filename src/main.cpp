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

	Group& g = song.makeNewGroup("normal");

	Phrase& lorule = song.addPhrase("Lorule", synth.getId());
	lorule.addNote(Note(tsal::G4, 100, 0, 24));
	lorule.addNote(Note(tsal::C4, 100, 24, 4));
	lorule.addNote(Note(tsal::G4, 100, 28, 4));
	lorule.addNote(Note(tsal::C5, 100, 32, 4));
	lorule.addNote(Note(tsal::A4, 100, 36, 2));
	lorule.addNote(Note(tsal::As4, 100, 38, 2));
	lorule.addNote(Note(tsal::A4, 100, 40, 22));
	lorule.addNote(Note(tsal::G4, 100, 60, 2));
	lorule.addNote(Note(tsal::F4, 100, 62, 2));

	lorule.addNote(Note(tsal::G4, 100, 64, 8));
	lorule.addNote(Note(tsal::C4, 100, 72, 16));
	lorule.addNote(Note(tsal::F4, 100, 88, 8));
	lorule.addNote(Note(tsal::D4, 100, 96, 2));
	lorule.addNote(Note(tsal::Ds4, 100, 98, 2));
	lorule.addNote(Note(tsal::D4, 100, 100, 28));

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
}
