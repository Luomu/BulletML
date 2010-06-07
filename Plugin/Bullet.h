#pragma once
#include "bulletml/bulletmlparser.h"
#include "bulletrunner.h"
#include "Vec2.h"
#define NOT_EXIST 0
#define NORMAL_BULLET 1
#define ACTIVE_BULLET 2
#define TOP_BULLET 3

class Bullet {
public:
	Bullet();
	~Bullet();
	bool readyForDeletion();
	Vec2f pos;
	int spd;
	double dir;
	BulletCommand* cmd;
	double rank;
	int spc;
	int type;
	int shield;
	int cnt;
	int hit;
	Vec2f vel; //acc
	float lifetime;
	cr::color color;

	BulletMLParser* parser;
};