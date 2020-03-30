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
			boost::archive::text_iarchive ia(ifs);
			ia >> song;
		} else {
			assert(false);
		}

		song.init(masterMixer);

		songs.emplace_back(song);
	}

	void LoTide::save(std::string filePath) {
		Song& song = sequencer.getSong();

		std::ofstream ofs(filePath);

		if (ofs.good()) {
			boost::archive::text_oarchive oa(ofs);
			oa << song;
		} else {
			assert(false);
		}
	}

	void LoTide::serve(int port) {
		Server serv(port);
		serv.init();
	}
}
