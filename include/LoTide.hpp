#ifndef LOTIDE_HPP
#define LOTIDE_HPP

#include <cereal/archives/xml.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/types/concepts/pair_associative_container.hpp>
#include <cereal/types/unordered_map.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/vector.hpp>

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
		void play();
		void stop();
		void load(std::string name, std::string filePath);
		void save(std::string filePath);
		std::string serializeJSON();
		Song& addSong(std::string name, int tempo);
		Song& addSong(std::string name);
		Song& getActiveSong();
		void setSong(std::string name);
		void setGroup(std::string name);
		void setNextGroup(std::string name);
		void serve(int port);
		void setTempo(int bpm) { 
			sequencer.setTempo(bpm);
		}
		void setInstrumentPlay(int group1, int group2, int instrumentId);
		void removeInstrument(int instrumentId);
	private:
		tsal::Mixer masterMixer;
		Sequencer sequencer;
		std::vector<Song> songs;
	};

}

#endif
#endif
