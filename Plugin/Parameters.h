#pragma once

class Parameters
{
public:
	int maxLifeTime;
	float speedMultiplier;
	float timeMultiplier;
	float defaultSpeed;
	bool destroyOutsideScreen;
	Parameters();
	void Serialize(bin& ar);
};