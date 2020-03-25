#include <iostream>

#include "LoTide.hpp"
#include "LTSynth.hpp"
#include "Group.hpp"
#include "Phrase.hpp"
#include "Note.hpp"

#include <cassert>

using namespace lotide;

int main(int argc, char *argv[])
{
	lotide::LoTide lt;
	
	// make a song
	Song& song = lt.addSong("Song1");

	LTSynth& synth = song.addSynth();
	synth.play(tsal::A5, 50);		//Debug play - no sound

	// all of these pass :(
	// still no sound
	assert(&lt.getMixer() == &synth.getSynth().getMixer());
	assert(&lt.getMixer() == &song.getMixer());
	assert(&synth.getSynth().getMixer() == &song.getMixer());

	// If I do this, sound plays:
	tsal::Mixer m;
	LTSynth synth2(0, m);
	m.add(synth2.getSynth());
	synth2.play(tsal::A4, 50);
	synth2.play(tsal::C4, 50);
	synth2.play(tsal::E4, 50);

	Group& g = song.makeNewGroup("normal");

	Phrase& p = song.addPhrase("tempPhrase", synth.getId());
	p.addNote(Note(tsal::A5, 100, 0, 90));

	g.addPhrase(synth.getId(), p.getId());

	lt.setSong("Song1");
	lt.setGroup("normal");

	lt.play();

	char input;
	std::cout << "Press <enter> to quit:" << std::endl;
	std::cin.get(input);

	lt.stop();

	synth2.stop(tsal::A4);
	synth2.stop(tsal::C4);
	synth2.stop(tsal::E4);
}
