#pragma once

//Abstract subaction (fire, changedir etc) base class
class SubAction
{
public:
	SubAction(void) {};
	~SubAction(void) {};
	virtual void call(BulletPtr owner, Action& action,
					  float params, float rank, BulletList* created) = 0;
};

typedef std::list<SubAction> SubActionList;
