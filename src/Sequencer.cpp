#include "Sequencer.hpp"

namespace lotide {

Sequencer::Sequencer(LoTide& parent) {
	isPlaying = false;
	loTide = parent;
	currentTIme = -1;
}

// Corresponds to when the songs should start to play
// Timing events will now be relative to when this is called
void Sequencer::start() {
	findUpcomingNotes();

	isplaying = true;

	std::thread thread_obj(tick);
}

void Sequencer::start(int time) {
	currentTime = time - 1;
	start();
}

void Sequencer::stop() {
	clearAll();

	isPlaying = false;
}

// Look in LoTide to find all notes which need to be added
void Sequencer::findUpcomingNotes() {
	std::unordered_map<tsal::Synth, std::queue<Note>> newUpcoming = loTide.getUpcoming(currentTime);

	for (std::pair<tsal::Synth, std::queue<Note>> newNotes : newUpcoming) {
		tsal::Synth newSynth = newNotes.first();

		for (Note newNote : newNotes.second()) {
			addUpcoming(newNote, newSynth);
		}
	}
}

void Sequencer::processNotes() {
	// check if notes need to be stopped
	for (std::pair<tsal::Synth, std::queue<Note>> playingNotes : playing) {
		tsal::Synth synth = playingNotes.first();

		std:queue<Note> toBeRemoved;

		for (Note playingNote : playingNotes.second()) {
			if (playingNote.getDuration() <= currentTime - playingNote.getStartTime()) {
				synth.stop(playingNote.getNote());
			}
		}
	}
}

void Sequencer::addUpcoming(Note note, tsal::Synth synth) {
	if (playing.find(synth) == playing.end()) {
		std::queue<Note> synthNotes;
		synthNotes.push(note);

		playing.insert(std::make_pair<tsal::Synth, std::queue<Note>>(synth, synthNotes));
	} else {
		playing[synth].push(note);
	}

	synth.play(note.getNote(), note.getVelocity());
}

void Sequencer::tick() {
	currentTime++;

	findUpcomingNotes();
	processNotes();

	//std::this_thread::sleep_for(std::chrono::milliseconds(ms));

	if (isPlaying) {
		tick();
	}
}

void Sequencer::clearAll() {
	for (std::pair<tsal::Synth, std::queue<Note>> noteList : playing) {
		noteList.first.stop();
	}

	playing.clear();
}

}