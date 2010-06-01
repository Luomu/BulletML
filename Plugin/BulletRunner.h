#pragma once
#include "bulletml/bulletmlparser.h"
#include "bulletml/bulletmlparser-tinyxml.h"
#include "bulletml/bulletmlrunner.h"
#include "Bullet.h"

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

private:
	Bullet* bullet;
};