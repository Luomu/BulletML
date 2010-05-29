#include "stdafx.h"
#include "Action.h"
#include "Fire.h"

static int blah = 0;
void Action::step()
{
	//run sub-actions
	//handle repeats and waits
	if(blah == 0)
	{
		BulletList created;
		FireDef foo("temp",
					BulletDirection(DirectionType::absolute, 0.f),
					FireSpeed(SpeedType::absolute, 200.f));
		foo.call(owner_, *this, 0.f, 0.f, created);
		blah = 1;
	}
}