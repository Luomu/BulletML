// Edittime.cpp - Edittime implementation of object
//

// Include StdAfx and Properties.h
#include "StdAfx.h"

#ifndef RUN_ONLY

//////////////////////////////////////////////////////////////////////////////////
// Property table
//////////////////////////////////////////////////////////////////////////////////

// The property table defines the list of properties that appear in the property
// grid when your object is selected in the layout editor.
//
// See the SDK docs for full documentation, but to get you started:-
//
// PROPERTY_EDIT  (myVariable, "Label", "Description");		// A text field property.
// PROPERTY_VALUE (myVariable, "Label 2", "Description");	// An integer property.
// PROPERTY_FLOAT (myVariable, "Label 3", "Description");	// A double/float property
//
// The labels must be unique!

BEGIN_PROPERTY_TABLE();

	PROPERTY_VALUE(parameters.maxLifeTime, "Timeout", "Timeout in milliseconds before destroying bullet (without unfinished actions).");
	PROPERTY_BOOL(parameters.destroyOutsideScreen, "Destroy outside screen", "Destroy bullets if they get outside the screen.");
	PROPERTY_BUTTON("Edit", "Texture", "Edit", BtnEditTexture());

	PROPERTY_FLOAT(parameters.defaultSpeed, "Default speed", "For bullets without specified speed, in pixels per second.");
	PROPERTY_FLOAT(parameters.speedMultiplier, "Speed multiplier", "Use this to adjust speed values");
	PROPERTY_FLOAT(parameters.timeMultiplier, "Time multiplier", "Use this to adjust time (wait) values");

END_PROPERTY_TABLE  ();


/////////////////////////////////////////////////////////////////////////////////
// Edittime functions
//////////////////////////////////////////////////////////////////////////////////

// Constructor
EditExt::EditExt(VEditTime* pVEditTime, editInfo* pEInfo) :
	parameters()
{
	// Store the edittime and einfo pointers
	pEditTime = pVEditTime;
	pInfo = pEInfo;
	imgHandle = -1;
}

// Destructor: when your object is deleted or the application closed:
// close any allocated resources here
EditExt::~EditExt()
{

}

void EditExt::BtnEditTexture()
{
	if(imgHandle == -1)
		imgHandle = pEditTime->AddImage(32, 32);
	pEditTime->EditImage(imgHandle);
}

// Initialization:  when the frame editor is opened.  Create textures, fonts,
// and any other DirectX volatile data here.
void EditExt::Initialize()
{

}

// Called when any property has been changed.
void EditExt::OnPropertiesUpdate()
{
}

// When the object is inserted to the layout editor by the user.
void EditExt::OnPut()
{
	// Default object size
	pInfo->objectWidth = 64;
	pInfo->objectHeight = 64;
	pInfo->originX = 0.5f;
	pInfo->originY = 0.5f;
	imgHandle = pEditTime->AddImage(32, 32);
}


// When the object is removed from the layout editor by the user.
void EditExt::OnRemoved()
{

}

// On object resized
BOOL EditExt::OnSizeObject()
{
	return TRUE;
}

void EditExt::GetAnimationHandle(int& handle)
{
	
}

#else //ifndef RUN_ONLY

BOOL WINAPI ETCreateObject(editInfo* editObject) {return FALSE;}
BOOL WINAPI ETInitializeObject(editInfo* editObject, VEditTime* pVEditTime) {return FALSE;}
BOOL WINAPI ETDestroyObject(editInfo* editObject) {return FALSE;}
int WINAPI ETDrawObject(editInfo *editObject) {return 0;}
void ETOnPropertyChanged(editInfo* editObject) {}
long LinkPropTable() {return 0;}
void WINAPI ETSerialize(editInfo* editObject, bin& ar) {}
void WINAPI ETPutObject(editInfo* editObject) {}
void WINAPI ETRemoveObject(editInfo* editObject) {}
void WINAPI GetInfo(LPOINFO objectInfo) {}
int WINAPI ETGetMenuIcons(editInfo* editObject, int ACEMenu) {return 0;}
int WINAPI ETShowACEMenu(editInfo* editObject, TABLE ACEType)  {return 0;}
BOOL WINAPI ETSizeObject(editInfo* editObject)  {return FALSE;}

#endif // RUN_ONLY