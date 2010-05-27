#pragma once

class Bullet;

typedef std::list<Bullet> BulletList;

class BulletRunner
{
public:
	BulletRunner(void);
	~BulletRunner(void);
	void run(float timeDelta = 0.5f);

	BulletList& Bullets();

protected:
	void doFire();

private:
	BulletList bullets;
};
