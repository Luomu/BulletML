#include "stdafx.h"
#include <boost/foreach.hpp>
#include "bulletml/bulletmlparser-tinyxml.h"
#include "bulletml/bulletmlerror.h"
#include "BulletManager.h"

BulletManager::BulletManager(CRunObject* newp) :
	parser_(0),
	paused_(false),
	finished_(true),
	angle_(0),
	rank_(0.5),
	parent_(newp),
	cObjectType_(0)
{
	screen_.left, screen_.top = 0;
	screen_.right = 800;
	screen_.bottom = 600;
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

void BulletManager::load(const std::string& filename)
{
	if(parser_ != 0)
	{
		parserTrash_.push_back(parser_);
	}
	parser_ = 0;
	parser_ = new BulletMLParserTinyXML(filename);
	if(parser() != 0)
		parser_->build();
}

void BulletManager::restart()
{
	if(parser_ != 0)
	{
		setPaused(false);
		Bullet* b = getNextBullet();
		b->spc = TOP_BULLET;
		b->pos = this->pos();
		b->dir = static_cast<int>(angle_);
		b->color = cr::color(RGB(255,0,255));
		b->parser = parser();
		b->cmd = new BulletCommand(parser(), b);
		b->cmd->setManager(this);
		b->rank = this->rank();
	}
	else
	{
		throw BulletMLError("No parser available");
	}
	setFinished(false);
}

void BulletManager::addSimpleBullet(int x, int y, float speed, int direction, double rank)
{
	Bullet* b = getNextBullet();
	if(!b) return;
	b->cmd = 0;
	b->pos.x = x;
	b->pos.y = y;
	b->spd = speed * parameters().speedMultiplier;
	b->dir = direction;
	b->spc = NORMAL_BULLET;
	b->rank = this->rank();
	if(cObjectType() != 0)
	{
		b->cObject = parent()->pRuntime->CreateObject(cObjectType(),
			parent()->info.layer,
			parent()->pLayout);
		assert(b->cObject != 0);
	}
}

void BulletManager::addActiveBullet(int x, int y, double rank, int dir,
									float speed, BulletMLState* state)
{
	Bullet* b = getNextBullet();
	if(!b) return;
	b->rank = this->rank();
	b->cmd = new BulletCommand(state, b);
	b->cmd->setManager(this);
	b->pos.x = x;
	b->pos.y = y;
	b->dir = dir;
	b->spd = speed * parameters().speedMultiplier;
	b->spc = ACTIVE_BULLET;
	b->color = cr::color(RGB(255,200,200));
	if(cObjectType() != 0)
	{
		b->cObject = parent()->pRuntime->CreateObject(cObjectType(),
			parent()->info.layer,
			parent()->pLayout);
		assert(b->cObject != 0);
	}
}

Bullet* BulletManager::getNextBullet()
{
	Bullet* newb = new Bullet();
	bullets_.push_back(newb);
	return newb;
}

// Point/box overlaps.
inline bool PointInsideBox(float x, float y, const RECTF& box)
{
	return (x >= box.left && x < box.right && y >= box.top && y < box.bottom);
}

void BulletManager::move(const float timeDelta)
{
	bbox_.left = 0;
	bbox_.top = 0;
	bbox_.right = 800;
	bbox_.bottom = 600;

	BOOST_FOREACH(Bullet* b, bullets_)
	{
		assert(b != 0);
		if(b->spc == NOT_EXIST && b->cmd == 0) continue;
		if(b->spc == TOP_BULLET)
		{
			b->pos.x = pos().x;
			b->pos.y = pos().y;
		}
		if(b->cmd)
		{
			if(!paused())
				b->cmd->run();
			if(b->cmd->isEnd())
			{
				if(b->spc == TOP_BULLET)
					removeBullet(b);
				setFinished(true);
			}
			else
				setFinished(false);
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
		b->pos.x += cos(RADIANS(b->dir)) * b->spd * timeDelta + b->vel.x * timeDelta;
		b->pos.y += sin(RADIANS(b->dir)) * b->spd * timeDelta + b->vel.y * timeDelta;
		b->cnt++;
		if(b->cObject != 0)
		{
			b->updateCObject();
			if(b->cObject == 0)
				removeBullet(b);
			else
				parent()->pRuntime->UpdateBoundingBox(b->cObject);
		}
		b->lifetime += timeDelta * 1000;

		if(b->lifetime > parameters_.maxLifeTime && b->cmd == 0) removeBullet(b);

		//out of bounds check
		if(parameters_.destroyOutsideScreen && b->cmd == 0)
		{
			if(!PointInsideBox(b->pos.x, b->pos.y, screen()))
				removeBullet(b);
		}
	}
}

void BulletManager::removeBullet(Bullet* b)
{
	assert(b != 0);
	b->spc = NOT_EXIST;
	if(b->cObject != 0)
	{
		parent()->pRuntime->DestroyObject(b->cObject);
		b->cObject = 0;
	}
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

bool BulletManager::queryCollision(RECTF &box)
{
	bool coll = false;
	BOOST_FOREACH(Bullet* b, bullets())
	{
		if(b->spc == NOT_EXIST || b->spc == TOP_BULLET) continue;
		if(PointInsideBox(b->pos.x, b->pos.y, box))
		{
			coll = true;
			removeBullet(b);
		}
	}
	return coll;
}

void BulletManager::setParameters(const Parameters& newp)
{
	parameters_ = newp;
}

void BulletManager::setFinished(const bool newstate)
{
	finished_ = newstate;
}

void BulletManager::setTargetPos(const float x, const float y)
{
	targetPos_.x = x;
	targetPos_.y = y;
}

void BulletManager::setRank(double newr)
{
	Clamp<double>(newr, 0.0, 1.0);
	rank_ = newr;
}

void BulletManager::setCObjectType(CRunObjType* newt)
{
	if(newt != 0)
		cObjectType_ = newt;
}

void BulletManager::removeAllBullets()
{
	BOOST_FOREACH(Bullet* b, bullets())
	{
		removeBullet(b);
	}
}