#include "stdafx.h"
#include "Bullet.h"

//Updates position, runs actions, returns any new bullets created
void Bullet::step(float timeDelta)
{
	//run all actions this bullet might have

	x_ += (accX_ + sin(dir_) * speed_) * timeDelta;
	y_ += (-accY_ + cos(dir_) * speed_) * timeDelta;

	//return any new created bullets
}