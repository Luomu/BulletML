#include "stdafx.h"
#include "Action.h"
#include "SubAction.h"
#include "Fire.h"
#include <boost/foreach.hpp>

Action::Action(BulletPtr newowner) :
	finished_(false),
	repeat_(0),
	owner_(newowner)
{
	FireDef foo("temp",
				BulletDirection(DirectionType::absolute, 0.f),
				FireSpeed(SpeedType::absolute, 200.f));
	actions_.push_back(foo);
}

static int blah = 0;
BulletList* Action::step()
{
	//run sub-actions
	//handle repeats and waits
	BulletList* created = 0;
	BOOST_FOREACH(SubAction& action, actions_)
	{
		created = new BulletList;
		action.call(owner_, *this, 0.f, 0.f, created);
	}
	return created;
}

inline SubActionList& Action::actions()
{
	return actions_;
}