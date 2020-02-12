#include "Note.hpp"

namespace lotide {

Note::Note(double n, double v, int s, int d) {
	note = n;
	velocity = v;
	startTime = s;
	duration = d;
}

double Note::getNote() {
	return note;
}

double Note::getVelocity(){ 
	return velocity;
}

int Note::getStartTime(){ 
	return startTime;
}

int Note::getDuration(){ 
	return duration;
}

void Note::setNote(double n){ 
	note = n;
}

void Note::setVelocity(double v){ 
	velocity = v;
}

void Note::setStartTime(int t){ 
	startTime = t;
}

void Note::setDuration(int d){ 
	duration = d;
}


}