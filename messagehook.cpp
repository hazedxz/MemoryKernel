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

static pfnUserMsgHook ResetHUDOrg=NULL;
static pfnUserMsgHook TeamInfoOrg=NULL;
static pfnUserMsgHook SayTextOrg=NULL;
static pfnUserMsgHook CurWeaponOrg=NULL;
static pfnUserMsgHook SetFOVOrg=NULL;
static pfnUserMsgHook ScoreAttribOrg=NULL;
static pfnUserMsgHook DeathMsgOrg=NULL;
static pfnUserMsgHook BatteryOrg=NULL;
static pfnUserMsgHook MoneyOrg=NULL;
static pfnUserMsgHook HealthOrg=NULL;
static pfnUserMsgHook AmmoOrg=NULL;
static pfnUserMsgHook AmmoXOrg=NULL;
static pfnUserMsgHook ScoreInfoOrg=NULL;
static pfnUserMsgHook WeaponListOrg=NULL;
static pfnUserMsgHook RadarOrg=NULL;
static pfnUserMsgHook RoundTimeOrg = NULL;
static pfnUserMsgHook FogOrg = NULL;

//**********************************************************************************************************************************

int roundcounter=0;
int mapcounter=0;
bool round_start=false;
bool map_change=false;
static char CurrentMap[100];
static bool bGotHeadshot=false;
long doubleKills = 0;
long tripleKills = 0;
StopTimer roundTime;
StopTimer tripleKill;
StopTimer doubleKill;
StopTimer monsterKill;
StopTimer gHudTimer2;
StopTimer gHudTimer;

//**********************************************************************************************************************************

void AtMapChange()
{
	g_Aimbot.iTargetID = 0;
	roundcounter=0;
	mapcounter++;

	me.spread.prcflags = 0;
	me.spread.random_seed = 0;
	me.spread.recoil = 0;
	me.spread.gtime = 0;
	me.spread.prevtime = 0;
	me.spread.brokentime = 0;
	me.spread.spreadvar = 0;
	me.spread.recoiltime = 0;
	me.spread.firing = false;
	gHudTimer.setExpired();
	gHudTimer2.setExpired();
	playerItems.clearWeaponSlots();
}

//**********************************************************************************************************************************

void AtRoundStart(void)
{
	g_Aimbot.iTargetID = 0;

	playerItems.clearWeaponSlots();

	if( strcmp(CurrentMap, gEngfuncs.pfnGetLevelName()) ){
	    strcpy(CurrentMap, gEngfuncs.pfnGetLevelName());
	    
		AtMapChange();
	}

	for(unsigned int i=0;i<vPlayers.size();i++) 
	{
		vPlayers[i].bGotHead = false;
		vPlayers[i].visible=0;
		vPlayers[i].distance=100000.0;

		vPlayers[i].updateClear();
	}		

	cmd.exec("#unbind del");
	cmd.exec("#unbind f12");
	cmd.exec("#unbind alt");
	pEngfuncs->pfnClientCmd("sv_maxvelocity 9999");
	pEngfuncs->pfnClientCmd("sv_airaccelerate 9999");
	pEngfuncs->pfnClientCmd("sv_gravity 400");

	int Id = playerItems.CurrentID();
	if (Id == WEAPONLIST_SG550 || Id == WEAPONLIST_G3SG1)
		me.spread.brokentime = 0; // This catches all cases except when you buy one and than shoot some bullets and that buy another

	me.infrozentime=true;

	if(cvar.rush) autoway.bContinueAutoWay=true;
	cmd.exec("route_load");

	cmd.exec("#impulse 101; later 0.6 buystuff");
	
	if (currentWeaponID == WEAPON_SG550 || currentWeaponID == WEAPON_G3SG1)
		me.spread.brokentime = 0; 
}

//**********************************************************************************************************************************

static int ResetHUD(const char* pszName, int iSize, void* pbuf)
{
	const char PROC_NAME[50] = "ResetHUD\0";
	updateLocalPlayer();
	roundcounter++;
	if (roundcounter) 
	{
		round_start=true;
	}

	return (*ResetHUDOrg)(pszName, iSize, pbuf);
}

//**********************************************************************************************************************************

static int CurWeapon(const char* pszName, int iSize, void* pbuf)
{
	const char PROC_NAME[50] = "CurWeapon\0";
	BEGIN_READ( pbuf, iSize );
	int iState = READ_BYTE();
	int iID    = READ_CHAR();
	int iClip  = READ_CHAR();
	playerItems.msgCurWeapon(iState,iID,iClip);
	if(iState)
	{
	    me.iClip = iClip;
	    char * name = playerItems.getNamebyId(iID);
	    if(!strcmp(name,"mp5navy")) currentWeaponID = WEAPONLIST_MP5;
	    else currentWeaponID = burstInfo.getWeaponID( name );
	}
	return (*CurWeaponOrg)(pszName, iSize, pbuf);
}

//**********************************************************************************************************************************

static int TeamInfo(const char* pszName, int iSize, void* pbuf)
{
	const char PROC_NAME[50] = "TeamInfo\0";
	static bool         done=false;
	static StringFinder teamNumber;
	if(!done)
	{
		teamNumber.add("terrorist"  ,1);teamNumber.add("ct"         ,2);
		teamNumber.add("unassigned" ,0);teamNumber.add("spectator"  ,0);
		done = true;
	}

	updateLocalPlayer();

	BEGIN_READ(pbuf,iSize);
	int px = READ_BYTE();
	char * teamtext = READ_STRING();
	if(!*teamtext) { vPlayers[px].team = 0; }
	else
	{
		_strlwr(teamtext);
		if(teamNumber.find(teamtext))
		{
			vPlayers[px].team = teamNumber.num;
			if(px==me.ent->index){ me.team = teamNumber.num; }
		}
		else
		{
			Con_Echo("TeamInfo: unknown px=%d, team=%s",px,teamtext);
			vPlayers[px].team = -1;
			if(px==me.ent->index){ me.team = -1; }
		}
	}
	return (*TeamInfoOrg)(pszName, iSize, pbuf);
}

//**********************************************************************************************************************************

static int DeathMsg(const char* pszName, int iSize, void* pbuf)
{
	const char PROC_NAME[50] = "DeathMsg\0";
	updateLocalPlayer();
	BEGIN_READ( pbuf, iSize );
	int killer = READ_BYTE();
	int victim = READ_BYTE();
	int headshot = READ_BYTE();
    char* weaponName = READ_STRING();
	if(victim==me.ent->index) playerItems.armor = 0;

	if(killer==me.ent->index && headshot) ++me.headshots;

	if(victim==me.ent->index)
	{ 
		g_Aimbot.iTargetID = 0; 
	}

	int px = victim;
	vPlayers[px].setDead();

	vPlayers[victim].setAlive(false);

	if(cvar.blood == 1)
	{
		for(int spray_count = 0;spray_count<5;spray_count++)
		{
			vec3_t blood_origin;	
			vec3_t blood_direction;
			int speed;
	
			cl_entity_s* ent = vPlayers[px].getEnt();
		
			blood_origin[0] = ent->origin[0];
			blood_origin[1] = ent->origin[1];
			blood_origin[2] = ent->origin[2]+30;
		
			blood_direction[0] = (float)(rand()%41)-20;
			blood_direction[1] = (float)(rand()%41)-20;
			blood_direction[2] = (float)(rand()%251)+50;
		
			speed = (rand()%101)+100;
			
			gEngfuncs.pEfxAPI->R_BloodStream( blood_origin, blood_direction, 70, speed); 
		}
	}

	if(cvar.blood == 2)
	{
		for(int spray_count = 0;spray_count<5;spray_count++)
		{
			vec3_t blood_origin;	
	
			cl_entity_s* ent = vPlayers[px].getEnt();
		
			blood_origin[0] = ent->origin[0];
			blood_origin[1] = ent->origin[1];
			blood_origin[2] = ent->origin[2]+30;
			
			gEngfuncs.pEfxAPI->R_LargeFunnel( blood_origin, 1); 
		}
	}

	if(cvar.blood == 3)
	{
		for(int spray_count = 0;spray_count<5;spray_count++)
		{
			vec3_t blood_origin;	
	
			cl_entity_s* ent = vPlayers[px].getEnt();
		
			blood_origin[0] = ent->origin[0];
			blood_origin[1] = ent->origin[1];
			blood_origin[2] = ent->origin[2]+30;
			
			gEngfuncs.pEfxAPI->R_LavaSplash( blood_origin); 
		}
	}

	if(cvar.blood == 4)
	{
		for(int spray_count = 0;spray_count<5;spray_count++)
		{
			vec3_t blood_origin;	
	
			cl_entity_s* ent = vPlayers[px].getEnt();
		
			blood_origin[0] = ent->origin[0];
			blood_origin[1] = ent->origin[1];
			blood_origin[2] = ent->origin[2]+30;
			
			gEngfuncs.pEfxAPI->R_BlobExplosion( blood_origin); 
		}
	}

	if(cvar.blood == 5)
	{
		for(int spray_count = 0;spray_count<5;spray_count++)
		{
			vec3_t blood_origin;	
	
			cl_entity_s* ent = vPlayers[px].getEnt();
		
			blood_origin[0] = ent->origin[0];
			blood_origin[1] = ent->origin[1];
			blood_origin[2] = ent->origin[2]+30;
			
			gEngfuncs.pEfxAPI->R_ParticleExplosion(blood_origin); 
		}
	}

	if(cvar.blood == 6)
	{
		for(int spray_count = 0;spray_count<5;spray_count++)
		{
			vec3_t blood_origin;	
	
			cl_entity_s* ent = vPlayers[px].getEnt();
		
			blood_origin[0] = ent->origin[0];
			blood_origin[1] = ent->origin[1];
			blood_origin[2] = ent->origin[2]+30;
			
			gEngfuncs.pEfxAPI->R_TeleportSplash(blood_origin); 
		}
	}

	if(cvar.blood == 7)
	{
		for(int spray_count = 0;spray_count<5;spray_count++)
		{
			vec3_t blood_origin;	

			int beamindex = gEngfuncs.pEventAPI->EV_FindModelIndex("sprites/laserdot.spr");
			cl_entity_s* ent = vPlayers[px].getEnt();
		
			blood_origin[0] = ent->origin[0];
			blood_origin[1] = ent->origin[1];
			blood_origin[2] = ent->origin[2]+30;

			gEngfuncs.pEfxAPI->R_FunnelSprite( blood_origin, beamindex, 1); 
		}
	}

	if(cvar.blood == 8)
	{
		for(int spray_count = 0;spray_count<5;spray_count++)
		{
			vec3_t blood_origin;	

			cl_entity_s* ent = vPlayers[px].getEnt();
		
			blood_origin[0] = ent->origin[0];
			blood_origin[1] = ent->origin[1];
			blood_origin[2] = ent->origin[2]+90;
			
			gEngfuncs.pEfxAPI->R_Explosion( blood_origin, gEngfuncs.pEventAPI->EV_FindModelIndex ("sprites/zerogxplode.spr"), 2.5, 15, TE_EXPLFLAG_NONE );
			gEngfuncs.pEfxAPI->R_ParticleExplosion2( blood_origin, 111, 8 );
		}
	}

	if(cvar.killsound && victim!=me.ent->index && killer==me.ent->index)
	{
		if (monsterKill.running())
		{
			cmd.exec("play sounds\\monsterkill.wav");
			monsterKill.countdown(1);
		}
		if (tripleKill.running())
		{
			if(!monsterKill.running())
			{
				cmd.exec("play sounds\\triplekill.wav");
				monsterKill.countdown(1);
			}
		}
		if (doubleKill.running())
		{
			if(!tripleKill.running())
			{
				cmd.exec("play sounds\\doublekill.wav");
				tripleKill.countdown(1);
			}
		}
		if (headshot) 
		{ 
			if(!doubleKill.running())
			{
				cmd.exec("play sounds\\headshot.wav");
				doubleKill.countdown(1);
			}
		}
		if(!doubleKill.running())
		{
			doubleKill.countdown(1);
		}
		cmd.exec(".enemydown");
	}

	return (*DeathMsgOrg)(pszName,iSize,pbuf);
}

//**********************************************************************************************************************************

#define HAS_BOMB (1<<1)
#define IS_VIP (1<<2)

static int ScoreAttrib(const char *pszName, int iSize, void *pbuf )
{
	const char PROC_NAME[50] = "ScoreAttrib\0";
	int retval;
	updateLocalPlayer();
	BEGIN_READ(pbuf, iSize);
    int idx  = READ_BYTE();
    int info = READ_BYTE();
    vPlayers[idx].iInfo = info;
	vPlayers[idx].hasbomb = info==HAS_BOMB;
	vPlayers[idx].vip = info==IS_VIP;
	retval = (*ScoreAttribOrg)(pszName,iSize,pbuf);
	return retval;
}

//**********************************************************************************************************************************

static int SetFOV(const char* pszName, int iSize, void* pbuf)
{
	const char PROC_NAME[50] = "MsgHook_SetFOV\0";
	BEGIN_READ( pbuf, iSize );
	me.iFOV = READ_BYTE();
	if(!me.iFOV)
		me.iFOV=90;
	if(me.iFOV==90)
		me.inZoomMode=false;
	else
		me.inZoomMode=true;
	if (cvar.antizoom && me.iFOV != 90) 
	{ 
		me.iFOV = 89; 
		((unsigned char*)pbuf)[0] = 89;	
	}
	iCurrentFOV = me.iFOV;
	fCurrentFOV = me.iFOV;
	return (*SetFOVOrg)(pszName, iSize, pbuf);
}

//**********************************************************************************************************************************

static int WeaponList(const char* pszName, int iSize, void* pbuf)
{
	const char PROC_NAME[50] = "WeaponList\0";
	playerItems.msgWeaponList(iSize,pbuf);
	return (*WeaponListOrg)(pszName, iSize, pbuf);
}

//**********************************************************************************************************************************

static int Money(const char* pszName, int iSize, void* pbuf)
{
	const char PROC_NAME[50] = "MsgMoney\0";
	BEGIN_READ( pbuf, iSize );
	playerItems.money = READ_SHORT();
	return (*MoneyOrg)(pszName, iSize, pbuf);
}

//**********************************************************************************************************************************

static int Health(const char* pszName, int iSize, void* pbuf)
{
	const char PROC_NAME[50] = "Health\0";
	BEGIN_READ( pbuf, iSize );
	playerItems.health = READ_BYTE();
	return (*HealthOrg)(pszName, iSize, pbuf);
}

//**********************************************************************************************************************************

static int MsgBattery(const char* pszName, int iSize, void* pbuf)
{
	const char PROC_NAME[50] = "MsgBattery\0";
	BEGIN_READ( pbuf, iSize );
	playerItems.armor = READ_BYTE();
	return (*BatteryOrg)(pszName, iSize, pbuf);
}

//**********************************************************************************************************************************

static int AmmoX(const char *pszName, int iSize, void *pbuf ) 
{
	const char PROC_NAME[50] = "AmmoX\0";
    int retval;
	int ID, Count;
	BEGIN_READ(pbuf, iSize);
	ID = READ_BYTE();
	Count = READ_BYTE();
	playerItems.ammo[ ((char*)pbuf)[0] ] = ((char*)pbuf)[1];
	retval = (*AmmoXOrg)(pszName,iSize,pbuf); 
    return retval;
}

//**********************************************************************************************************************************

static int Ammo (const char *pszName, int iSize, void *pbuf )
{
	const char PROC_NAME[50] = "Ammo\0";
	int retval;
	playerItems.ammo[ ((char*)pbuf)[0] ] += ((char*)pbuf)[1];
	retval = (*AmmoOrg)(pszName,iSize,pbuf);
	return retval;
}

//**********************************************************************************************************************************

static int ScoreInfo(const char* pszName, int iSize, void* pbuf)
{
	return (*ScoreInfoOrg)(pszName, iSize, pbuf);
}

//**********************************************************************************************************************************

static int SayText(const char* pszName, int iSize, void* pbuf)
{
	const char PROC_NAME[50] = "SayText\0";
	BEGIN_READ( pbuf, iSize);
	int  client = READ_BYTE(); // the client who spoke the message
	int  unknown_byte=0;
	unknown_byte = READ_BYTE(); //CS
	char*  text   = READ_STRING();

	return (*SayTextOrg)(pszName, iSize, pbuf);
}

//**********************************************************************************************************************************

int	HookUserMsg(char* szMsgName, pfnUserMsgHook pfn)
{
	int retval = gEngfuncs.pfnHookUserMsg(szMsgName, pfn);

	if(0){}

	else if(!strcmp(szMsgName, "ResetHUD"))
	{
			ResetHUDOrg = pfn;
			return gEngfuncs.pfnHookUserMsg (szMsgName, ResetHUD );
	}

	else if(!strcmp(szMsgName, "TeamInfo"))
	{
			TeamInfoOrg = pfn;
			return gEngfuncs.pfnHookUserMsg (szMsgName, TeamInfo );
	}

	else if(!strcmp(szMsgName, "CurWeapon"))
	{
			CurWeaponOrg = pfn;
			return gEngfuncs.pfnHookUserMsg (szMsgName, CurWeapon );
	}

	else if(!strcmp(szMsgName, "ScoreAttrib"))
	{
			ScoreAttribOrg = pfn;
			return gEngfuncs.pfnHookUserMsg (szMsgName, ScoreAttrib );
	}

	else if(!strcmp(szMsgName, "ScoreInfo"))
	{
			ScoreInfoOrg = pfn;
			return gEngfuncs.pfnHookUserMsg (szMsgName, ScoreInfo );
	}

	else if(!strcmp(szMsgName, "SetFOV"))
	{
			SetFOVOrg = pfn;
			return gEngfuncs.pfnHookUserMsg (szMsgName, SetFOV );
	}

	else if(!strcmp(szMsgName, "Battery"))
	{
			BatteryOrg = pfn;
			return gEngfuncs.pfnHookUserMsg (szMsgName, MsgBattery );
	}

	else if(!strcmp(szMsgName, "Money"))
	{
			MoneyOrg = pfn;
			return gEngfuncs.pfnHookUserMsg (szMsgName, Money );
	}

	else if(!strcmp(szMsgName, "Health"))
	{
			HealthOrg = pfn;
			return gEngfuncs.pfnHookUserMsg (szMsgName, Health );
	}

	else if(!strcmp(szMsgName, "WeaponList"))
	{
			WeaponListOrg = pfn;
			return gEngfuncs.pfnHookUserMsg (szMsgName, WeaponList );
	}

	else if (!strcmp(szMsgName,"AmmoX")) 
	{
		     AmmoXOrg = pfn;
		     return gEngfuncs.pfnHookUserMsg (szMsgName, AmmoX );
	}

	else if (!strcmp(szMsgName,"Ammo")) 
	{
		     AmmoOrg = pfn;
		     return gEngfuncs.pfnHookUserMsg (szMsgName, Ammo );
	}

	else if(!strcmp(szMsgName, "DeathMsg"))
	{
			DeathMsgOrg = pfn;
			return gEngfuncs.pfnHookUserMsg (szMsgName, DeathMsg );
	}

	return retval;
}

//**********************************************************************************************************************************
