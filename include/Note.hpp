#ifndef NOTE_HPP
#define NOTE_HPP

#include <cereal/access.hpp>

namespace lotide {


	class Note {

	public:
		Note();
		Note(double n, double v, int s, int d);
		Note(const Note& otherNote);
		double getNote() const;
		double getVelocity() const;
		int getStartTime() const;
		int getDuration() const;
		unsigned getId() const { return id; }
		void setNote(double n);
		void setVelocity(double v);
		void setStartTime(int t);
		void setDuration(int d);
		static unsigned nextId;
		bool operator ==(const Note& rhs) const {
			return id == rhs.id;
		}
		bool operator <(const Note& rhs) const
		{
			return id < rhs.getId();
		}
		bool operator =(const Note& other) const {
			return id == other.getId();
		}
	private:
		friend class cereal::access;
		template<class Archive>
		void serialize(Archive& ar)
		{
			ar(note, velocity, startTime, duration, id);
		}

		double note;
		double velocity;
		int startTime;
		int duration;
		unsigned id;
		
	};
}

#endif
