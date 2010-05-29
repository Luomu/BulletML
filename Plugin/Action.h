#pragma once
#include <boost/shared_ptr.hpp>

class Bullet;
typedef boost::shared_ptr<Bullet> BulletPtr;

class Action;
typedef std::list<Action*> ActionList;

class Action
{
public:
	Action(BulletPtr newowner) :
	  owner_(newowner),
	  previousFireSpeed_(0.f)
	{}

	void step();
	float previousFireSpeed() const { return previousFireSpeed_; }
	void setPreviousFireSpeed(const float news) { previousFireSpeed_ = news; }
private:
	bool finished_;
	int repeat_;
	BulletPtr owner_;
	int waitframes_;
	float previousFireSpeed_;
};