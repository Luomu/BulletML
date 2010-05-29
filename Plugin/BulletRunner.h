#pragma once
#include "Bullet.h"

class BulletRunner
{
public:
	BulletRunner(void);
	~BulletRunner(void);
	void run(float timeDelta = 0.5f);

	BulletList& Bullets();

	bool unreportedFinish;
	bool finished() const { return finished_; }

private:
	bool finished_;
	BulletList bullets;
	int type; // none | vertical | horizontal
};
