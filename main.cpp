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

#include "UNITS/pe.h"
#include "UNITS/ade32.hpp"
#include "UNITS/base64.h"
#include "UNITS/md5.h"
#include "UNITS/crc32.h"
#include "UNITS/pehook.h"
#include "UTILS/detour.h"
#include "UTILS/hidemodule.h"
#include "UTILS/utils.h"

#include "client.h"

//**********************************************************************************************************************************

typedef BOOL (WINAPI* QueryPerformanceCounterFunc)(LARGE_INTEGER*);
QueryPerformanceCounterFunc QueryPerformanceCounterPtr=NULL;
FARPROC (WINAPI *pGetProcAddress)(HMODULE hModule, LPCSTR lpProcName);
typedef FARPROC (WINAPI* GetProcAddressFunc)(HMODULE,LPCTSTR);
FARPROC WINAPI newGetProcAddress ( HMODULE hModule, LPCSTR lpProcName );

DWORD gpoffset;
DWORD gppt=(DWORD)&newGetProcAddress;

#ifndef QWORD
#define QWORD unsigned __int64
#endif

QWORD last_real=0;
QWORD last_fake=0;

BOOL WINAPI newQueryPerformanceCounter(LARGE_INTEGER* lp)
{
	BOOL  ret=(*QueryPerformanceCounterPtr)(lp);

	//////////////////////////////////////////////////////////////////////////

	QWORD new_real  = lp->QuadPart;
	double factor = (cvar.speed<0.01 ? 1:cvar.speed);
	DWORD diff_real = (DWORD)(new_real-last_real);
	DWORD diff_fake = (DWORD)(factor * double(diff_real));
	lp->QuadPart     = last_fake + diff_fake;
	
	last_fake += diff_fake;
	last_real += diff_real;

	/////////////////////////////////////////////////////////////////////

	if(!bEngineActive)
	{
		OnlyHook(lp, false);
	}

	if(!bClientActive)
	{
		ActivateClient();
	}

	return ret;
}

//**********************************************************************************************************************************

FARPROC WINAPI newGetProcAddress( HMODULE hModule, LPCSTR lpProcName )
{
	FARPROC nResult;

	nResult = GetProcAddress(hModule, lpProcName);
	if( HIWORD( lpProcName ) )
	{
		if( !lstrcmpi( lpProcName, "GetProcAddress" ) )
			return( ( FARPROC )&newGetProcAddress );
		else if(!strcmp(lpProcName,"QueryPerformanceCounter"))
        {
			QueryPerformanceCounterPtr = (QueryPerformanceCounterFunc)nResult;
			return (FARPROC)&newQueryPerformanceCounter;
        } else {
			void CheckForOpenGlHook(FARPROC* pProc,LPCTSTR lpProcName);
			CheckForOpenGlHook(&nResult, lpProcName);
		}
	}
	return nResult;
}

//**********************************************************************************************************************************

bool WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
	switch( fdwReason ) 
	{ 
		case DLL_PROCESS_ATTACH :
		{
			GetModuleFileName((HINSTANCE)hinstDLL,ogcdir,255);
		    char* pos = ogcdir+strlen(ogcdir);
		    while(pos>=ogcdir && *pos!='\\') --pos;
		    pos[1]=0;
		    PIMAGE_DOS_HEADER pDOSHeader = MakePtr<PIMAGE_DOS_HEADER>(hinstDLL); 
		    PIMAGE_NT_HEADERS pNTHeader = MakePtr<PIMAGE_NT_HEADERS>(pDOSHeader,pDOSHeader->e_lfanew);
		    HMODULE MainModule = GetModuleHandle(NULL);
		    ReRoute(MainModule, pNTHeader,&gppt,"Kernel32.dll","GetProcAddress",&gpoffset);
		    hm.HideModule((HMODULE)hinstDLL);
		}
		if( DLL_PROCESS_DETACH || DLL_THREAD_ATTACH || DLL_THREAD_DETACH )
		{
			break;
		}
	}

	return(true);
}

//**********************************************************************************************************************************
