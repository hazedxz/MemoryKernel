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

struct cl_enginefuncs_s gEngfuncs;
cl_enginefuncs_s* pEngfuncs=0; 
engine_studio_api_t IEngineStudio;
engine_studio_api_t* pIEngineStudio=0;

//**********************************************************************************************************************************

local_player_info me;
VecPlayers vPlayers;
SCREENINFO screeninfo;
typedef list<ScheduledCommand> ScheduleList;
ScheduleList scheduleList;

//**********************************************************************************************************************************

bool __fastcall CalcScreen(float* origin,float* vecScreen)
{
	if(cvar.chase && me.alive)
	{
		int cResult = 0;
		if( gEngfuncs.GetLocalPlayer() != NULL )
			cResult = gEngfuncs.pTriAPI->WorldToScreen( origin, vecScreen );
		if( vecScreen[0] < 1 && vecScreen[1] < 1 && vecScreen[0] > -1 && vecScreen [1] > -1 && !cResult )
		{
			vecScreen[0] = vecScreen[0] * displayCenterX + displayCenterX;
			vecScreen[1] = -vecScreen[1] * displayCenterY + displayCenterY;
			return true;
		}
		return NULL;
	}
	else
	{
		return NewCalcScreen(origin, vecScreen);
	}
	return NULL;
}

//**********************************************************************************************************************************

int HUD_Init(void)
{
	return 1;
}

//**********************************************************************************************************************************

void updateLocalPlayer()
{
	me.ent = gEngfuncs.GetLocalPlayer();
	static cl_entity_s dummy;
	memset((char*)&dummy,0,sizeof(dummy));
	if(!me.ent){ me.ent = &dummy; }
	cl_entity_t *pLocal = GetLocalPlayer();
	me.iIndex = pLocal->index;
}

//**********************************************************************************************************************************

static bool bInitialize=false;

void Initialize()
{
	if (!bInitialize)
	{		
		screeninfo.iSize=sizeof(SCREENINFO);
		gEngfuncs.pfnGetScreenInfo(&screeninfo);
		displayCenterX = screeninfo.iWidth/2;
		displayCenterY = screeninfo.iHeight/2;

		cmd.exec(".bind 1 slot1;.bind 2 slot2;.bind 3 slot3");
		cmd.exec(".bind F5 snapshot");
		pEngfuncs->pfnClientCmd("bind space +jump");
		pEngfuncs->pfnClientCmd("bind enter +attack");
		pEngfuncs->pfnClientCmd("bot_stop 1");

		bInitialize=true;
	}
}

//**********************************************************************************************************************************

float nofreshon=1;
float nofreshoff=0 ;

void Norefresh()
{
	if(nofreshon && cvar.norefresh && cvar.rush && me.alive && !me.infrozentime)
	{
		cmd.exec ("#r_norefresh 1");
		nofreshon=0;
		nofreshoff=1;
	}
	if(nofreshoff && !cvar.rush || nofreshoff && !me.alive || nofreshoff && me.infrozentime)
	{
		cmd.exec ("#r_norefresh 0");
		nofreshon=1;
		nofreshoff=0;
	}
}

//**********************************************************************************************************************************

void sendScriptSignal(const char* name)
{
	char signal[32];
	sprintf(signal,"sig%s",name);
	cmd.exec(signal);
}

void sendscript()
{
	static bool previous_alive_state=false;
	if     (  previous_alive_state && !me.alive )  { sendScriptSignal("dead"); }
	else if( !previous_alive_state &&  me.alive )  { sendScriptSignal("live"); }
	previous_alive_state = me.alive;
}

//**********************************************************************************************************************************

bool bNewFrame2=false;
bool bNewFrame3=false;

int HUD_Redraw( float a, int b )
{
	int nResult=0;

	bNewFrame2=true;
	bNewFrame3=true;

	updateLocalPlayer();

	Initialize();

	gMenu.Init();

	gMenu.Draw();

	AttackHandling();

	hudDrawInfoTexts();

	Norefresh();

	Consoledraw();

	idhookdraw();

	sendscript();

	drawesp();

	kuvikbars();

	if(me.alive)
		g_Aimbot.Hud_Redraw();

	if(!cvar.rush && me.alive)
		Strafebot.InitHud();

	if(cvar.skeleton && !cvar.rush) 
		Aimbone.Draw();

	if(cvar.crosshair && cvar.nospread && me.alive && !cvar.rush) 
		DrawSpread();
		
	if(cvar.crosshair && cvar.norecoil && me.alive && !cvar.rush) 
		DrawRecoil();

	if(cvar.cheatmode == 2)
		autoway.DrawWay();
		
	if(cvar.radarpoints && cvar.cheatmode == 2)
		autoway.drawRadarsPoints();

	if(cvar.miniradar)
		drawRadarFrame();

	if(cvar.radar)
		drawRadarFrame2();
		
	return nResult;
}

//**********************************************************************************************************************************

double pisobre180 = (PI/180.0f);

void HUD_PlayerMove( struct playermove_s* ppmove, int server )
{
	ONCE_ONLY(InitTextureTypes(ppmove);)

	me.pmfriction = ppmove->friction;
	me.pmwaterlevel = ppmove->waterlevel;
	me.pmmovevarsgravity = ppmove->movevars->gravity;
	me.pmiUseHull = ppmove->usehull;
	me.pmgravity = ppmove->gravity;
	me.pmframeTime = ppmove->frametime;
	me.pmFlags = ppmove->flags;
	me.pmMoveType = ppmove->movetype;
	me.pmMaxSpeed = ppmove->maxspeed;
	me.pmAirAccelerate = ppmove->movevars->airaccelerate;
	me.pmfSpeed = sqrt(POW(ppmove->velocity[0]) + POW(ppmove->velocity[1]));
	me.pmGroundSpeed = sqrt(ppmove->velocity[0]*ppmove->velocity[0]+ppmove->velocity[1]*ppmove->velocity[1]);
	me.pmInDuck = ppmove->bInDuck;
	me.pmvVelocity = ppmove->velocity;
	me.pmflFallSpeed = ppmove->flFallVelocity;
	me.pmfAngleSpeed = (me.pmvAngles)[1]-(ppmove->angles)[1];while(me.pmfAngleSpeed<-180){me.pmfAngleSpeed+=360;}while(me.pmfAngleSpeed>180){me.pmfAngleSpeed-=360;}
	me.pmvAngles = ppmove->angles;
	VectorCopy(ppmove->velocity,me.pmVelocity);
	Vector vel = ppmove->velocity;
	me.pmfVSpeed = vel.Length();

	gEngfuncs.pEventAPI->EV_LocalPlayerViewheight(me.vEye);
	me.vEye = me.vEye + ppmove->origin;

	me.pmvOrigin = ppmove->origin;
	Vector vTemp1 = me.pmvOrigin;
	vTemp1[2] -= 8192;
	pmtrace_t *trace = PM_TraceLine(me.pmvOrigin, vTemp1, 1, ppmove->usehull, -1); 
	me.pmflHeight=abs(trace->endpos.z - me.pmvOrigin.z);

	if(me.pmflHeight <= 60) me.pmflGroundAngle=acos(trace->plane.normal[2])/PI*180; 
	else me.pmflGroundAngle = 0;

	Vector vTemp2=trace->endpos;
	pmtrace_t pTrace;
	gEngfuncs.pEventAPI->EV_SetTraceHull( ppmove->usehull );
	gEngfuncs.pEventAPI->EV_PlayerTrace( me.pmvOrigin, vTemp2, PM_GLASS_IGNORE | PM_STUDIO_BOX, me.iIndex, &pTrace );
	if( pTrace.fraction < 1.0f )
	{
		me.pmflHeight=abs(pTrace.endpos.z - me.pmvOrigin.z);
		int ind=gEngfuncs.pEventAPI->EV_IndexFromTrace(&pTrace);
		if(ind>0&&ind<33)
		{
			float dst=me.pmvOrigin.z-(me.pmiUseHull==0?32:18)-vPlayers[ind].vOrigin.z-me.pmflHeight;
			if(dst<30)
			{
				me.pmflHeight-=14.0;
			}
		}
	}
	else
	{
		if (me.pmflGroundAngle>1)
		{
			Vector vTemp2 = ppmove->origin;
			vTemp2[2] -= 8192;
			pmtrace_t *trace4 = PM_TraceLine(ppmove->origin, vTemp2, 1, 2, -1);
			me.pmflHeight = abs(ppmove->origin.z - trace4->endpos.z - (me.pmiUseHull == 1 ? 18.0f : 36.0f));
		}
		else
		{
			Vector vTemp5 = ppmove->origin;
			vTemp5[2] -= 8192;
			pmtrace_t *trace5 = PM_TraceLine(ppmove->origin, vTemp5, 1, ppmove->usehull, -1);
			me.pmflHeight = abs(trace5->endpos.z - ppmove->origin.z);
		}
	}

	gEngfuncs.pEventAPI->EV_LocalPlayerViewheight(me.pmEyePos);
	if (cvar.preshoot > 0){
		me.pmEyePos[0] += ppmove->origin[0] + ((ppmove->velocity[0] * cvar.preshoot) * ppmove->frametime);
		me.pmEyePos[1] += ppmove->origin[1] + ((ppmove->velocity[1] * cvar.preshoot) * ppmove->frametime);	
		me.pmEyePos[2] += ppmove->origin[2] + ((ppmove->velocity[2] * cvar.preshoot) * ppmove->frametime);
	}
	else
		VectorAdd(me.pmEyePos,ppmove->origin,me.pmEyePos);

	if(me.alive)
	{
       me.pmEyePos[0] += (cvar.forward_correction*cos(me.viewAngles[1]*pisobre180))+(cvar.right_correction*cos((me.viewAngles[1]+90.0)*pisobre180));
	   me.pmEyePos[1] += (cvar.forward_correction*sin(me.viewAngles[1]*pisobre180))+(cvar.right_correction*sin((me.viewAngles[1]+90.0)*pisobre180));
	   me.pmEyePos[2] += cvar.height_correction + cvar.distance_correction;
	}
	
	float yaw = ppmove->angles[1] * (pisobre180);
	me.sin_yaw       =  sin(yaw);
	me.minus_cos_yaw = -cos(yaw);
	VectorCopy(ppmove->angles,me.viewAngles);
}

//**********************************************************************************************************************************

void mealive()
{
	cl_entity_s *LocalEnt = GetLocalPlayer();
	me.alive = LocalEnt && !(LocalEnt->curstate.effects & EF_NODRAW) && LocalEnt->player && LocalEnt->curstate.movetype !=6 && LocalEnt->curstate.movetype != 0;
}

//**********************************************************************************************************************************

int currentWeaponID=0;

void Attack( struct usercmd_s* usercmd )
{
	if (usercmd->buttons&IN_ATTACK && me.alive || 
		usercmd->buttons&IN_ATTACK2 && currentWeaponID==WEAPON_KNIFE && me.alive ||
		!me.iClip && me.alive && cvar.rspeed && g_Aimbot.iTargetID!=0 && cvar.aspeed>1){
		if (me.secondary)
		{
			static bool flipFlop = true;
			if(flipFlop){ usercmd->buttons |= IN_ATTACK;    }
			else        { usercmd->buttons &= (~IN_ATTACK); }
			flipFlop = !flipFlop;
		}
		if (cvar.aspeed>1 && 
			currentWeaponID!=WEAPON_C4 && 
			currentWeaponID!=WEAPON_HE && 
			currentWeaponID!=WEAPON_FLASH && 
			currentWeaponID!=WEAPON_SMOKE)
		{
			cvar.speed = cvar.aspeed;
		}
	} 
	else 
	{
		if (cvar.aspeed>1)
		{ 
			cvar.speed = 1; 
		}
	}
}

//**********************************************************************************************************************************

bool bNewFrame=false;

void CL_CreateMove( float frametime, struct usercmd_s* usercmd, int active )
{
	bNewFrame=true; 

	mealive();	

	g_Aimbot.CL_CreateMove(usercmd);

	if(active)
		Speedbot.AdjustSpeed(1);
	if(active)
		Speedbot.AdjustSpeed(cvar.wavspeed);

	if(!cvar.rush && me.alive)
		Strafebot.InitCreatemove(frametime, usercmd);

	listidhookmenu();

	opengl_ClearBackground(); 

	Attack(usercmd);

	recoil(usercmd);

	nospread(usercmd);
	
	autoway.Autodir(usercmd);

	if(cvar.cheatmode == 2)
		autoway.CreateMove(usercmd);

	if(cvar.rush && cvar.kniferush && currentWeaponID!=WEAPON_KNIFE)
		cmd.exec("#slot3");

	if(cvar.rush && cvar.auto_br && currentWeaponID!=WEAPONLIST_KNIFE)
		autodirection.adjustMyDirection2(usercmd);

	if(!cvar.rush && cvar.cheatmode == 2 && cvar.auto_br && currentWeaponID!=WEAPONLIST_KNIFE)
		autodirection.adjustMyDirection1(usercmd);
		
	if((cvar.antiaimpitch || cvar.antiaimyaw && me.alive) && !me.explosive && me.alive)
		FixupAngleDifference(usercmd);
	
	updateLocalPlayer();
}
//**********************************************************************************************************************************

void PreV_CalcRefdef (struct ref_params_s *pparams)
{
	VectorCopy(pparams->punchangle,me.punchangle);
	VectorCopy(pparams->forward, me.pmvForward);
	VectorCopy(pparams->right, me.pmvRight);

	me.pmhealth = pparams->health;

	me.vNoRecoilAng[0] = cvar.recoil * pparams->punchangle[0];
	me.vNoRecoilAng[1] = cvar.recoil * pparams->punchangle[1];

	if(cvar.norecoil_visual)
			VectorClear(pparams->punchangle);
		
	if(cvar.norecoil_visible)
	{
		pparams->punchangle[0] -= me.vNoRecoilAng[0];
		pparams->punchangle[1] -= me.vNoRecoilAng[1];
	}

	if(cvar.nospread)
		if(cvar.nospread_visible && pparams->cmd->buttons & IN_ATTACK)
		{
			pparams->punchangle[0] += me.vNoSpreadAng[0];
			pparams->punchangle[1] += me.vNoSpreadAng[1];
		}

	if( pparams->nextView == 0 )
	{
		if(!me.alive) 
		{ 
			cvar.speed = 1; 
		}
		for(int ax=0;ax<vPlayers.size();ax++) 
		{
			vPlayers[ax].bGotHead = false;
		}
	}
}

//**********************************************************************************************************************************

void PostV_CalcRefdef (struct ref_params_s *pparams)
{
	me.ent = gEngfuncs.GetLocalPlayer();
	if(me.ent && me.ent->curstate.solid)
	{
		float yaw;
		yaw = pparams->viewangles[1]*(pisobre180);
		mainViewAngles_SinYaw = sin(yaw);
		mainViewAngles_CosYaw = cos(yaw);
	}
	if( pparams->nextView == 0 )
	{

		VectorCopy(pparams->viewangles,mainViewAngles);
		VectorCopy(pparams->vieworg,mainViewOrigin);
		float yaw = pparams->viewangles[1]*(pisobre180);
		mainViewAngles_SinYaw = sin(yaw);
		mainViewAngles_CosYaw = cos(yaw);
		if(cvar.chaseoffs)
		{
			vec3_t vecEnd, up, right, forward, EntViewOrg;
			gEngfuncs.pfnAngleVectors (mainViewAngles, forward, right, up);
			mainViewOrigin[0] += cvar.chaseoffs*forward[0];
			mainViewOrigin[1] += cvar.chaseoffs*forward[1];
			mainViewOrigin[2] -= cvar.chaseoffs*forward[2];
		}
	}
}

//**********************************************************************************************************************************

void ActivatePlayer(struct cl_entity_s *ent)
{
	int px = ent->index;

	if(ent->curstate.solid) { vPlayers[px].setAlive();}

	if(ent == me.ent) 
	{ 
		vPlayers[px].distance = 100000.0;
		vPlayers[px].visible  = 0;
		vPlayers[px].SuspectNextOrigin();
		return;
	}
	if( vPlayers[px].getAlive() )
	{
		vPlayers[px].updateAddEntity(ent->origin);
		playerCalcExtraData(px,ent);
	}
}

//**********************************************************************************************************************************

extern int AddEntResult;

void HUD_AddEntity( int type, struct cl_entity_s* ent, const char* modelname )
{
	AddEntResult = 1;

	if(0){/*do nothing*/}
	else if(ent->player)
	{
		ActivatePlayer(ent);

		cl_entity_s* pLocal=pEngfuncs->GetLocalPlayer();
		if(!me.alive)
		{
			if( pLocal!=NULL && pLocal->curstate.iuser1 == 4 && 
				pLocal->curstate.iuser2 == ent->index)
			{
				AddEntResult = 0; //dont draw spec bug when dead
			}
		}
		
		if(!cvar.rush && cvar.barrel)
		{
			if(cvar.espteam || isEnemy(ent->index))
			{
				ColorEntry *pClr = PlayerColor(ent->index);
				vec3_t vecBegin,vecEnd,up,right,forward;
				VectorCopy(ent->origin,vecBegin);
				if(ent->curstate.usehull)
					vecBegin[2]+=12;
				else
					vecBegin[2]+=17;
				gEngfuncs.pfnAngleVectors(ent->angles,forward,right,up);
				forward[2]=-forward[2];
				vecBegin[0]+=forward[0]*10;
				vecBegin[1]+=forward[1]*10;
				vecBegin[2]+=forward[2]*10;
				vecEnd=vecBegin+forward*999;
				DrawLine(vecBegin,vecEnd,pClr->r,pClr->g,pClr->b,0.001f);
			}
		}
	}

	if (bNewFrame && cvar.cheatmode == 2)
	{
		autoway.DrawWay();
		bNewFrame=false;
	}
}

//**********************************************************************************************************************************

int lastWeaponID=0;

void HUD_PostRunCmd( struct local_state_s *from, struct local_state_s *to, struct usercmd_s *usercmd, int runfuncs, double time, unsigned int random_seed )
{
	int Id;
	if (runfuncs)
	{
		me.spread.random_seed = random_seed;
		me.spread.gtime = time;
		me.spread.prcflags = to->client.flags;
		me.speed=to->client.velocity.Length();
		Id = to->client.m_iId;
		if (Id >= 0 && Id < MAX_WEAPONS)
			me.spread.WeaponState = to->weapondata[Id].m_iWeaponState;
		if (!(usercmd->buttons & (IN_ATTACK | IN_ATTACK2)))
		{
			if (me.spread.firing)
			{
				me.spread.firing = false;

				if (me.spread.recoil > 15)
					me.spread.recoil = 15;

				me.spread.recoiltime = time + 0.4f;
			}

			if (currentWeaponID >= WEAPON_USP && currentWeaponID <= WEAPON_FIVE7)
			{
				me.spread.recoil = 0;
			}
			else if (me.spread.recoil > 0)
			{
				if (me.spread.recoiltime <= time)
				{
					me.spread.recoiltime = me.spread.recoiltime + 0.0225f;
					me.spread.recoil--;
				}
			}
		}
		if (Id >= 0 && Id < MAX_WEAPONS && to->weapondata[Id].m_fInReload)
		{
			me.spread.recoil = 0;
			me.spread.prevtime = 0;
			DefaultSpreadVar(Id);
			me.spread.recoiltime = time;
			me.spread.firing = false;
		}
		if (lastWeaponID != currentWeaponID)
		{
			lastWeaponID = currentWeaponID;

			me.spread.recoil = 0;
			me.spread.prevtime = 0;
			DefaultSpreadVar(Id);
			me.spread.recoiltime = time;
			me.spread.firing = true;

			if (cvar.aim_enable && me.alive)
			{
				char signal[256];
				sprintf( signal ,"new-%s;txt |[ %s ]|",gGetWeaponName(me.ent->curstate.weaponmodel),gGetWeaponName(me.ent->curstate.weaponmodel) );
				cmd.exec( signal );
			}
			
			if(cvar.norecoil && me.alive)
			{
				char signal[256];
				sprintf(signal,"rec_%s",gGetWeaponName(me.ent->curstate.weaponmodel));
				cmd.exec(signal);
			}
		}
	}
}

//**********************************************************************************************************************************

extern int KeyEventResult;

void HUD_Key_Event( int eventcode, int keynum, const char* pszCurrentBinding )
{
	if(gMenu.Active && eventcode)
	{
		KeyEventResult=gMenu.KeyEvent(keynum);

		if (!KeyEventResult) 
			return;
	}

	if (keynum >= 239 && keynum <= 244){
		switch(keynum){
			case 239:
			keyBindManager.notifyMouseEvent("mwheeldown", (eventcode == 1));
			break;
			case 240:
			keyBindManager.notifyMouseEvent("mwheelup", (eventcode == 1));
			break;
			case 241: 
			keyBindManager.notifyMouseEvent("mouse1", (eventcode == 1)); 
			break; 
			case 242: 
			keyBindManager.notifyMouseEvent("mouse2", (eventcode == 1)); 
			break; 
			case 243: 
			keyBindManager.notifyMouseEvent("mouse3", (eventcode == 1)); 
			break; 
			case 244: 
			keyBindManager.notifyMouseEvent("mouse4", (eventcode == 1)); 
			break; 
			case 245: 
			keyBindManager.notifyMouseEvent("mouse5", (eventcode == 1));
			break;
		}
	}

	else
	{
		if (eventcode)
			keyBindManager.notifyKeyEvent(keynum, true, false);
		else
			keyBindManager.notifyKeyEvent(keynum, false, false);
	}

	int retval = (keyBindManager.keyBlocked(keynum, (eventcode) ? true : false)) ? 0 : 1;

	if( gPlayerActive() && (keynum >= 239 && keynum <= 245))
		retval = 0;

	KeyEventResult = retval;
}

//**********************************************************************************************************************************

void HUD_TempEntUpdate( double ft, double ct, double grav, struct tempent_s** ppFreeTE, struct tempent_s** ppActiveTE, int ( *addTEntity )( struct cl_entity_s* pEntity ), void ( *playTESound )( struct tempent_s* pTemp, float damp ) )
{
	//
}

//**********************************************************************************************************************************

bool blinkPhase = false;
StopTimer blinkTimer;

void HUD_UpdateClientData( client_data_t* cd, float time )
{
	if(bNewFrame3)// con la misma frecuencia que redraw
	{
		//--------------------------------------------------------

		ClientTime::reportMapTime(GetClientTime());

		static bool previous_frozen_state=false;
		if(me.speed > 10.0 && (me.pmFlags & FL_ONGROUND))
		   me.infrozentime = false;
		if(previous_frozen_state && !me.infrozentime)
			cmd.exec("buystuff");
		previous_frozen_state = me.infrozentime;
		//----------------------------------------------------------------
		if(cvar.infobars && me.alive)
		{
			delSel3=HEALTH();
			delSel4=ARMOR();
		}
		//----------------------------------------------------------------
		for( ScheduleList::iterator pos = scheduleList.begin();
			pos != scheduleList.end();
			++pos)
			{
			if( (*pos).timer.expired() )
			{
				cmd.exec( const_cast<char*>((*pos).cmd.c_str()) );
				scheduleList.erase(pos);
				break;
			}	
		}

		if(blinkTimer.expired())
		{
			blinkPhase = !blinkPhase;
			if(blinkPhase){ blinkTimer.countdown(0.2f); }
			else          { blinkTimer.countdown(0.1f); }
		}

		bNewFrame3=false;
	}
}

//**********************************************************************************************************************************

extern bool round_start;

void HUD_Frame( double time )
{
	if(bNewFrame2)// con la misma frecuencia que redraw
	{

		if(round_start)
		{
			AtRoundStart();
			round_start=false;
		}
		//----------------------------------------------------------------
		if(cvar.chase == 1 && me.alive)
		{	
			cmd.exec("chase_active hide 1;r_drawviewmodel hide 0");
			cvar.chaseoffs = -100.0;
		}
		else 
		{
			cmd.exec("chase_active hide 0;r_drawviewmodel hide 1");
			cvar.chaseoffs = 0.0;
		}
		//////////////////////////////////////////////////////////
		if(me.alive)
		{
			me.explosive = (currentWeaponID==WEAPON_C4||currentWeaponID==WEAPON_FLASH||currentWeaponID==WEAPON_SMOKE||
					  currentWeaponID==WEAPON_HE);
			me.powergun = (currentWeaponID==WEAPON_AWP||currentWeaponID==WEAPON_PARA||currentWeaponID==WEAPON_AK||
						 currentWeaponID==WEAPON_SCOUT||currentWeaponID==WEAPON_G3SG1);
			me.secondary = (currentWeaponID==WEAPON_USP||currentWeaponID==WEAPON_DEAGLE||currentWeaponID==WEAPON_GLOCK||
						  currentWeaponID==WEAPON_P228||currentWeaponID==WEAPON_ELITE||currentWeaponID==WEAPON_FIVE7);
			me.specialgun = (currentWeaponID==WEAPON_KNIFE ||currentWeaponID== WEAPON_M3);

			me.bBadWeapon = (currentWeaponID==WEAPON_C4)||(currentWeaponID==WEAPON_FLASH)||(currentWeaponID==WEAPON_HE)||(currentWeaponID==WEAPON_SMOKE);
		}
		////////////////////////////////////////////////////
		if(cvar.infobars&&me.alive)
		{
			delSel2=CLIP();
			delSel5=MONEY();
			delSel1=AMMO();
		}
		//////////////////////////////////////////////
		if (cvar.noflash)
		{
			static screenfade_t sf = { 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0 }; 
			gEngfuncs.pfnSetScreenFade( &sf ); 
		}
		/////////////////////////////////
		bNewFrame2=false;
	}
}

//**********************************************************************************************************************************


