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
		if(bullet->spc == NOT_EXIST) continue;
		renderer->Point(cr::point(bullet->pos.x + info.x, bullet->pos.y + info.y), col);
	}
	renderer->SetPointSize(oldptsize);

}

#else // RUN_ONLY

/////////////////////////////
// EDITTIME drawing
// Draw your object in the layout editor.
void EditExt::Draw()
{
	/*RECT rc;
	rc.left = pInfo->objectX;
	rc.top = pInfo->objectY;
	rc.right = pInfo->objectX + pInfo->objectWidth;
	rc.bottom = pInfo->objectY + pInfo->objectHeight;*/

	// Draw a simple rectangle
	//pEditTime->Box(rc, D3D_CONVERTCOLORREF(RGB(0, 0, 0)));
	D3DCOLOR col = D3D_CONVERTCOLORREF(RGB(50, 100, 0));
	float x = pInfo->objectX;
	float y = pInfo->objectY;
	float radius = min(pInfo->objectWidth / 2, pInfo->objectHeight / 2);
	float angle = RADIANS(pInfo->objectAngle);
	pEditTime->SetTexture(-1);
	float endX = x + cos(angle - 40) * radius;
	float endY = y + sin(angle - 40) * radius;
	pEditTime->Line(x, y, endX, endY, col);

	endX = x +cos(angle + 40) * radius;
	endY = y + sin(angle + 40) * radius;
	pEditTime->Line(x, y, endX, endY, col);
}

#endif // RUN_ONLY