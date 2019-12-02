#include "Hello.hpp"
#include "libzippp.h"
// #include <libzippp>


int main(int argc, char *argv[])
{
    Hello hi;
    hi.print();
    libzippp::ZipArchive zf("archive.zip");
    zf.open(ZipArchive::READ_ONLY);
    zf.close();
    return 0;
}
