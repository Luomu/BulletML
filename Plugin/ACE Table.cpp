// Include StdAfx
#include "StdAfx.h"

// Include any used common ACE definitions.
#ifdef RUN_ONLY
#include "..\Common\CommonAceDef.hpp"
#endif

//////////////////////////////////////////////////////////////////////////////////
// ACE table
//////////////////////////////////////////////////////////////////////////////////

void DefineACES(MicroAceTime* at)
{
	// Define your ACE tables here.
	// Use ADDPARAM before each ADDACT/ADDCND/ADDEXP to add parameters.
	// See the documentation for full details.

	// Note in the display string, %o is your object icon and %0-%9 make up parameters.
	// Note the script name should be a name suitable for the routine as if it were a member function in a
	// scripting language, eg. "Clear Stored Items" -> "ClearStoredItems"

	/////////////////////////////
	// Conditions
	// Format:
	// ADDCND(List name, Category, Display string, Function address, Script name, Flags)
	//ADDCND("My condition", "My category", "%o My condition", &ExtObject::cMyCondition, "MyCondition", 0);
	ADDCND("On finished", "BulletML", "%o On finished", &ExtObject::cFinished, "Finished", 0);
	ADDCND("On error occurred", "BulletML", "%o On error occurred", &ExtObject::cErrorOccurred, "ErrorOccurred", 0);
	ADDPARAM(PARAM_OBJECT, "Object name", "Name of the object");
	ADDCND("On collision", "BulletML", "%o A bullet collides with %0", &ExtObject::cOnCollision, "OnCollision", SOL_MODIFIER);
	ADDCND("Is running", "BulletML", "%o Script is running", &ExtObject::cIsRunning, "IsRunning", 0);

	/////////////////////////////
	// Actions
	// Format:
	// ADDCND(List name, Category, Display string, Function address, Script name, Flags)
	//ADDPARAM(PARAM_VALUE, "Example parameter", "Here is an example parameter.");
	//ADDACT("My action", "My category", "Example action (%0)", &ExtObject::aMyAction, "MyAction", 0);
	ADDPARAM(PARAM_STRING, "File name", "BulletML file to load.");
	ADDACT("Load", "BulletML", "Load file %0", &ExtObject::aLoad, "Load", 0);
	ADDACT("Restart", "BulletML", "Restart", &ExtObject::aRestart, "Restart", 0);
	ADDACT("Stop", "BulletML", "Stop", &ExtObject::aStop, "Stop", 0);
	ADDACT("Clear", "BulletML", "Remove all bullets", &ExtObject::aClear, "Clear", 0);
	ADDPARAM(PARAM_VALUE, "X", "X coordinate");
	ADDPARAM(PARAM_VALUE, "Y", "Y coordinate");
	ADDACT("Set target position", "BulletML",
		"Set position for aimed bullets to target at", &ExtObject::aSetTargetPos,
		"SetTargetPos", 0);

	//Room saving
	/////////////////////////////
	// Expressions
	// ADDEXP(List name, Category, Display string, Function address, Flags)
	//ADDEXP("My expression", "My category", "MyExpression", &ExtObject::eMyExpression, RETURN_INTEGER);
	// This line includes your common ACEs as specified in Main.h
	ADDEXP("Bullet count", "BulletML", "BulletCount", &ExtObject::eBulletCount, RETURN_INTEGER);
	ADDEXP("Last error string", "BulletML", "LastErrorString", &ExtObject::eErrorString, RETURN_STRING);
#include "..\Common\CommonAceTable.hpp"
}


