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

static unsigned int glSeed = 0; 
unsigned int seed_table[ 256 ] =
{
	28985, 27138, 26457, 9451, 17764, 10909, 28790, 8716, 6361, 4853, 17798, 21977, 19643, 20662, 10834, 20103,
	27067, 28634, 18623, 25849, 8576, 26234, 23887, 18228, 32587, 4836, 3306, 1811, 3035, 24559, 18399, 315,
	26766, 907, 24102, 12370, 9674, 2972, 10472, 16492, 22683, 11529, 27968, 30406, 13213, 2319, 23620, 16823,
	10013, 23772, 21567, 1251, 19579, 20313, 18241, 30130, 8402, 20807, 27354, 7169, 21211, 17293, 5410, 19223,
	10255, 22480, 27388, 9946, 15628, 24389, 17308, 2370, 9530, 31683, 25927, 23567, 11694, 26397, 32602, 15031,
	18255, 17582, 1422, 28835, 23607, 12597, 20602, 10138, 5212, 1252, 10074, 23166, 19823, 31667, 5902, 24630,
	18948, 14330, 14950, 8939, 23540, 21311, 22428, 22391, 3583, 29004, 30498, 18714, 4278, 2437, 22430, 3439,
	28313, 23161, 25396, 13471, 19324, 15287, 2563, 18901, 13103, 16867, 9714, 14322, 15197, 26889, 19372, 26241,
	31925, 14640, 11497, 8941, 10056, 6451, 28656, 10737, 13874, 17356, 8281, 25937, 1661, 4850, 7448, 12744,
	21826, 5477, 10167, 16705, 26897, 8839, 30947, 27978, 27283, 24685, 32298, 3525, 12398, 28726, 9475, 10208,
	617, 13467, 22287, 2376, 6097, 26312, 2974, 9114, 21787, 28010, 4725, 15387, 3274, 10762, 31695, 17320,
	18324, 12441, 16801, 27376, 22464, 7500, 5666, 18144, 15314, 31914, 31627, 6495, 5226, 31203, 2331, 4668,
	12650, 18275, 351, 7268, 31319, 30119, 7600, 2905, 13826, 11343, 13053, 15583, 30055, 31093, 5067, 761,
	9685, 11070, 21369, 27155, 3663, 26542, 20169, 12161, 15411, 30401, 7580, 31784, 8985, 29367, 20989, 14203,
	29694, 21167, 10337, 1706, 28578, 887, 3373, 19477, 14382, 675, 7033, 15111, 26138, 12252, 30996, 21409,
	25678, 18555, 13256, 23316, 22407, 16727, 991, 9236, 5373, 29402, 6117, 15241, 27715, 19291, 19888, 19847
};

//**********************************************************************************************************************************

unsigned int U_Random( void ) 
{ 
	glSeed *= 69069; 
	glSeed += seed_table[ glSeed & 0xff ];
	return ( ++glSeed & 0x0fffffff ); 
} 

//**********************************************************************************************************************************

void U_Srand( unsigned int seed )
{
	glSeed = seed_table[ seed & 0xff ];
}

//**********************************************************************************************************************************

int UTIL_SharedRandomLong( unsigned int seed, int low, int high )
{
	unsigned int range;
	U_Srand( (int)seed + low + high );
	range = high - low + 1;
	if ( !(range - 1) )
	{
		return low;
	}
	else
	{
		int offset;
		int rnum;
		rnum = U_Random();
		offset = rnum % range;
		return (low + offset);
	}
}

//**********************************************************************************************************************************

float UTIL_SharedRandomFloat( unsigned int seed, float low, float high )
{
	unsigned int range;
	U_Srand( (int)seed + *(int *)&low + *(int *)&high );
	U_Random();
	U_Random();
	range = (unsigned int)(high - low);
	if ( !range )
	{
		return low;
	}
	else
	{
		int tensixrand;
		float offset;
		tensixrand = U_Random() & 65535;
		offset = (float)tensixrand / 65536.0f;
		return (low + offset * range );
	}
}

//**********************************************************************************************************************************

// FIX: (me.iFOV < 90.0f) doesn't work for weapons that unzoom between shots
// on the client the weapon shoots then unzooms to chamber another round,
// on server no unzoom between shots so spread is off if IN_ATTACK is held on
// and multiple shots are fired

//**********************************************************************************************************************************

float GetVecSpread(float speed)
{
	float spread;

	switch (currentWeaponID)
	{
	case WEAPONLIST_DEAGLE:
		if (me.spread.prcflags & FL_ONGROUND)
		{
			if (speed)
				spread = 0.25 * (1.0f - me.spread.spreadvar);
			else if (me.spread.prcflags & FL_DUCKING)
				spread = 0.115 * (1.0f - me.spread.spreadvar);
			else
				spread = 0.13 * (1.0f - me.spread.spreadvar);
		}
		else
			spread = 1.5 * (1.0f - me.spread.spreadvar);

		break;
	case WEAPONLIST_ELITE:
		if (me.spread.prcflags & FL_ONGROUND)
		{
			if (speed)
				spread = 0.175 * (1.0f - me.spread.spreadvar);
			else if (me.spread.prcflags & FL_DUCKING)
				spread = 0.08 * (1.0f - me.spread.spreadvar);
			else
				spread = 0.1 * (1.0f - me.spread.spreadvar);
		}
		else
			spread = 1.3 * (1.0f - me.spread.spreadvar);

		break;
	case WEAPONLIST_GALIL:
		if (me.spread.prcflags & FL_ONGROUND)
		{
			if (speed > 140.0f)
				spread = me.spread.spreadvar * 0.07 + 0.04;
			else
				spread = me.spread.spreadvar * 0.0375;
		}
		else
			spread = me.spread.spreadvar * 0.4 + 0.03;

		break;
	case WEAPONLIST_FAMAS:
		if (me.spread.prcflags & FL_ONGROUND)
		{
			if (speed > 140.0f)
				spread = me.spread.spreadvar * 0.07 + 0.03;
			else
				spread = me.spread.spreadvar * 0.020;
		}
		else
			spread = me.spread.spreadvar * 0.4 + .04;
		break;
	case WEAPONLIST_FIVESEVEN:
		if (me.spread.prcflags & FL_ONGROUND)
		{
			if (speed)
				spread = 0.255 * (1.0f - me.spread.spreadvar);
			else if (me.spread.prcflags & FL_DUCKING)
				spread = 0.075 * (1.0f - me.spread.spreadvar);
			else
				spread = 0.15 * (1.0f - me.spread.spreadvar);
		}
		else
			spread = 1.5 * (1.0f - me.spread.spreadvar);

		break;
	case WEAPONLIST_GLOCK18:
		if (!(me.spread.WeaponState & GLOCK18_BURST))
		{
			if (me.spread.prcflags & FL_ONGROUND)
			{
				if (speed)
					spread = 0.165 * (1.0f - me.spread.spreadvar);
				else if (me.spread.prcflags & FL_DUCKING)
					spread = 0.075 * (1.0f - me.spread.spreadvar);
				else
					spread = 0.1 * (1.0f - me.spread.spreadvar);
			}
			else
				spread = 1.0f - me.spread.spreadvar;
		}
		else
		{
			if (me.spread.prcflags & FL_ONGROUND)
			{
				if (speed)
					spread = 0.185 * (1.0f - me.spread.spreadvar);
				else if (me.spread.prcflags & FL_DUCKING)
					spread = 0.095 * (1.0f - me.spread.spreadvar);
				else
					spread = 0.3 * (1.0f - me.spread.spreadvar);
			}
			else
				spread = 1.2 * (1.0f - me.spread.spreadvar);
		}

		break;
	case WEAPONLIST_P228:
		if (me.spread.prcflags & FL_ONGROUND)
		{
			if (speed)
				spread = 0.255 * (1.0f - me.spread.spreadvar);
			else if (me.spread.prcflags & FL_DUCKING)
				spread = 0.075 * (1.0f - me.spread.spreadvar);
			else
				spread = 0.15 * (1.0f - me.spread.spreadvar);
		}
		else
			spread = 1.5 * (1.0f - me.spread.spreadvar);

		break;
	case WEAPONLIST_G3SG1:
		if (me.spread.prcflags & FL_ONGROUND)
		{
			if (speed)
				spread = 0.15f;
			else if (me.spread.prcflags & FL_DUCKING)
				spread = 0.035 * (1.0f - me.spread.spreadvar);
			else
				spread = 0.055 * (1.0f - me.spread.spreadvar);
		}
		else
			spread = 0.45 * (1.0f - me.spread.spreadvar);

		if (!(me.iFOV < 90.0f))
			spread += 0.025f;

		break;
	case WEAPONLIST_SG550:
		if (me.spread.prcflags & FL_ONGROUND)
		{
			if (speed)
				spread = 0.15f;
			else if (me.spread.prcflags & FL_DUCKING)
				spread = 0.04 * (1.0f - me.spread.spreadvar);
			else
				spread = 0.05 * (1.0f - me.spread.spreadvar);
		}
		else
			spread = 0.45 * (1.0f - me.spread.spreadvar);

		if (!(me.iFOV < 90.0f))
			spread += 0.025f;

		break;
	case WEAPONLIST_USP:
		if (!(me.spread.WeaponState & USP_SILENCER))
		{
			if (me.spread.prcflags & FL_ONGROUND)
			{
				if (speed)
					spread = 0.225 * (1.0f - me.spread.spreadvar);
				else if (me.spread.prcflags & FL_DUCKING)
					spread = 0.08 * (1.0f - me.spread.spreadvar);
				else
					spread = 0.1 * (1.0f - me.spread.spreadvar);
			}
			else
				spread = 1.2 * (1.0f - me.spread.spreadvar);
		}
		else
		{
			if (me.spread.prcflags & FL_ONGROUND)
			{
				if (speed)
					spread = 0.25 * (1.0f - me.spread.spreadvar);
				else if (me.spread.prcflags & FL_DUCKING)
					spread = 0.125 * (1.0f - me.spread.spreadvar);
				else
					spread = 0.15 * (1.0f - me.spread.spreadvar);
			}
			else
				spread = 1.3 * (1.0f - me.spread.spreadvar);
		}

		break;
	case WEAPONLIST_AK47:
		if (me.spread.prcflags & FL_ONGROUND)
		{
			if (speed > 140.0f)
				spread = me.spread.spreadvar * 0.07 + 0.04;
			else
				spread = me.spread.spreadvar * 0.0275;
		}
		else
			spread = me.spread.spreadvar * 0.4 + .04;

		break;
	case WEAPONLIST_SG552:
		if (me.spread.prcflags & FL_ONGROUND)
		{
			if (speed > 140.0f)
				spread = me.spread.spreadvar * 0.07 + 0.035;
			else
				spread = me.spread.spreadvar * 0.02;
		}
		else
			spread = me.spread.spreadvar * 0.4 + .035;

		break;
	case WEAPONLIST_AUG:
		if (me.spread.prcflags & FL_ONGROUND)
		{
			if (speed > 140.0f)
				spread = me.spread.spreadvar * 0.07 + 0.035;
			else
				spread = me.spread.spreadvar * 0.02;
		}
		else
			spread = me.spread.spreadvar * 0.4 + .035;

		break;
	case WEAPONLIST_M249:
		if (me.spread.prcflags & FL_ONGROUND)
		{
			if (speed > 140.0f)
				spread = me.spread.spreadvar * 0.095 + 0.045;
			else
				spread = me.spread.spreadvar * 0.03;
		}
		else
			spread = me.spread.spreadvar * 0.5 + .045;

		break;
	case WEAPONLIST_M4A1:
		if (me.spread.prcflags & FL_ONGROUND)
		{
			if (!(me.spread.WeaponState & M4A1_SILENCER))
			{
				if (speed > 140.0f)
					spread = me.spread.spreadvar * 0.07 + 0.035;
				else
					spread = me.spread.spreadvar * 0.02;
			}
			else
			{
				if (speed > 140.0f)
					spread = me.spread.spreadvar * 0.07 + 0.035;
				else
					spread = me.spread.spreadvar * 0.025;
			}
		}
		else
			spread = me.spread.spreadvar * 0.4 + .035;

		break;
	case WEAPONLIST_MP5:
		if (me.spread.prcflags & FL_ONGROUND)
			spread = 0.04 * me.spread.spreadvar;
		else
			spread = 0.2 * me.spread.spreadvar;
		break;
	case WEAPONLIST_MAC10:
		if (me.spread.prcflags & FL_ONGROUND)
			spread = 0.03 * me.spread.spreadvar;
		else
			spread = 0.375 * me.spread.spreadvar;

		break;
	case WEAPONLIST_P90:
		if (me.spread.prcflags & FL_ONGROUND)
		{
			if (speed > 170.0f)
				spread = me.spread.spreadvar * 0.115;
			else
				spread = me.spread.spreadvar * 0.045;
		}
		else
			spread = me.spread.spreadvar * 0.3;

		break;
	case WEAPONLIST_TMP:
		if (me.spread.prcflags & FL_ONGROUND)
			spread = 0.03 * me.spread.spreadvar;
		else
			spread = 0.25 * me.spread.spreadvar;

		break;
	case WEAPONLIST_UMP45:
		if (me.spread.prcflags & FL_ONGROUND)
			spread = 0.04 * me.spread.spreadvar;
		else
			spread = 0.24 * me.spread.spreadvar;

		break;
	case WEAPONLIST_AWP:
		if (me.spread.prcflags & FL_ONGROUND)
		{
			if (speed < 10.0f)
			{
				if (me.spread.prcflags & FL_DUCKING)
					spread = 0;
				else
					spread = 0.001f;
			}
			else if (speed < 140.0f)
			{
				spread = 0.1f;
			}
			else
				spread = 0.25f;
		}
		else
			spread = 0.85f;

		if (!(me.iFOV < 90.0f))
			spread += 0.08f;

		break;
	case WEAPONLIST_SCOUT:
		if (me.spread.prcflags & FL_ONGROUND)
		{
			if (speed < 170.0f)
			{
				if (me.spread.prcflags & FL_DUCKING)
					spread = 0;
				else
					spread = 0.007f;
			}
			else
				spread = 0.075f;
		}
		else
			spread = 0.2f;

		if (!(me.iFOV < 90.0f))
			spread += 0.025f;

		break;
	default:
		spread = 0;
		break;
	}

	return spread;
}

//**********************************************************************************************************************************

void GetSpreadXY(unsigned int seed, int future, float* velocity, float* vec)
{
	float vecspread;

	vec[0] = UTIL_SharedRandomFloat(seed + future, -0.5, 0.5) + UTIL_SharedRandomFloat(seed + 1 + future, -0.5, 0.5);

	vec[1] = UTIL_SharedRandomFloat(seed + 2 + future, -0.5, 0.5) + UTIL_SharedRandomFloat(seed + 3 + future, -0.5, 0.5);

	me.spread.speed = sqrt(velocity[0] * velocity[0] + velocity[1] * velocity[1]);
	
	vecspread = GetVecSpread(me.spread.speed);

	vec[0] *= vecspread;
	vec[1] *= vecspread;

	return;
}

//**********************************************************************************************************************************

void GetRecoilOffset(unsigned int seed, int future, float* inangles, float* velocity, float* outangles)
{
	float forward[3], right[3], up[3], vecDir[3];
	float view[3], dest[3], spread[2];
	
	gEngfuncs.pfnAngleVectors(inangles, forward, right, up);

	GetSpreadXY(seed, future, velocity, spread);

	vecDir[0] = forward[0] + spread[0] * right[0] + spread[1] * up[0];
	view[0] = 8192 * vecDir[0];

	vecDir[1] = forward[1] + spread[0] * right[1] + spread[1] * up[1];
	view[1] = 8192 * vecDir[1];

	vecDir[2] = forward[2] + spread[0] * right[2] + spread[1] * up[2];
	view[2] = 8192 * vecDir[2];

	VectorAngles(view, dest);
	dest[0] *= -1;

	outangles[0] = inangles[0] - dest[0];
	outangles[1] = inangles[1] - dest[1];
	outangles[2] = 0;
}

//**********************************************************************************************************************************

void DefaultSpreadVar(int weaponid)
{
	if (cvar.spreadvar)
	{
		switch(weaponid)
		{
		case WEAPONLIST_DEAGLE:
		me.spread.spreadvar = 0.9f;
		me.weaponspeed  = 250.0f-2.0f;
		break;
		case WEAPONLIST_P228:
		me.spread.spreadvar = 0.9f;
		me.weaponspeed  = 250.0f-2.0f;
		break;
		case WEAPONLIST_FIVESEVEN:
		me.spread.spreadvar = 0.9f;
		me.weaponspeed  = 250.0f-2.0f;
		break;
		case WEAPONLIST_ELITE:
		me.spread.spreadvar = 0.8f;
		me.weaponspeed  = 250.0f-2.0f;
		break;
		case WEAPONLIST_GLOCK18:
		me.spread.spreadvar = 0.9f;
		me.weaponspeed  = 250.0f-2.0f;
		break;
		case WEAPONLIST_USP:
		me.spread.spreadvar = 0.9f;
		me.weaponspeed  = 250.0f-2.0f;
		break;
		case WEAPONLIST_TMP:
		me.spread.spreadvar = 0.2f;
		me.weaponspeed  = 250.0f-2.0f;
		break;
		case WEAPONLIST_MAC10:
		me.spread.spreadvar = 0.15f;
		me.weaponspeed  = 250.0f-2.0f;
		break;
		case WEAPONLIST_P90:
		me.spread.spreadvar = 0.15f;
		me.weaponspeed  = 245.0f-2.0f;
		break;
		case WEAPONLIST_MP5:
		me.spread.spreadvar = 0;// -------------------> 0
		me.weaponspeed  = 250.0f-2.0f;
		break;
		case WEAPONLIST_UMP45:
		me.spread.spreadvar = 0;// -------------------> 0
		me.weaponspeed  = 250.0f-2.0f;
		break;
		case WEAPONLIST_M3:
		me.spread.spreadvar = 0;// -------------------> 0
		me.weaponspeed  = 230.0f-2.0f;
		break;
		case WEAPONLIST_XM1014:
		me.spread.spreadvar = 0;// -------------------> 0
		me.weaponspeed = 240.0f-2.0f;
		break;
		case WEAPONLIST_FAMAS:
		me.spread.spreadvar = 0.2f;// -------------------> 0
		me.weaponspeed  = 240.0f-2.0f;
		break;
		case WEAPONLIST_GALIL:
		me.spread.spreadvar = 0.2f;// -------------------> 0
		me.weaponspeed  = 240.0f-2.0f;
		break;
		case WEAPONLIST_AUG:
		me.spread.spreadvar = 0.3f;
		me.weaponspeed  = 240.0f-2.0f;
		break;
		case WEAPONLIST_SG552:
		me.spread.spreadvar = 0.2f;
		me.weaponspeed  = 235.0f-2.0f;
		break;
		case WEAPONLIST_M4A1:
		me.spread.spreadvar = 0.2f;
		me.weaponspeed  = 230.0f-2.0f;
		break;
		case WEAPONLIST_AK47:
		me.spread.spreadvar = 0.2f;
		me.weaponspeed  = 221.0f-2.0f;
		break;
			case WEAPONLIST_AWP:
		me.spread.spreadvar = 0;// -------------------> 0
		me.weaponspeed  = 210.0f-2.0f;
		break;
		case WEAPONLIST_SCOUT:
		me.spread.spreadvar = 0;// -------------------> 0
		me.weaponspeed  = 260.0f-2.0f;
		break;
		case WEAPONLIST_SG550:
		me.spread.spreadvar = 0.2f;
		me.weaponspeed  = 210.0f-2.0f;
		break;
		case WEAPONLIST_G3SG1:
		me.spread.spreadvar = 0.2f;
		me.weaponspeed  = 210.0f-2.0f;
		break;
		case WEAPONLIST_M249:
		me.spread.spreadvar = 0.2f;
		me.weaponspeed  = 220.0f-2.0f;
		break;
		default:
		me.spread.spreadvar = 0;
		me.weaponspeed  = 0;
		break;
		}
	}
}

//**********************************************************************************************************************************

void recoil(struct usercmd_s* usercmd)
{
	if(cvar.norecoil)
	{
		usercmd->viewangles[0] -= (me.punchangle[0] * cvar.recoil);
		usercmd->viewangles[1] -= (me.punchangle[1] * cvar.recoil);
	}
}

void ApplySilentAnglesNospread(float *angles,usercmd_s *cmd)
{
	cl_entity_t *pLocal;
	Vector viewforward, viewright, viewup, aimforward, aimright, aimup, vTemp;
	float newforward, newright, newup;
	float forward = cmd->forwardmove;
	float right = cmd->sidemove;
	float up = cmd->upmove;

	pLocal = GetLocalPlayer();
	if(!pLocal) return;

	if(pLocal->curstate.movetype == MOVETYPE_WALK)
		gEngfuncs.pfnAngleVectors(Vector(0.0f, cmd->viewangles.y, 0.0f), viewforward, viewright, viewup);
	else
		gEngfuncs.pfnAngleVectors(cmd->viewangles, viewforward, viewright, viewup);

	if(pLocal->curstate.movetype == MOVETYPE_WALK && !(me.pmMoveType == 5)){
		cmd->viewangles.x += angles[0];
		cmd->viewangles.y += angles[1];}	

	if(pLocal->curstate.movetype == MOVETYPE_WALK)
		gEngfuncs.pfnAngleVectors(Vector(0.0f, cmd->viewangles.y, 0.0f), aimforward, aimright, aimup);
	else
		gEngfuncs.pfnAngleVectors(cmd->viewangles, aimforward, aimright, aimup);

	newforward = DotProduct(forward * viewforward.Normalize(), aimforward) + DotProduct(right * viewright.Normalize(), aimforward) + DotProduct(up * viewup.Normalize(), aimforward);
	newright = DotProduct(forward * viewforward.Normalize(), aimright) + DotProduct(right * viewright.Normalize(), aimright) + DotProduct(up * viewup.Normalize(), aimright);
	newup = DotProduct(forward * viewforward.Normalize(), aimup) + DotProduct(right * viewright.Normalize(), aimup) + DotProduct(up * viewup.Normalize(), aimup);

	if (angles[0]>81)
		cmd->forwardmove = -newforward; 
	else
		cmd->forwardmove = newforward;

	cmd->sidemove = newright;
	cmd->upmove = newup;
}

float offset[3];

void nospread(struct usercmd_s* usercmd)
{
	me.cmdViewAngles = usercmd->viewangles;

	GetRecoilOffset(me.spread.random_seed, 1, usercmd->viewangles, me.pmVelocity, offset);
	VectorCopy(offset, me.vNoSpreadAng);
	if(cvar.nospread && (usercmd->buttons & IN_ATTACK))
		ApplySilentAnglesNospread(offset, usercmd);
}

