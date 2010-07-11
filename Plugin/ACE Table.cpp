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
	//privatevar conditions
	ADDPARAM(PARAM_PRIVATEVARIABLE, "Private variable", "Select the private variable to test.");
	ADDPARAMCOMBO("Comparison", "Select the comparison to make.", "Equal to|Not equal to|Less than|Less or equal|Greater than|Greater or equal");
	ADDPARAM(PARAM_VALUE, "Value", "Value to compare to");
	ADDCND("*Compare a private variable", "Private variables", "%o %n:  Value %0 %1 %2", &ExtObject::cValueCmp, "CompareValue", 0);
	ADDPARAM(PARAM_PRIVATEVARIABLE, "Variable name", "Variable to find lowest value in.");
	ADDCND("Pick object with lowest variable", "Private variables", "%o %n: Pick with lowest '%0'", &ExtObject::cPickLowestVar, "PickLowestVar", CND_STATIC);
	ADDPARAM(PARAM_PRIVATEVARIABLE, "Variable name.", "Variable to find highest value in.");
	ADDCND("Pick object with highest variable", "Private variables", "%o %n: Pick with highest '%0'", &ExtObject::cPickHighestVar, "PickHighestVar", CND_STATIC);

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
		"Set aim target at %0, %1", &ExtObject::aSetTargetPos,
		"SetTargetPos", 0);
	ADDPARAM(PARAM_PRIVATEVARIABLE, "Private variable", "Select the private variable to modify.");
	ADDPARAM(PARAM_VALUE, "Value", "Value to add.");
	ADDACT("Add to value", "Private variables", "Add %1 to %0", &ExtObject::aAddValue, "AddValue", 0);
	ADDPARAM(PARAM_PRIVATEVARIABLE, "Private variable", "Select the private variable to modify.");
	ADDPARAM(PARAM_VALUE, "Value", "Value to subtract.");
	ADDACT("Subtract from value", "Private variables", "Subtract %1 from %0", &ExtObject::aSubValue, "SubValue", 0);
	ADDPARAM(PARAM_PRIVATEVARIABLE, "Private variable", "Select the private variable to modify.");
	ADDPARAM(PARAM_VALUE, "Value", "Value to store");
	ADDACT("*Set value", "Private variables", "Set %0 to %1", &ExtObject::aSetValue, "SetValue", 0);
	ADDPARAM(PARAM_VALUE, "Rank (difficulty)", "Rank (difficulty) for new bullets. 0.0 - 1.0.");
	ADDACT("Set rank", "BulletML", "Set rank to %0", &ExtObject::aSetRank,
		"SetRank", 0);
	ADDPARAM(PARAM_OBJECT, "Object", "Object type to use as bullet.");
	ADDACT("Set bullet object type", "BulletML", "Set %0 as bullet object type",
		&ExtObject::aSetBulletObject, "SetBulletObject", 0);

	/////////////////////////////
	// Expressions
	// ADDEXP(List name, Category, Display string, Function address, Flags)
	//ADDEXP("My expression", "My category", "MyExpression", &ExtObject::eMyExpression, RETURN_INTEGER);
	// This line includes your common ACEs as specified in Main.h
	ADDEXP("Bullet count", "BulletML", "BulletCount", &ExtObject::eBulletCount, RETURN_INTEGER);
	ADDEXP("Last error string", "BulletML", "LastErrorString", &ExtObject::eErrorString, RETURN_STRING);
	ADDPARAM(PARAM_PRIVATEVARIABLE, "'Variable name'", "Name of value.");
	ADDEXP("Get private variable", "Private variables", "Value", &ExtObject::eGetValue, 0);
	ADDEXP("Get private variable count", "Private variables", "NumVars", &ExtObject::eNumPVs, RETURN_VALUE);
	ADDEXP("Rank", "BulletML", "Rank", &ExtObject::eRank, RETURN_FLOAT);
#include "..\Common\CommonAceTable.hpp"
}


