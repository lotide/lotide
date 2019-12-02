#include <iostream>

#include "Cli.hpp"

using namespace lotide;

int main(int argc, char *argv[])
{
    Cli cli;
    cli.launch();

    // libzippp::ZipArchive zf("archive.zip");
    // zf.open(libzippp::ZipArchive::READ_ONLY);

    // //raw access
    // char* data = (char*)zf.readEntry("CMakeLists.txt", true);
    // libzippp::ZipEntry entry1 = zf.getEntry("CMakeLists.txt");
    // std::string str1(data, entry1.getSize());

    // //text access
    // libzippp::ZipEntry entry2 = zf.getEntry("CMakeLists.txt");
    // std::string str2 = entry2.readAsText();

    // std::cout<< "hello: " << str1 << ", and: "<< str2 << std::endl;


    // zf.close();
    return 0;
}
