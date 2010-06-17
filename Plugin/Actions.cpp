// Include StdAfx
#include "StdAfx.h"
#include "bulletml/bulletmlerror.h"

//////////////////////////////////////////////////////////////////////////////////
// Actions
//////////////////////////////////////////////////////////////////////////////////
long ExtObject::aRestart(LPVAL params)
{
	unreportedFinish = true;
	manager.restart();
	return 0;
}

long ExtObject::aStop(LPVAL params)
{
	manager.setPaused(true);
	return 0;
}

long ExtObject::aClear(LPVAL params)
{
	RaiseConstructError("Not implemented");
	//manager.clean();
	return 0;
}

long ExtObject::aLoad(LPVAL params)
{
	CT2CA filename(params[0].GetString());
	try
	{
		manager.load(std::string(filename));
	}
	catch(BulletMLError& berror)
	{
		CString errorstring("Error while loading or parsing " + params[0].GetString() + ": ");
		errorstring += berror.what();
		RaiseConstructError(errorstring);
	}
	catch(std::exception& stex)
	{
		RaiseConstructError(stex.what());
	}
	catch(...)
	{
		RaiseConstructError("Cannot load or parse " + params[0].GetString() + ". Unknown error.");
	}
	return 0;
}

long ExtObject::aSetTargetPos(LPVAL params)
{
	int x = params[0].GetInt();
	int y = params[1].GetInt();
	return 0;
}