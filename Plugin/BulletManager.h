#pragma once
#include "Bullet.h"
#include "Vec2.h"
#include "Parameters.h"

class BulletMLParser;

//holds the bullets, calls their commands
class BulletManager
{
public:
	BulletManager();
	~BulletManager();
	std::list<Bullet*>& bullets() { return bullets_; }
	BulletMLParser* parser() const { return parser_; }
	void restart();
	void load(const std::string& filename);
	bool queryCollision(RECTF& box);

	void move(const float timeDelta);
	void clean();
	void addSimpleBullet(int x, int y, float speed, int dir);
	void addActiveBullet(int x, int y, double rank, int dir,
						 float speed, BulletMLState* state);
	void removeBullet(Bullet* bullet);

	bool finished() const { return finished_; }

	Vec2f& pos() { return pos_; }
	void setPos(const int x, const int y);
	double angle() const { return angle_; }
	void setAngle(const double);
	RECTF& boundingBox() { return bbox_; }

	int maxLifeTime() const { return parameters_.maxLifeTime; }

	RECTF& screen() { return screen_; }

	Parameters& parameters() { return parameters_; }
	void setParameters(const Parameters&);

	float defaultSpeed() const { return parameters_.defaultSpeed; }

	bool paused() const { return paused_; }
	void setPaused(const bool newp) { paused_ = newp; }

private:
	Bullet* getNextBullet();
	std::list<Bullet*> bullets_;
	BulletMLParser* parser_;
	bool finished_;
	bool paused_;
	Vec2f pos_;
	double angle_;
	RECTF bbox_;
	//TODO: Store parsers in a map by name
	//Add checkbox to enable/disable caching
	std::list<BulletMLParser*> parserTrash_; //temporary, I hope, should use smartptrs instead

	Parameters parameters_;
	RECTF screen_;
};