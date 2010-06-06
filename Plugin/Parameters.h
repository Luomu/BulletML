#pragma once

class Parameters
{
public:
	int maxLifeTime;
	bool destroyOutsideScreen;
	Parameters();
	void Serialize(bin& ar);
};