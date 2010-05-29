#pragma once

//Abstract subaction (fire, changedir etc) base class
class SubAction
{
public:
	SubAction(void) {};
	~SubAction(void) {};
	virtual void call(BulletPtr owner, ActionPtr action,
					  float params, float rank, BulletPtrList created) = 0;
};
