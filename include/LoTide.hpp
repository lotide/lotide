#ifndef LOTIDE_HPP
#define LOTIDE_HPP

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>

#ifndef TSF_IMPLEMENTATION
#define TSF_IMPLEMENTATION
#include "tsal.hpp"
#include "Sequencer.hpp"
#include "Note.hpp"
#include "Song.hpp"

namespace lotide {

	class LoTide {
	public:
		LoTide();
		//~LoTide();
		void play();
		void stop();
		void load(std::string name, std::string filePath);
		void save(std::string filePath);
		Song& addSong(std::string name);
		void setSong(std::string name);
		void setGroup(std::string name);
	private:
		tsal::Mixer masterMixer;
		Sequencer sequencer;
		std::vector<Song> songs;
	};

}

#endif
#endif
