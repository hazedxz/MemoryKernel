#include "client.h"

//**********************************************************************************************************************************

char* gGetWeaponName( int weaponmodel )
{
	static char weapon[50];
	weapon[0]=0;
	model_s* mdl = IEngineStudio.GetModelByIndex( weaponmodel );
	if( !mdl ){ return weapon; }
	char* name = mdl->name;  if( !name )          { return weapon; }
	int len = strlen(name);  if( len>48 || len<10){ return weapon; }
	strcpy(weapon,name+9); len -=9;
	if(len>4)weapon[len-4]=(char)0;
	return weapon;
}

float GetDistanceFrom(float* pos)
{	
	register float a = pos[0] - me.pmEyePos[0];
	register float b = pos[1] - me.pmEyePos[1];
	register float c = pos[2] - me.pmEyePos[2];
	return sqrt(a*a + b*b + c*c);
}

void playerCalcExtraData(int ax, cl_entity_s* ent)
{
	PlayerInfo& r = vPlayers[ax];
	r.updateEntInfo();
	if( cvar.weapon && IEngineStudio.GetModelByIndex )
		r.setWeapon(gGetWeaponName(r.getEnt()->curstate.weaponmodel));
	r.distance  = GetDistanceFrom (ent->origin); 
	if(r.distance<1) r.distance=1;
	
	vPlayers[ax].bGotHead = false;
}

//**********************************************************************************************************************************
