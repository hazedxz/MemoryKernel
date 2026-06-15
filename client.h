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

#ifndef CLIENT_H
#define CLIENT_H

//**********************************************************************************************************************************

#define  WIN32_LEAN_AND_MEAN //Para acelerar el proceso de generación
#define _WIN32_WINNT 0x0500

#pragma warning (disable: 4410)
#pragma warning (disable: 4409)
#pragma warning (disable: 4700)
#pragma warning (disable: 4305)
#pragma warning (disable: 4800)
#pragma warning (disable: 4806)
#pragma warning (disable: 4723)

//**********************************************************************************************************************************

#include <windows.h>
#include <mmsystem.h>
#include <fstream>
#include <list>
#include <map>
#include <string>//.h
#include <time.h>
#include <vector>
#include <stdio.h>
#include <errno.h>
#include <string>
#include <tlhelp32.h>
#include <winnt.h>
#include <assert.h>
#include <iomanip>
#include <cstdarg>
#include <cstring>
#include <cstdio>
#include <iostream>

using namespace std;

//**********************************************************************************************************************************

//#include "SDK/engine/progdefs.h"
//#include "SDK/engine/eiface.h"
//#include "SDK/engine/edict.h"
#include "SDK/engine/wrect.h"
#include "SDK/engine/cl_dll.h"
#include "SDK/engine/cdll_int.h"
#include "SDK/engine/cdll_int.h"
//#include "SDK/engine/cl_dll.h"
#include "SDK/engine/const.h" // trace_t
#include "SDK/engine/entity_types.h"
#include "SDK/engine/pmtrace.h"
#include "SDK/engine/pm_defs.h"
#include "SDK/engine/pm_movevars.h"
#include "SDK/engine/r_efx.h"
#include "SDK/engine/studio.h"
#include "SDK/engine/studio_event.h"
#include "SDK/engine/triangleapi.h"
#include "SDK/engine/util_vector.h"
//#include "SDK/engine/wrect.h"
#include "SDK/common/com_model.h"
#include "SDK/common/event_api.h"
#include "SDK/common/net_api.h"
#include "SDK/common/ref_params.h"
#include "SDK/common/screenfade.h"
#include "SDK/misc/parsemsg.h"
#include "SDK/misc/r_studioint.h"
#include "SDK/misc/sprites.h"
//#include "SDK/engine/entity_state.h"
//#include "SDK/engine/cl_entity.h"
#include "SDK/engine/pm_materials.h"

//**********************************************************************************************************************************

#include "defs.h"
#include "cvar.h"
#include "timehandling.h"
#include "attack.h"
#include "autodirection.h"
#include "bind.h"
#include "client.h"
#include "color.h"
#include "console.h"
#include "drawing.h"
#include "engine.h"
#include "eventhook.h"
#include "gateways.h"
#include "gpatch.h"
#include "interpreter.h"
#include "mempatcher.h"
#include "menu.h"
#include "messagehook.h"
#include "miniradar.h"
#include "model.h"
#include "opengl.h"
#include "playeritems.h"
#include "recoil.h"
#include "soundhook.h"
#include "stringfinder.h"
#include "textures.h"
#include "trace.h"
#include "xorstr.h"
#include "players.h"
#include "autoroute.h"
#include "StudioModelRenderer.h"
#include "Aimbone.h"
#include "Strafe.h"
#include "wavspeed.h"
#include "StudioModelOffsets.h"
#include "gui/TableFont.h"
#include "gui/cube_hud.h"
#include "aimsilent.h"
#include "esp.h"
#include "spin.h"
#include "AttackHandling.h"
#include "cfg.h"
#include "calcscreen.h"
#include "functions.h"
#include "txt.h"
#include "weapon.h"

int HUD_Init(void);
void HUD_HudInit( void );
void HUD_HudVidInit( void );
void HUD_UpdateClientData( client_data_t* cd, float time );
void HUD_Frame( double time );
int HUD_Redraw( float a, int b );
void HUD_PlayerMove( struct playermove_s* ppmove, int server );
void HUD_PlayerMoveInit( struct playermove_s* ppmove );
void HUD_PlayerTextureType( char* name );
void CL_CreateMove( float frametime, struct usercmd_s* usercmd, int active );
void CL_IsThirdPerson();
void PreV_CalcRefdef( struct ref_params_s* pparams );
void PostV_CalcRefdef( struct ref_params_s* pparams );
void HUD_AddEntity( int type, struct cl_entity_s* ent, const char* modelname );
void HUD_CreateEntities( void );
void HUD_DrawNormalTriangles( void );
void HUD_DrawTransparentTriangles( void );
void HUD_StudioEvent( const struct mstudioevent_s* event, const struct cl_entity_s* entity );
void HUD_PostRunCmd( struct local_state_s* from, struct local_state_s* to, struct usercmd_s* usercmd, int runfuncs, 
				 double time, unsigned int random_seed );
void HUD_TxferLocalOverrides( struct entity_state_s* state, const struct clientdata_s* client );
void HUD_ProcessPlayerState( struct entity_state_s* dst, /*const*/ struct entity_state_s* src );
void HUD_TxferPredictionData ( struct entity_state_s* ps, 
							   const struct entity_state_s* pps, 
						       struct clientdata_s* pcd, 
						       const struct clientdata_s* ppcd, 
						       struct weapon_data_s* wd, 
						       const struct weapon_data_s* pwd );
void Demo_ReadBuffer( int size, unsigned char* buffer );
int HUD_ConnectionlessPacket( const struct netadr_s* net_from, 
							  const char* args, 
							  char* response_buffer, 
							  int* response_buffer_size );
int HUD_GetHullBounds( int hullnumber, float* mins, float* maxs );
void HUD_Key_Event( int eventcode, int keynum, const char* pszCurrentBinding );
void HUD_TempEntUpdate( double ft, double ct, double grav, struct tempent_s** ppFreeTE, struct tempent_s** ppActiveTE, 
					    int ( *addTEntity )( struct cl_entity_s* pEntity ), 
						void ( *playTESound )( struct tempent_s* pTemp, float damp ) );
struct cl_entity_s* HUD_GetUserEntity( int index );
void HUD_DirectorEvent(unsigned char command, unsigned int firstObject, unsigned int secondObject, unsigned int flags);

void HUD_GetStudioModelInterface(int version, struct r_studio_interface_s** ppinterface, struct engine_studio_api_s* pstudio);

//**********************************************************************************************************************************

extern struct cl_enginefuncs_s gEngfuncs;
extern cl_enginefuncs_s* pEngfuncs; 
extern engine_studio_api_t IEngineStudio;
extern engine_studio_api_t* pIEngineStudio;

//**********************************************************************************************************************************

#define MAX_VALUE(a,b,c) ( a>b? (a>c?a:(b>c?b:c)) : (b>c?b:c) )
#define ONCE_ONLY(a) static bool xdone=false; if(!xdone){ xdone=true; a; }
#define BOUND_VALUE(var,min,max) if((var)>(max)){(var)=(max);};if((var)<(min)){(var)=(min);}
#define VectorDistance(a,b)sqrt(POW((a)[0]-(b)[0])+POW((a)[1]-(b)[1])+POW((a)[2]-(b)[2]))
#define POW(x) ((x)*(x))
#define HSPRITE int
#define DegToRad(Angle)((PI/180.0)*Angle)
#define PI 3.14159265358979f
extern bool blinkPhase;
extern char  gHudMessage[256];
extern char  gHudMessage2[256];
extern char ogcdir [256];
extern int currentWeaponID;
extern float chams_render_r;
extern float chams_render_g;
extern float chams_render_b;

//**********************************************************************************************************************************

void ogc_exec(const char* filename);
char* gGetWeaponName( int weaponmodel );
bool isEnemy(int ax);
void optimization(void);
extern bool oglSubtractive;
void PlayerEsp();
void updateLocalPlayer();
inline std::string getOgcDirFile(const char* basename);
bool __fastcall CalcScreen(float* origin,float* vecScreen);
void gSetHudMessage(const char* message);

//**********************************************************************************************************************************

#ifndef CDLL_INT_H
typedef unsigned char 		byte;
typedef unsigned short 		word;
typedef struct
{
	char *name;
	short ping;
	byte thisplayer;
	byte spectator;
} hud_player_info_t;
#endif

//**********************************************************************************************************************************

enum{  MAX_VPLAYERS =36 };

enum { UPDATE_MISSING=0, UPDATE_ADDENT=1, UPDATE_SOUND_RADAR=2, UPDATE_UNKNOWN=3 };

#define GAITSEQUENCE_STAND 1
#define GAITSEQUENCE_DUCK 2
#define GAITSEQUENCE_WALK 3
#define GAITSEQUENCE_RUNNING 4
#define GAITSEQUENCE_DUCKMOVE 5
#define GAITSEQUENCE_JUMP 6

//**********************************************************************************************************************************

struct ScheduledCommand
{
	string cmd; 
	RunningStopTimer timer; 
};

struct spread_info
{
	unsigned int random_seed;
	int recoil;
	float gtime;
	float prevtime;
	float brokentime; // This is only supposed to be set to zero when you buy the sg550 or the g3sg1
						// not when you reload, switch weapons or pick up a weapon, this is do to the
						// cs bugs for these guns (valve fix your code please)
	float spreadvar;
	float recoiltime;
	bool firing;
	int WeaponState;
	int prcflags;
	float speed;
	float spread[3];
};

//**********************************************************************************************************************************

struct local_player_info
{
    local_player_info():team(0),sin_yaw(0),minus_cos_yaw(-1),inZoomMode(false),pmframeTime(0),
	infrozentime(false),iFOV(0),weaponspeed(0.0),iClip(0),speed(0),entindex(-11111),spectator(true),ent(0),alive(false)
	{}

	float fTrigRadius;
	float fTrigDiff;
	bool bBadWeapon;
	vec3_t vEye;
	int iIndex;
	struct cl_entity_s* ent;
	float punchangle[3];
	int entindex;
	bool alive;
	float viewAngles[3];
	int pmFlags; 
	int pmMoveType;
	int pmInDuck;
	int pmiUseHull;
	int pmhealth;
	float pmVelocity[3];
	float pmEyePos[3];
	float pmGroundSpeed;
	float pmAirAccelerate;
	float pmMaxSpeed;
	float pmfSpeed;
	float pmfVSpeed;
	float pmflFallSpeed;
	float pmflHeight;
	float pmflGroundAngle;
	float pmgravity;
	float pmmovevarsgravity;
	float pmfriction;
	float pmwaterlevel;
	float pmfAngleSpeed;
	Vector pmvVelocity;
	Vector pmvRight;
	Vector pmvForward;
	Vector pmvOrigin;
	Vector pmvAngles;
	Vector vt1,vt2;
	Vector StartJumpPos;
	Vector cmdViewAngles;
	Vector vNoSpreadAng;
	Vector vNoSpreadAngScr;
	Vector vNoRecoilAng;
	float flDuckTimeMax;
	float flJumpDist;
	float flJumpMessTime;
	bool bPlayerjb;
	bool bJumped;
	int iClip;
	int iFOV;
	bool inZoomMode;
	int team;
	float sin_yaw, minus_cos_yaw;
	spread_info spread;
	float weaponspeed;
	bool infrozentime;
	double pmframeTime;
	int prcflags;
	int currentWeaponID;
	int headshots;
	float speed;
	bool spectator;
	bool explosive;
	bool powergun;
	bool secondary;
	bool specialgun;
	int ammo;
	int fullammo;
	int fullclip;
};

//**********************************************************************************************************************************

class PlayerInfo 
{
protected:
	friend class VecPlayers;
	void init(int _entindex) 
	{ 
		team=0;
		iInfo=0;
		entinfo.name="\\missing-name\\";
		entinfo.ping=0;
		entinfo.thisplayer=0;
		entinfo.spectator=0;
		entinfo.packetloss=0;
		entinfo.model="missing-model";
		entinfo.topcolor=0;
		alive=false;
		entindex = _entindex;
		distance = 1000.0;
		visible = 0;
		frags=0;
		strcpy(m_weapon,"");
		damage=0;
		bGotHead = false;
		previous_alive_state = false;
	}

public:
	bool bVisible;
	float fDistance;
	float fFov;
	hud_player_info_t entinfo;
	int team;
	int iInfo;
	float distance;
	int visible;
	bool previous_alive_state;
	int alive_stats;
	int frags;
	vec3_t vHitbox[8];
	vec3_t vBone[54];
	vec3_t vOrigin;
	bool bGotHead;
	int damage;
	bool alive;
	int entindex;
	bool hasbomb;
	bool vip;

public:

	const char* getWeapon() { 
		return m_weapon; 
	}

	void setWeapon(const char* newname)
	{
		register int len = strlen(newname);
		if(len && len<30) { strcpy(m_weapon,newname); }
	}
	////////////////////////////////////////////////////

	const char* getName() const { 
		return entinfo.name; 
	}

	const char* getModel() const { 
		return entinfo.model; 
	}

	struct cl_entity_s* getEnt(){ 
		return gEngfuncs.GetEntityByIndex(entindex); 
	}
	
	void updateEntInfo(){
	    gEngfuncs.pfnGetPlayerInfo(entindex, &entinfo);
	    if(!entinfo.name ) { entinfo.name  = ""; }
	    if(!entinfo.model) { entinfo.model = "unknown model";    } 
    }
	
	float * origin(){ 
		return m_origin; 
	}

	bool isUpdatedAddEnt(){ 
		return m_lastUpdateType==UPDATE_ADDENT;  
	}

	void setAlive( bool state=true ){ 
		alive = state; 
	}

	void setDead(){ 
		alive = false; m_lastUpdateType=UPDATE_MISSING; 
	}

	bool getAlive(){ 
		return  alive; 
	}

	void updateClear(){ 
		m_lastUpdateType=UPDATE_MISSING; 
	}

	bool isUpdated(){ 
		return m_lastUpdateType!=UPDATE_MISSING; 
	}

	vec3_t SuspectNextOrigin(); //use it instead of a the function which normally returns the origins
	
	void updateAddEntity (vec3_t neworg);	

	float timeSinceLastUpdate(){ 
		return (float)(ClientTime::current-m_lastUpdateTime); 
	}

	void updateSoundRadar(const float* neworg);

	void Quick_Update( const float*const origin, const char*const sample );

private:

	float   m_origin[3];
	char    m_weapon[32];
	
	int     m_lastUpdateType;
	double  m_lastUpdateTime;
	DWORD dwUpdatetime;
	float flSoundpos[3];
	float flOffset[3];
	float flLastSoundpos[3];
	//*****//
public:
	PlayerInfo(){ 
		init(0); 
	}
};

//**********************************************************************************************************************************

class VecPlayers
{

private:
	PlayerInfo* players;

public:
	
	~VecPlayers(){ 
		delete[] players; 
	}

	VecPlayers(){ 
		players = new PlayerInfo[MAX_VPLAYERS];
		for(int i=0;i<MAX_VPLAYERS;i++){ 
			players[i].init(i); 
		}
	}

	inline PlayerInfo& operator [] (unsigned int i){
		if(i>=MAX_VPLAYERS) {return players[0];}
		else                {return players[i];}
	}
	
	inline unsigned int size(){ 
		return MAX_VPLAYERS; 
	}
};

//**********************************************************************************************************************************

extern VecPlayers vPlayers;
extern local_player_info me;
extern SCREENINFO screeninfo;
typedef list<ScheduledCommand> ScheduleList;
extern ScheduleList scheduleList;

//**********************************************************************************************************************************

#include "idhook.h"

//**********************************************************************************************************************************

#endif

//**********************************************************************************************************************************


