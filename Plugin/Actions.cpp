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
	loadScript(params[0].GetString());
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
	CString newScript = params[0].GetString();
	if(newScript != scriptName)
	{
		loadScript(newScript);
	}
	loops = params[1].GetInt();
	loopDelay = params[2].GetInt();
	unreportedFinish = true;
	manager.restart();
	elapsedDelay = 0.f;
	loops--;
	return 0;
}

void ExtObject::loadScript(const ATL::CString &sname)
{
	CT2CA filename(sname);
	scriptName = sname;
	try
	{
		manager.load(std::string(filename));
	}
	catch(BulletMLError& berror)
	{
		CString errorstring("Error while loading or parsing " + sname + ": ");
		errorstring += berror.what();
		RaiseConstructError(errorstring);
	}
	catch(std::exception& stex)
	{
		RaiseConstructError(stex.what());
	}
	catch(...)
	{
		RaiseConstructError("Cannot load or parse " + sname + ". Unknown error.");
	}
}