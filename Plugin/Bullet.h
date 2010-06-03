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