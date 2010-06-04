#pragma once
#include "bulletml/bulletmlparser.h"
#include "bulletml/bulletmlparser-tinyxml.h"
#include "bulletml/bulletmlrunner.h"

class Bullet;
class BulletManager;

class BulletCommand : public BulletMLRunner
{
public:
	BulletCommand(BulletMLParser* parser, Bullet* b);
	BulletCommand(BulletMLState* state, Bullet* b);
	virtual ~BulletCommand();

	virtual double getBulletDirection();
	virtual double getAimDirection();
	virtual double getBulletSpeed();
	virtual double getDefaultSpeed();
	virtual double getRank();
	virtual void createSimpleBullet(double direction, double speed);
	virtual void createBullet(BulletMLState* state, double direction, double speed);
	virtual int getTurn();
	virtual void doVanish();

	virtual void doChangeDirection(double d);
	virtual void doChangeSpeed(double s);
	virtual void doAccelX(double ax);
	virtual void doAccelY(double ay);
	virtual double getBulletSpeedX();
	virtual double getBulletSpeedY();

	BulletManager* getManager() { return manager; }
	void setManager(BulletManager*);

private:
	Bullet* bullet;
	BulletManager* manager;
};