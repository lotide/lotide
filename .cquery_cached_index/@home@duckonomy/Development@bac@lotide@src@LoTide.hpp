#ifndef LOTIDE_H
#define LOTIDE_H

#include <vector>
#include <string>

#include "FileOperations.hpp"

namespace lotide {

class LoTide {
public:
     // Pass in object reference
    LoTide(std::wstring);
    ~LoTide();

private:
    std::vector<std::string> midiFiles;
    std::vector<std::string> sf2Files;
};

}

#endif
