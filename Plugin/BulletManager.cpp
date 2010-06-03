#include "stdafx.h"
#include "BulletManager.h"
#include <boost/foreach.hpp>

BulletManager::BulletManager()
{
	addSimpleBullet(10, 20, 0);
	addSimpleBullet(10, 30, 1);
}

BulletManager::~BulletManager()
{
	BOOST_FOREACH(Bullet* bullet, bullets_)
	{
		delete bullet;
	}
}

void BulletManager::addSimpleBullet(int x, int y, int speed)
{
	Bullet* b = getNextBullet();
	if(!b) return;
	b->cmd = 0;
	b->pos.x = x;
	b->pos.y = y;
	b->spc = NORMAL_BULLET;
}

Bullet* BulletManager::getNextBullet()
{
	Bullet* newb = new Bullet();
	bullets_.push_back(newb);
	return newb;
}

void BulletManager::move()
{
	/*foreach(Bullet* b in bullets)
	{
		if(b->spc == NOT_EXIST) continue;
		if(b->cmd)
		{
			b->cmd->run();
			if(b->spc == NOT_EXIST)
			{
				if(b->cmd)
				{
					delete b->cmd;
					b->cmd = 0;
				}
				continue;
			}
		}
		//hit check, out of bounds check...
	}*/
}