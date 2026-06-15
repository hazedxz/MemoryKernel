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
#include "./UNITS/ade32.hpp" // replace ade with xde 1.01

//**********************************************************************************************************************************

inline static bool datacompare(const BYTE* data1, const BYTE* data2, const char* mask)
{
	for(;*mask;++mask,++data1,++data2)
	{
		if(*mask=='x' && *data1!=*data2 ) return false;
	}
	return (*mask)==0;
}

//**********************************************************************************************************************************

bool GenericPatch::find_location(BYTE* hint,const BYTE* sig_bytes,const char* sig_mask)
{
	assert(sig_mask&&strlen(sig_mask)&&sig_bytes&&hint);
	assert(!patchloc&&!patchsize);
	DWORD len = strlen(sig_mask);
	assert(len<PATCH_MAX);
	if( !datacompare(hint,sig_bytes,sig_mask) ) { return false; }
	patchloc  = hint;
	patchsize = len;
	assert(patchsize<PATCH_MAX);
	memcpy(backup ,patchloc,patchsize);
	memcpy(patchdata,patchloc,patchsize);

	return true;
}

//**********************************************************************************************************************************

void GenericPatch::set_location (BYTE* loc,int length)
{
	assert(!patchloc&&!patchsize);
	assert(loc&&length);
	assert(length<PATCH_MAX);
	patchloc  = loc;
	patchsize =length;
	memcpy(backup ,patchloc,patchsize);
	memcpy(patchdata,patchloc,patchsize);
}

//**********************************************************************************************************************************

void GenericPatch::apply()
{
	assert(patchloc&&patchsize);
	assert(!memcmp(patchdata+patchsize,backup+patchsize,PATCH_MAX-patchsize));
	Protect(patchloc,patchsize);
	memcpy(patchloc,patchdata,patchsize);
	Protect(patchloc);
}

//**********************************************************************************************************************************

void GenericPatch::restore()
{
	assert(patchloc&&patchsize);
	Protect(patchloc,patchsize);
	memcpy(patchloc,backup,patchsize);
	Protect(patchloc);
}

//**********************************************************************************************************************************

void GenericPatch::Protect(void* addr, int size /*=-1*/)
{
	if (size!=-1)
	{
		protect_size = size;
		VirtualProtectEx(GetCurrentProcess(), addr,protect_size,PAGE_EXECUTE_READWRITE,&protect_old);
	}
	else 
	{   
		DWORD dummy;
		VirtualProtectEx(GetCurrentProcess(), addr,protect_size,protect_old,&dummy);
	}
}

//**********************************************************************************************************************************

