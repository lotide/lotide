#include "LoTide.hpp"
#include "Sequencer.hpp"

/*
  Groups are settings for how the song is played
  They are discrete
  They contain all instruments and information
  on what tracks those instruments play

  ------

  Chains are an implementation which allow for
  pathing through the graph in defined ways

*/

namespace lotide {

	LoTide::LoTide() : sequencer(90) {
	}

	Song& LoTide::addSong(std::string name) {
		songs.emplace_back(Song(name, masterMixer));

		return songs[songs.size() - 1];
	}

	void LoTide::setSong(std::string name) {
		for (Song& s : songs) {
			if (s.getName() == name) {
				sequencer.setSong(s);
			}
		}
	}

	void LoTide::setGroup(std::string name) {
		Song* activeSong = &sequencer.getSong();

		if (activeSong) {
			activeSong->setGroup(name);
		}
	}

	void LoTide::setNextGroup(std::string name) {
		Song* activeSong = &sequencer.getSong();

		if (activeSong) {
			activeSong->setNextGroup(name);
		}
	}

	void LoTide::play() {
		sequencer.start();
	}

	void LoTide::stop() {
		sequencer.stop();
	}

	// TODO make it so that it filters the name rather than getting a song
	// TODO or make it so that it imports all the songs in song array
	void LoTide::load(std::string name, std::string filePath) {
		Song song;
		std::ifstream ifs(filePath);

		if (ifs.good()) {
			cereal::JSONInputArchive archive_in(ifs);
			archive_in(song);
		} else {
			assert(false);
		}

		song.init(masterMixer);

		songs.emplace_back(std::move(song));
	}

	void LoTide::save(std::string filePath) {
		Song& song = sequencer.getSong();

		std::ofstream ofs(filePath);

		if (ofs.good()) {
			cereal::JSONOutputArchive archive_out(ofs);
			archive_out(song);
		} else {
			assert(false);
		}
	}

	std::string LoTide::serializeJSON() {
		Song& song = sequencer.getSong();
		std::stringstream os;

		if (os.good()) {
			cereal::JSONOutputArchive archive_out(os);
			archive_out(CEREAL_NVP(song));
		} else {
			assert(false);
		}

		return os.str();
	}

	Song& LoTide::getActiveSong() {
		return sequencer.getSong();
	}
}
