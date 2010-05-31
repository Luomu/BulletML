#include "stdafx.h"
#include "Action.h"
#include "SubAction.h"
#include "Fire.h"
#include "ChangeDir.h"
#include <boost/foreach.hpp>

Action::Action(BulletPtr newowner) :
	finished_(false),
	repeat_(0),
	owner_(newowner)
{
	FireDef* foo = new FireDef("temp",
							   BulletDirection(DirectionType::absolute, 0.f),
							   FireSpeed(SpeedType::absolute, 200.f));
	actions_.push_back(foo);
}

Action::~Action()
{
	for (SubActionList::iterator i = actions_.begin(), e = actions_.end(); i != e; )
	{
		SubActionList::iterator tmp(i++);
		delete *tmp;
		actions_.erase(tmp);
	}
}

BulletList* Action::step()
{
	//run sub-actions
	//handle repeats and waits
	BulletList* created = new BulletList;
	//bool actionsDone = false;
	BOOST_FOREACH(SubAction* action, actions_)
	{
		if(action->finished())
			break;
		action->call(owner_, *this, 0.f, 0.f, created);
		//if(action->finished())
		//	actionsDone = true;
	}
	//if(actionsDone)
	//	finished_ = true;
	return created;
}

SubActionList& Action::actions()
{
	return actions_;
}