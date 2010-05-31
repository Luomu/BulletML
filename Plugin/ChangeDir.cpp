#include "stdafx.h"
#include "ChangeDir.h"
#include "Bullet.h"

ChangeDir::ChangeDir(void) :
	SubAction(),
	dir_(DirectionType::relative, 0)
{
}

ChangeDir::ChangeDir(BulletDirection dir, int term) :
	SubAction(),
	dir_(dir),
	term_(term)
{
}

ChangeDir::~ChangeDir(void)
{
}

void ChangeDir::call(BulletPtr owner, Action& action,
		float params, float rank, BulletList* created)
{
	
}