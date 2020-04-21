#include <iostream>

#include "LoTide.hpp"
#include "LTSynth.hpp"
#include "Group.hpp"
#include "Phrase.hpp"
#include "Sequencer.hpp"
#include "Note.hpp"

#include "Server.hpp"

using namespace lotide;

int main()
{
	Server serv(8198);
	serv.init();
}
