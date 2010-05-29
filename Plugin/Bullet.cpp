#include "stdafx.h"
#include "Bullet.h"
#include <boost/foreach.hpp>
#include "Action.h"

//Updates position, runs actions, returns any new bullets created
static int abloo = 0;
BulletList* Bullet::step(float timeDelta)
{
	BulletList* newbullets = 0;
	//run all actions this bullet might have
	BOOST_FOREACH(Action& action, actions_)
	{
		action.step();
	}

	x_ += (accX_ + sin(dir_) * speed_) * timeDelta;
	y_ += (-accY_ + cos(dir_) * speed_) * timeDelta;

	if(y() > 400)
		vanish();

	//return any new created bullets
	return newbullets;
}

//Vanish this bullet and stop all actions
void Bullet::vanish()
{
	finished_ = true;
}