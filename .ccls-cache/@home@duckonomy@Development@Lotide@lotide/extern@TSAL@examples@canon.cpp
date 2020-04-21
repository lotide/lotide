#include "tsal.hpp"
#include <omp.h>
#include <vector>

/** @example canon.cpp
 * 
 * ThreadSynth is an instrument that uses blocking calls to schedule its midi events.
 * If this instrument was used in a process with only one thread, there could only be 
 * one synth playing at a time. To achieve a multi-instrument sound, each ThreadSynth
 * will need its own thread. The omp parallel pragma creates these threads for each synth
 * so that when the ThreadSynth makes a call to play or stop, only that synth's thread
 * is blocked
 * 
 * A canon (or a round) is a musical composition technique that takes a melody and duplicates it over multiple voices with some variation in time offset or pitch.
 * In this example, the given midifile is played on the specified number of threads, each with a measure offset
 *
 * Jubilate Deo is a basic round
 * https://youtu.be/ILLvDfsI_iM?t=33 (sine waves sounds less angelic)
 * 
 * Parse the parameters\n
 * Create the mixer and synths\n
 * Set the number of threads\n
 * Run parallel block
 * - Calculate an offset into the song for a round effect
 * - Play the midi events
 */
int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cout << "Invalid arguments\n\n"
              << "canon <midifile> <voices>\n" 
              << "\tmidifile = a path to a midifile\n" 
              << "\tvoices = the number of voices (<6)\n"
              << std::endl;
    return 0;
  }
  tsal::MidiParser midiParser(1, argv[1]);
  const int numVoices = atoi(argv[2]);


  tsal::Mixer mixer;
  std::vector<tsal::ThreadSynth> voices(numVoices, tsal::ThreadSynth(mixer.getContext()));  

  omp_set_num_threads(numVoices);

  #pragma omp parallel
  {
    int id = omp_get_thread_num();
    
    mixer.add(voices[id]);
    
    voices[id].setVolume(0.5);
    
    // Wait to come in based on thread id
    voices[id].stop(tsal::Timing::HALF, id);

    for (unsigned i = 0; i < midiParser.size(); i++) {
      auto& me = midiParser[i];
      if (me.isNoteOn()) {
        voices[id].play(me.getKeyNumber(), tsal::Timing::TICK, me.getTickDuration()); 
      }
    }
  }
  return 0;
}
