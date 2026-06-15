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

#pragma warning (disable: 4244)
#include <math.h>
#include "SDK/common/mathlib.h"
//#include "client.h" //not include bug

//**********************************************************************************************************************************

#ifndef NULL
#define NULL ((void *)0)
#endif NULL
#define BOUND_VALUE(var,min,max) if((var)>(max)){(var)=(max);};if((var)<(min)){(var)=(min);}
float mainViewOrigin[3],mainViewAngles[3];
float displayCenterX=500, displayCenterY=350;
float mainViewAngles_SinYaw;
float mainViewAngles_CosYaw;
int iCurrentFOV=90;
float fCurrentFOV=90.0;
float fCurrentFOVbox=90.0;
float fCurrentFOVbone=90.0;
#define M_PI 3.14159265359
double pisobre180_2 = (M_PI/180.0f);
double _180sobrepi_2 = (180.0f/M_PI);

//**********************************************************************************************************************************

inline float VectorLength(const vec3_t v)
{
	return /*(float)*/sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
}

//**********************************************************************************************************************************

inline float VectorAngle(const vec3_t a, const vec3_t b)
{
    float length_a = VectorLength(a);
	float length_b = VectorLength(b);
	float length_ab = length_a*length_b;
	if( length_ab==0.0 ){ return 0.0; }
	else                { return (double)(acos(DotProduct(a,b)/length_ab) * (_180sobrepi_2)); }
}

//**********************************************************************************************************************************

void MakeVector(const vec3_t ain, vec3_t vout)
{
	float pitch;
	float yaw;
	float tmp;		
	pitch = (ain[0] * pisobre180_2);
	yaw = (ain[1] * pisobre180_2);
	tmp = cos(pitch);
	vout[0] = (-tmp * -cos(yaw));
	vout[1] = (sin(yaw)*tmp);
	vout[2] = -sin(pitch);
}

//**********************************************************************************************************************************

void VectorRotateX(const vec3_t in, float angle, vec3_t out)
{
    float	a,c,s;
	a = (angle * pisobre180_2);
	c = cos(a);
	s = sin(a);
	out[0] = in[0];
	out[1] = c*in[1] - s*in[2];
	out[2] = s*in[1] + c*in[2];	
}

//**********************************************************************************************************************************

void VectorRotateY(const vec3_t in, float angle, vec3_t out)
{
	float a,c,s;
	a = (angle * pisobre180_2);
	c = cos(a);
	s = sin(a);
	out[0] = c*in[0] + s*in[2];
	out[1] = in[1];
	out[2] = -s*in[0] + c*in[2];
}

//**********************************************************************************************************************************

void VectorRotateZ(const vec3_t in, float angle, vec3_t out)
{
	float a,c,s;
	a = (angle * pisobre180_2);
	c = cos(a);
	s = sin(a);
	out[0] = c*in[0] - s*in[1];
	out[1] = s*in[0] + c*in[1];
	out[2] = in[2];
}

//**********************************************************************************************************************************

int NewCalcScreen(float* in, float* out)
{
	vec3_t aim;
	vec3_t newaim;
	vec3_t view;
	vec3_t tmp;
	float num;
	if(!in||!out){ return false; }
	VectorSubtract(in,mainViewOrigin,aim);	
	MakeVector(mainViewAngles,view);	
	if (VectorAngle(view,aim) > (fCurrentFOV/1.8))
	{
		return false;
	}		
	VectorRotateZ(aim,-mainViewAngles[1],newaim);
	VectorRotateY(newaim,-mainViewAngles[0],tmp);
	VectorRotateX(tmp,-mainViewAngles[2],newaim);
	if (newaim[0] <= 0)
	{
		return false;
	}
	if(fCurrentFOV==0.0){ return false; }
	num = /*(float)*/((displayCenterX/newaim[0])*(120.0/fCurrentFOV - 1.0/3.0));
	out[0] = displayCenterX - num*newaim[1];
	out[1] = displayCenterY - num*newaim[2];
	BOUND_VALUE(out[0],0,displayCenterX*2);
	BOUND_VALUE(out[1],0,displayCenterY*2);
	return true;
}

//**********************************************************************************************************************************

int NewCalcScreen1(float* in, float* out)
{
	vec3_t aim;
	vec3_t newaim;
	vec3_t view;
	vec3_t tmp;
	float num;
	if (!in || !out){
		return false; 
	}
	VectorSubtract(in, mainViewOrigin, aim);	
	MakeVector(mainViewAngles, view);		
	VectorRotateZ(aim, -mainViewAngles[1], newaim); // yaw
	VectorRotateY(newaim, -mainViewAngles[0], tmp); // pitch
	VectorRotateX(tmp, -mainViewAngles[2], newaim); // roll
	num=(float)((displayCenterX/newaim[0])*(120.0/fCurrentFOV-1.0/3.0));
	out[0]=displayCenterX-num*newaim[1];
	out[1]=displayCenterY-num*newaim[2];
	BOUND_VALUE(out[0], 0, displayCenterX*2);
	BOUND_VALUE(out[1], 0, displayCenterY*2);
	return true;
}

//**********************************************************************************************************************************

