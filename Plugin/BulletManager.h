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
	void load(const std::string& filename);
	bool queryCollision(RECTF& box);

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
	RECTF& boundingBox() { return bbox_; }

	int maxLifeTime() const { return maxLifeTime_; }
	void setMaxLifeTime(const int);

private:
	Bullet* getNextBullet();
	std::list<Bullet*> bullets_;
	BulletMLParser* parser_;
	bool finished_;
	Vec2 pos_;
	double angle_;
	RECTF bbox_;
	int maxLifeTime_;
	//TODO: Store parsers in a map by name
	//Add checkbox to enable/disable caching
	std::list<BulletMLParser*> parserTrash_; //temporary, I hope, should use smartptrs instead
};