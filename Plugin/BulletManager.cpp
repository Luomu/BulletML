#include "stdafx.h"
#include "BulletManager.h"
#include <boost/foreach.hpp>

BulletManager::BulletManager()
{
	addSimpleBullet(10, 20, 0, 0);
	addSimpleBullet(10, 30, 1, 0);
	addSimpleBullet(30, 30, 10, 0);
}

BulletManager::~BulletManager()
{
	BOOST_FOREACH(Bullet* bullet, bullets_)
	{
		delete bullet;
	}
}

void BulletManager::addSimpleBullet(int x, int y, int speed, int direction)
{
	Bullet* b = getNextBullet();
	if(!b) return;
	b->cmd = 0;
	b->pos.x = x;
	b->pos.y = y;
	b->dir = direction;
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
	int dx = 0;
	int dy = 1;
	BOOST_FOREACH(Bullet* b, bullets_)
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
		b->pos.x += dx;
		b->pos.y += dy;
		b->cnt++;
		//hit check, out of bounds check...
	}
}

void BulletManager::removeBullet(Bullet* b)
{
	b->spc = NOT_EXIST;
}