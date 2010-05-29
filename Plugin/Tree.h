#pragma once

class Node
{
public:
	Node(void);
	~Node(void);
};

class Speed
{
	int type; //absolute, relative, sequence
	int value;
};

class Wait
{
	int frames;

	void call()
	{
		//Action->wait_frames = frames;
	}
};

//Accelerates a bullet <horizontal> in a horizontal line and
//<vertical> in a vertical line in <term> frames. 
class Accel
{
	int horizontal;
	int vertical;
	int frames;
};
