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

StudioModelRenderer_t*	pStudioModelRenderer;
StudioModelRenderer_t	gStudioModelRenderer;

DWORD* dwClientPtr=0;

static bool bFirstTime = true;
static bool bStudioFirst = true;

//**********************************************************************************************************************************

typedef int ( *INITIALIZE_FUNCTION )				         ( struct cl_enginefuncs_s*, int );
typedef void( *HUD_INIT_FUNCTION )					         ( void );
typedef int ( *HUD_VIDINIT_FUNCTION )				         ( void );
typedef int ( *HUD_REDRAW_FUNCTION )				         ( float, int );
typedef int ( *HUD_UPDATECLIENTDATA_FUNCTION )			     ( struct client_data_s*, float );
typedef void( *HUD_RESET_FUNCTION )					         ( void );
typedef void( *HUD_CLIENTMOVE_FUNCTION )				     ( struct playermove_s* ppmove, qboolean server );
typedef void( *HUD_CLIENTMOVEINIT_FUNCTION )			     ( struct playermove_s* ppmove );
typedef char( *HUD_TEXTURETYPE_FUNCTION )				     ( char* name );
typedef void( *HUD_IN_ACTIVATEMOUSE_FUNCTION )			     ( void );
typedef void( *HUD_IN_DEACTIVATEMOUSE_FUNCTION )			 ( void );
typedef void( *HUD_IN_MOUSEEVENT_FUNCTION )				     ( int mstate );
typedef void( *HUD_IN_CLEARSTATES_FUNCTION )		     	 ( void );
typedef void( *HUD_IN_ACCUMULATE_FUNCTION )			  	     ( void );
typedef void( *HUD_CL_CREATEMOVE_FUNCTION )				     ( float frametime, struct usercmd_s *cmd, int active );
typedef int	( *HUD_CL_ISTHIRDPERSON_FUNCTION )			     ( void );
typedef void( *HUD_CL_GETCAMERAOFFSETS_FUNCTION)			 ( float* offs );
typedef struct kbutton_s *( *HUD_KB_FIND_FUNCTION )			 ( const char* name );
typedef void( *HUD_CAMTHINK_FUNCTION )				         ( void );
typedef void( *HUD_V_CALCREFDEF_FUNCTION )			   	     ( struct ref_params_s* pparams );
typedef int	( *HUD_ADDENTITY_FUNCTION )				         ( int type, struct cl_entity_s* ent, const char* modelname );
typedef void( *HUD_CREATEENTITIES_FUNCTION )			     ( void );
typedef void( *HUD_DRAWNORMALTRIS_FUNCTION )			     ( void );
typedef void( *HUD_DRAWTRANSTRIS_FUNCTION )				     ( void );
typedef void( *HUD_STUDIOEVENT_FUNCTION )				     ( const struct mstudioevent_s* event, const struct cl_entity_s* entity );
typedef void( *HUD_POSTRUNCMD_FUNCTION )				     ( struct local_state_s* from, struct local_state_s* to, struct usercmd_s* cmd, int runfuncs, double time, unsigned int random_seed );
typedef void( *HUD_SHUTDOWN_FUNCTION )				         ( void );
typedef void( *HUD_TXFERLOCALOVERRIDES_FUNCTION )			 ( struct entity_state_s *state, const struct clientdata_s* client );
typedef void( *HUD_PROCESSPLAYERSTATE_FUNCTION )			 ( struct entity_state_s *dst, const struct entity_state_s* src );	
typedef void( *HUD_TXFERPREDICTIONDATA_FUNCTION )		 	 ( struct entity_state_s *ps, const struct entity_state_s* pps, struct clientdata_s* pcd, const struct clientdata_s* ppcd, struct weapon_data_s* wd, const struct weapon_data_s* pwd );
typedef void( *HUD_DEMOREAD_FUNCTION )				         ( int size, unsigned char *buffer );
typedef int	( *HUD_CONNECTIONLESS_FUNCTION )			     ( const struct netadr_s* net_from, const char* args, char* response_buffer, int* response_buffer_size );
typedef int	( *HUD_GETHULLBOUNDS_FUNCTION )				     ( int hullnumber, float* mins, float* maxs );
typedef void( *HUD_FRAME_FUNCTION )					         ( double );
typedef int	( *HUD_KEY_EVENT_FUNCTION )				         ( int eventcode, int keynum, const char* pszCurrentBinding );
typedef void( *HUD_TEMPENTUPDATE_FUNCTION )				     ( double frametime, double client_time, double cl_gravity, struct tempent_s** ppTempEntFree, struct tempent_s** ppTempEntActive, 	int ( *Callback_AddVisibleEntity )( struct cl_entity_s* pEntity ),	void ( *Callback_TempEntPlaySound )( struct tempent_s* pTemp, float damp ) );
typedef struct cl_entity_s*( *HUD_GETUSERENTITY_FUNCTION )	 ( int index );
typedef void( *HUD_DIRECTORMESSAGE_FUNCTION )			     ( int iSize, void* pbuf );
typedef int	( *HUD_STUDIO_INTERFACE_FUNCTION )			     ( int version, struct r_studio_interface_s** ppinterface, struct engine_studio_api_s* pstudio );
typedef void( *HUD_CHATINPUTPOSITION_FUNCTION )			     ( int* x, int* y );
typedef int	( *HUD_GETPLAYERTEAM_FUNCTION )				     ( int iplayer );
typedef void( *CLIENTFACTORY )					             ( );
void( *pHUD_PlayerMoveInit )( struct playermove_s * );

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void HUD_PlayerMoveInit( struct playermove_s* ppmove )
{
	InitTextureTypes(ppmove);

	pHUD_PlayerMoveInit( ppmove );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct _CLIENT_
{
	INITIALIZE_FUNCTION						Initialize;
	HUD_INIT_FUNCTION						HUD_Init;
	HUD_VIDINIT_FUNCTION					HUD_VidInit;
	HUD_REDRAW_FUNCTION						HUD_Redraw;
	HUD_UPDATECLIENTDATA_FUNCTION			HUD_UpdateClientData;
	HUD_RESET_FUNCTION						HUD_Reset;
	HUD_CLIENTMOVE_FUNCTION					HUD_PlayerMove;
	HUD_CLIENTMOVEINIT_FUNCTION				HUD_PlayerMoveInit;
	HUD_TEXTURETYPE_FUNCTION				HUD_PlayerMoveTexture;
	HUD_IN_ACTIVATEMOUSE_FUNCTION			IN_ActivateMouse;
	HUD_IN_DEACTIVATEMOUSE_FUNCTION			IN_DeactivateMouse;
	HUD_IN_MOUSEEVENT_FUNCTION				IN_MouseEvent;
	HUD_IN_CLEARSTATES_FUNCTION				IN_ClearStates;
	HUD_IN_ACCUMULATE_FUNCTION				IN_Accumulate;
	HUD_CL_CREATEMOVE_FUNCTION				CL_CreateMove;
	HUD_CL_ISTHIRDPERSON_FUNCTION			CL_IsThirdPerson;
	HUD_CL_GETCAMERAOFFSETS_FUNCTION		CL_CameraOffset;
	HUD_KB_FIND_FUNCTION					KB_Find;
	HUD_CAMTHINK_FUNCTION					CAM_Think;
	HUD_V_CALCREFDEF_FUNCTION				V_CalcRefdef;
	HUD_ADDENTITY_FUNCTION					HUD_AddEntity;
	HUD_CREATEENTITIES_FUNCTION				HUD_CreateEntities;
	HUD_DRAWNORMALTRIS_FUNCTION				HUD_DrawNormalTriangles;
	HUD_DRAWTRANSTRIS_FUNCTION				HUD_DrawTransparentTriangles;
	HUD_STUDIOEVENT_FUNCTION				HUD_StudioEvent;
	HUD_POSTRUNCMD_FUNCTION					HUD_PostRunCmd;
	HUD_SHUTDOWN_FUNCTION					HUD_Shutdown;
	HUD_TXFERLOCALOVERRIDES_FUNCTION		HUD_TxferLocalOverrides;
	HUD_PROCESSPLAYERSTATE_FUNCTION			HUD_ProcessPlayerState;
	HUD_TXFERPREDICTIONDATA_FUNCTION		HUD_TxferPredictionData;
	HUD_DEMOREAD_FUNCTION					Demo_ReadBuffer;
	HUD_CONNECTIONLESS_FUNCTION				HUD_ConnectionlessPacket;
	HUD_GETHULLBOUNDS_FUNCTION				HUD_GetHullBounds;
	HUD_FRAME_FUNCTION						HUD_Frame;
	HUD_KEY_EVENT_FUNCTION					HUD_Key_Event;
	HUD_TEMPENTUPDATE_FUNCTION				HUD_TempEntUpdate;
	HUD_GETUSERENTITY_FUNCTION				HUD_GetUserEntity;
	HUD_DIRECTORMESSAGE_FUNCTION			HUD_DirectorMessage;
	HUD_STUDIO_INTERFACE_FUNCTION			HUD_GetStudioModelInterface;
	HUD_CHATINPUTPOSITION_FUNCTION			HUD_ChatInputPosition;
	HUD_GETPLAYERTEAM_FUNCTION				HUD_GetPlayerTeam;
	CLIENTFACTORY							ClientFactory;
} CLIENT, *PCLIENT;

//**********************************************************************************************************************************

CLIENT gClient				= { NULL };

BOOL bClientActive			= FALSE;
BOOL bEngineActive			= FALSE;

DWORD retaddress;

//**********************************************************************************************************************************

__declspec(naked) void Gateway2_HUD_Init(void)
{
	__asm call HUD_Init;
	__asm jmp retaddress;
}
DWORD Init=(DWORD)&Gateway2_HUD_Init;
__declspec(naked) void Gateway1_HUD_Init(void)
{
	__asm push esi;
    __asm mov esi,dword ptr ss:[esp+0x08];
    __asm mov retaddress,esi;
    __asm push Init
    __asm pop esi;
    __asm mov dword ptr ss:[esp+0x08],esi;
    __asm pop esi;
    __asm ret;
}

//**********************************************************************************************************************************

__declspec(naked) void Gateway2_HUD_PlayerMove(void)
{
	__asm call HUD_PlayerMove
	__asm jmp retaddress
}
DWORD PlayerMove=(DWORD)&Gateway2_HUD_PlayerMove;
__declspec(naked) void Gateway1_HUD_PlayerMove(void)
{
	__asm push esi
	__asm mov esi,dword ptr ss:[esp+0x10]
	__asm mov retaddress,esi
	__asm push PlayerMove
	__asm pop esi
	__asm mov dword ptr ss:[esp+0x10],esi
	__asm pop esi
	__asm ret
}

//**********************************************************************************************************************************

int iUpdateResult;
DWORD dwRetAddr;
__declspec( naked ) void Gateway2_HUD_UpdateClientData(void)
{
    _asm mov  [iUpdateResult],eax
    _asm call HUD_UpdateClientData
    _asm mov  eax,[iUpdateResult]
    _asm jmp  [dwRetAddr]
}
DWORD dwUpdateClD = (DWORD)&Gateway2_HUD_UpdateClientData;
__declspec( naked ) void Gateway1_HUD_UpdateClientData(void)
{
    _asm push esi
    _asm mov  esi,[esp+0x10]
    _asm mov  [dwRetAddr],esi
    _asm push [dwUpdateClD]
    _asm pop  esi
    _asm mov  [esp+0x10],esi
    _asm pop  esi
    _asm retn
}

//**********************************************************************************************************************************

__declspec(naked) void Gateway2_HUD_Redraw(void)
{
	__asm call HUD_Redraw
	__asm jmp retaddress
}
DWORD Redraw=(DWORD)&Gateway2_HUD_Redraw;
__declspec(naked) void Gateway1_HUD_Redraw(void)
{
	__asm push esi
	__asm mov esi, dword ptr ss:[esp+0x10]
	__asm mov retaddress, esi
	__asm push Redraw
	__asm pop esi
	__asm mov dword ptr ss:[esp+0x10], esi
	__asm pop esi
	__asm ret
}

//**********************************************************************************************************************************

__declspec(naked) void Gateway2_CL_CreateMove(void)
{
	__asm call CL_CreateMove
	__asm jmp retaddress
}
DWORD CreateMove=(DWORD)&Gateway2_CL_CreateMove;
__declspec(naked) void Gateway1_CL_CreateMove(void)
{
	__asm push esi
	__asm mov esi,dword ptr ss:[esp+0x28]
	__asm mov retaddress,esi
	__asm push CreateMove
	__asm pop esi
	__asm mov dword ptr ss:[esp+0x28],esi
	__asm pop esi
	__asm ret
}

//**********************************************************************************************************************************

__declspec(naked) void Gateway2_V_CalcRefdef(void)
{
	__asm call PostV_CalcRefdef;
	__asm jmp retaddress;
}
DWORD CalcRef=(DWORD)&Gateway2_V_CalcRefdef;
__declspec(naked) void Gateway1_V_CalcRefdef(void)
{
	__asm push esi
	__asm mov esi,dword ptr ss:[esp+0x10]
	__asm push esi
	__asm call PreV_CalcRefdef
	__asm add esp,4
	__asm mov esi,dword ptr ss:[esp+0x0c]
	__asm mov retaddress,esi
	__asm push CalcRef
	__asm pop esi
	__asm mov dword ptr ss:[esp+0x0c],esi;
	__asm pop esi
	__asm ret
}

//**********************************************************************************************************************************

int AddEntResult;
__declspec(naked) void Gateway2_HUD_AddEntity(void)
{
	__asm mov AddEntResult, eax
	__asm call HUD_AddEntity
	__asm mov eax, AddEntResult
	__asm jmp retaddress
}
DWORD AddEnt=(DWORD)&Gateway2_HUD_AddEntity;
__declspec(naked) void Gateway1_HUD_AddEntity(void)
{
    //__asm int 3
	__asm push esi
	__asm mov esi,dword ptr ss:[esp+0x14]
	__asm mov retaddress,esi
	__asm push AddEnt
	__asm pop esi
	__asm mov dword ptr ss:[esp+0x14],esi
	__asm pop esi
	__asm ret
}

//**********************************************************************************************************************************

__declspec(naked) void Gateway2_HUD_PostRunCmd(void)
{
    __asm nop;
    __asm nop; 
    __asm nop;
    __asm call HUD_PostRunCmd;
    __asm nop;
    __asm nop;
    __asm nop;
    __asm jmp retaddress;
}
DWORD PostRunCmd=(DWORD)&Gateway2_HUD_PostRunCmd;
__declspec(naked) void Gateway1_HUD_PostRunCmd(void)
{
    __asm nop;
    __asm nop;
    __asm nop;
    __asm push esi;
    __asm mov esi,dword ptr ss:[esp+0x38];
    __asm mov retaddress,esi;
    __asm push PostRunCmd
    __asm pop esi;
    __asm mov dword ptr ss:[esp+0x38],esi;
    __asm pop esi;
    __asm ret;
}

//**********************************************************************************************************************************

int KeyEventResult=0;
__declspec( naked )void Gateway2_HUD_Key_Event( void )
{
	__asm mov KeyEventResult, eax;
	__asm call HUD_Key_Event;
	__asm mov eax, KeyEventResult;
	__asm jmp retaddress;
}
DWORD KeyEvent = (DWORD)&Gateway2_HUD_Key_Event;
__declspec( naked )void Gateway1_HUD_Key_Event( void )
{
	__asm push esi;
	__asm mov esi,dword ptr ss:[esp+0x14];
	__asm mov retaddress,esi;
	__asm push KeyEvent
	__asm pop esi;
	__asm mov dword ptr ss:[esp+0x14],esi;
	__asm pop esi;
	__asm ret;
}

//**********************************************************************************************************************************

__declspec(naked) void Gateway2_HUD_TempEntUpdate(void)
{	
	__asm nop;
	__asm nop;
	__asm nop;
	__asm call HUD_TempEntUpdate;
	__asm nop;
	__asm nop;
	__asm nop;
	__asm jmp retaddress;
}
DWORD TempEntUpdate=(DWORD)&Gateway2_HUD_TempEntUpdate;
__declspec(naked) void Gateway1_HUD_TempEntUpdate(void)
{
	__asm nop;
	__asm nop;
	__asm nop;
	__asm push esi;
	__asm mov esi,dword ptr ss:[esp+0x100];
	__asm mov retaddress,esi;
	__asm push TempEntUpdate;
	__asm pop esi;
	__asm mov dword ptr ss:[esp+0x100],esi;
	__asm pop esi;
	__asm ret;
}

//**********************************************************************************************************************************

__declspec(naked) void Gateway2_HUD_Frame(void)
{
	__asm call HUD_Frame
	__asm jmp retaddress
}
DWORD Frame=(DWORD)&Gateway2_HUD_Frame;
__declspec(naked) void Gateway1_HUD_Frame(void)
{
	__asm push esi
	__asm mov esi,dword ptr ss:[esp+0x0c]
	__asm mov retaddress,esi
	__asm push Frame
	__asm pop esi
	__asm mov dword ptr ss:[esp+0x0c],esi
	__asm pop esi
	__asm ret
}

//**********************************************************************************************************************************

BOOL ActivateClient( void )
{

	if ( !IsBadReadPtr( ( LPCVOID )dwClientPtr, sizeof DWORD ) )
	{
		if ( *( ( DWORD* )dwClientPtr ) != NULL )
		{
			DWORD dwClientRealPtr;
			__asm push eax;
			__asm push edx;
			__asm xor eax, eax;
			__asm xor edx, edx;
			__asm mov edx, dwClientPtr;
			__asm mov eax, [edx];
			__asm mov dwClientRealPtr, eax;	
			__asm pop edx;
			__asm pop eax;
			
			memcpy( &gClient, ( LPVOID )dwClientRealPtr, sizeof CLIENT );
			
			gClient.HUD_Redraw =					(HUD_REDRAW_FUNCTION)			   &Gateway1_HUD_Redraw;
			gClient.HUD_PlayerMove =				(HUD_CLIENTMOVE_FUNCTION)		   &Gateway1_HUD_PlayerMove;
			gClient.HUD_UpdateClientData =			(HUD_UPDATECLIENTDATA_FUNCTION)    &Gateway1_HUD_UpdateClientData;
			gClient.CL_CreateMove =					(HUD_CL_CREATEMOVE_FUNCTION)	   &Gateway1_CL_CreateMove;
			gClient.V_CalcRefdef =					(HUD_V_CALCREFDEF_FUNCTION)	       &Gateway1_V_CalcRefdef;
			gClient.HUD_AddEntity =					(HUD_ADDENTITY_FUNCTION)		   &Gateway1_HUD_AddEntity;
			gClient.HUD_PostRunCmd =				(HUD_POSTRUNCMD_FUNCTION)		   &Gateway1_HUD_PostRunCmd;
			gClient.HUD_Key_Event =					(HUD_KEY_EVENT_FUNCTION)		   &Gateway1_HUD_Key_Event;
			gClient.HUD_Frame =                     (HUD_FRAME_FUNCTION)               &Gateway1_HUD_Frame;
			
			pStudioModelRenderer = (StudioModelRenderer_t*)Studiooffsets.OffsetCStudioModelRenderer();
			memcpy(&gStudioModelRenderer, pStudioModelRenderer, sizeof(StudioModelRenderer_t));
			
			HookRendererFunction(StudioRenderModel);
			HookRendererFunction(StudioRenderFinal);
			HookRendererFunction(StudioDrawPlayer);

			SpeedPtr = (DWORD)Speedbot.SpeedHackPtr();

			DWORD dwClientNewPtr = ( DWORD ) &gClient;
			__asm push eax;
			__asm push edx;
			__asm xor eax, eax;
			__asm xor edx, edx;
			__asm mov edx, dwClientPtr;
			__asm mov eax, dwClientNewPtr;
			__asm mov [edx], eax;
			__asm pop edx;
			__asm pop eax;

			bClientActive = TRUE;
			return TRUE;
		} 
		else
		{
			return FALSE;
		}
	} 
	else 
	{
		return FALSE;
	}

	return TRUE;
}

//**********************************************************************************************************************************

DWORD FindPattern(char* pattern, int len, DWORD dwStart, DWORD dwLen) 
{ 
    char* m = (char *)dwStart; 
    for(; (DWORD)m < (dwStart + dwLen); m++) 
		if(!memcmp(m, pattern, len)) 
			return (DWORD)m; 
		return NULL; 
}

//**********************************************************************************************************************************

bool bDataCompare1(const BYTE* pData, const BYTE* bMask, const char* szMask)
{
	for(;*szMask;++szMask,++pData,++bMask){
		if(*szMask=='x' && *pData!=*bMask){
			return false;
		}
	}
	return (*szMask) == NULL;
}

//**********************************************************************************************************************************

bool bDataCompare2(const BYTE* pData, const BYTE* bMask, int iLen)
{
	int i;
	for( i =0; i < iLen; i++ ){
		if (pData[i] == bMask[i]){
			continue;
		}
		else
		{
			if (bMask[i] == 0x00 && bMask[i + 1] == 0x00 && bMask[i + 2] == 0x00 && bMask[i + 3] == 0x00 ){
				i += 3;
				continue;
			}
			else
				return false;
		}
	}
	return (i >= iLen);
}

//**********************************************************************************************************************************

DWORD dwFindPattern1(DWORD dwAddress,DWORD dwLen,BYTE* bMask,char* szMask)
{
	for(DWORD i=0; i < dwLen; i++){
		if(bDataCompare1((BYTE*)(dwAddress+i ),bMask,szMask)){
			return (DWORD)(dwAddress+i);
		}
	}
	return 0;
}

//**********************************************************************************************************************************

DWORD dwFindPattern2(DWORD dwAddress, DWORD dwSize, BYTE* pbMask, int iLen)
{
	for(DWORD i = NULL; i < dwSize; i++){
		if(bDataCompare2((BYTE*)(dwAddress + i), pbMask, iLen)){
			return (DWORD)(dwAddress + i);
		}
	}
	return 0;
}

//**********************************************************************************************************************************

bool bDataCompare(const BYTE* pData, const BYTE* bMask, const char* szMask) 
{ 
    for(;*szMask;++szMask,++pData,++bMask) 
        if(*szMask=='x' && *pData!=*bMask ) 
            return false; 
    return (*szMask) == NULL; 
} 

//**********************************************************************************************************************************

DWORD dwFindPattern(DWORD dwAddress,DWORD dwLen,BYTE *bMask,char * szMask) 
{ 
    for(DWORD i=0; i < dwLen; i++) 
        if( bDataCompare( (BYTE*)( dwAddress+i ),bMask,szMask) ) 
            return (DWORD)(dwAddress+i); 
      
    return 0; 
}

//**********************************************************************************************************************************

bool autooffsets()
{
	if (pEngfuncs==0){
		int a;
		for(a=0x01D00000;a<0x01D0FFFF;a++){ 
			if(*(PBYTE)(a) == 0x68 && *(PBYTE)(a + 0x05) == 0xE8 && 
			   *(PBYTE)(a + 0x0A) == 0x6A && *(PBYTE)(a + 0x0B) == 0x07 && 
			   *(PBYTE)(a + 0x0C) == 0x68 && *(PBYTE)(a + 0x11) == 0xFF && 
			   *(PBYTE)(a + 0x12) == 0x15 && *(PBYTE)(a + 0x17) == 0x68) 
			{ 
			   pEngfuncs = (cl_enginefunc_t*)*(DWORD*)(a+0x0D);  
			   break; 
			} 
		}
	}
			
	if (pIEngineStudio==0){
		int b; 
		for(b=0x01D00000;b<0x01D0FFFF;b++){ 
			if(*(PBYTE)(b) == 0x68 && *(PBYTE)(b + 0x05) == 0x68 && 
			   *(PBYTE)(b + 0x0A) == 0x6A && *(PBYTE)(b + 0x0B) == 0x01 && 
			   *(PBYTE)(b + 0x0C) == 0xFF && *(PBYTE)(b + 0x0D) == 0xD0 && 
			   *(PBYTE)(b + 0x0E) == 0x83 && *(PBYTE)(b + 0x27) == 0xC3) 
			{ 
			   pIEngineStudio = (engine_studio_api_s*)*(DWORD*)(b+0x01);  
			   break; 
			} 
		}
	}
	
	if( ((DWORD*)pEngfuncs <= (DWORD*)(0x01EB52B8)))
	{
		dwClientPtr = (DWORD*)0x01A179D0;
	}
	else
	{
		dwClientPtr = (DWORD*)0x01A179F0;
	}

	if(pEngfuncs!=0 && pIEngineStudio!=0 && dwClientPtr!=0)return true;

	return false;
}

//**********************************************************************************************************************************

void CB_KeyManager_Exec(const string& commandlist)
{
	cmd.exec( const_cast<char*>( commandlist.c_str() ) );
}

//**********************************************************************************************************************************

void CB_KeyManager_ConType(char ch)
{
	gConsole.key(ch);
}

//**********************************************************************************************************************************

void StudioDrawPoints( void );
void StudioEntityLight( struct alight_s *plight );

void OnlyHook(LARGE_INTEGER* lp, bool force)
{
	//====================================================

	while(!autooffsets());
	while(!Speedbot.Initialize());
	//====================================================

	if( pEngfuncs->pfnHookUserMsg && bFirstTime )
	{
		memcpy( &gEngfuncs, pEngfuncs, sizeof( cl_enginefunc_t ) );
	  	if( pIEngineStudio->GetModelByIndex && bStudioFirst )
		{
		    memcpy(&IEngineStudio, pIEngineStudio, sizeof(IEngineStudio));
			pIEngineStudio->StudioDrawPoints=&StudioDrawPoints;
			pIEngineStudio->StudioEntityLight=&StudioEntityLight;
		    bStudioFirst = false;
	    }

		//==== engine hooks
		pEngfuncs->pfnHookUserMsg = &HookUserMsg;
		pEngfuncs->pfnHookEvent = &HookEvent;
		pEngfuncs->pfnFillRGBA = &FillRGBA;
		pEngfuncs->pfnSPR_DrawAdditive = &SPR_DrawAdditive;
        pEngfuncs->pfnSPR_Set = &SPR_Set;
		pEngfuncs->pfnDrawCharacter = &DrawCharacter;
        pEngfuncs->pfnSPR_Draw = &SPR_Draw;
        pEngfuncs->pfnSPR_DrawHoles = &SPR_DrawHoles;
		pEngfuncs->pfnSPR_EnableScissor = &SPR_EnableScissor;
		pEngfuncs->V_ApplyShake = &V_ApplyShake;
		pEngfuncs->PlayerInfo_ValueForKey = &PlayerInfo_ValueForKey;
		pEngfuncs->PlayerInfo_SetValueForKey = &PlayerInfo_SetValueForKey;
		pEngfuncs->pfnClientCmd = &ClientCmd;


		//////////////////////////////////////////////////////////////////////////////

		keyBindManager.init();
		keyBindManager.CallBack_Execute = CB_KeyManager_Exec;
		keyBindManager.CallBack_ConType = CB_KeyManager_ConType;
		keyBindManager.con_visible = pEngfuncs->Con_IsVisible;

		Init_Command_Interpreter();

		Compras();

		cmd.exec("loadcvar cvar.bin");
		ogc_exec("main");

		me.spread.prcflags = 0;
		me.spread.random_seed = 0;
		me.spread.gtime = 0;
		me.spread.prevtime = 0;
		me.spread.brokentime = 0;
		me.spread.spreadvar = 0;
		me.spread.firing = false;
		me.alive = false;

		detour_S_DynamicSound();

		bEngineActive = TRUE;
		bFirstTime = false;
	}
}

//**********************************************************************************************************************************

