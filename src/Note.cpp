#include "Note.hpp"

namespace lotide {

unsigned Note::nextId = 0;

Note::Note() {
	note = 0;
	velocity = 0;
	startTime = 0;
	duration = 0;

	id = 0;
}

Note::Note(double n, double v, int s, int d) : note(n), velocity(v), startTime(s), duration(d), id(nextId) {
	nextId++;
}

Note::Note(const Note& otherNote) {
	note = otherNote.getNote();
	velocity = otherNote.getVelocity();
	startTime = otherNote.getStartTime();
	duration = otherNote.getDuration();

	id = otherNote.id;
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
