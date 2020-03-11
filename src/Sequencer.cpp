#include "Sequencer.hpp"


namespace lotide {

	Sequencer::Sequencer(unsigned bpm) : mBpm(bpm) {
		isPlaying = false;
		currentTime = -1;
	}

	// Corresponds to when the songs should start to play
	// Timing events will now be relative to when this is called
	void Sequencer::start() {
		findUpcomingNotes();

		isPlaying = true;

		std::thread thread_obj(&Sequencer::tick, this);
	}

	void Sequencer::start(unsigned time) {
		this->currentTime = time - 1;
		start();
	}

	void Sequencer::stop() {
		clearAll();

		isPlaying = false;
	}

	// Look in LoTide to find all notes which need to be added
	void Sequencer::findUpcomingNotes() {
		/*std::vector<tsal::PolySynth>& synths = loTide.getAllSynths();
		
		for (int i = 0; i < synths.size(); i++) {
			std::vector<Note> notes = loTide.getUpcoming(i, currentTime);

			for (Note newNote : notes) {
				addUpcoming(newNote, i);
			}
		}*/
		
	
		std::unordered_map<unsigned, std::vector<Note>> newUpcoming = activeSong->getUpcoming(currentTime);
		for (std::pair<unsigned, std::vector<Note>> newNotes : newUpcoming) {
			unsigned synthId = newNotes.first;

			for (Note newNote : newNotes.second) {
				addUpcoming(newNote, newNotes.first);
			}
		}
	}

	void Sequencer::processNotes() {
		// check if notes need to be stopped
		for (std::pair<unsigned, std::vector<Note>> playingNotes : playing) {
			std::vector<tsal::PolySynth*> synths = activeSong->getSynths();

			tsal::PolySynth* synth = synths[playingNotes.first];

			std::vector<Note> toBeRemoved;

			for (Note playingNote : playingNotes.second) {
				if (playingNote.getDuration() <= currentTime - playingNote.getStartTime()) {
					synth->stop(playingNote.getNote());
				}
			}
		}
	}

	void Sequencer::addUpcoming(Note note, unsigned synthId) {
		std::vector<tsal::PolySynth*> synths = activeSong->getSynths();

		if (playing.find(synthId) == playing.end()) {
			std::vector<Note> synthNotes;
			synthNotes.push_back(note);

			playing.insert(std::pair<unsigned, std::vector<Note>>(synthId, synthNotes));
		} else {
			playing[synthId].push_back(note);
		}

		tsal::PolySynth* synth = synths[synthId];
		synth->play(note.getNote(), note.getVelocity());
	}

	void Sequencer::tick() {
		std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

		currentTime++;

		if (currentTime % (mBpm / 4) == 0) {
			findUpcomingNotes();
			processNotes();
		}

		std::chrono::system_clock::time_point after = std::chrono::system_clock::now();

		std::chrono::milliseconds time = std::chrono::milliseconds(60000 / (mBpm * ppq)) - std::chrono::duration_cast<std::chrono::milliseconds>(after - now);
		std::this_thread::sleep_for(time);

		if (isPlaying) {
			tick();
		}
	}

	void Sequencer::clearAll() {
		std::vector<tsal::PolySynth*> synths = activeSong->getSynths();

		for (std::pair<unsigned, std::vector<Note>> noteList : playing) {
			tsal::PolySynth* synth = synths[noteList.first];

			for (double note = tsal::A0; note != tsal::Gs7; note++) {
				synth->stop(note);
			}
			synth->stop(tsal::Gs7);
		}

		playing.clear();
	}

}