#pragma once
#include "Bullet.h"

//holds the bullets, calls their commands
class BulletManager
{
public:
	std::list<Bullet*>& bullets() { return bullets_; }

	void move();

private:
	std::list<Bullet*> bullets_;
};