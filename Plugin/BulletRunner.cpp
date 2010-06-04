#include "stdafx.h"
#include "bulletml/bulletmlerror.h"
#include "Bullet.h"
#include "BulletRunner.h"

BulletCommand::BulletCommand(BulletMLParser *parser, Bullet *b)
: BulletMLRunner(parser)
{
	bullet = b;
	manager = 0;
}

BulletCommand::BulletCommand(BulletMLState *state, Bullet *b)
: BulletMLRunner(state)
{
	bullet = b;
	manager = 0;
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
	return 250;
}

double BulletCommand::getRank()
{
	return bullet->rank;
}

void BulletCommand::createSimpleBullet(double direction, double speed)
{
	if(manager == 0)
		throw BulletMLError("createsimple: Command has no manager! Bad!");
	int dir = static_cast<int>(direction);
	int spd = static_cast<int>(speed);
	manager->addSimpleBullet(bullet->pos.x, bullet->pos.y, spd, dir);
}

void BulletCommand::createBullet(BulletMLState *state, double direction, double speed)
{
	if(manager == 0)
		throw BulletMLError("createbullet: Command has no manager! Bad!");
	int dir = static_cast<int>(direction);
	int spd = static_cast<int>(speed);
	manager->addActiveBullet(bullet->pos.x,
							 bullet->pos.y,
							 bullet->rank,
							 dir, spd, state);
}

int BulletCommand::getTurn()
{
	return static_cast<int>(GetTickCount());
}

void BulletCommand::doVanish()
{
	manager->removeBullet(this->bullet);
}

void BulletCommand::doChangeSpeed(double s)
{
	bullet->spd = static_cast<int>(s);
}

void BulletCommand::doChangeDirection(double d)
{
	bullet->dir = static_cast<int>(d);
}

void BulletCommand::doAccelX(double ax)
{
	bullet->vel.x = static_cast<int>(ax);
}

void BulletCommand::doAccelY(double ay)
{
	bullet->vel.y = static_cast<int>(ay);
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
	manager = newm;
}