#include "FileOperations.hpp"

namespace lotide {

FileOperations::FileOperations(std:wstring filePath) {

}

FileOperations::~FileOperations() {
}

// TODO Parse OS for tmp directory
// TODO Test if file extension is correct
// Operate accordingly
int FileOperations::load(std::wstring filePath) {
    // Extract

    // Read from file
    XMLDocument doc;
    // Parse buffer (from zip)
    doc.Parse(zf);

    // return status of success or maybe just error handle

    // send reference of file path of midi files and sound fonts to

    return 1;
}

int FileOperations::save(std::wstring destPath) {
    // Write to tmp directory xml
    XMLDocument doc;
    doc.SaveFile( "foo.xml" );

    XMLPrinter printer( fp );
    doc.Print( &printer );

    // Compare changes made other than xml (i.e. whic file have changed so far)
    // add xml and change made to zip or other
    // This doesn't get case of entirely new file
    char* buffer = buf;
    uint32_t bufferSize = sizeOfBuffer;

    ZipArchive* zf = ZipArchive::fromBuffer(buf, bufferSize);
    /* work with zf */
    zf->close();
    delete zf;

    // return status of success or maybe just error handle
    return 1;
}

int unzip(std:wstring filePath) {
    libzippp::ZipArchive zf(filePath);
    zf.open(libzippp::ZipArchive::READ_ONLY);

    std::vector<libzippp::ZipEntry> entries = zf.getEntries();
    std::vector<libzippp::ZipEntry>::iterator it;
    for(it = entries.begin(); it != entries.end(); ++it) {
        libzippp::ZipEntry entry = *it;

        std::string name = entry.getName();
        int size = entry.getSize();

        //the length of binaryData will be size
        void* binaryData = entry.readAsBinary();

        //the length of textData will be size
        std::string textData = entry.readAsText();

        std::cout << textData << std::endl;
        std::cout << name << std::endl;
    }

    zf.close();
}


}
