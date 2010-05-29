#pragma once
#include "tree.h"
#include <boost/shared_ptr.hpp>

class Action;
typedef std::list<Action*> ActionList;

class Bullet;

class Action :
	public Node
{
public:

	Action(void) :
	  repeat_(1)
	{
	}

	~Action(void)
	{
	}

	virtual void step(); //= 0;
protected:
	int repeat_;
	boost::shared_ptr<Bullet> owner;
};

typedef boost::shared_ptr<Bullet> BulletPtr;

//fires a bullet
class Fire :
	public Action
{
public:
	Fire(BulletPtr newowner, int dir, int speed);
	virtual void step();
private:
	int dir_;
	int speed_;
};

//refers to labeled fire action
class FireRef :
	public Action
{
	//BulletList created;
	//BulletPtr bullet = new Bullet(30, 30);
	//created.push_back(bullet);
};

//makes a bullet vanish
class Vanish :
	public Action
{
	//BulletPtr owner;
	//owner()->vanish();
};