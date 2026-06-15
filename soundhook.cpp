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
#include "players.h"

//**********************************************************************************************************************************

#define BOUND_INTEGER(var,min,max) if((var)>(max)){(var)=(max);};if((var)<(min)){(var)=(min);}

//**********************************************************************************************************************************

void OGC_ConsoleScrollUp(const char* message)
{
	gConsole.echo(message);
}

//**********************************************************************************************************************************

void OGCmessage(const char* fmt, ... )
{
	va_list va_alist;
	char buf[256];
	
	va_start (va_alist, fmt);
	_vsnprintf (buf, sizeof(buf), fmt, va_alist);
	va_end (va_alist);
	
	OGC_ConsoleScrollUp(buf); // echo + scroll up:
}

//**********************************************************************************************************************************

DWORD dwFindPattern(DWORD dwAddress,DWORD dwLen,BYTE *bMask,char * szMask);

//**********************************************************************************************************************************

// ====== sound data
static ColorEntry dummycolor;

class SoundMarker
{
public:
	SoundMarker() : color(&dummycolor),priority(0) {} // "snd_default"
	float origin[3];
	char description[16]; //16
	int team;
	int entindex;
	StopTimer timer;
	ColorEntry* color;
	int priority; // 0/1/2
};

typedef vector<SoundMarker> SoundMarkerVector;
SoundMarkerVector vecSoundMarker(65);
int soundMarkerCurrentIndex = 0;

GenericPatch soundPatch;
static DWORD sound_reloc_addr1=0;

//**********************************************************************************************************************************

void PlayerInfo::updateAddEntity (vec3_t neworg)
{ 
	if(alive)
	{
		m_lastUpdateType=UPDATE_ADDENT; 
		m_lastUpdateTime=ClientTime::current; 
		VectorCopy(neworg,m_origin); 
	} 
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PlayerInfo::updateSoundRadar(const float* neworg)   
{ 		
	if(alive)
	{
		if( m_lastUpdateType!=UPDATE_ADDENT || timeSinceLastUpdate()>0.3 ) // dont mess with hud_addentity updates
		{
			m_lastUpdateType=UPDATE_SOUND_RADAR;  
			m_lastUpdateTime=ClientTime::current; 
			VectorCopy(neworg,m_origin); 
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vec3_t PlayerInfo::SuspectNextOrigin()
{
	float absFraction = (float) ClientTime::current - dwUpdatetime;
	vec3_t pflOutOrigin;
	pflOutOrigin[0] = flSoundpos[0] + (flOffset[0] * absFraction);
	pflOutOrigin[1] = flSoundpos[1] + (flOffset[1] * absFraction);
	pflOutOrigin[2] = flSoundpos[2] + (flOffset[2] * absFraction); 

	if (timeSinceLastUpdate()>0.4) updateClear();

	return pflOutOrigin;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PlayerInfo::Quick_Update( const float*const origin, const char*const sample )// call this func in the soundhook 
{		
	float absFraction = (float)(ClientTime::current - dwUpdatetime);
	dwUpdatetime = (DWORD)ClientTime::current;

	flOffset[0] = (origin[0] - flSoundpos[0]) / absFraction;
	flOffset[1] = (origin[1] - flSoundpos[1]) / absFraction;
	flOffset[2] = (origin[2] - flSoundpos[2]) / absFraction;	

	VectorCopy(flLastSoundpos,flSoundpos);
	VectorCopy(origin,flSoundpos);

	updateSoundRadar( origin );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float GetPseudoDistance(const float* const pos1, const float* const pos2)
{
	return fabs(pos1[0]-pos2[0])+fabs(pos1[1]-pos2[1])+fabs(pos1[2]-pos2[2]);
}

//**********************************************************************************************************************************

bool passesSoundFilter(const float* const origin,const int bx)
{
	if( GetPseudoDistance(origin,me.pmEyePos)<cvar.soundtol){ return false; }
	int ax;
	{
		for (ax=0;ax<MAX_VPLAYERS;ax++)
		{
			{
				if( GetPseudoDistance(vPlayers[ax].getEnt()->origin, origin)<cvar.soundtol )
				{
					return false;
				}
			}
		}
	}
	return true;
}


//**********************************************************************************************************************************

inline void strcpy_x(char* dest, const char* pos)
{
	do{ 
		while( *pos>='0' && *pos<='9' )  ++pos; // ignore numbers
		
		if(*pos=='.')				{*dest=0;break; } // cut off ".wav"
		*dest=*pos;
		++dest;
		++pos; 
	}
	while(*pos);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void strcpy_x2(char* dest, const char* pos)
{
	do{ 
		if(*pos=='.'||*pos=='-'||*pos=='_') {*dest=0;break; } // cut off ".wav"
		*dest=*pos;
		++dest;
		++pos; 
	}
	while(*pos);
}

//**********************************************************************************************************************************

void PreS_DynamicSound(const DWORD a,const DWORD b,const DWORD c,const char*const sample,const float*const origin,DWORD f,const DWORD g,const DWORD h)
{
	BOUND_VALUE(soundMarkerCurrentIndex,0,64);
	SoundMarker& ref = vecSoundMarker[soundMarkerCurrentIndex];

	////////////////////////////////////////////////////////////////////

	string theMessage;
	if (b>0 && b<=36)
	{
		vPlayers[b].entindex = b;
		vPlayers[b].updateEntInfo();
		theMessage = vPlayers[b].getName();
		ref.team = vPlayers[b].team;
	}
	else return;

	if(sample[0]=='p' && sample[3]=='y' && sample[6]=='/')
	{
		if(!passesSoundFilter(origin,b)) return;
		const char* pos = sample+7;
		if(pos[0]=='p' && pos[2]=='_')
		{
			if(pos[3]=='s' && pos[4]=='h' && pos[5]=='e' && pos[6]=='l' )  return;   
			pos+=3;
			ref.color = colorList.get(6+ref.team);
			ref.priority = 0;
		} 
		strcpy_x(ref.description,pos);
	}

	else
	if( sample[0]=='w' && sample[1]=='e' && sample[7]=='/' ) // weapons/ric1.wav
	{
		const char* pos = sample+8;
		if(   (pos[0]=='r' && pos[1]=='i')    // ricxxx
			||(pos[0]=='b' && pos[1]=='u') )  // bullet-hit...
		{
			return;
		}
		if(!passesSoundFilter(origin,b)) return;
		ref.priority = 1;
		ref.color = colorList.get(ref.team+ref.team);
		strcpy_x2(ref.description,pos);
		for(char *pos1=ref.description;*pos1;++pos1){ *pos1 = toupper(*pos1); }
	}
	else  
	{
		return;
	}

	if(!cvar.soundesp) 
	{ 
		return; 
	}
	if(cvar.soundesp && cvar.esptype)
	{
		vPlayers[b].Quick_Update( origin, sample );
		return;
	}

	VectorCopy( origin, ref.origin );

	////////////////////////////////////////////////////////////////////

	ref.timer.countdown( cvar.soundtime );

	////////////////////////////////////////////////////

	// advance to next sound marker
	++soundMarkerCurrentIndex;
	if(soundMarkerCurrentIndex>=12){ soundMarkerCurrentIndex=0;}
}
__declspec(naked) void JumpGate_DynamicSound()
{
    __asm
	{
		call PreS_DynamicSound;  
        sub esp,0x48;
        mov  eax, soundPatch.patchloc;
        add  eax, soundPatch.patchsize;
        push eax;
        mov  eax,sound_reloc_addr1;
        mov  eax,[eax];
        ret;
	}
}

//**********************************************************************************************************************************

bool detour_S_DynamicSound()
{
    static bool applied = false;
    if( applied ){ return true;}
	applied = true;
	DWORD SOUND_ADDR = dwFindPattern(0x1D90000,0x30000,(BYTE*)"\x83\xEC\x48\xA1\x00\x00\x00\x00","xxxx???");
    BYTE* offs = (BYTE*)SOUND_ADDR;
	BYTE* sig   = (BYTE*)"\x83\xEC\x48\xA1\x00\x00\x00\x00";
	char* mask  = "xxxx????";

	if(!soundPatch.find_location(offs,sig,mask))
	{
//	   MessageBox(0,/*not sound location*/XorStr<0x5A,19,0x6A8CAF12>("\x34\x34\x28\x7D\x2D\x30\x15\x0F\x06\x43\x08\x0A\x05\x06\x1C\x00\x05\x05"+0x6A8CAF12).s,
//		   /*not sound location*/XorStr<0x5A,19,0x6A8CAF12>("\x34\x34\x28\x7D\x2D\x30\x15\x0F\x06\x43\x08\x0A\x05\x06\x1C\x00\x05\x05"+0x6A8CAF12).s,0);
       return false;
	}
	soundPatch.patchdata[0]=0x68;
	*(DWORD*)(soundPatch.patchdata+1) = (DWORD)JumpGate_DynamicSound;
	soundPatch.patchdata[5]=0xC3;
	soundPatch.patchdata[6]=0x90;
	soundPatch.patchdata[7]=0x90;
	sound_reloc_addr1 = *(DWORD*)(soundPatch.backup+4);

	soundPatch.apply();

	gConsole.setcolortag( 'r',255, 0, 0);
	gConsole.setcolortag( 'w',255,255,255);

	OGCmessage("&w The first hack with a cubical interface :-D");
	OGCmessage("&r Yes awesome");
	OGCmessage("&w Code By:  BS");
	OGCmessage("&r Thank you David BS");
	OGCmessage("");
	OGCmessage("&w Recode By:  &reVOL");
	OGCmessage("&r-=[eVOL]=- &w> all");


    return true;
}

//**********************************************************************************************************************************
