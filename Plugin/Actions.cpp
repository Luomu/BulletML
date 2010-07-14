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
	manager.removeAllBullets();
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
	manager.setTargetPos(params[0].GetFloat(), params[1].GetFloat());
	return 0;
}

//Privatevar actions
long ExtObject::aSetValue(LPVAL params)
{
	privateVars[params[0].GetVariableIndex(pRuntime, pType)] = params[1];
	return 0;
}

long ExtObject::aAddValue(LPVAL params)
{
	privateVars[params[0].GetVariableIndex(pRuntime, pType)] += params[1];
	return 0;
}

long ExtObject::aSubValue(LPVAL params)
{
	privateVars[params[0].GetVariableIndex(pRuntime, pType)] -= params[1];
	return 0;
}

long ExtObject::aSetRank(LPVAL params)
{
	manager.setRank(params[0].GetDouble());
	return 0;
}

long ExtObject::aSetBulletObject(LPVAL params)
{
	manager.setCObjectType(params[0].GetObjectParam(pRuntime));
	return 0;
}

long ExtObject::aPlayAndLoop(LPVAL params)
{
	CString scriptName = params[0].GetString();
	loops = params[1].GetInt();
	loopDelay = params[2].GetInt();
	unreportedFinish = true;
	manager.restart();
	return 0;
}