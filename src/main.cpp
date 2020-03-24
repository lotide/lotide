#include <iostream>

#include "LoTide.hpp"
#include "LTSynth.hpp"
#include "Group.hpp"
#include "Phrase.hpp"
#include "Note.hpp"

using namespace lotide;

int main(int argc, char *argv[])
{
	lotide::LoTide lt;
	
	Song& song = lt.addSong("Song1");

	LTSynth& synth = song.addSynth();

	Group& g = song.makeNewGroup("normal");

	Phrase& p = song.addPhrase("tempPhrase", synth.getId());
	p.addNote(Note(tsal::A5, 50, 1, 5));

	g.addPhrase(synth.getId(), p.getId());

	lt.setSong("Song1");
	lt.setGroup("normal");

	lt.play();
}
