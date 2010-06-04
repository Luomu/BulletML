#include "stdafx.h"
#include <boost/foreach.hpp>
#include "bulletml/bulletmlparser-tinyxml.h"
#include "BulletManager.h"

BulletManager::BulletManager() :
	parser_(0)
{
	std::string filename("test.xml");
	parser_ = new BulletMLParserTinyXML(filename);
	parser_->build();
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
	b->spd = speed;
	b->dir = direction;
	b->spc = NORMAL_BULLET;
}

void BulletManager::addActiveBullet(int x, int y, double rank, int dir,
									int speed, BulletMLState* state)
{
	Bullet* b = getNextBullet();
	if(!b) return;
	b->cmd = new BulletCommand(state, b);
	b->pos.x = x;
	b->pos.y = y;
	b->vel.x = b->vel.y = 0;
	b->dir = dir;
	b->spd = speed;
	b->type = 0;
	b->spc = ACTIVE_BULLET;
}

Bullet* BulletManager::getNextBullet()
{
	Bullet* newb = new Bullet();
	bullets_.push_back(newb);
	return newb;
}

void BulletManager::move(float timeDelta)
{
	int dx = 0;
	int dy = 0;
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
		b->pos.x += dx + sin(RADIANS(b->dir)) * b->spd * timeDelta;
		b->pos.y += -dy + cos(RADIANS(b->dir)) * b->spd * timeDelta;
		b->cnt++;

		b->lifetime += timeDelta * 1000;
		if(b->lifetime > MAXLIFETIME) removeBullet(b);
		//hit check, out of bounds check...
	}
}

void BulletManager::removeBullet(Bullet* b)
{
	b->spc = NOT_EXIST;
}

void BulletManager::clean()
{
	BOOST_FOREACH(Bullet* bullet, bullets_)
	{
		if(bullet->spc != NOT_EXIST) continue;
		if(bullet->cmd != 0) continue;
		delete bullet;
	}
}