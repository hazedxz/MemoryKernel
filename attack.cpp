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

static StringFinder findWeaponID;
const int MAX_GUNS = 30;

BurstInfo burstInfo;

//**********************************************************************************************************************************

void BurstInfo::initWeaponID()
{
	findWeaponID.clear();

	//CS
	/*1*/findWeaponID.add("p228"        , WEAPON_P228    );
	/*2*/findWeaponID.add("unknown"     , WEAPON_UNKNOWN );
	/*3*/findWeaponID.add("scout"       , WEAPON_SCOUT   );
	/*4*/findWeaponID.add("hegrenade"   , WEAPON_HE      );
	/*5*/findWeaponID.add("xm1014"      , WEAPON_XM      ); // shotgun 2
	/*6*/findWeaponID.add("c4"          , WEAPON_C4      );
	/*7*/findWeaponID.add("mac10"       , WEAPON_MAC     );
	/*8*/findWeaponID.add("aug"         , WEAPON_AUG     ); // bullpup
	/*9*/findWeaponID.add("smokegrenade", WEAPON_SMOKE   );
	/*10*/findWeaponID.add("elite"       , WEAPON_ELITE   );
	/*11*/findWeaponID.add("fiveseven"   , WEAPON_FIVE7   );
	/*12*/findWeaponID.add("ump45"       , WEAPON_UMP     );
	/*13*/findWeaponID.add("sg550"       , WEAPON_SG550   );
	/*14*/findWeaponID.add("famas"       , WEAPON_FAMAS   );
	/*15*/findWeaponID.add("galil"       , WEAPON_GALIL   );
	/*16*/findWeaponID.add("usp"         , WEAPON_USP     );
	/*17*/findWeaponID.add("glock18"     , WEAPON_GLOCK   );
	/*18*/findWeaponID.add("awp"         , WEAPON_AWP     );
	/*19*/findWeaponID.add("mp5"	 , WEAPON_MP5     ); // mp5navy
	/*20*/findWeaponID.add("m249"        , WEAPON_PARA    ); // m16
    /*21*/findWeaponID.add("m3"          , WEAPON_M3      ); // shotgun 1
	/*22*/findWeaponID.add("m4a1"        , WEAPON_COLT    );    
    /*23*/findWeaponID.add("tmp"         , WEAPON_TMP     );
    /*24*/findWeaponID.add("g3sg1"       , WEAPON_G3SG1   );
	/*25*/findWeaponID.add("flashbang"   , WEAPON_FLASH   );
	/*26*/findWeaponID.add("deagle"      , WEAPON_DEAGLE  );
	/*27*/findWeaponID.add("sg552"       , WEAPON_SIG     );
    /*28*/findWeaponID.add("ak47"        , WEAPON_AK      );
	/*29*/findWeaponID.add("knife"       , WEAPON_KNIFE   );
	/*30*/findWeaponID.add("p90"         , WEAPON_P90     );	
}

//**********************************************************************************************************************************

int BurstInfo::getWeaponID(const char* weapon)
{
	if( findWeaponID.find(weapon) ){ return findWeaponID.num; }
	else                           { return 0; }
}

//**********************************************************************************************************************************

void BurstInfo::reset()
{
	initWeaponID();
}

//**********************************************************************************************************************************
