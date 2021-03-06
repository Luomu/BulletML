// Runtime.cpp - Runtime implementation of object
//

// Include StdAfx
#include "StdAfx.h"
#include <boost/foreach.hpp>
#include "bulletml/bulletmlerror.h"

//////////////////////////////////////////////////////////////////////////////////
// Runtime functions
//////////////////////////////////////////////////////////////////////////////////
#ifdef RUN_ONLY

// ExtObject constructor:
// Only use for class initializer list.  Object initialisation must be done in OnCreate.
// It is not safe to make runtime calls here: do so in OnCreate.
ExtObject::ExtObject(initialObject* editObject, VRuntime* pVRuntime) :
	renderer(pVRuntime->pRenderer),
	unreportedError(false),
	unreportedFinish(false),
	manager(this),
	loops(0),
	loopDelay(0),
	elapsedDelay(0.f)
{
	pRuntime = pVRuntime;
	info.editObject = editObject;
}

// This is called just after the constructor when your object has been created.  Construct has set
// up your object here so it is safe to make runtime calls.
void ExtObject::OnCreate()
{
	// Load the edittime data that was serialized.
	bin ar;
	ar.attach(info.editObject->eData, info.editObject->eSize);

	ImageHandleInfo* imgHandle = NULL;
	th = NULL;

	// Read the data.  Same format as you exported in EditExt::Serialize.
	// Your runtime loader must be able to load all versions!
	int Version = 0;
	ar >> Version;
	parameters.Serialize(ar);
	imgHandle = pRuntime->LoadSerializedImageHandle(ar);
	th = renderer->CreateTextureFromHandle(imgHandle);

	// Finished reading data
	ar.detach();

	info.curTexture = 0;
	info.imgHandle = 0;
	// Set default dimensions
	info.x = info.editObject->eX;
	info.y = info.editObject->eY;
	info.w = info.editObject->eWidth;
	info.h = info.editObject->eHeight;
	info.angle = info.editObject->eAngle;

	info.pInfo->filter = info.editObject->eColor;

	SetupPrivateVariableVector(pRuntime, this, privateVars);

	// Update bounding box
	pRuntime->UpdateBoundingBox(this);
	info.pDisplayBoxOverride = &manager.boundingBox();

	try
	{
		manager.setParameters(parameters);
		manager.setAngle(info.angle);
	}
	catch(BulletMLError& berror)
	{
		RaiseConstructError(berror.what());
	}
	catch(...)
	{
		RaiseConstructError("Unknown error while initializing BulletML");
	}
}

// Destructor: called when an instance of your object is destroyed.
ExtObject::~ExtObject()
{
}

void ExtObject::updateScreenBoundaries()
{
	manager.screen().left = pLayout->scrollX;
	manager.screen().top = pLayout->scrollY;
	manager.screen().right = manager.screen().left + pLayout->winWidth;
	manager.screen().bottom = manager.screen().top + pLayout->winHeight;
}

// Called every frame, before the events and after drawing, for you to update your object if necessary
// Return 1 (do not call again) or 0 (continue calling)
BOOL ExtObject::OnFrame()
{
	info.box.left = info.x;
	info.box.top = info.y;
	info.box.right = info.x + 1;
	info.box.bottom = info.y + 1;

	timeDelta = pRuntime->GetTimeDelta();
	/*if (timeDelta > 0.5f)
		timeDelta = 0.0f;*/
	elapsedDelay += timeDelta * 1000;
	manager.setPos(info.x + info.HotSpotX, info.y + info.HotSpotY);
	manager.setAngle(info.angle);

	updateScreenBoundaries();

	pRuntime->UpdateBoundingBox(this);

	try
	{
		if(elapsedDelay > loopDelay && loops > 0)
		{
			unreportedFinish = true;
			manager.restart();
			loops--;
			elapsedDelay = 0.f;
		}
		manager.move(timeDelta);
		manager.clean();
	}
	catch(BulletMLError& err)
	{
		RaiseConstructError(err.what());
	}
	catch(...)
	{
		RaiseConstructError("Unknown error while running bullet script");
	}

	return 0;	// Do not call again
}

// Called every frame, after the events and before drawing, for you to update your object if necessary
// Return 1 (do not call again) or 0 (continue calling)
// It is not safe to destroy objects in OnFrame2().  If you have to do this, use OnFrame().
// If you are storing any pointers to CRunObjects, check the info.destroying flag here.  If it is true,
// you must reset the pointer to NULL as it is no longer valid.
BOOL ExtObject::OnFrame2()
{
	manager.checkForDeadCObjects();
	return 0;	// Do not call again
}

// WindowProc:  called when a window message, or WM_COMMAND specifying your window,
// is sent to Construct.  You must call RegisterWindow() before Construct will send
// you messages for the given window.
LRESULT ExtObject::WindowProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, uMessage, wParam, lParam);
}

BOOL ExtObject::PreTranslateMessage(MSG* msg)
{
	return 0;
}

// For global objects
void ExtObject::OnFrameChange(int oldFrame, int newFrame)
{
	// Do anything your global object needs when the frame changes
	// oldFrame is -1 on start of app, newFrame is -1 on end of app
}

// User defined functions
long ExtObject::GetData(int id, void* param)
{
	return 0;
}

long ExtObject::CallFunction(int id, void* param)
{
	return 0;
}

void ExtObject::RaiseConstructError(const CString& error)
{
	unreportedError = true;
	errorString = error;
}
#else //ifdef RUN_ONLY

CRunObject* WINAPI RTCreateObject(bin& ar, VRuntime* pRuntime) 
{
	return NULL;
}

void WINAPI RTDestroyObject(ExtObject* object)
{
}

#endif