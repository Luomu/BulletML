#pragma once
#include "bulletml/bulletmlparser.h"
#include "bulletrunner.h"
#include "Vec2.h"
#define NOT_EXIST 0
#define NORMAL_BULLET 1

class Bullet {
public:
	Bullet();
	Vec2 pos;
	int dir, spd;
	BulletCommand* cmd;
	double rank;
	int spc;
	int type;
	int shield;
	int cnt, color;
	int hit;

	BulletMLParser* parser;
};

Bullet::Bullet()
{
	pos.x = 0;
	pos.y = 0;
	dir = 0;
	spd = 0;
	cmd = 0;
	rank = 0;
	spc = NORMAL_BULLET;
	type = 0;
	cnt = 0;
	color = 0;
	hit = 0;
	parser = 0;
}