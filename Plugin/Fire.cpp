#include "Bullet.h"
#include "Action.h"
#include "SubAction.h"

FireDef::FireDef(const std::string& label,
				 const BulletDirection& dir,
				 const FireSpeed& speed) :
	label_(label),
	direction_(dir),
	speed_(speed)
{
}

void FireDef::call(BulletPtr owner, ActionPtr action,
		float params, float rank, BulletPtrList& created)
{
	//default parameters for the new bullet here
	float speed = 0.f;
	int x = 0;
	int y = 0;

	if(speed_.type == SpeedType::absolute)
		speed = speed_.speed;
	else if(speed._type == SpeedType::relative)
		speed = owner->speed() + speed_.speed;
	else if(speed._type == SpeedType::sequence)
		speed += action->previousFireSpeed();
	else
		speed = 100.f;
	//action->setPreviousFireSpeed(speed);
	created.push_back(BulletPtr(new Bullet(0, 0)));
}