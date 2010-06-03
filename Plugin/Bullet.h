#pragma once
#include "bulletml/bulletmlparser.h"
#include "bulletrunner.h"
#include "Vec2.h"
#define NOT_EXIST 0
#define NORMAL_BULLET 1
#define ACTIVE_BULLET 2
#define MAXLIFETIME 10000

class Bullet {
public:
	Bullet();
	Vec2 pos;
	int spd;
	double dir;
	BulletCommand* cmd;
	double rank;
	int spc;
	int type;
	int shield;
	int cnt, color;
	int hit;
	Vec2 vel; //acc
	float lifetime;

	BulletMLParser* parser;
};