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



void FixupAngleDifference(usercmd_t *usercmd)
{
	if(!(usercmd->buttons&IN_ATTACK) && !(currentWeaponID==WEAPON_KNIFE && (usercmd->buttons & IN_ATTACK2)) && !(usercmd->buttons&IN_USE))
    {
		Vector viewforward, viewright, viewup, aimforward, aimright, aimup, v;
		float newforward, newright, newup, fTime;
		float forward = usercmd->forwardmove;
		float right = usercmd->sidemove;
		float up = usercmd->upmove;
		bool movetype_walk = (gEngfuncs.GetLocalPlayer()->curstate.movetype == MOVETYPE_WALK);
 
		if(movetype_walk){
			v[0]=0.0f;
			v[1]=usercmd->viewangles[1];
			v[2]=0.0f;
			gEngfuncs.pfnAngleVectors(v, viewforward, viewright, viewup);
		} else {
			gEngfuncs.pfnAngleVectors(usercmd->viewangles, viewforward, viewright, viewup);
		}
 
		fTime = gEngfuncs.GetClientTime();
		if(cvar.antiaimpitch==1)
		{
			//Down
			usercmd->viewangles.x = 88;
		}
		else if(cvar.antiaimpitch==2)
		{
			//Up
			usercmd->viewangles.x = -88;
		}
		else if(cvar.antiaimpitch==3)
		{
			//FakeDown
			usercmd->viewangles.x = 1620;
		}
		else if(cvar.antiaimpitch==4)
		{
			//FakeUp
			usercmd->viewangles.x = -1619;
		}
		else if(cvar.antiaimpitch==5)
		{
			//Spin X
			usercmd->viewangles.x = cos(fTime * 11 * 3.14159265358979323846) * 360.0f;
			usercmd->viewangles.x = cos(fTime * 11 * 3.14159265358979323846) * 90.0f;
		}
		else if(cvar.antiaimpitch==6)
		{
			//Static
			usercmd->viewangles.x = 0;
		}
 
		if(cvar.antiaimyaw==1)
		{
			//Backwards
			usercmd->viewangles.y = usercmd->viewangles.y + 180;
		}
		else if(cvar.antiaimyaw==2)
		{
			//Static Left
			usercmd->viewangles.y = 90;
		}
		else if(cvar.antiaimyaw==3)
		{
			//Static Right
			usercmd->viewangles.y = 270;
		}
		if(cvar.antiaimyaw==4)
		{
			//Left
			usercmd->viewangles.y = usercmd->viewangles.y + 90;
		}
		else if(cvar.antiaimyaw==5)
		{
			//Right
			usercmd->viewangles.y = usercmd->viewangles.y + 270;
		}
		else if(cvar.antiaimyaw==6)
		{
			//Spin Y
			usercmd->viewangles.y = sin(fTime * 11 * 3.14159265358979323846) * 360.0f;
		}
		else if(cvar.antiaimyaw==7)
		{
			//Static
			usercmd->viewangles.y = 0;
		}
		else if(cvar.antiaimyaw==8)
		{
			int random = rand() % 100;
 
			if (random < 98)
			// Look backwards
			usercmd->viewangles.y -= 180;
 
			// Jitter
			if (random < 15)
			{
				float change = -70 + (rand() % (int)(140 + 1));
				usercmd->viewangles.y += change;
			}
 
			if (random == 69)
			{
				float change = -90 + (rand() % (int)(180 + 1));
				usercmd->viewangles.y += change;
			}
		}
		else if(cvar.antiaimyaw==9)
		{
			//Jitter
			int random = 1 + (rand() % (int)(100 - 1 + 1));
			if(random < 10)
			{
				usercmd->viewangles.y+=180;
			}
			if(random > 90)
			{
				usercmd->viewangles.y=usercmd->viewangles.y;
			}
		}
 
		//
		if(movetype_walk){
			v[0]=0.0f;
			v[1]=usercmd->viewangles[1];
			v[2]=0.0f;
			gEngfuncs.pfnAngleVectors(v, aimforward, aimright, aimup);
		} else {
			gEngfuncs.pfnAngleVectors(usercmd->viewangles, aimforward, aimright, aimup);
		}
 
		//
		newforward = DotProduct(forward * viewforward.Normalize(), aimforward) + DotProduct(right * viewright.Normalize(), aimforward) + DotProduct(up * viewup.Normalize(), aimforward);
		newright = DotProduct(forward * viewforward.Normalize(), aimright) + DotProduct(right * viewright.Normalize(), aimright) + DotProduct(up * viewup.Normalize(), aimright);
		newup = DotProduct(forward * viewforward.Normalize(), aimup) + DotProduct(right * viewright.Normalize(), aimup) + DotProduct(up * viewup.Normalize(), aimup);
 
		//
		if(cvar.antiaimpitch==3||cvar.antiaimpitch==4)
		{
			usercmd->forwardmove = -newforward;
			usercmd->sidemove = newright;
			usercmd->upmove = newup;
		}
		else
		{
			usercmd->forwardmove = newforward;
			usercmd->sidemove = newright;
			usercmd->upmove = newup;
		}
	}
}