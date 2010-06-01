// Include StdAfx.h
#include "StdAfx.h"
#include "Bullet.h"
#include <boost/foreach.hpp>

#ifdef RUN_ONLY

/////////////////////////////
// RUNTIME drawing
// Draw: Construct calls this when it wants you to draw your object.  You can
// leave it blank if your plugin doesn't draw anything.  This is not called when OF_NODRAW is set.
void ExtObject::Draw()
{
	CRunLayer* pLayer = pRuntime->GetLayer(pLayout, info.layer);
	float totalZoom = pLayout->zoomX * pLayer->zoomXoffset;

	cr::color col(RGB(255,100,0));
	float oldptsize = renderer->GetPointSize();
	renderer->SetPointSize(10.0f * totalZoom);
	renderer->SetTexture(NULL);
	BOOST_FOREACH(const Bullet* bullet, manager.bullets())
	{
		renderer->Point(cr::point(bullet->x + info.x, bullet->y + info.y), col);
	}
	renderer->SetPointSize(oldptsize);

}

#else // RUN_ONLY

/////////////////////////////
// EDITTIME drawing
// Draw your object in the layout editor.
void EditExt::Draw()
{
	RECT rc;
	rc.left = pInfo->objectX;
	rc.top = pInfo->objectY;
	rc.right = pInfo->objectX + pInfo->objectWidth;
	rc.bottom = pInfo->objectY + pInfo->objectHeight;

	// Draw a simple rectangle
	pEditTime->Box(rc, D3D_CONVERTCOLORREF(RGB(0, 0, 0)));
}

#endif // RUN_ONLY