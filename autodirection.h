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

#ifndef AUTODIRECTION_H
#define AUTODIRECTION_H

//**********************************************************************************************************************************

class AutoDirection
{
public:	
		bool wayFree1(float* from,float* to);
		bool wayFree2(float* from,float* to);
		bool wayFree3(float* from,float* to);
		bool adjustMyDirection1(struct usercmd_s *usercmd);
		bool adjustMyDirection2(struct usercmd_s *usercmd);
		bool adjustMyAngles(float *viewangles);
		//////////////////////////////////////////////////
		void NextStepPos(float* nowpos,float* viewangles,float step,float* newpos);
		void SetAngle(float* viewangles);
		bool IsMyWayFree1(float step,float userangle);
		bool IsMyWayFree2(float step,float userangle);
        bool IsMyWayFree3(float step,float *viewangles);
		void adjustJump(struct usercmd_s* usercmd);
};

//**********************************************************************************************************************************

extern AutoDirection autodirection;

//**********************************************************************************************************************************

#endif

//**********************************************************************************************************************************
