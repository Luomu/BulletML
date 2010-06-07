#include "stdafx.h"
#include "bulletml/bulletmlerror.h"
#include "Bullet.h"
#include "BulletRunner.h"

BulletCommand::BulletCommand(BulletMLParser *parser, Bullet *b) :
	BulletMLRunner(parser),
	manager(0)
{
	assert(bullet != 0);
	bullet = b;
	manager = 0;
}

BulletCommand::BulletCommand(BulletMLState *state, Bullet *b) :
	BulletMLRunner(state),
	manager(0)
{
	assert(bullet != 0);
	bullet = b;
}

BulletCommand::~BulletCommand() {}

//get bullet direction in degrees
double BulletCommand::getBulletDirection()
{
	return static_cast<double>(bullet->dir);
}

double BulletCommand::getAimDirection()
{
	//direction to aim from this position to target (player) position
	return 0;
}

double BulletCommand::getBulletSpeed()
{
	//noiz multiplies this with COMMAND_SCREEN_SPD_RATE which is 800
	return static_cast<double>(bullet->spd);
}

double BulletCommand::getDefaultSpeed()
{
	return manager->defaultSpeed();
}

double BulletCommand::getRank()
{
	return bullet->rank;
}

void BulletCommand::createSimpleBullet(double direction, double speed)
{
	assert(manager != 0);
	assert(bullet != 0);
	int dir = static_cast<int>(direction);
	float spd = static_cast<float>(speed);
	manager->addSimpleBullet(bullet->pos.x, bullet->pos.y, spd, dir);
}

void BulletCommand::createBullet(BulletMLState *state, double direction, double speed)
{
	assert(manager != 0);
	assert(bullet != 0);
	int dir = static_cast<int>(direction);
	float spd = static_cast<float>(speed);
	manager->addActiveBullet(bullet->pos.x,
							 bullet->pos.y,
							 bullet->rank,
							 dir, spd, state);
}

int BulletCommand::getTurn()
{
	return static_cast<int>(GetTickCount()/manager->parameters().timeMultiplier);
}

void BulletCommand::doVanish()
{
	assert(manager != 0);
	assert(bullet != 0);
	manager->removeBullet(bullet);
}

void BulletCommand::doChangeSpeed(double s)
{
	bullet->spd = static_cast<float>(s);
}

void BulletCommand::doChangeDirection(double d)
{
	bullet->dir = static_cast<int>(d);
}

void BulletCommand::doAccelX(double ax)
{
	bullet->vel.x = static_cast<float>(ax);
}

void BulletCommand::doAccelY(double ay)
{
	bullet->vel.y = static_cast<float>(ay);
}

double BulletCommand::getBulletSpeedX()
{
	return static_cast<double>(bullet->vel.x);
}

double BulletCommand::getBulletSpeedY()
{
	return static_cast<double>(bullet->vel.y);
}

void BulletCommand::setManager(BulletManager* newm)
{
	assert(newm != 0);
	manager = newm;
}