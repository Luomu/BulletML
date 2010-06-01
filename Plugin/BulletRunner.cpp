#include "BulletRunner.h"

BulletCommand::BulletCommand(BulletMLParser *parser, Bullet *b)
: BulletMLRunner(parser)
{
	bullet = b;
}

BulletCommand::BulletCommand(BulletMLState *state, Bullet *b)
: BulletMLRunner(state)
{
	bullet = b;
}

BulletCommand::~BulletCommand() {}

double BulletCommand::getBulletDirection()
{
	return 0;
}

double BulletCommand::getDefaultSpeed()
{
	return 1;
}

double BulletCommand::getRank()
{
	return bullet->rank;
}

void BulletCommand::createSimpleBullet(double direction, double speed)
{
	int dir = 0;
	//manager->addfoenormalbullet...
}