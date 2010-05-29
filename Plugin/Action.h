#pragma once
#include "tree.h"

class Action :
	public Node
{
public:

	Action(void)
	{
	}

	~Action(void)
	{
	}

	virtual void step() {} //= 0;
};

//fires a bullet
class Fire :
	public Action
{

};

//refers to labeled fire action
class FireRef :
	public Action
{

};

//makes a bullet vanish
class Vanish :
	public Action
{

};