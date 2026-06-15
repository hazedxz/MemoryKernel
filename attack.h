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

#ifndef ATTACK_H
#define ATTACK_H

//**********************************************************************************************************************************

#include "stringfinder.h"

//**********************************************************************************************************************************

enum
{

/*0*/  WEAPON_NONE = 0
/*1*/  ,WEAPON_P228
/*2*/  ,WEAPON_UNKNOWN
/*3*/  ,WEAPON_SCOUT
/*4*/  ,WEAPON_HE
/*5*/  ,WEAPON_XM
/*6*/  ,WEAPON_C4
/*7*/  ,WEAPON_MAC
/*8*/  ,WEAPON_AUG
/*9*/  ,WEAPON_SMOKE
/*10*/  ,WEAPON_ELITE
/*11*/  ,WEAPON_FIVE7
/*12*/  ,WEAPON_UMP
/*13*/  ,WEAPON_SG550
/*14*/  ,WEAPON_FAMAS
/*15*/  ,WEAPON_GALIL
/*16*/  ,WEAPON_USP
/*17*/  ,WEAPON_GLOCK
/*18*/  ,WEAPON_AWP
/*19*/  ,WEAPON_MP5
/*20*/  ,WEAPON_PARA //(m249)
/*21*/  ,WEAPON_M3
/*22*/  ,WEAPON_COLT
/*23*/  ,WEAPON_TMP
/*24*/  ,WEAPON_G3SG1
/*25*/  ,WEAPON_FLASH
/*26*/  ,WEAPON_DEAGLE
/*27*/  ,WEAPON_SIG
/*28*/  ,WEAPON_AK
/*29*/  ,WEAPON_KNIFE
/*30*/  ,WEAPON_P90

};

/*
enum 
{
	 WEAPON_NONE = 0
	,WEAPON_USP,WEAPON_GLOCK,WEAPON_DEAGLE,WEAPON_P228,WEAPON_ELITE,WEAPON_FIVE7
	,WEAPON_XM,WEAPON_M3,WEAPON_GALIL,WEAPON_FAMAS
	,WEAPON_MP5,WEAPON_TMP,WEAPON_P90,WEAPON_MAC,WEAPON_UMP
	,WEAPON_AK,WEAPON_SIG,WEAPON_COLT,WEAPON_AUG
	,WEAPON_SCOUT,WEAPON_AWP,WEAPON_G3SG1,WEAPON_SG550
	,WEAPON_PARA,WEAPON_KNIFE
	,WEAPON_FLASH,WEAPON_HE,WEAPON_SMOKE,WEAPON_C4
};*/

//**********************************************************************************************************************************

class BurstInfo
{
public:
	BurstInfo(){ reset(); } 
public:
	void initWeaponID();
	int getWeaponID(const char* weapon);
	void reset();
protected:
	enum { NUM_USABLE_WEAPONS = 30 };
};

//**********************************************************************************************************************************

extern BurstInfo burstInfo;

//**********************************************************************************************************************************

#endif

//**********************************************************************************************************************************
