#pragma once
#include "Bullet.h"
#include "Vec2.h"

class BulletMLParser;

//holds the bullets, calls their commands
class BulletManager
{
public:
	BulletManager();
	~BulletManager();
	std::list<Bullet*>& bullets() { return bullets_; }
	BulletMLParser* parser() const { return parser_; }
	void init(); //temporary
	void restart();

	void move(const float timeDelta);
	void clean();
	void addSimpleBullet(int x, int y, int speed, int dir);
	void addActiveBullet(int x, int y, double rank, int dir,
						 int speed, BulletMLState* state);
	void removeBullet(Bullet* bullet);

	bool finished() const { return finished_; }

	Vec2& pos() { return pos_; }
	void setPos(const int x, const int y);
	double angle() const { return angle_; }
	void setAngle(const double);

private:
	Bullet* getNextBullet();
	std::list<Bullet*> bullets_;
	BulletMLParser* parser_;
	bool finished_;
	Vec2 pos_;
	double angle_;
};