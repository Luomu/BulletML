#pragma once
#include "Bullet.h"

//holds the bullets, calls their commands
class BulletManager
{
public:
	BulletManager();
	~BulletManager();
	std::list<Bullet*>& bullets() { return bullets_; }

	void move();
	void addSimpleBullet(int x, int y, int speed, int dir);
	void removeBullet(Bullet* bullet);

private:
	Bullet* getNextBullet();
	std::list<Bullet*> bullets_;
};