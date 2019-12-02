#include <LoTide.hpp>

namespace lotide {

// Pass in object reference
LoTide::LoTide(std:wstring filePath) {
    // Load files
    FileOperations fo = new FileOperations(filePath, LoTideFile);
    // Use data received from fileoperations
    this.midiFiles = lo.midi;

    // Initialize
    this.sf2Files  = lo.sf;
}

LoTide::~LoTide() {
    delete fo;
}


} // end of namespace lotide
