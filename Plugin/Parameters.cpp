#include "stdafx.h"
#include "Parameters.h"

Parameters::Parameters() :
	maxLifeTime(20000),
	destroyOutsideScreen(true),
	speedMultiplier(1.f),
	timeMultiplier(1.f),
	defaultSpeed(250.f)
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
	}
	else
	{
		ar << maxLifeTime;
		ar << destroyOutsideScreen;
		ar << speedMultiplier;
		ar << timeMultiplier;
		ar << defaultSpeed;
	}
} 