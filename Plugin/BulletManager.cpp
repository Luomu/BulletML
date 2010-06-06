#include "stdafx.h"
#include <boost/foreach.hpp>
#include "bulletml/bulletmlparser-tinyxml.h"
#include "BulletManager.h"

BulletManager::BulletManager() :
	parser_(0),
	finished_(false),
	angle_(0),
	maxLifeTime_(20000)
{
}

BulletManager::~BulletManager()
{
	BOOST_FOREACH(Bullet* bullet, bullets_)
	{
		assert(bullet != 0);
		delete bullet;
	}
	bullets_.clear();
	BOOST_FOREACH(BulletMLParser* trashed, parserTrash_)
	{
		delete trashed;
	}
	parserTrash_.clear();
	delete parser_;
}

void BulletManager::init()
{
	std::string filename("test.xml");
	parser_ = new BulletMLParserTinyXML(filename);
	parser_->build();

	if(parser_ != 0)
	{
		Bullet* b = getNextBullet();
		b->spc = TOP_BULLET;
		b->color = cr::color(RGB(0,255,100));
		b->parser = parser();
		b->cmd = new BulletCommand(parser(), b);
		b->cmd->setManager(this);
	}
}

void BulletManager::load(const std::string& filename)
{
	if(parser_ != 0)
	{
		parserTrash_.push_back(parser_);
	}
	parser_ = new BulletMLParserTinyXML(filename);
	parser_->build();
}

void BulletManager::restart()
{
	if(parser_ != 0)
	{
		Bullet* b = getNextBullet();
		b->spc = TOP_BULLET;
		b->color = cr::color(RGB(0,255,100));
		b->parser = parser();
		b->cmd = new BulletCommand(parser(), b);
		b->cmd->setManager(this);
	}
}

void BulletManager::addSimpleBullet(int x, int y, int speed, int direction)
{
	Bullet* b = getNextBullet();
	if(!b) return;
	b->cmd = 0;
	b->pos.x = x + pos().x;
	b->pos.y = y + pos().y;
	b->spd = speed;
	b->dir = angle_ + 90 + direction;
	b->spc = NORMAL_BULLET;
}

void BulletManager::addActiveBullet(int x, int y, double rank, int dir,
									int speed, BulletMLState* state)
{
	Bullet* b = getNextBullet();
	if(!b) return;
	b->cmd = new BulletCommand(state, b);
	b->cmd->setManager(this);
	b->pos.x = x + pos().x;
	b->pos.y = y + pos().y;
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

void BulletManager::move(const float timeDelta)
{
	bbox_.left = 0;
	bbox_.top = 0;
	bbox_.right = 800;
	bbox_.bottom = 600;
	int dx = 0;
	int dy = 0;
	BOOST_FOREACH(Bullet* b, bullets_)
	{
		assert(b != 0);
		if(b->spc == NOT_EXIST && b->cmd == 0) continue;
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
		b->pos.y -= -dy + cos(RADIANS(b->dir)) * b->spd * timeDelta;
		b->cnt++;

		b->lifetime += timeDelta * 1000;

		if(b->lifetime > maxLifeTime_ && b->cmd == 0) removeBullet(b);
		//hit check, out of bounds check...

		//update bbox
		/*if(b->spc == NOT_EXIST) continue;
		if(b->spc == TOP_BULLET) continue;
		if(b->pos.x < bbox_.left)
			bbox_.left = b->pos.x;
		if(b->pos.x > bbox_.right)
			bbox_.right = b->pos.x;
		if(b->pos.y < bbox_.top)
			bbox_.top = b->pos.y;
		if(b->pos.x > bbox_.bottom)
			bbox_.bottom = b->pos.y;*/
	}
}

void BulletManager::removeBullet(Bullet* b)
{
	assert(b != 0);
	b->spc = NOT_EXIST;
}

void BulletManager::clean()
{
	std::list<Bullet*>::iterator it = bullets().begin();
	for(; it != bullets().end(); )
	{
		if((*it)->readyForDeletion()) {
			delete *(it);
			it = bullets().erase(it);
		} else
			it++;
	}
}

void BulletManager::setAngle(const double newa)
{
	angle_ = newa;
}

void BulletManager::setPos(const int x, const int y)
{
	pos_.x = x;
	pos_.y = y;
}

void BulletManager::setMaxLifeTime(const int newl)
{
	if(newl > 0)
		maxLifeTime_ = newl;
}

// Point/box overlaps.
inline bool PointInsideBox(float x, float y, const RECTF& box)
{
	return (x >= box.left && x < box.right && y >= box.top && y < box.bottom);
}

bool BulletManager::queryCollision(RECTF &box)
{
	bool coll = false;
	BOOST_FOREACH(Bullet* b, bullets())
	{
		if(b->spc == NOT_EXIST) continue;
		if(PointInsideBox(b->pos.x, b->pos.y, box))
		{
			coll = true;
			removeBullet(b);
		}
	}
	return coll;
}