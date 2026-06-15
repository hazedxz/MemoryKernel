/************************************************************************************************************************************
*
*
* 007 HOOK
* Code By: 007 + boy_scout
* msn: david_bs@live.com
* (c)2011
* www.etalking.com.ar
*
*
************************************************************************************************************************************/

#include "client.h"

//**********************************************************************************************************************************

static void calcRadarPoint(const float* origin, int& screenx, int& screeny)
{
	float dx  = origin[0] - me.pmEyePos[0];
	float dy  = origin[1] - me.pmEyePos[1];
	
    // rotate
	float x =  dy*(-mainViewAngles_CosYaw)  + dx*mainViewAngles_SinYaw;
	float y =  dx*(-mainViewAngles_CosYaw)  - dy*mainViewAngles_SinYaw;
	
	float& range = cvar.radar_range;
	if(fabs(x)>range || fabs(y)>range)
	{ 
		// clipping
		if(y>x)
		{
			if(y>-x) {
				x = range*x/y;
				y = range;
			}  else  {
				y = -range*y/x; 
				x = -range; 
			}
		} else {
			if(y>-x) {
				y = range*y/x; 
				x = range; 
			}  else  {
				x = -range*x/y;
				y = -range;
			}
		}
	}
	screenx = displayCenterX+int(x/cvar.radar_range*float(cvar.miniradar_size));
	screeny = displayCenterY+int(y/cvar.radar_range*float(cvar.miniradar_size));
}

static void calcRadarPoint2(const float* origin, int& screenx, int& screeny) //needed to not cause conflict
{
	float dx  = origin[0] - me.pmEyePos[0];
	float dy  = origin[1] - me.pmEyePos[1];
	
    // rotate
	float x =  dy*(-mainViewAngles_CosYaw)  + dx*mainViewAngles_SinYaw;
	float y =  dx*(-mainViewAngles_CosYaw)  - dy*mainViewAngles_SinYaw;
	
	float& range = cvar.radar_range;
	if(fabs(x)>range || fabs(y)>range)
	{ 
		// clipping
		if(y>x)
		{
			if(y>-x) {
				x = range*x/y;
				y = range;
			}  else  {
				y = -range*y/x; 
				x = -range; 
			}
		} else {
			if(y>-x) {
				y = range*y/x; 
				x = range; 
			}  else  {
				x = -range*x/y;
				y = -range;
			}
		}
	}
	screenx = cvar.radar_x+int(x/cvar.radar_range*float(cvar.radar_size));
	screeny = cvar.radar_y+int(y/cvar.radar_range*float(cvar.radar_size));
}
//**********************************************************************************************************************************

void calcRadarPointX(const float* origin, int& screenx, int& screeny)
{	
	calcRadarPoint(origin,screenx,screeny);
}

void calcRadarPointY(const float* origin, int& screenx, int& screeny)
{	
	calcRadarPoint2(origin,screenx,screeny);
}

//**********************************************************************************************************************************

void drawMiniRadarPoint(const float* origin,int r,int g,int b,int w, int h,bool blink=false)
{
	int screenx,screeny;
	calcRadarPointX(origin,screenx,screeny);
	if(!blink || blinkPhase){ 
		oglSubtractive = true;
		gEngfuncs.pfnFillRGBA(screenx-1,screeny-1,h,w,r,g,b,255);
		oglSubtractive = false;
		blackBorder(screenx-1,screeny-1,h,w+1);
	}
}

void drawRadarPoint(const float* origin,int r,int g,int b,int w, int h,bool blink=false)
{
	int screenx,screeny;
	calcRadarPointY(origin,screenx,screeny);
	if(!blink || blinkPhase){ 
		oglSubtractive = true;
		gEngfuncs.pfnFillRGBA(screenx-1,screeny-1,h,w,r,g,b,255);
		oglSubtractive = false;
		blackBorder(screenx-1,screeny-1,h,w+1);
	}
}

//**********************************************************************************************************************************

void drawRadarFrame()
{
	int radar_x = displayCenterX;
    int radar_y = displayCenterY;
	int& size    = cvar.miniradar_size;
	{
		ColorEntry* cDivider = colorList.get(26);
		oglSubtractive=true;
		gEngfuncs.pfnFillRGBA(radar_x,radar_y-size,1,2*size,cDivider->r,cDivider->g,cDivider->b,255);
		gEngfuncs.pfnFillRGBA(radar_x-size,radar_y,2*size,1,cDivider->r,cDivider->g,cDivider->b,255);
		oglSubtractive=false;
	}
}

//**********************************************************************************************************************************

void TrapezoidalConsole(int con_x, int con_y, int con_w, int con_h);
void drawRadarFrame2()
{
	int& centerx = cvar.radar_x;
	int& centery = cvar.radar_y;
	int& size    = cvar.radar_size;

	oglSubtractive = true;
	gEngfuncs.pfnFillRGBA(centerx,centery-size,1,2*size,255,255,255,255);
	gEngfuncs.pfnFillRGBA(centerx-size,centery,2*size,1,255,255,255,255);
	oglSubtractive = false;

	TrapezoidalConsole(centerx-size,centery-size,2*size,2*size);
}

//**********************************************************************************************************************************
