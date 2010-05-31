#include "stdafx.h"
#include "BulletRunner.h"
#include "Bullet.h"
#include <boost/foreach.hpp>

BulletRunner::BulletRunner(void) :
	unreportedFinish(false)
{
	BulletPtr topact = BulletPtr(new Bullet(0, 0, 0));
	topact->actions().push_back(new Action(topact));
	Bullets().push_back(topact);
}

BulletRunner::~BulletRunner(void)
{
	bullets.clear();
}

void BulletRunner::run(float timeDelta)
{
	BOOST_FOREACH(BulletPtr bullet, Bullets())
	{
		if(bullet->finished())
			break;
		BulletList* newbullets = 0;
		newbullets =  bullet->step(timeDelta);
		if(newbullets != 0)
			Bullets().merge(*newbullets);
		delete newbullets;
	}
	//erase expired
	BulletIterator b = Bullets().begin();
	for(; b != Bullets().end(); )
	{
		if((*b)->finished())
			b = Bullets().erase(b);
		else
			b++;
	}
}

BulletList& BulletRunner::Bullets()
{
	return bullets;
}