#include "MidiParser.hpp"
#include <iostream>

namespace tsal {

/**
 * @brief Construct a new MidiParser
 * 
 */
MidiParser::MidiParser() {
  setNumThreads(1);
}

/**
 * @brief Construct a new MidiParser 
 * 
 * @param threads 
 */
MidiParser::MidiParser(unsigned threads) {
  setNumThreads(threads);
}

/**
 * @brief Construct a new MidiParser and reads in a midi file
 * 
 * @param threads 
 * @param filename 
 */
MidiParser::MidiParser(unsigned threads, const std::string& filename) {
  setNumThreads(threads);
  read(filename);
}

/**
 * @brief Read a midi file from disk
 * 
 * A midi file is read and parsed by the midifile library. Useless events are also added 
 * to the events stored in memory so that portions of the song can be equally processed
 * by the number of threads previously specified
 * 
 * @param filename 
 */
void MidiParser::read(const std::string& filename) {
  if (!validPath(filename)) {
    std::cout << "MidiParser: Invalid path to file: " << filename << std::endl;
    return;
  }
  mMidiFile.read(filename);
  
  mHasRead = true;
  mMidiFile.joinTracks();
  mMidiFile.linkNotePairs();

  smf::MidiEventList& midiTrack = mMidiFile[0];

  /* Basically, divide up the track time between the number fo threads
   * Each time segment has to identify the midi note that corresponds
   * to its tick.
   */
  std::vector<unsigned> eventRegions;
  int previousRegionBound = 0;
  int totalTicks = mMidiFile.getFileDurationInTicks();
  for (unsigned i = 0; i < mNumThreads; i++) {
    // Set the new bound for the region
    // Equally divided time between threads
    int tick = (i + 1) * totalTicks/mNumThreads;
    for (int j = 0; j < midiTrack.size(); j++) {
      // Find the events that corresponds to the bound time
      if (midiTrack[j].tick >= tick) {
        // If there are multiple notes at the same tick time, make sure to include them all
        if (j < midiTrack.size() - 1 && midiTrack[j + 1].tick == tick) {
          continue;
        }
        // Add the new midi event region
        eventRegions.push_back(j - previousRegionBound);
        previousRegionBound = j;
        break;
      }
    }
  }

  // Find the biggest region and make sure all other regions match it in midi events size
  unsigned maxRegion = *std::max_element(eventRegions.begin(), eventRegions.end());
  for (unsigned i = 0; i < eventRegions.size(); i++) {
    int tick = i * totalTicks/eventRegions.size();
    for (unsigned j = eventRegions[i]; j < maxRegion; j++) {
      mMidiFile.addNoteOff(0, tick, 0, 21);
    }
  }

  mMidiFile.sortTracks();
}

/**
 * @brief Get a MidiEvent
 * 
 * @param aEvent 
 * @return const smf::MidiEvent& 
 */
const smf::MidiEvent& MidiParser::operator[] (int aEvent) const {
  return mMidiFile[0][aEvent];
}

/**
 * @brief Set a MidiEvent
 * 
 * @param aEvent 
 * @return smf::MidiEvent& 
 */
smf::MidiEvent& MidiParser::operator[] (int aEvent) {
  return mMidiFile[0][aEvent];
}

bool MidiParser::validPath(const std::string& filename) { 
  std::ifstream test(filename); 
  bool isValid = (bool) test;
  test.close();
  return isValid;
}

} 
