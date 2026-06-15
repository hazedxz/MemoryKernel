#include "client.h"

aimbot_s g_Aimbot;

float fAimAngles[3]={0,0,0};
float fOldFOV = 9999999.9f;
float fOldDistance = 9999999.9f;

int aimbot_s::iTargetID = 0;

#define M_PI 3.14159265358979323846

float aimbot_s::fCalcFOV(Vector a,Vector b,float lena,float lenb)
{
	float l1=0.0f, l2=0.0f;
	if(lena>0)l1=lena;else l1=a.Length();
	if(lenb>0)l2=lenb;else l2=b.Length();
	float sc=a.x*b.x+a.y*b.y+a.z*b.z;
	return acos(sc/(l1*l2))*(180.0/M_PI);
}

void aimbot_s::SortTargetByFov(int iIndex)
{
	if(vPlayers[iIndex].fFov<=cvar.aim_fov)
	{
		if(vPlayers[iIndex].fFov<=fOldFOV || iTargetID==0)
		{
			fOldFOV = vPlayers[iIndex].fFov;
			iTargetID = iIndex;
		}
	}
	else {iTargetID = 0;}
}

void aimbot_s::SortTargetByDistance(int iIndex)
{
	if(vPlayers[iIndex].fDistance<=cvar.aim_distance)
	{
		if(vPlayers[iIndex].fDistance<=fOldDistance || iTargetID==0)
		{
			fOldDistance = vPlayers[iIndex].fDistance;
			iTargetID = iIndex;
		}
	}
	else {iTargetID = 0;}
}

Vector aimbot_s::vCalcOriginOffset(int iIndex)
{
	cl_entity_s *ent = GetEntityByIndex(iIndex);

	Vector vAngles,vF,vR,vU,vOut;

	vAngles=Vector(0.0f,ent->angles[1],0.0f);

	gEngfuncs.pfnAngleVectors(vAngles,vF,vR,vU);

	if(ent->curstate.gaitsequence == 2 || ent->curstate.gaitsequence == 5)
		vOut = ent->origin+vF*cvar.aim_x_duck+vR*cvar.aim_y_duck+vU*cvar.aim_z_duck;
	else if(ent->curstate.gaitsequence == 6)
		vOut = ent->origin+vF*cvar.aim_x_jump+vR*cvar.aim_y_jump+vU*cvar.aim_z_jump;
	else
		vOut = ent->origin+vF*cvar.aim_x_stand+vR*cvar.aim_y_stand+vU*cvar.aim_z_stand;

	return vOut;
}

void aimbot_s::ApplySilentAngles(float *angles,usercmd_s *cmd)
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
		cmd->viewangles.x = angles[0];
		cmd->viewangles.y = angles[1];}	

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

void aimbot_s::MyVectorAngles(const float *forward,float *angles)
{
	float tmp, yaw, pitch;

	if (forward[1] == 0 && forward[0] == 0){
		yaw = 0;
		if (forward[2] > 0)
			pitch = 270;
		else
			pitch = 90;}
	else{
		yaw = (atan2(forward[1], forward[0]) * 180 / M_PI);
		if (yaw < 0)
			yaw += 360;

		tmp = sqrt (forward[0]*forward[0] + forward[1]*forward[1]);
		pitch = (atan2(-forward[2], tmp) * 180 / M_PI);
		if (pitch < 0)
			pitch += 360;}

	angles[0] = pitch;
	angles[1] = yaw;
	angles[2] = 0;
	while(angles[0]<-89){angles[0]+=180;angles[1]+=180;}
	while(angles[0]>89){angles[0]-=180;angles[1]+=180;}
	while(angles[1]<-180){angles[1]+=360;}
	while(angles[1]>180){angles[1]-=360;}
}

bool aimbot_s::bIsValidEnt(int iIndex)
{
	cl_entity_s *ent = GetEntityByIndex(iIndex);

	if(ent->player
		&& me.iIndex !=ent->index 
		&& ent->curstate.movetype !=6 
		&& ent->curstate.movetype != 0 
		&& !(ent->curstate.messagenum<GetLocalPlayer()->curstate.messagenum) 
		&& !(GetLocalPlayer()->curstate.iuser1==4 
		&& GetLocalPlayer()->curstate.iuser2==ent->index))
		return true;
	else
		return false;
}

bool aimbot_s::bCheckTeam(int iIndex)
{
	if(cvar.aim_team == 0 && me.team == vPlayers[iIndex].team)return false;

	return true;
}

bool aimbot_s::bVisible(int iIndex) 
{
	if(cvar.aim_thru == 0 && !vPlayers[iIndex].bVisible)
		return false;
	return true;
}

float AngleBetvenVectors( Vector a , Vector b )
{
	float l1 = 0.0f , l2 = 0.0f;
	float sc = a.x*b.x + a.y*b.y + a.z*b.z;
	return cos( sc / ( l1*l2 ) )*( 180.0 / M_PI );
}

void aimbot_s::CL_CreateMove(usercmd_s *cmd)
{
	iTargetID = 0;

	if(!me.alive) return;

	if(currentWeaponID==WEAPON_KNIFE && cvar.knf_aim && cvar.cheatmode == 0)
	{
		for ( int i = 1; i<33; i++ )
		{
			if(!bIsValidEnt(i))continue;
			if(!bCheckTeam(i))continue;
			if(!bVisible(i))continue;

			float distance = 0;

			if ( !cvar.knf_attack )
				distance = (float)cvar.knf_distattack;
			else
				distance = (float)cvar.knf_distattack2;
			
			Vector vAttack= vPlayers[i].vOrigin-me.vEye;

			cl_entity_s* ent = gEngfuncs.GetEntityByIndex(i);

			if( VectorDistance( me.pmvOrigin,ent->origin)<=distance)
			{
				float fov = AngleBetvenVectors( me.pmvForward , vAttack );

				if( (int)fov <= cvar.knf_aimfov )
				{ 
					if(!cvar.knf_attack )
						cmd->buttons |= IN_ATTACK;
					else
						cmd->buttons |= IN_ATTACK2;
				}
			}
		}
	}

	if(!cvar.aim_enable) return;

	for(int i = 1;i<33;i++)
	{
		if ( idhook.FirstKillPlayer[i]==1 || cvar.id_mode==0 )
		{
			if(!bIsValidEnt(i))continue;
			if(!bCheckTeam(i))continue;
			if(!bVisible(i))continue;
			
			if(currentWeaponID==WEAPON_KNIFE)
				SortTargetByDistance(i);
			else
				SortTargetByFov(i);
			
			if(iTargetID != 0) 
			{
				MyVectorAngles(g_Aimbot.vCalcOriginOffset(iTargetID)-me.vEye,fAimAngles);

				if(cvar.aim_auto != 0 && !me.bBadWeapon)
				{
					if(currentWeaponID==WEAPON_KNIFE)
					{
						float distance = 0;
							
						distance = (float)cvar.knifeattackdist;
							
						Vector vAttack= vPlayers[i].vOrigin-me.vEye;
							
						cl_entity_s* ent = gEngfuncs.GetEntityByIndex(i);
							
						if( VectorDistance( me.pmvOrigin,ent->origin)<=distance)
						{
							if(!cvar.knf_attack )
								cmd->buttons |= IN_ATTACK;
							else
								cmd->buttons |= IN_ATTACK2;
						}
					}
					else 
					{
						if(me.iClip && bAttacking)
						{
							if(cvar.aim_punch)
							{
								if(VectorLength(me.punchangle) == 0)
								cmd->buttons |= IN_ATTACK;
							}
							else
								cmd->buttons |= IN_ATTACK;
						}
					}
				}

				if(currentWeaponID==WEAPON_KNIFE && cvar.knf_aim)
				{
					float distance = 0;

					if ( !cvar.knf_attack )
						distance = (float)cvar.knf_distattack;
					else
						distance = (float)cvar.knf_distattack2;
			
					Vector vAttack= vPlayers[i].vOrigin-me.vEye;

					cl_entity_s* ent = gEngfuncs.GetEntityByIndex(i);

					if( VectorDistance( me.pmvOrigin,ent->origin)<=distance)
					{
						float fov = AngleBetvenVectors( me.pmvForward , vAttack );

						if( (int)fov <= cvar.knf_aimfov )
						{ 
							if(!cvar.knf_attack )
								cmd->buttons |= IN_ATTACK;
							else
								cmd->buttons |= IN_ATTACK2;
						}
					}
				}

				if(cvar.aim_trigger && !me.bBadWeapon && currentWeaponID!=WEAPON_KNIFE)
				{
					bTriggerBot(cmd);
				}
			
				if((cmd->buttons&IN_ATTACK && !me.bBadWeapon)
				|| (cmd->buttons&IN_ATTACK2 && currentWeaponID==WEAPON_KNIFE))
				{
					if(cvar.aim_silent == 0)
					{
						cmd->viewangles = fAimAngles;
						gEngfuncs.SetViewAngles(fAimAngles);
					}
					else
					{
						ApplySilentAngles(fAimAngles,cmd);
					}
				}
			}
		}
	}

	if( cvar.id_mode!=2 && iTargetID == 0 )
	{
		for(int i = 1;i<33;i++)
		{
			if (idhook.FirstKillPlayer[i]<2 )
			{
				if(!bIsValidEnt(i))continue;
				if(!bCheckTeam(i))continue;
				if(!bVisible(i))continue;
			
				if(currentWeaponID==WEAPON_KNIFE)
					SortTargetByDistance(i);
				else
					SortTargetByFov(i);
			
				if(iTargetID != 0) 
				{
					MyVectorAngles(g_Aimbot.vCalcOriginOffset(iTargetID)-me.vEye,fAimAngles);

					if(cvar.aim_auto != 0 && !me.bBadWeapon)
					{
						if(currentWeaponID==WEAPON_KNIFE)
						{
							float distance = 0;
							
							distance = (float)cvar.knifeattackdist;
							
							Vector vAttack= vPlayers[i].vOrigin-me.vEye;
							
							cl_entity_s* ent = gEngfuncs.GetEntityByIndex(i);
							
							if( VectorDistance( me.pmvOrigin,ent->origin)<=distance)
							{
								if(!cvar.knf_attack )
									cmd->buttons |= IN_ATTACK;
								else
									cmd->buttons |= IN_ATTACK2;
							}
						}
						else 
						{
							if(me.iClip && bAttacking)
							{
								if(cvar.aim_punch)
								{
									if(VectorLength(me.punchangle) == 0)
									cmd->buttons |= IN_ATTACK;
								}
								else
									cmd->buttons |= IN_ATTACK;
							}
						}
					}

					if(currentWeaponID==WEAPON_KNIFE && cvar.knf_aim)
					{
						float distance = 0;

						if ( !cvar.knf_attack )
							distance = (float)cvar.knf_distattack;
						else
							distance = (float)cvar.knf_distattack2;
			
						Vector vAttack= vPlayers[i].vOrigin-me.vEye;

						cl_entity_s* ent = gEngfuncs.GetEntityByIndex(i);

						if( VectorDistance( me.pmvOrigin,ent->origin)<=distance)
						{
							float fov = AngleBetvenVectors( me.pmvForward , vAttack );

							if( (int)fov <= cvar.knf_aimfov )
							{ 
								if(!cvar.knf_attack )
									cmd->buttons |= IN_ATTACK;
								else
									cmd->buttons |= IN_ATTACK2;
							}
						}
					}

					if(cvar.aim_trigger && !me.bBadWeapon && currentWeaponID!=WEAPON_KNIFE)
					{
						bTriggerBot(cmd);
					}
			
					if((cmd->buttons&IN_ATTACK && !me.bBadWeapon)
					|| (cmd->buttons&IN_ATTACK2 && currentWeaponID==WEAPON_KNIFE))
					{
						if(cvar.aim_silent == 0)
						{
							cmd->viewangles = fAimAngles;
							gEngfuncs.SetViewAngles(fAimAngles);
						}
						else
						{
							ApplySilentAngles(fAimAngles,cmd);
						}
					}
				}
			}
		}
	}
}

void aimbot_s::bTriggerBot(usercmd_s *cmd)
{
	iTargetID = 0;

	float view[3], diff[3], radius, distance, boxradius;
	vec3_t vecEnd, up, right, forward, EntViewOrg, playerAngles, taimangles, faimangles;

	faimangles[0] = cmd->viewangles[0] + me.punchangle[0];
	faimangles[1] = cmd->viewangles[1] + me.punchangle[1];

	for(int i = 1;i<33;i++)
	{
		if ( idhook.FirstKillPlayer[i]==1 || cvar.id_mode==0 )
		{
			if(!bIsValidEnt(i))continue;
			if(!bCheckTeam(i))continue;
			if(!bVisible(i))continue;
			
			if(currentWeaponID==WEAPON_KNIFE)
				SortTargetByDistance(i);
			else
				SortTargetByFov(i);
			
			if(iTargetID != 0) 
			{
				VectorCopy(vPlayers[i].vOrigin,EntViewOrg);
		
				EntViewOrg[2] += cvar.aim_tspot;	
		
				view[0] = EntViewOrg[0] - me.vEye[0];
				view[1] = EntViewOrg[1] - me.vEye[1];
				view[2] = EntViewOrg[2] - me.vEye[2];
			
				VectorAngles(view,taimangles);
				taimangles[0] *= -1;

				if (taimangles[1]>180) taimangles[1]-=360;
	
				diff[0] = faimangles[0] - taimangles[0];
				diff[1] = faimangles[1] - taimangles[1];

				if (diff[1]>180) diff[1]-=360;
				if (diff[1]>45 || diff[1]<-45) continue;

				diff[2] = sqrt(diff[0] * diff[0] + diff[1] * diff[1]);

				distance = sqrt(view[0] * view[0] + view[1] * view[1] + view[2] * view[2]);
		
				boxradius = cvar.aim_tfov;
				radius = (float) ((atan2( boxradius, distance) * 180 / M_PI));
				me.fTrigRadius = radius;
				me.fTrigDiff = diff[2];
				if (diff[2] < radius)
					cmd->buttons |= IN_ATTACK;
			}
		}
	}

	if( cvar.id_mode!=2 && iTargetID == 0 )
	{
		for(int i = 1;i<33;i++)
		{
			if (idhook.FirstKillPlayer[i]<2 )
			{
				if(!bIsValidEnt(i))continue;
				if(!bCheckTeam(i))continue;
				if(!bVisible(i))continue;
			
				if(currentWeaponID==WEAPON_KNIFE)
					SortTargetByDistance(i);
				else
					SortTargetByFov(i);
			
				if(iTargetID != 0) 
				{
					VectorCopy(vPlayers[i].vOrigin,EntViewOrg);
		
					EntViewOrg[2] += cvar.aim_tspot;	
		
					view[0] = EntViewOrg[0] - me.vEye[0];
					view[1] = EntViewOrg[1] - me.vEye[1];
					view[2] = EntViewOrg[2] - me.vEye[2];
			
					VectorAngles(view,taimangles);
					taimangles[0] *= -1;

					if (taimangles[1]>180) taimangles[1]-=360;
	
					diff[0] = faimangles[0] - taimangles[0];
					diff[1] = faimangles[1] - taimangles[1];

					if (diff[1]>180) diff[1]-=360;
					if (diff[1]>45 || diff[1]<-45) continue;

					diff[2] = sqrt(diff[0] * diff[0] + diff[1] * diff[1]);

					distance = sqrt(view[0] * view[0] + view[1] * view[1] + view[2] * view[2]);
		
					boxradius = cvar.aim_tfov;
					radius = (float) ((atan2( boxradius, distance) * 180 / M_PI));
					me.fTrigRadius = radius;
					me.fTrigDiff = diff[2];
					if (diff[2] < radius)
						cmd->buttons |= IN_ATTACK;
				}
			}
		}
	}
}

bool bPathFree( float *pflFrom, float *pflTo )
{
	if( !pflFrom || !pflTo ) { return false; }
	pmtrace_t pTrace;
	gEngfuncs.pEventAPI->EV_SetTraceHull( 2 );
	gEngfuncs.pEventAPI->EV_PlayerTrace( pflFrom, pflTo, PM_GLASS_IGNORE | PM_STUDIO_BOX, me.iIndex, &pTrace );
	return ( pTrace.fraction == 1.0f );
}

void aimbot_s::Hud_Redraw()
{
	for(int i=1; i<33; i++)
	{
		PlayerInfo& p = vPlayers[i];
		cl_entity_s *ent = GetEntityByIndex(i);

		vPlayers[i].vOrigin			= ent->origin;
		vPlayers[i].bVisible		= bPathFree(me.vEye,g_Aimbot.vCalcOriginOffset(i));
		vPlayers[i].fDistance		= floor(sqrt(POW(abs(p.vOrigin.x - me.pmvOrigin.x)) + POW(abs(p.vOrigin.y - me.pmvOrigin.y)) + POW(abs(p.vOrigin.z - me.pmvOrigin.z)))-32);
		vPlayers[i].fFov			= g_Aimbot.fCalcFOV(me.pmvForward,g_Aimbot.vCalcOriginOffset(i)-me.vEye);
	}
}

void VectorAngles( const float *forward, float *angles )
{
	float tmp, yaw, pitch;
	if (forward[1] == 0 && forward[0] == 0)
	{
		yaw = 0;
		if (forward[2] > 0) 
			pitch = 90; 
		else
			pitch = 270;
	}
	else
	{
		yaw = float(atan2(forward[1], forward[0]) * 180/3.14159265358979323846);
		
		if (yaw < 0) yaw += 360.0;
		
		tmp = sqrt(forward[0]*forward[0] + forward[1]*forward[1]);
		
		pitch = float(atan2(forward[2], tmp) * 180/3.14159265358979323846);
	}
	angles[0] = pitch;
	angles[1] = yaw;
	angles[2] = 0;
}

//**********************************************************************************************************************************

