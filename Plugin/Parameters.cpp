#include "stdafx.h"
#include "Parameters.h"

Parameters::Parameters() :
	maxLifeTime(20000),
	destroyOutsideScreen(true)
{ }

void Parameters::Serialize(bin &ar)
{
	int Version = 1;
	SerializeVersion(ar, Version);

	if(ar.loading)
	{
		ar >> maxLifeTime;
		ar >> destroyOutsideScreen;
	}
	else
	{
		ar << maxLifeTime;
		ar << destroyOutsideScreen;
	}
} 