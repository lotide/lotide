#ifndef NOTE_HPP
#define NOTE_HPP

namespace lotide {

class Note {

public:
    Note(double n, double v, int s, int d);
    double getNote();
    double getVelocity();
    int getStartTime();
    int getDuration();
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
