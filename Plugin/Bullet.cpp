#include "stdafx.h"
#include "Action.h"
#include "Bullet.h"
#include <boost/foreach.hpp>

//Updates position, runs actions, returns any new bullets created
BulletList* Bullet::step(float timeDelta)
{
	BulletList* newbullets = 0;
	//run all actions this bullet might have
	BOOST_FOREACH(Action* action, actions_)
	{
		action->step();
	}

	x_ += (accX_ + sin(dir_) * speed_) * timeDelta;
	y_ += (-accY_ + cos(dir_) * speed_) * timeDelta;

	//TODO: die if lifetime or range exceeded

	//return any new created bullets
	return newbullets;
}

Bullet::~Bullet()
{
	for (ActionList::iterator i = actions_.begin(), e = actions_.end(); i != e; )
	{
		ActionList::iterator tmp(i++);
		delete *tmp;
		actions_.erase(tmp);
	}

}

//Vanish this bullet and stop all actions
void Bullet::vanish()
{
	finished_ = true;
}

void Bullet::addAction(Action* newact)
{
	actions_.push_back(newact);
}

void Bullet::setX(const int newx)
{
	x_ = newx;
}

void Bullet::setY(const int newy)
{
	y_ = newy;
}