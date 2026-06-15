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

#ifndef CALCSCREEN_H
#define CALCSCREEN_H

//**********************************************************************************************************************************

extern float mainViewOrigin[3], mainViewAngles[3];
extern float mainViewFov;
extern float displayCenterX, displayCenterY;
int NewCalcScreen(float* in, float* out);
extern float mainViewAngles_SinYaw;
extern float mainViewAngles_CosYaw;
extern int iCurrentFOV;
extern float fCurrentFOV;
//**********************************************************************************************************************************

#endif

//**********************************************************************************************************************************
