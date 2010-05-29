#include "stdafx.h"
#include "Action.h"
#include "Bullet.h"

void Action::step()
{

}

Fire::Fire(BulletPtr newowner, int dir, int speed) :
	dir_(dir),
	speed_(speed)
{
	owner = newowner;
}

void Fire::step()
{
	//owner->setX(owner->x() + 1);
	owner->x_++;
}