#include "tsal.hpp"

using namespace tsal;

#define MAX_VALUE 10000

void selectionSort(ThreadSynth& synth, int size, int* data) {
  int min;
  int temp;
  for (int i = 0; i < size; i++) {
    min = i; 
    for (int j = i; j < size; j++) {
      synth.play(C2 + 55 * ((double) data[j] / MAX_VALUE), Timing::MICROSECOND, 100);
      
      min = data[j] < data[min] ? j : min;
    }
    temp = data[i];
    data[i] = data[min];
    data[min] = temp;
  }
}

int main() {
  Mixer mixer;
  ThreadSynth synth;
  mixer.add(synth);
  synth.setEnvelopeActive(false);
  
  // Generate the data
  const int size = 500;
  int* data = new int[size];
  for (int i = 0; i < size; i++) {
    data[i] = rand() % MAX_VALUE;
  }
  // Sort the data
  selectionSort(synth, size, data);
}
