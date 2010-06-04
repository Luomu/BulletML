// Include StdAfx
#include "StdAfx.h"

//////////////////////////////////////////////////////////////////////////////////
// Conditions
//////////////////////////////////////////////////////////////////////////////////
long ExtObject::cFinished(LPVAL params)
{
	/*if(runner.unreportedFinish)
	{
		runner.unreportedFinish = false;
		return 1;
	}*/
	return 0;
}

long ExtObject::cErrorOccurred(LPVAL params)
{
	if(unreportedError)
	{
		unreportedError = false;
		return 1;
	}
	return 0;
}