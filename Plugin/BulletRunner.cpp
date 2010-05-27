#include "stdafx.h"
#include "BulletRunner.h"
#include "Bullet.h"
#include <boost/foreach.hpp>

BulletRunner::BulletRunner(void)
{
	//Create some bullets
	/*for(int i = 0; i < 100; ++i)
	{
		bullets.push_back(Bullet(i * 12, 50));
	}*/
}

BulletRunner::~BulletRunner(void)
{
}

void BulletRunner::run(float timeDelta)
{
	BOOST_FOREACH(Bullet& bullet, Bullets())
	{
		bullet.step(timeDelta);
		if(bullet.finished())
		{

		}
	}
}

BulletList& BulletRunner::Bullets()
{
	return bullets;
}