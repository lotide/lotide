#include "Sequencer.hpp"


namespace lotide {

	Sequencer::Sequencer(unsigned bpm) : mBpm(bpm) {
		isPlaying = false;
		currentTime = -1;

		activeSong = NULL;
	}

	// Corresponds to when the songs should start to play
	// Timing events will now be relative to when this is called
	void Sequencer::start() {
		isPlaying = true;

		std::thread thread_obj(&Sequencer::tick, this);
		thread_obj.detach();
	}

	void Sequencer::start(unsigned time) {
		this->currentTime = time - 1;
		start();
	}

	void Sequencer::stop() {
		isPlaying = false;
	}

	// Look in LoTide to find all notes which need to be added
	void Sequencer::findUpcomingNotes() {	
		if (activeSong == NULL) {
			return;
		}

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
			std::vector<LTSynth*> synths = activeSong->getSynths();

			LTSynth* synth = synths[playingNotes.first];

			std::vector<int> toBeRemoved;

			for (int i = 0; i < playingNotes.second.size(); i++) {
				Note& playingNote = playingNotes.second[i];

				if (playingNote.getDuration() <= abs(currentTime - noteTimes.at(playingNote))) {
					synth->stop(playingNote.getNote());
					noteTimes.erase(playingNote);
					toBeRemoved.push_back(i);
				}
			}

			int offset = 0;
			for (int remIndex : toBeRemoved) {
				playingNotes.second.erase(playingNotes.second.begin() + remIndex - offset);
				offset++;
			}

			playing[playingNotes.first] = std::move(playingNotes.second);
		}
	}

	void Sequencer::addUpcoming(Note note, unsigned synthId) {
		std::vector<LTSynth*> synths = activeSong->getSynths();

		if (playing.find(synthId) == playing.end()) {
			std::vector<Note> synthNotes;
			synthNotes.push_back(note);

			playing.insert(std::pair<unsigned, std::vector<Note>>(synthId, std::move(synthNotes)));
		} else {
			playing[synthId].push_back(note);
		}

		noteTimes[note] = currentTime;

		LTSynth* synth = synths[synthId];
		synth->play(note.getNote(), note.getVelocity());
	}

	void Sequencer::tick() {
		std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

		unsigned currentLength = activeSong->getLength();
		currentTime = (currentTime + 1) % currentLength;

		if (currentTime == 0) {
			clearAll();
		}

		findUpcomingNotes();
		processNotes();

		std::chrono::system_clock::time_point after = std::chrono::system_clock::now();

		std::chrono::milliseconds time = max(std::chrono::milliseconds(0),
			std::chrono::milliseconds(60000 / (mBpm * ppq))
			- std::chrono::duration_cast<std::chrono::milliseconds>(after - now));

		std::this_thread::sleep_for(time);

		if (isPlaying) {
			tick();
		}
		else {
			clearAll();
		}
	}

	void Sequencer::clearAll() {
		if (!activeSong) {
			return;
		}

		std::vector<LTSynth*> synths = activeSong->getSynths();

		for (std::pair<unsigned, std::vector<Note>> noteList : playing) {
			LTSynth* synth = synths[noteList.first];

			for (double note = tsal::A0; note != tsal::Gs7; note++) {
				synth->stop(note);
			}
			synth->stop(tsal::Gs7);

			noteList.second.clear();
		}
	}

	void Sequencer::setSong(Song& s) {
		activeSong = &s;
	}
}