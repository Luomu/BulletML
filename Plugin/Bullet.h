#ifndef BULLET_H
#define BULLET_H

#include "Tree.h"
#include "Action.h"

typedef std::list<Action> ActionList;

class Bullet : public Node
{
	friend class ExtObject;
	friend class EditExt;
public:
	Bullet(int xpos, int ypos) :
		x_(xpos),
		y_(ypos),
		finished_(false),
		speed_(250.f),
		dir_(0.f),
		accX_(0.f),
		accY_(0.f)
	{ }

	void step(float timedelta = 0.5f);
	void vanish();

	bool finished() const { return finished_; }
	bool vanished() const { return finished_; }
	int x() const { return x_; }
	int y() const { return y_; }
	float speed() const { return speed_; }
private:
	int x_;
	int y_;
	bool finished_;
	float speed_;
	float accX_;
	float accY_;
	float dir_;
	ActionList actions_;
};

#endif