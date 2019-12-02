#ifndef FILEOPERATIONS_H
#define FILEOPERATIONS_H

#include <iostream>
#include <tinyxml2.h>
#include <libzippp.h>

// Object structure
#include <LoTide.h>

namespace lotide {

class FileOperations {
public:
    FileOperations(void);
    ~FileOperations(void);

    int load(std::string);
    int save(std::string);

private:
    // Should have one for each song
    std::string midiFiles[];
    std::string sfFiles[];
    const std::string fileTypes[] = ["what", "", ""];


};

} // end of namespace lotide

#endif
