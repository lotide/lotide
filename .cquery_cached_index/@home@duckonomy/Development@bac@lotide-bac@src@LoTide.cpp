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
    // Should
    int loadFile(std::string) const;
    int saveFile(std::string);

    // These set lotide object
    Lotide getLotideObject const (void);
    void setLotideObject const (Lotide);

private:
    // Should have one for each song
    Lotide lotideObject;
    Lotide fileObject;
    std::string midiFiles[];
    std::string sfFiles[];
    const std::string fileTypes[] = ["what", "", ""];


};

} // end of namespace lotide

#endif
