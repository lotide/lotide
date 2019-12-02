#ifndef FILEOPERATIONS_H
#define FILEOPERATIONS_H

#include <iostream>
// #include <tinyxml2.h>
#include <string>
#include <vector>
// #include "libzippp.h"

class FileOperations {
public:
    FileOperations(std::wstring filePath);
    ~FileOperations();

    int load(std::wstring);
    int save(std::wstring);
    std::string unzip(std::wstring);
    // LoTideFile lf;

private:
    std::string fileTypes[4] = {".xml", ".lot", ".midi", ".sf2"};
    std::vector<std::string> fileList;
};

#endif
