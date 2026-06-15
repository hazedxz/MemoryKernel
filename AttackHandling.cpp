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

enum { FIRESEQ_INACTIVE     = 0, 
       FIRESEQ_STARTDELAY   = 1, 
	   FIRESEQ_ACTIVE       = 2,
	   FIRESEQ_RELEASEDELAY = 3 };

bool bAttacking = false;
static bool bAttack2 = false;
static int  nFireSequence = FIRESEQ_INACTIVE;
static bool bFireCycle  = true;

void AttackHandling()
{
	static double timer=0;

 	if( !cvar.ftime ) { cvar.ftime = 0.1f; }

	if (g_Aimbot.iTargetID!=0)
	{
		switch (nFireSequence)
		{
		case FIRESEQ_INACTIVE:
			if( cvar.sdelay )
			{
				nFireSequence =  FIRESEQ_STARTDELAY;
				timer = ClientTime::current;

			} else {
				nFireSequence =  FIRESEQ_ACTIVE;
				timer = ClientTime::current;
				bFireCycle  = true;
				bAttacking = true;
			}
			break;
		case FIRESEQ_STARTDELAY:
			if( ClientTime::current >= (timer+cvar.sdelay) )
			{
				nFireSequence =  FIRESEQ_ACTIVE;
				timer = ClientTime::current;
				bFireCycle  = true;
				bAttacking = true;
			}
			break;
		case FIRESEQ_ACTIVE:
			if( bFireCycle )
			{
				if( (ClientTime::current >= (timer+cvar.ftime)) && (cvar.dtime!=0))
				{
					bAttacking = false;
					timer = ClientTime::current;
					bFireCycle = false;
				}

			} else {
				if( ClientTime::current >= (timer+cvar.dtime) )
				{
					bAttacking = true;
					timer = ClientTime::current;
					bFireCycle = true;
				}
			}
			break;
		case FIRESEQ_RELEASEDELAY:
			nFireSequence =  FIRESEQ_ACTIVE;
			timer = ClientTime::current;
			bFireCycle  = true;
			bAttacking = true;
			break;
		}
	} 
	else 
	{
		switch (nFireSequence)
		{
		case FIRESEQ_INACTIVE:
			break;
		case FIRESEQ_STARTDELAY:
			nFireSequence =  FIRESEQ_INACTIVE;
			break;
		case FIRESEQ_ACTIVE:
			if( !bFireCycle || (cvar.rdelay==0) )
			{
				bAttacking = false;
				nFireSequence =  FIRESEQ_INACTIVE;

			} else {
				timer = ClientTime::current;
				nFireSequence = FIRESEQ_RELEASEDELAY;
			}
			break;
		case FIRESEQ_RELEASEDELAY:
			if( ClientTime::current >= (timer+cvar.rdelay) )
			{
				bAttacking = false;
				nFireSequence =  FIRESEQ_INACTIVE;
			}
			break;
		}
	}
}

//*************************************************************************************

