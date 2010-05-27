#ifndef BULLET_H
#define BULLET_H

#include "Tree.h"

class Bullet : public Node
{
	friend class ExtObject;
	friend class EditExt;
public:
	Bullet(int xpos, int ypos) :
		x(xpos),
		y(ypos) { }
private:
	int x;
	int y;
};

#endif