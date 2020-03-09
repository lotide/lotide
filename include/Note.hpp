#ifndef NOTE_HPP
#define NOTE_HPP

namespace lotide {

class Note {

public:
    Note(double n, double v, int s, int d);
    Note(const Note& otherNote);
    double getNote() const;
    double getVelocity() const;
    int getStartTime() const;
    int getDuration() const;
    void setNote(double n);
    void setVelocity(double v);
    void setStartTime(int t);
    void setDuration(int d);
private:
    double note;
    double velocity;
    int startTime;
    int duration;
};

}

#endif
