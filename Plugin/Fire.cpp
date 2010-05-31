#include "stdafx.h"
#include "Bullet.h"
#include "Action.h"
#include "SubAction.h"
#include "Fire.h"
#include "ChangeDir.h"

FireDef::FireDef(const std::string& label,
				 const BulletDirection& dir,
				 const FireSpeed& speed) :
	SubAction(),
	label_(label),
	direction_(dir),
	speed_(speed)
{
}

void FireDef::call(BulletPtr owner, Action& action,
		float params, float rank, BulletList* created)
{
	//default parameters for the new bullet here
	float speed = 0.f;
	int x = 0;
	int y = 0;

	if(speed_.type == SpeedType::absolute)
		speed = speed_.speed;
	else if(speed_.type == SpeedType::relative)
		speed = owner->speed() + speed_.speed;
	else if(speed_.type == SpeedType::sequence)
		speed += action.previousFireSpeed();
	else
		speed = 100.f;
	action.setPreviousFireSpeed(speed);
	BulletPtr newb(new Bullet(0, 0, 250));
	//Adding a test action
	Action* faction = new Action(newb);
	ChangeDir* bar = new ChangeDir(BulletDirection(0, 0.f), 120);
	faction->actions().push_back(bar);
	newb->actions().push_back(faction);
	created->push_back(newb);
	finished_ = true;
}