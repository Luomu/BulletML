#include "stdafx.h"
#include "BulletRunner.h"
#include "Bullet.h"

BulletRunner::BulletRunner(void)
{
	//Create some bullets
	bullets.push_back(Bullet(10, 10));
	bullets.push_back(Bullet(100, 100));
	bullets.push_back(Bullet(50, 50));
}

BulletRunner::~BulletRunner(void)
{
}

void BulletRunner::run()
{

}

BulletList& BulletRunner::Bullets()
{
	return bullets;
}