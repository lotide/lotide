#include "FileOperations.hpp"

namespace lotide {

FileOperations::FileOperations(std::wstring filePath, LoTideFile &lo) {
    // fp = load(filePath)
    // lo.xml = fp.things // stuct LoTide File
    // lo.midi = fp.midi // struct fp
    //


}

FileOperations::~FileOperations() {

}

// TODO Parse OS for tmp directory
// TODO Test if file extension is correct
// Operate accordingly
int FileOperations::load(std::wstring filePath) {
    // Initial load (lot file) change to enum
    if (this.fileTypes[1].compare(filePath) != 0) {
        XMLDocument doc;
        std::string buf = this.unzip();
        doc.Parse(buf);
    } else if (this.fileTypes[2].compare(filePath) != 0) {
        // Send stuff to lotide/tsal
    } else if (this.fileTypes[3].compare(filePath) != 0) {
        // Send stuff to lotide/tsal
    }
    // TODO: error
    // else {
    //     error
    // }

    // send reference of file path of midi files and sound fonts to

    // return status of success or maybe just error handle
    return 0;
}

// Change size by getting binary size (form libzippp)
int FileOperations::save(std::wstring destPath) {
    // Write to tmp directory xml
    XMLPrinter printer( fp );
    doc.Print( &printer );

    // Determine what files to change
    ZipArchive zf(destPath);
    zf.open(ZipArchive::WRITE);
    zf.addEntry("");

    // TODO: midifile & sound fonts


    // xml part
    const char* textData = "Hello,World!";
    zf.addData(destPath, textData, 12);

    zf.close();

    // Compare changes made other than xml (i.e. whic file have changed so far)
    // add xml and change made to zip or other
    // This doesn't get case of entirely new file
    // char* buffer = buf;
    // uint32_t bufferSize = sizeOfBuffer;

    // ZipArchive* zf = ZipArchive::fromBuffer(buf, bufferSize);
    ZipArchive* zf = ZipArchive::fromBuffer(buf, bufferSize);
    /* work with zf */
    zf->close();
    delete zf;

    // return status of success or maybe just error handle
    return 1;
}

std::string FileOperations::unzip(std::wstring filePath) {
    libzippp::ZipArchive zf(filePath);
    zf.open(libzippp::ZipArchive::READ_ONLY);
    string xml;

    std::vector<libzippp::ZipEntry> entries = zf.getEntries();
    std::vector<libzippp::ZipEntry>::iterator it;
    for(it = entries.begin(); it != entries.end(); ++it) {
        libzippp::ZipEntry entry = *it;

        std::string name = entry.getName();
        std::string textData = entry.readAsText();

        this.fileList.push(name);

        if (this.fileTypes[0].compare(name) != 0) {
            xml = textData;
        }
    }

    zf.close();

    return xml;
}


}
