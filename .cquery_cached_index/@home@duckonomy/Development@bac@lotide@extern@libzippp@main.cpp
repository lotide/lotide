#include "libzippp.h"
#include <iostream>
using namespace libzippp;

int main() {
    ZipArchive zf("hello.zip");
    zf.open(ZipArchive::READ_ONLY);
    
    std::vector<ZipEntry> entries = zf.getEntries();
    std::vector<ZipEntry>::iterator it;
    for(it=entries.begin(); it!=entries.end(); ++it) {
        ZipEntry entry = *it;
        std::string name = entry.getName();
        int size = entry.getSize();
      
        //the length of binaryData will be size
        void* binaryData = entry.readAsBinary();
      
        //the length of textData will be size
        std::string textData = entry.readAsText();
      
        //...
        std::cout << textData << std::endl;
        std::cout << name << std::endl;
    }
    
    zf.close();
}

