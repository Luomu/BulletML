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
	float oldptsize = renderer->GetPointSize();
	float pointsize = parameters.bulletSize * totalZoom;
	cr::point hotspot(pointsize/2, pointsize/2);
	renderer->SetPointSize(pointsize);

	cr::renderstate_value oldPointSpriteState = renderer->GetRenderState(cr::rs_pointsprite_enabled);
	if(parameters.useTexture)
	{
		renderer->SetRenderState(cr::rs_pointsprite_enabled, cr::rsv_enabled);
		renderer->SetTexture(th);
	}
	else
		renderer->SetTexture(NULL);

	BOOST_FOREACH(const Bullet* bullet, manager.bullets())
	{
#ifndef _DEBUG
		if(bullet->spc == NOT_EXIST || bullet->spc == TOP_BULLET) continue;
#endif
		cr::color col = bullet->color;
		col *= info.pInfo->filter;
		if(parameters.allowRotations && bullet->dir != 0)
		{
			renderer->Quad_xywh(bullet->pos.x, bullet->pos.y, pointsize, pointsize, bullet->dir, hotspot, col);
		}
		else
		{
			renderer->Point(cr::point(bullet->pos.x, bullet->pos.y), col);
		}
	}
	if(parameters.useTexture)
		renderer->SetRenderState(cr::rs_pointsprite_enabled, oldPointSpriteState);
	renderer->SetPointSize(oldptsize);

#ifdef _DEBUG
	// Draw a simple rectangle
	//renderer->Box(cr::rect(info.x, info.y, info.x + info.w, info.y + info.h), cr::color(50, 0, 0, 0), info.angle);
	float startx = info.x + info.HotSpotX;
	float starty = info.y + info.HotSpotY;
	float endx = startx + cos(RADIANS(info.angle)) * 50;
	float endy = starty + sin(RADIANS(info.angle)) * 50;
	cr::color col(RGB(255,255,0));
	renderer->Line(cr::point(startx, starty),
				   cr::point(endx, endy), col);

	endx = startx + cos(RADIANS(info.angle - 90)) * 20;
	endy = starty + sin(RADIANS(info.angle - 90)) * 20;
	renderer->Line(cr::point(startx, starty),
				   cr::point(endx, endy), col);
#endif

}

#else // RUN_ONLY

/////////////////////////////
// EDITTIME drawing
// Draw your object in the layout editor.
void EditExt::Draw()
{
	D3DCOLOR col = D3D_CONVERTCOLORREF(RGB(200, 200, 0));
	pEditTime->SetTexture(-1);
	float x = pInfo->objectX;
	float y = pInfo->objectY;
	float radius = min(pInfo->objectWidth / 3, pInfo->objectHeight / 2);
	float angle = RADIANS(pInfo->objectAngle);
	float tipX = x + cos(angle) * radius;
	float tipY = y + sin(angle) * radius;

	float endX = x + cos(angle + 10) * radius;
	float endY = y + sin(angle + 10) * radius;
	pEditTime->Line(tipX, tipY, endX, endY, col);

	float endXB = x + cos(angle - 10) * radius;
	float endYB = y + sin(angle - 10) * radius;
	pEditTime->Line(tipX, tipY, endXB, endYB, col);

	pEditTime->Line(endX, endY, endXB, endYB, col);
}

#endif // RUN_ONLY