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

static int sprset_hsprite = 0;
static int sprset_r, sprset_g, sprset_b;

//**********************************************************************************************************************************

int SPR_Load( const char* szPicName )//Needed
{
	HSPRITE spr = gEngfuncs.pfnSPR_Load (szPicName);
	add_sprite (spr, szPicName);
	return spr;
}

int SPR_Frames( int hPic )
{
	return gEngfuncs.pfnSPR_Frames(hPic);
}

int SPR_Height( int hPic, int frame )
{
	return gEngfuncs.pfnSPR_Height(hPic,frame);
}

int SPR_Width( int hPic, int frame )
{
	return gEngfuncs.pfnSPR_Width(hPic,frame);
}

void SPR_Set( int hPic, int r, int g, int b )//Needed
{
	gEngfuncs.pfnSPR_Set (hPic,r,g,b);
}

void SPR_Draw( int frame, int x, int y, const wrect_t* prc )//Needed
{
	if(cvar.rush) return;

	if(cvar.infobars>0)
	{
		int newhud_y = (screeninfo.iHeight-80);
		if(y < newhud_y)gEngfuncs.pfnSPR_Draw (frame, x, y, prc);
		else if((y > newhud_y))return; // don't draw
	}
	else
		gEngfuncs.pfnSPR_Draw (frame, x, y, prc);
}

void SPR_DrawHoles( int frame, int x, int y, const wrect_t* prc )//Needed
{
	if(cvar.rush) return;

	if(cvar.infobars>0)
	{
		int newhud_y = (screeninfo.iHeight-80);
		if(y < newhud_y)gEngfuncs.pfnSPR_DrawHoles (frame, x, y, prc);
		else if(y > newhud_y)return; // don't draw holes
	}
	else
		gEngfuncs.pfnSPR_DrawHoles (frame, x, y, prc);
}

void SPR_DrawAdditive( int frame, int x, int y, const wrect_t* prc )//Needed
{
	if(cvar.rush) return;

	if(cvar.infobars>0)
	{
		int newhud_y = (screeninfo.iHeight-80);
		if(y < newhud_y)gEngfuncs.pfnSPR_DrawAdditive(frame,x,y,prc);
		else if((y > newhud_y))return; // don't draw sprites
	}
	else
		gEngfuncs.pfnSPR_DrawAdditive(frame,x,y,prc);
}

void SPR_EnableScissor( int x, int y, int width, int height )//Needed
{
	if(cvar.rush) return;

	if(cvar.infobars>0)
	{
		int newhud_y = (screeninfo.iHeight-80);
		if(y < newhud_y)gEngfuncs.pfnSPR_EnableScissor( x, y, width, height );
		 else if(y > newhud_y)return; // don't enable scissoring
	}
	else
		gEngfuncs.pfnSPR_EnableScissor( x, y, width, height );
}

void SPR_DisableScissor( void )
{
	gEngfuncs.pfnSPR_DisableScissor();
}

client_sprite_t* SPR_GetList( char* psz, int* piCount )
{
	return gEngfuncs.pfnSPR_GetList(psz,piCount);
}

void FillRGBA( int x, int y, int width, int height, int r, int g, int b, int a )//Needed
{
	if(cvar.rush) return;

	if(cvar.infobars>0)
	{
		register ColorEntry* color = colorList.get(5);
		gEngfuncs.pfnFillRGBA(displayCenterX+2,screeninfo.iHeight-32,2,16,color->r,color->g,color->b,a);

		int newhud_x = (displayCenterX*2)-180;
		int newhud_y = (screeninfo.iHeight-100);
		if(x < newhud_x && (y < newhud_y))gEngfuncs.pfnFillRGBA(x,y,width,height,r,g,b,a);
		else if((x > newhud_x) && (y > newhud_y))return; // don't draw in that area
	}
	else 
		gEngfuncs.pfnFillRGBA(x,y,width,height,r,g,b,a);
}

int GetScreenInfo( SCREENINFO* pscrinfo )
{
	return gEngfuncs.pfnGetScreenInfo(pscrinfo);
}

void SetCrosshair( int hspr, wrect_t rc, int r, int g, int b )
{
	gEngfuncs.pfnSetCrosshair(hspr,rc,r,g,b);
}

struct cvar_s* RegisterVariable( char* szName, char* szValue, int flags )//Needed
{

	return gEngfuncs.pfnRegisterVariable(szName,szValue,flags);
}

float GetCvarFloat( char* szName )
{
	return gEngfuncs.pfnGetCvarFloat(szName);
}

char* GetCvarString( char* szName )
{
	return gEngfuncs.pfnGetCvarString(szName);
}

int AddCommand( char* cmd_name, void (*function)(void) )
{
	return gEngfuncs.pfnAddCommand(cmd_name,function);
}

/*
int HookUserMsg( char* szMsgName, pfnUserMsgHook pfn )//Needed
{
	return gEngfuncs.pfnHookUserMsg(szMsgName,pfn);
}*/

int ServerCmd( char* szCmdString )//Needed
{
	return gEngfuncs.pfnServerCmd(szCmdString);
}

int ClientCmd( char* szCmdString )//Needed
{
	return gEngfuncs.pfnClientCmd(szCmdString);
}

void GetPlayerInfo( int ent_num, hud_player_info_t* pinfo )
{
	gEngfuncs.pfnGetPlayerInfo(ent_num,pinfo);
}

void PlaySoundByName( char* szSound, float volume )
{
	gEngfuncs.pfnPlaySoundByName(szSound,volume);
}

void PlaySoundByIndex( int iSound, float volume )
{
	gEngfuncs.pfnPlaySoundByIndex(iSound,volume);
}

void AngleVectors( const float*  vecAngles, float*  forward, float*  right, float*  up )
{
	gEngfuncs.pfnAngleVectors(vecAngles,forward,right,up);
}

client_textmessage_t* TextMessageGet( const char* pName )
{
	return gEngfuncs.pfnTextMessageGet(pName);
}

int DrawCharacter( int x, int y, int number, int r, int g, int b )//Needed
{
	return gEngfuncs.pfnDrawCharacter(x,y,number,r,g,b);
}

int DrawConsoleString( int x, int y, char* string )
{
	return gEngfuncs.pfnDrawConsoleString(x,y,string);
}

void DrawSetTextColor( float r, float g, float b )
{
	gEngfuncs.pfnDrawSetTextColor(r,g,b);
}

void DrawConsoleStringLen(  const char* string, int* length, int* height )
{
	gEngfuncs.pfnDrawConsoleStringLen(string,length,height);
}

void ConsolePrint( const char* string )
{
	gEngfuncs.pfnConsolePrint(string);
}

void CenterPrint( const char* string )
{
	gEngfuncs.pfnCenterPrint(string);
}

int GetWindowCenterX( void )
{
	return gEngfuncs.GetWindowCenterX();
}

int GetWindowCenterY( void )
{
	return gEngfuncs.GetWindowCenterY();
}

void GetViewAngles( float* v )
{
	gEngfuncs.GetViewAngles(v);
}

void SetViewAngles( float* v )
{
	gEngfuncs.SetViewAngles(v);
}

int GetMaxClients( void )
{
	return gEngfuncs.GetMaxClients();
}

void Cvar_SetValue( char* cvar, float value )
{
	gEngfuncs.Cvar_SetValue(cvar,value);
}

int Cmd_Argc(void)
{
	return gEngfuncs.Cmd_Argc();
}

char* Cmd_Argv( int arg )
{
	return gEngfuncs.Cmd_Argv(arg);
}

/*
void Con_Printf( char* fmt, ... )
{
}*/

/*
void Con_DPrintf( char* fmt, ... )
{
}*/

/*
void Con_NPrintf( int pos, char* fmt, ... )
{
}*/

/*
void Con_NXPrintf( struct con_nprint_s* info, char* fmt,...)
{
}*/

const char* PhysInfo_ValueForKey( const char* key )
{
	return gEngfuncs.PhysInfo_ValueForKey(key);
}

const char* ServerInfo_ValueForKey( const char* key )
{
	return gEngfuncs.ServerInfo_ValueForKey(key);
}

float GetClientMaxspeed( void )
{
	return gEngfuncs.GetClientMaxspeed();
}

int CheckParm( char* parm, char** ppnext )
{
	return gEngfuncs.CheckParm(parm,ppnext);
}

void Key_Event( int key, int down )
{
	gEngfuncs.Key_Event(key,down);
}

void GetMousePosition( int* mx, int* my )
{
	gEngfuncs.GetMousePosition(mx,my);
}

int IsNoClipping( void )
{
	return gEngfuncs.IsNoClipping();
}

struct cl_entity_s* GetLocalPlayer( void )
{
	return gEngfuncs.GetLocalPlayer();
}

struct cl_entity_s* GetViewModel( void )
{
	return gEngfuncs.GetViewModel();
}

struct cl_entity_s* GetEntityByIndex( int idx )
{
	return gEngfuncs.GetEntityByIndex(idx);
}

float GetClientTime( void )
{
	return gEngfuncs.GetClientTime();
}

void V_CalcShake( void )//Needed
{
	gEngfuncs.V_CalcShake();
}

void V_ApplyShake( float* origin, float* angles, float factor )//Needed
{
	return;
}

int PM_PointContents( float* point, int* truecontents )
{
	return gEngfuncs.PM_PointContents(point,truecontents);
}

int PM_WaterEntity( float* p )
{
	return gEngfuncs.PM_WaterEntity(p);
}

struct pmtrace_s* PM_TraceLine( float* start, float* end, int flags, int usehull, int ignore_pe )
{
	return gEngfuncs.PM_TraceLine(start,end,flags,usehull,ignore_pe);
}

struct model_s* CL_LoadModel( const char* modelname, int* index )
{
	return gEngfuncs.CL_LoadModel(modelname,index);
}

int CL_CreateVisibleEntity( int type, struct cl_entity_s* ent )
{
	return gEngfuncs.CL_CreateVisibleEntity(type,ent);
}

const struct model_s*  GetSpritePointer( int hSprite )
{
	return gEngfuncs.GetSpritePointer(hSprite);
}

void PlaySoundByNameAtLocation( char* szSound, float volume, float* origin )
{
	gEngfuncs.pfnPlaySoundByNameAtLocation(szSound,volume,origin);
}

unsigned short PrecacheEvent( int type, const char* psz )
{
	return gEngfuncs.pfnPrecacheEvent(type,psz);
}

/*
void PlaybackEvent( int flags, const struct edict_s* pInvoker, unsigned short eventindex, 
				    float delay, float* origin, float* angles, float fparam1, float fparam2, 
					int iparam1, int iparam2, int bparam1, int bparam2 )
{
	gEngfuncs.pfnPlaybackEvent(flags,pInvoker,eventindex,delay,origin,angles,fparam1,fparam2,iparam1,iparam2,bparam1,bparam2);
}*/

void WeaponAnim( int iAnim, int body )
{
	gEngfuncs.pfnWeaponAnim(iAnim,body);
}

float RandomFloat( float flLow, float flHigh )//Needed
{
	return gEngfuncs.pfnRandomFloat(flLow,flHigh);
}

long RandomLong( long lLow, long lHigh )//Needed
{
	return gEngfuncs.pfnRandomLong(lLow,lHigh);
}

/*
void HookEvent( char* name, void (* pfnEvent )( struct event_args_s* args ) )//Needed
{
	gEngfuncs.pfnHookEvent(name,pfnEvent);
}*/

int Con_IsVisible()//Needed
{
	return gEngfuncs.Con_IsVisible();
}

const char* GetGameDirectory( void )
{
	return gEngfuncs.pfnGetGameDirectory();
}

struct cvar_s* GetCvarPointer( const char* szName )
{
	return gEngfuncs.pfnGetCvarPointer(szName);
}

const char* Key_LookupBinding( const char* pBinding )
{
	return gEngfuncs.Key_LookupBinding(pBinding);
}

const char* GetLevelName( void )
{
	return gEngfuncs.pfnGetLevelName();
}

void GetScreenFade( struct screenfade_s* fade )
{
	gEngfuncs.pfnGetScreenFade(fade);
}

void SetScreenFade( struct screenfade_s* fade )
{
	gEngfuncs.pfnSetScreenFade(fade);
}

void* VGui_GetPanel()
{
	return gEngfuncs.VGui_GetPanel();
}

void VGui_ViewportPaintBackground(int extents[4])
{
	gEngfuncs.VGui_ViewportPaintBackground(extents);
}

byte* COM_LoadFile( char* path, int usehunk, int* pLength )
{
	return gEngfuncs.COM_LoadFile(path,usehunk,pLength);
}

char* COM_ParseFile( char* data, char* token )
{
	return gEngfuncs.COM_ParseFile(data,token);
}

void COM_FreeFile( void* buffer )
{
	gEngfuncs.COM_FreeFile(buffer);
}

int IsSpectateOnly( void )//Needed
{
	return gEngfuncs.IsSpectateOnly();
}

struct model_s* LoadMapSprite( const char* filename )
{
	return gEngfuncs.LoadMapSprite(filename);
}

void COM_AddAppDirectoryToSearchPath( const char* pszBaseDir, const char* appName )
{
	gEngfuncs.COM_AddAppDirectoryToSearchPath(pszBaseDir,appName);
}

int COM_ExpandFilename( const char* fileName, char* nameOutBuffer, int nameOutBufferSize )
{
	return gEngfuncs.COM_ExpandFilename(fileName,nameOutBuffer,nameOutBufferSize);
}

const char* PlayerInfo_ValueForKey( int playerNum, const char* key )
{
	return gEngfuncs.PlayerInfo_ValueForKey(playerNum,key);
}

void PlayerInfo_SetValueForKey( const char* key, const char* value )
{
	gEngfuncs.PlayerInfo_SetValueForKey(key,value);
}

qboolean GetPlayerUniqueID(int iPlayer, char playerID[16])
{
	return gEngfuncs.GetPlayerUniqueID(iPlayer,playerID);
}

int GetTrackerIDForPlayer(int playerSlot)
{
	return gEngfuncs.GetTrackerIDForPlayer(playerSlot);
}

int GetPlayerForTrackerID(int trackerID)
{
	return gEngfuncs.GetPlayerForTrackerID(trackerID);
}

int ServerCmdUnreliable( char* szCmdString )//Needed
{
	return gEngfuncs.pfnServerCmdUnreliable(szCmdString);
}

//**********************************************************************************************************************************

