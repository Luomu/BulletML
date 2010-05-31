#ifndef BULLET_H
#define BULLET_H

#include "Tree.h"
#include "Action.h"
#include <boost/shared_ptr.hpp>

class Bullet;
typedef boost::shared_ptr<Bullet> BulletPtr;
typedef std::list<BulletPtr> BulletList;
typedef std::list<BulletPtr>::iterator BulletIterator;

class Bullet : public Node
{
	friend class ExtObject;
	friend class EditExt;
	friend class Fire;
public:
	Bullet(int xpos, int ypos, float speed = 250.f, float dir = 0.f);
	~Bullet();

	BulletList* step(float timedelta = 0.5f);
	void vanish();
	void addAction(Action*);

	bool finished() const { return finished_; }
	bool vanished() const { return finished_; }
	int x() const { return x_; }
	int y() const { return y_; }
	void setX(const int);
	void setY(const int);
	void setSpeed(const float);
	float speed() const { return speed_; }
	void setDirection(const float);
	std::list<Action*>& actions() { return actions_; }
private:
	int x_;
	int y_;
	bool finished_;
	float speed_;
	float accX_;
	float accY_;
	float dir_;
	std::list<Action*> actions_;
};

#endif