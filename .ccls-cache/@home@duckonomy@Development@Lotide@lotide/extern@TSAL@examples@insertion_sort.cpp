#include "tsal.hpp"

using namespace tsal;

#define MAX_VALUE 100000

void insertionSort(ThreadSynth& synth, int size, int* data) {
  int insertValue;
  int j;
  for (int i = 1; i < size; i++) {
    insertValue = data[i];
    j = i;
    while (j > 0 && data[j - 1] > insertValue) {
      synth.play(C3 + 45 * ((double) data[j] / MAX_VALUE), Timing::MICROSECOND, 50);
      
      data[j] = data[j - 1];
      j--;
    }
    data[j] = insertValue;
  }
}

int main() {
  Mixer mixer;
  ThreadSynth synth;
  mixer.add(synth);
  synth.setEnvelopeActive(false);

  // Generate data
  const int size = 5000;
  int* data = new int[size];
  for (int i = 0; i < size; i++) {
    data[i] = rand() % MAX_VALUE;
  }
  // Sort the data
  insertionSort(synth, size, data);
} 

