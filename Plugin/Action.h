#pragma once
#include <boost/shared_ptr.hpp>

class Bullet;
typedef boost::shared_ptr<Bullet> BulletPtr;
typedef std::list<BulletPtr> BulletList;

class Action;
typedef std::list<Action*> ActionList;

class SubAction;

class Action
{
public:
	Action(BulletPtr newowner);

	BulletList* step();
	float previousFireSpeed() const { return previousFireSpeed_; }
	void setPreviousFireSpeed(const float news) { previousFireSpeed_ = news; }
	SubActionList& actions();
private:
	bool finished_;
	int repeat_;
	BulletPtr owner_;
	int waitframes_;
	float previousFireSpeed_;
	SubActionList actions_;
};