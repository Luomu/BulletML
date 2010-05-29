#include "stdafx.h"
#include "BulletRunner.h"
#include "Bullet.h"
#include <boost/foreach.hpp>

BulletRunner::BulletRunner(void)
{
	//Create some bullets
	for(int i = 0; i < 100; ++i)
	{
		bullets.push_back(new Bullet(i * 12, 50));
	}
}

BulletRunner::~BulletRunner(void)
{
	bullets.clear();
}

void BulletRunner::run(float timeDelta)
{
	BOOST_FOREACH(BulletPtr bullet, Bullets())
	{
		BulletList* newbullets =  bullet->step(timeDelta);
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