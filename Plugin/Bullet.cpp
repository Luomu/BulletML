#include "stdafx.h"
#include "Bullet.h"
#include <boost/foreach.hpp>
#include "Action.h"

//Updates position, runs actions, returns any new bullets created
void Bullet::step(float timeDelta)
{
	//run all actions this bullet might have
	BOOST_FOREACH(Action& action, actions_)
	{
		action.step();
	}

	x_ += (accX_ + sin(dir_) * speed_) * timeDelta;
	y_ += (-accY_ + cos(dir_) * speed_) * timeDelta;

	//return any new created bullets
}

//Vanish this bullet and stop all actions
void Bullet::vanish()
{

}