/************************************************************************************************************************************
*
*
* 007 HOOK
* Code By: 007 + boy_scout
* msn: david_bs@live.com
* (c);2011
* www.etalking.com.ar
*
*
************************************************************************************************************************************/

#ifndef ENGINE_H
#define ENGINE_H

//**********************************************************************************************************************************

int SPR_Load( const char* szPicName );

int SPR_Frames( int hPic );


int SPR_Height( int hPic, int frame );


int SPR_Width( int hPic, int frame );

void SPR_Set( int hPic, int r, int g, int b );


void SPR_Draw( int frame, int x, int y, const wrect_t* prc );


void SPR_DrawHoles( int frame, int x, int y, const wrect_t* prc );


void SPR_DrawAdditive( int frame, int x, int y, const wrect_t* prc );


void SPR_EnableScissor( int x, int y, int width, int height );

void SPR_DisableScissor( void );

client_sprite_t* SPR_GetList( char* psz, int* piCount );


void FillRGBA( int x, int y, int width, int height, int r, int g, int b, int a );

int GetScreenInfo( SCREENINFO* pscrinfo );


void SetCrosshair( int hspr, wrect_t rc, int r, int g, int b );

struct cvar_s* RegisterVariable( char* szName, char* szValue, int flags );


float GetCvarFloat( char* szName );

char* GetCvarString( char* szName );


int AddCommand( char* cmd_name, void (*function)(void) );

/*
int HookUserMsg( char* szMsgName, pfnUserMsgHook pfn );
*/

int ServerCmd( char* szCmdString );


int ClientCmd( char* szCmdString );


void GetPlayerInfo( int ent_num, hud_player_info_t* pinfo );


void PlaySoundByName( char* szSound, float volume );


void PlaySoundByIndex( int iSound, float volume );

void AngleVectors( const float*  vecAngles, float*  forward, float*  right, float*  up );

client_textmessage_t* TextMessageGet( const char* pName );


int DrawCharacter( int x, int y, int number, int r, int g, int b );


int DrawConsoleString( int x, int y, char* string );

void DrawSetTextColor( float r, float g, float b );


void DrawConsoleStringLen(  const char* string, int* length, int* height );

void ConsolePrint( const char* string );


void CenterPrint( const char* string );


int GetWindowCenterX( void );


int GetWindowCenterY( void );


void GetViewAngles( float* v );


void SetViewAngles( float* v );


int GetMaxClients( void );

void Cvar_SetValue( char* cvar, float value );


int Cmd_Argc(void);


char* Cmd_Argv( int arg );


/*
void Con_Printf( char* fmt, ... );
*/

/*
void Con_DPrintf( char* fmt, ... );
*/

/*
void Con_NPrintf( int pos, char* fmt, ... );
*/

/*
void Con_NXPrintf( struct con_nprint_s* info, char* fmt,...);
*/

const char* PhysInfo_ValueForKey( const char* key );


const char* ServerInfo_ValueForKey( const char* key );


float GetClientMaxspeed( void );


int CheckParm( char* parm, char** ppnext );


void Key_Event( int key, int down );


void GetMousePosition( int* mx, int* my );


int IsNoClipping( void );

struct cl_entity_s* GetLocalPlayer( void );


struct cl_entity_s* GetViewModel( void );


struct cl_entity_s* GetEntityByIndex( int idx );


float GetClientTime( void );


void V_CalcShake( void );


void V_ApplyShake( float* origin, float* angles, float factor );


int PM_PointContents( float* point, int* truecontents );


int PM_WaterEntity( float* p );

struct pmtrace_s* PM_TraceLine( float* start, float* end, int flags, int usehull, int ignore_pe );


struct model_s* CL_LoadModel( const char* modelname, int* index );


int CL_CreateVisibleEntity( int type, struct cl_entity_s* ent );

const struct model_s*  GetSpritePointer( int hSprite );


void PlaySoundByNameAtLocation( char* szSound, float volume, float* origin );


unsigned short PrecacheEvent( int type, const char* psz );


/*
void PlaybackEvent( int flags, const struct edict_s* pInvoker, unsigned short eventindex, 
				    float delay, float* origin, float* angles, float fparam1, float fparam2, 
					int iparam1, int iparam2, int bparam1, int bparam2 );*/

void WeaponAnim( int iAnim, int body );

float RandomFloat( float flLow, float flHigh );

long RandomLong( long lLow, long lHigh );


/*
void HookEvent( char* name, void (* pfnEvent )( struct event_args_s* args ) );
*/

int Con_IsVisible();

const char* GetGameDirectory( void );


struct cvar_s* GetCvarPointer( const char* szName );


const char* Key_LookupBinding( const char* pBinding );


const char* GetLevelName( void );


void GetScreenFade( struct screenfade_s* fade );


void SetScreenFade( struct screenfade_s* fade );


void* VGui_GetPanel();


void VGui_ViewportPaintBackground(int extents[4]);

byte* COM_LoadFile( char* path, int usehunk, int* pLength );


char* COM_ParseFile( char* data, char* token );


void COM_FreeFile( void* buffer );


int IsSpectateOnly( void );

struct model_s* LoadMapSprite( const char* filename );


void COM_AddAppDirectoryToSearchPath( const char* pszBaseDir, const char* appName );


int COM_ExpandFilename( const char* fileName, char* nameOutBuffer, int nameOutBufferSize );

const char* PlayerInfo_ValueForKey( int playerNum, const char* key );


void PlayerInfo_SetValueForKey( const char* key, const char* value );

qboolean GetPlayerUniqueID(int iPlayer, char playerID[16]);

int GetTrackerIDForPlayer(int playerSlot);


int GetPlayerForTrackerID(int trackerID);


int ServerCmdUnreliable( char* szCmdString );

//**********************************************************************************************************************************

#endif

//**********************************************************************************************************************************

