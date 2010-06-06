// Include StdAfx
#include "StdAfx.h"
#include "bulletml/bulletmlerror.h"

//////////////////////////////////////////////////////////////////////////////////
// Actions
//////////////////////////////////////////////////////////////////////////////////
long ExtObject::aRestart(LPVAL params)
{
	manager.restart();
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
	catch(...)
	{
		RaiseConstructError("Cannot load or parse " + params[0].GetString() + ". Unknown error.");
	}
	return 0;
}