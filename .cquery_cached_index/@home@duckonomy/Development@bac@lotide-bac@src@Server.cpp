#include "FileOperations.hpp"
#include <iostream>

namespace lotide {

FileOperations::FileOperations() {
}

FileOperations::~FileOperations() {
}


// Parse OS because of TEMP directory
// Extract to TEMP
// Use tinyxml2 to load lotide object and file object
// Test if file extension is correct
int FileOperations::loadFile(std::string filePath) {
    // Extract

    // Read from file
    XMLDocument doc;
    doc.LoadFile( "file.xml" );
    // return status of success or maybe just error handle

    // send reference of file path of midi files and sound fonts to

    return 1;
}

// take
// Test if file extension is correct
int FileOperations::saveFile(std::string filePath) {
    // Write to tmp directory xml
    XMLDocument doc;
    doc.SaveFile( "foo.xml" );

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

Lotide FileOperations::getLotideObjectFile(void) const {

    return lotideObject;
}

void FileOperations::setLotideObjectFile(Lotide lotide) const {
    lotideObject = lotide;
}

bool unzip(const std::wstring &zipPath, const std::wstring &desPath)
{
    int err;
    struct zip *hZip = zip_open_w(zipPath.c_str(), 0, &err);
    if (hZip)
    {
        size_t totalIndex = zip_get_num_entries(hZip, 0);
        for (size_t i = 0; i < totalIndex; i++)
        {
            struct zip_stat st;
            zip_stat_init(&st);
            zip_stat_index(hZip, i, 0, &st);

            struct zip_file *zf = zip_fopen_index(hZip, i, 0);
            if (!zf)
            {
                zip_close(hZip);
                return false;
            }

            std::vector<char> buffer;
            buffer.resize(st.size);
            zip_fread(zf, buffer.data(), st.size);
            zip_fclose(zf);

            // your code here: write buffer to file
            // desPath
            // st.name: the file name

        }
        zip_close(hZip);
    }
    return true;
}

int launch() {
// TODO replace with nurses
std::string path = "";
std::cin >> path;
}

}
