#pragma once

class Bullet;

typedef std::list<Bullet> BulletList;

class BulletRunner
{
public:
	BulletRunner(void);
	~BulletRunner(void);
	void run();

	BulletList& Bullets();

private:
	BulletList bullets;
};
