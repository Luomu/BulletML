#include "stdafx.h"
#include "Parameters.h"

Parameters::Parameters() :
	maxLifeTime(10000),
	destroyOutsideScreen(true),
	speedMultiplier(1.f),
	timeMultiplier(1.f),
	defaultSpeed(250.f),
	useTexture(false),
	bulletSize(16)
{ }

void Parameters::Serialize(bin &ar)
{
	int Version = 1;
	SerializeVersion(ar, Version);

	if(ar.loading)
	{
		ar >> maxLifeTime;
		ar >> destroyOutsideScreen;
		ar >> speedMultiplier;
		ar >> timeMultiplier;
		ar >> defaultSpeed;
		ar >> useTexture;
		ar >> bulletSize;
	}
	else
	{
		ar << maxLifeTime;
		ar << destroyOutsideScreen;
		ar << speedMultiplier;
		ar << timeMultiplier;
		ar << defaultSpeed;
		ar << useTexture;
		ar << bulletSize;
	}
} 