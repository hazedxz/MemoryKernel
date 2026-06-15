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

#ifndef MINIRADAR_H
#define MINIRADAR_H

//**********************************************************************************************************************************

void calcRadarPointX(const float* origin, int& screenx, int& screeny);
void calcRadarPointY(const float* origin, int& screenx, int& screeny);
void drawMiniRadarPoint(const float* origin,int r,int g,int b,int w, int h, bool blink);
void drawRadarPoint(const float* origin,int r,int g,int b,int w, int h, bool blink);
void drawRadarFrame();
void drawRadarFrame2();

//**********************************************************************************************************************************

#endif

//**********************************************************************************************************************************
