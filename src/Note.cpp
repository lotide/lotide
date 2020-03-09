#include "Note.hpp"

namespace lotide {

Note::Note(double n, double v, int s, int d) {
	note = n;
	velocity = v;
	startTime = s;
	duration = d;
}

Note::Note(const Note& otherNote) {
	note = otherNote.getNote();
	velocity = otherNote.getVelocity();
	startTime = otherNote.getStartTime();
	duration = otherNote.getStartTime();
}

double Note::getNote() const {
	return note;
}

double Note::getVelocity() const { 
	return velocity;
}

int Note::getStartTime() const { 
	return startTime;
}

int Note::getDuration() const { 
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