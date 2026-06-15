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

#ifndef GPATCH_H
#define GPATCH_H

//**********************************************************************************************************************************

class GenericPatch
{
private:
enum{ PATCH_MAX=64 };
public:
	// INTERFACE:
	bool find_location(BYTE* hint,const BYTE* sig_bytes,const char* sig_mask);
	void set_location (BYTE* loc,int length);
	BYTE*  patchloc;
	DWORD  patchsize;
	BYTE   backup   [PATCH_MAX];
	BYTE   patchdata  [PATCH_MAX];
	void apply();
	void restore();
private:
	DWORD protect_size;
	DWORD protect_old;
	void  Protect(void* addr, int size=-1);
public:
	GenericPatch() :patchloc(0),patchsize(0) {}
};

//**********************************************************************************************************************************

#endif

//**********************************************************************************************************************************
