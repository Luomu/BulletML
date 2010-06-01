#pragma once
#include "bulletml/bulletmlparser.h"
#include "bulletrunner.h"

struct Bullet {
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