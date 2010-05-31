#pragma once
#include "SubAction.h"

/*
Changes the direction of bullet to <direction>
degrees in <term> frames. 1 frame is 1/60 seconds.
*/
class ChangeDir :
	public SubAction
{
public:
	ChangeDir(void);
	ChangeDir(BulletDirection, int term);
	~ChangeDir(void);

	const BulletDirection& direction() { return dir_; }
	int term() const { return term_; }
	void call(BulletPtr owner, Action& action,
			  float params, float rank, BulletList* created);
private:
	BulletDirection dir_;
	int term_;
};
