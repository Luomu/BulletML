#pragma once

class Parameters
{
public:
	Parameters();
	void Serialize(bin& ar);

	int maxLifeTime;
	float speedMultiplier;
	float timeMultiplier;
	float defaultSpeed;
	bool destroyOutsideScreen;
	bool useTexture;
	float bulletSize;
	bool allowRotations;
};