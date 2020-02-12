#include "LoTide.hpp"

/*
Groups are settings for how the song is played
They are discrete
They contain all instruments and information
on what tracks those instruments play

------

Chains are an implementation which allow for 
pathing through the graph in defined ways

*/

namespace lotide {

// LoTide::LoTide(std::string filePath) {
//     load(filePath);
// }

LoTide::LoTide() {
    // synth = new tsal::PolySynth(&mixer);
    // tsal::Mixer mixer;
}

// LoTide::~LoTide() {
    // delete &midiFiles;
// }

// TODO: Add different file types
// TODO: Confirm load when load exists
// TODO: Compare size
int LoTide::load(std::string filePath) {
    libzippp::ZipArchive zf(filePath);
    zf.open(libzippp::ZipArchive::READ_ONLY);
    char* data = (char*)zf.readEntry("meta.xml", true);
    libzippp::ZipEntry entry = zf.getEntry("meta.xml");
    std::string fullText = entry.readAsText();

    std::cout<< fullText << std::endl;

    tinyxml2::XMLDocument doc;
    doc.Parse(fullText.c_str());

    // TODO: loop through list
    projectName = doc.FirstChildElement( "lotide" )->FirstChildElement( "name" )->GetText();
    midiFiles.push_back(doc.FirstChildElement( "lotide" )->FirstChildElement( "tracks" )->FirstChildElement( "path" )->GetText());

    std::cout << projectName << std::endl;
    std::cout << midiFiles[0] << std::endl;

    zf.close();

    return 0;
}

// polymorphic by obj type or just parse filepath
// TODO: Add different file types
int LoTide::save(std::string filePath) {
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLNode *root = doc.NewElement("lotide");
    doc.InsertFirstChild(root);

    tinyxml2::XMLElement *element = doc.NewElement("name");
    element->SetText(projectName.c_str());
    root->InsertEndChild(element);

    tinyxml2::XMLElement *trackElement = doc.NewElement("tracks");

    for (const auto &tracks : midiFiles) {
        tinyxml2::XMLElement *midiElement = doc.NewElement("path");
        midiElement->SetText(tracks.c_str());
        trackElement->InsertEndChild(midiElement);
    }
    root->InsertEndChild(trackElement);

    tinyxml2::XMLPrinter printer;
    doc.Print(&printer);

    libzippp::ZipArchive zf(filePath);
    zf.open(libzippp::ZipArchive::WRITE);
    const char* textData = printer.CStr();
    zf.addData("meta.xml", textData, 12);

    zf.close();

    return 0;
}

void LoTide::play() {
    tsal::Mixer mixer;
    tsal::PolySynth synth(&mixer);
    mixer.add(synth);
    synth.play(tsal::C4);
    char input;
    std::cout << "Press <enter> to quit:" << std::flush;
    std::cin.get(input);
}

std::unordered_map<tsal::Synth, std::queue<Note>> getUpcoming(int time) {
    
}

// LoTide::pause(Track t) {

// }

// LoTide::stop (Track t) {
//     synth.stop(C4);
// }

// LoTide::addC4(Track t) {

// }

// std::string LoTide::unzipXML(std::string filePath) {


// }


} // end of namespace lotide
