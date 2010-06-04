#pragma once
#include "Bullet.h"

class BulletMLParser;

//holds the bullets, calls their commands
class BulletManager
{
public:
	BulletManager();
	~BulletManager();
	std::list<Bullet*>& bullets() { return bullets_; }
	BulletMLParser* parser() const { return parser_; }

	void move(float timeDelta);
	void clean();
	void addSimpleBullet(int x, int y, int speed, int dir);
	void addActiveBullet(int x, int y, double rank, int dir,
						 int speed, BulletMLState* state);
	void removeBullet(Bullet* bullet);

private:
	Bullet* getNextBullet();
	std::list<Bullet*> bullets_;
	BulletMLParser* parser_;
};