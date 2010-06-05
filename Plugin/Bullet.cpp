#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet()
{
	pos.x = 0;
	pos.y = 0;
	dir = 0;
	spd = 0;
	cmd = 0;
	rank = 0;
	spc = NORMAL_BULLET;
	type = 0;
	cnt = 0;
	color = 0;
	hit = 0;
	parser = 0;
	vel.x = 0;
	vel.y = 0;
	lifetime = 0;
}

Bullet::~Bullet()
{
	//assert(cmd == 0);
	if(cmd != 0)
	{
		delete cmd;
		cmd = 0;
	}
}