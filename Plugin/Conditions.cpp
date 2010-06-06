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

long ExtObject::cOnCollision(LPVAL params)
{
	CRunObjType* pOtherType = params[0].GetObjectParam(pRuntime);
	if (pOtherType == NULL)
		return 0;

	CRunObject** objects;
	int count;
	pRuntime->GetTypeSelectedInstances(pOtherType, objects, count);

	if(count == 0 || objects == 0)
		return 0;

	// For each othertype object
	CRunObject** end = objects + count;
	CRunObject** i = objects;

	for(; i != end; ++i)
	{
		RECTF box = (*i)->info.box;
		 return manager.queryCollision(box);
	}
	return 0;
}