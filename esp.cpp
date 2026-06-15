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

int Cstrike_SequenceInfo[] = 
{
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0, // 0..9   
	0,	1,	2,	0,	1,	2,	0,	1,	2,	0, // 10..19 
	1,	2,	0,	1,	1,	2,	0,	1,	1,	2, // 20..29 
	0,	1,	2,	0,	1,	2,	0,	1,	2,	0, // 30..39 
	1,	2,	0,	1,	2,	0,	1,	2,	0,	1, // 40..49 
	2,	0,	1,	2,	0,	0,	0,	8,	0,	8, // 50..59 
	0, 16,	0, 16,	0,	0,	1,	1,	2,	0, // 60..69 
	1,	1,	2,	0,	1,	0,	1,	0,	1,	2, // 70..79 
	0,	1,	2, 	32, 40, 32, 40, 32, 32, 32, // 80..89
   	33, 64, 33, 34, 64, 65, 34, 32, 32, 4, // 90..99
	4,	4,	4,	4,	4,	4,	4,	4,	4,	4, // 100..109
	4                                      	// 110
};

//********************************************************************************************************************************** 

int getSeqInfo(int ax)
{
	return Cstrike_SequenceInfo[vPlayers[ax].getEnt()->curstate.sequence];
}

//**********************************************************************************************************************************

void DrawEntEsp(void)
{
	if(cvar.rush) return;

 	cl_entity_s * pMe = gEngfuncs.GetLocalPlayer();
	for(int i=1023; i>0; i--)
	{
		cl_entity_s * pEnt = gEngfuncs.GetEntityByIndex(i);
		ColorEntry * clr;
		if(pEnt && (pEnt->curstate.messagenum+10 > pMe->curstate.messagenum) && pEnt->model && pEnt->model->name && !pEnt->player)
		{
			float tmp[2];
			char mdl[64];
			char *wpn = NULL;

			strncpy(mdl, pEnt->model->name, 64);
			wpn = mdl;

			if(CalcScreen(pEnt->origin,tmp))
			{

				float distance = GetDistanceFrom(pEnt->origin)/22.0f;
				extern float fCurrentFOV;
				int   boxradius = (300.0*90.0) / (distance*fCurrentFOV);
				BOUND_VALUE(boxradius,1,200);

				float org[3];
				org[0]=pEnt->origin.x;
				org[1]=pEnt->origin.y;
				org[2]=pEnt->origin.z;

				if(wpn && strstr(wpn, /*w_*/XorStr<0x52,3,0xA2204F51>("\x25\x0C"+0xA2204F51).s))
				{
					wpn += 9;
					wpn[strlen(wpn)-4] = 0;
					clr = colorList.get(29);

					if(strstr(wpn,/*thighpack*/XorStr<0x6F,10,0x0CA9EFF6>("\x1B\x18\x18\x15\x1B\x04\x14\x15\x1C"+0x0CA9EFF6).s))
					{
						gDrawBoxAtScreenXY(tmp[0],tmp[1],clr->r,clr->g,clr->b,clr->a,boxradius);
						DrawConStringCenter(tmp[0],tmp[1],clr->r,clr->g,clr->b,/*Defusal-Kit*/XorStr<0x96,12,0x322C9107>("\xD2\xF2\xFE\xEC\xE9\xFA\xF0\xB0\xD5\xF6\xD4"+0x322C9107).s);							
					}
					else if(strstr(wpn,/*backpack*/XorStr<0x6D,9,0x06AC5324>("\x0F\x0F\x0C\x1B\x01\x13\x10\x1F"+0x06AC5324).s))
					{
						gDrawBoxAtScreenXY(tmp[0],tmp[1],clr->r,clr->g,clr->b,clr->a,boxradius);
						DrawConStringCenter(tmp[0],tmp[1],clr->r,clr->g,clr->b,/*C4 Dropped*/XorStr<0x43,11,0x7282C5B9>("\x00\x70\x65\x02\x35\x27\x39\x3A\x2E\x28"+0x7282C5B9).s);							
					}
					else if(strstr(wpn,/*c4*/XorStr<0xF1,3,0x2BB8BC8C>("\x92\xC6"+0x2BB8BC8C).s))
					{
						gDrawBoxAtScreenXY(tmp[0],tmp[1],clr->r,clr->g,clr->b,clr->a,boxradius);
						DrawConStringCenter(tmp[0],tmp[1],clr->r,clr->g,clr->b,/*C4 Activated*/XorStr<0x41,13,0xCEC6CF2A>("\x02\x76\x63\x05\x26\x32\x2E\x3E\x28\x3E\x2E\x28"+0xCEC6CF2A).s);	
					}
					else
					{
						DrawConStringCenter(tmp[0],tmp[1],clr->r,clr->g,clr->b,wpn);
					}
				}
				else if(wpn && (strstr(wpn, /*hostage*/XorStr<0xBF,8,0x834F4B39>("\xD7\xAF\xB2\xB6\xA2\xA3\xA0"+0x834F4B39).s) || (strstr(wpn, /*scientist*/XorStr<0x87,10,0xD8179B2B>("\xF4\xEB\xE0\xEF\xE5\xF8\xE4\xFD\xFB"+0xD8179B2B).s))))
				{
					vec3_t forward, right, up, entOrg ;
					
					wpn += 7;
					wpn[strlen(wpn)-4] = 0;
					
					VectorCopy(pEnt->origin, entOrg);
					gEngfuncs.pfnAngleVectors(pEnt->angles, forward, right, up);
					entOrg = entOrg + up * 40;
					if(CalcScreen(entOrg, tmp))
					{
						gDrawBoxAtScreenXY(tmp[0],tmp[1],clr->r,clr->g,clr->b,clr->a,boxradius);
						DrawConStringCenter(tmp[0],tmp[1],clr->r,clr->g,clr->b,wpn);
					}
				}
			}
		}
		else if(!pEnt)
			break;
	}
}

//**********************************************************************************************************************************

void PlayerEsp()
{
	for(int i = 0; i < 33; i++)
	{
		ColorEntry* color = PlayerColor(i);
		ColorEntry* yellow = colorList.get(27);

		cl_entity_t *pLocal = GetLocalPlayer(); 
		if(i == pLocal->index) continue;

		cl_entity_s *ent = GetEntityByIndex(i);
		cl_entity_s *pEnt = IEngineStudio.GetCurrentEntity();

		if(ent != NULL &&  bIsValidEnt(ent))
		{
			float VecScreen[2];

			if(CalcScreen(ent->origin,VecScreen))
			{
				if(cvar.miniradar)
				{
					if( cvar.espteam || isEnemy(i))
					{
						drawMiniRadarPoint(ent->origin,color->r,color->g,color->b,3,3,false);
					}
				}

				if(cvar.radar)
				{
					if( cvar.espteam || isEnemy(i))
					{
						drawRadarPoint(ent->origin,color->r,color->g,color->b,3,3,false);
					}
				}

				float distance = vPlayers[i].distance/22.0f;
				extern float fCurrentFOV;
				int   boxradius = (300.0*90.0) / (distance*fCurrentFOV);	 
				BOUND_VALUE(boxradius,1,200);
				int text_dist = (int)(boxradius);

				float distancebox = vPlayers[i].distance/22.0f;
				extern float fCurrentFOVbox;
				int   boxradiusbox = (300.0*90.0) / (distancebox*fCurrentFOVbox);	 
				BOUND_VALUE(boxradiusbox,1,000);
				int text_distbox = (int)(boxradiusbox);

				enum{ CHAR_HEIGHT = 13 }; 
				int ystep = CHAR_HEIGHT;

				int x = VecScreen[0];
				int y = VecScreen[1]-text_dist-CHAR_HEIGHT; 
				y = y-text_dist-CHAR_HEIGHT; 
			
				y-=12;
				
/*				if(!cvar.rush && cvar.esp_box2d)
				{
					if(cvar.espteam || isEnemy(i))
					{
						Draw2DBox(pEnt,ent->origin,text_distbox,color); // box 2d
					}
				}
				
				if(!cvar.rush && cvar.esp_box3d)
				{
					if(cvar.espteam || isEnemy(i))
					{
						if(ent->curstate.sequence == 99 || ent->curstate.sequence == 100)
							Draw3DBox(ent,ent->origin,text_distbox,yellow);
						else
							Draw3DBox(ent,ent->origin,text_distbox,color);
					}
				}
				
				if(!cvar.rush && cvar.esp_box3ds && cvar.cheatmode == 1)
				{
					if (g_Aimbot.iTargetID!=0)
					{
						if(cvar.espteam || isEnemy(i))
						{
							if(ent->curstate.sequence == 99 || ent->curstate.sequence == 100)
								Draw3DBoxSpinn(ent,ent->origin,text_distbox,yellow);
							else
								Draw3DBoxSpinn(ent,ent->origin,text_distbox,color);
						}
					}
				}*/

	            if(!cvar.rush && cvar.weapon==1 || (cvar.weapon==2 && idhook.FirstKillPlayer[i]))
				{
					if(cvar.espteam || isEnemy(i))
					{
						DrawHudStringCenter(x, y, color->r, color->g, color->b, "%s",gGetWeaponName(ent->curstate.weaponmodel)); 
						y -= ystep;
					}
				}

				if(!cvar.rush && cvar.name==1 || (cvar.name==2 && idhook.FirstKillPlayer[i]))
				{
					if(cvar.espteam || isEnemy(i))
					{
						hud_player_info_t pinfo;
						GetPlayerInfo(i, &pinfo);
						char buf[1024];
						sprintf(buf,"%s",pinfo.name);
						DrawHudStringCenter(x, y, color->r, color->g, color->b, buf);
						y -= ystep;
					}
				}
				if(!cvar.rush && cvar.sequence==1 || (cvar.sequence==2 && idhook.FirstKillPlayer[i]))
				{
					if(cvar.espteam || isEnemy(i))
					{
						int atype = getSeqInfo(i);
						if (ent->curstate.gaitsequence==GAITSEQUENCE_RUNNING) 
						{ 
							DrawHudStringCenter(x,y,yellow->r,yellow->g,yellow->b,"- RUNNING -");
							y -= ystep;
						}
						if (ent->curstate.gaitsequence==GAITSEQUENCE_STAND) 
						{ 
							DrawHudStringCenter(x,y,yellow->r,yellow->g,yellow->b,"- STANDING -");
							y -= ystep;
						}
						if (ent->curstate.gaitsequence==GAITSEQUENCE_DUCK) 
						{ 
							DrawHudStringCenter(x,y,yellow->r,yellow->g,yellow->b,"- DUCKING -");
							y -= ystep;
						}
						if (ent->curstate.gaitsequence==GAITSEQUENCE_WALK) 
						{ 
							DrawHudStringCenter(x,y,yellow->r,yellow->g,yellow->b,"- WALKING -");
							y -= ystep;
						}
						if (ent->curstate.gaitsequence==GAITSEQUENCE_DUCKMOVE) 
						{ 
							DrawHudStringCenter(x,y,yellow->r,yellow->g,yellow->b,"- DUCKMOVING -");
							y -= ystep;
						}
						if (ent->curstate.gaitsequence==GAITSEQUENCE_JUMP) 
						{ 
							DrawHudStringCenter(x,y,yellow->r,yellow->g,yellow->b,"- JUMPING -");
							y -= ystep;
						}
						if (ent->curstate.sequence == 99 || ent->curstate.sequence == 100)
						{
							oglSubtractive=true;
							gEngfuncs.pfnFillRGBA(x-31,y+4,64,14,yellow->r,yellow->g,yellow->b,yellow->a);
							oglSubtractive=false;
							DrawHudStringCenter(x,y,yellow->r,yellow->g,yellow->b,"-- HIT --");
							y -= ystep;
						}
						if(atype == 8)
						{
							DrawHudStringCenter(x,y,yellow->r,yellow->g,yellow->b,"- THROWING -");
							y -= ystep;
						}
						if(atype == 32)
						{
							DrawHudStringCenter(x,y,yellow->r,yellow->g,yellow->b,"- SHIELD TO SIDE -");
							y -= ystep;
						}
						if(atype == 64)
						{
							DrawHudStringCenter(x,y,yellow->r,yellow->g,yellow->b,"- SHIELDED -");
							y -= ystep;
						}
						if(atype == 1)
						{
							DrawHudStringCenter(x,y,yellow->r,yellow->g,yellow->b,"- SHOOTING -");
							y -= ystep;
						}
						if( atype == 2)
						{
							DrawHudStringCenter(x,y,yellow->r,yellow->g,yellow->b,"- RELOADING -");
							y -= ystep;
						}
						if (atype==5 || atype== 16) 
						{ 
							DrawHudStringCenter(x,y,yellow->r,yellow->g,yellow->b,"- PLANTING c4 -");
							y -= ystep;
						}
					}
				}

				if(!cvar.rush && cvar.reloadmeter) 
				{
					if(cvar.espteam || isEnemy(i))
        			{
						int seqinfo = Cstrike_SequenceInfo[ent->curstate.sequence];
						if( seqinfo == 2)
						{
							oglSubtractive=true;
    						gEngfuncs.pfnFillRGBA(x-26,y+1,53,12,0,0,0,250);
    						oglSubtractive=false;
    						gEngfuncs.pfnFillRGBA(x-25,y+2,(ent->curstate.frame/255)*50,10,0,255,0,255);
    						y-=ystep;
						}
						else if( seqinfo == 16)
						{
    						oglSubtractive=true;
    						gEngfuncs.pfnFillRGBA(x-26,y+1,53,12,0,0,0,250);
    						oglSubtractive=false;
    						gEngfuncs.pfnFillRGBA(x-25,y+2,(ent->curstate.frame/255)*101,10,255,255,0,255);
    						y-=ystep;
						}
					}
				}

				if(!cvar.rush && cvar.playerinfo)
				{
					if(vPlayers[i].hasbomb)
					{
						DrawHudStringCenter(x,y,yellow->r,yellow->g,yellow->b,"-Bomb Carrier-");
						y -= ystep;
					}
					if(vPlayers[i].vip)
					{
						DrawHudStringCenter(x,y,yellow->r,yellow->g,yellow->b,"-VIP-");
						y -= ystep;
					}
				}

/*				if(!cvar.rush && cvar.esp_line)
				{
					if(cvar.espteam || isEnemy(i))
					{
						DrawLines(displayCenterX,0,x,y,1,color->r,color->g,color->b,color->a);
						y -= ystep * 2;
					}
				}*/
			}
		}
	}
}

//********************************************************************************************************************************** 

void drawPlayerEsp(int ax)
{

	cl_entity_s *pEnt=gEngfuncs.GetEntityByIndex(ax); 

	cl_entity_s *pEnt2d=IEngineStudio.GetCurrentEntity();

	ColorEntry* color = PlayerColor(ax);
	ColorEntry* yellow = colorList.get(27);

	float vecScreen[2];

	const char* format_string; 
	const char* format_int;
	if (vPlayers[ax].visible) { format_string="%s";format_int="%i"; }
	else                      { format_string="%s";format_int="%i"; }

	float distance = vPlayers[ax].distance/22.0f;
	extern float fCurrentFOV;
	int   boxradius = (300.0*90.0) / (distance*fCurrentFOV);	 
	BOUND_VALUE(boxradius,1,200);
	int text_dist = (int)(boxradius);

	float distancebox = vPlayers[ax].distance/22.0f;
	extern float fCurrentFOVbox;
	int   boxradiusbox = (300.0*90.0) / (distancebox*fCurrentFOVbox);	 
	BOUND_VALUE(boxradiusbox,1,000);
	int text_distbox = (int)(boxradiusbox);

	if(cvar.miniradar)
	{
		if( cvar.espteam || isEnemy(ax))
		{
			drawMiniRadarPoint(vPlayers[ax].origin(),color->r,color->g,color->b,3,3,false);
		}
	}

	if(cvar.radar)
	{
		if( cvar.espteam || isEnemy(ax))
		{
			drawRadarPoint(vPlayers[ax].origin(),color->r,color->g,color->b,3,3,false);
		}
	}


	if( !CalcScreen(vPlayers[ax].origin(),vecScreen) ){ return; } 
	
	enum{ CHAR_HEIGHT = 13 }; 
	int ystep = CHAR_HEIGHT;

	int x = vecScreen[0];
	int y = vecScreen[1]-text_dist-CHAR_HEIGHT; 
	y = y-text_dist-CHAR_HEIGHT; 
	y-=12;

	/////////////////////////////////////////

/*	if(!cvar.rush && cvar.esp_box2d)
	{
		if(bIsValidEnt(ax))
		{	
			if(cvar.espteam || isEnemy(ax))
			{
				Draw2DBox(pEnt2d,vPlayers[ax].getEnt()->origin,text_distbox,color); // box 2d
			}
		}
	}

	if(!cvar.rush && cvar.esp_box3d)
	{
		if(bIsValidEnt(ax))
		{
			if(cvar.espteam || isEnemy(ax))
			{
				if(vPlayers[ax].getEnt()->curstate.sequence == 99 || vPlayers[ax].getEnt()->curstate.sequence == 100)
					Draw3DBox(pEnt,vPlayers[ax].getEnt()->origin,text_distbox,yellow);
				else
					Draw3DBox(pEnt,vPlayers[ax].getEnt()->origin,text_distbox,color);
			}
		}
	}

	if(!cvar.rush && cvar.esp_box3ds && cvar.cheatmode == 1)
	{
		if (g_Aimbot.iTargetID!=0)
		{
			if(cvar.espteam || isEnemy(ax))
			{
				if(vPlayers[ax].getEnt()->curstate.sequence == 99 || vPlayers[ax].getEnt()->curstate.sequence == 100)
					Draw3DBoxSpinn(pEnt,vPlayers[ax].getEnt()->origin,text_distbox,yellow);
				else
					Draw3DBoxSpinn(pEnt,vPlayers[ax].getEnt()->origin,text_distbox,color);
			}
		}
	}*/

	if(!cvar.rush && cvar.weapon==1 || (cvar.weapon==2 && idhook.FirstKillPlayer[ax]))
	{
	   	if(cvar.espteam || isEnemy(ax))
       	{
			const char* displayname = vPlayers[ax].getWeapon();
			DrawConStringCenter(x,y,color->r,color->g,color->b,displayname);
			y -= ystep;
		}
	}

	if (!cvar.rush && cvar.name==1 || (cvar.name==2 && idhook.FirstKillPlayer[ax]))
	{
	   if(cvar.espteam || isEnemy(ax))
       {
		   char displayname[32];
		   strncpy(displayname,vPlayers[ax].entinfo.name,30);
		   displayname[30] = 0;
		   DrawConStringCenter(x,y,color->r,color->g,color->b,format_string,displayname);
		   y -= ystep;
	   }
	}

	if (!cvar.rush && cvar.sequence==1 || (cvar.sequence==2 && idhook.FirstKillPlayer[ax]))
	{
		if(bIsValidEnt(ax))
		{
			if(cvar.espteam || isEnemy(ax))
			{
				int atype = getSeqInfo(ax);
				if (vPlayers[ax].getEnt()->curstate.gaitsequence==GAITSEQUENCE_RUNNING) 
				{ 
					DrawConStringCenter(x,y,yellow->r,yellow->g,yellow->b,"- RUNNING -");
					y -= ystep;
				}
				if (vPlayers[ax].getEnt()->curstate.gaitsequence==GAITSEQUENCE_STAND) 
				{ 
					DrawConStringCenter(x,y,yellow->r,yellow->g,yellow->b,"- STANDING -");
					y -= ystep;
				}
				if (vPlayers[ax].getEnt()->curstate.gaitsequence==GAITSEQUENCE_DUCK) 
				{ 
					DrawConStringCenter(x,y,yellow->r,yellow->g,yellow->b,"- DUCKING -");
					y -= ystep;
				}
				if (vPlayers[ax].getEnt()->curstate.gaitsequence==GAITSEQUENCE_WALK) 
				{ 
					DrawConStringCenter(x,y,yellow->r,yellow->g,yellow->b,"- WALKING -");
					y -= ystep;
				}
				if (vPlayers[ax].getEnt()->curstate.gaitsequence==GAITSEQUENCE_DUCKMOVE) 
				{ 
					DrawConStringCenter(x,y,yellow->r,yellow->g,yellow->b,"- DUCKMOVING -");
					y -= ystep;
				}
				if (vPlayers[ax].getEnt()->curstate.gaitsequence==GAITSEQUENCE_JUMP) 
				{ 
					DrawConStringCenter(x,y,yellow->r,yellow->g,yellow->b,"- JUMPING -");
					y -= ystep;
				}
				if(vPlayers[ax].getEnt()->curstate.sequence == 99 || vPlayers[ax].getEnt()->curstate.sequence == 100)
				{
					oglSubtractive=true;
					gEngfuncs.pfnFillRGBA(x-31,y+4,64,14,yellow->r,yellow->g,yellow->b,yellow->a);
					oglSubtractive=false;
					DrawConStringCenter(x,y,yellow->r,yellow->g,yellow->b,"-- HIT --");
					y -= ystep;
				}
				if(atype == 8)
				{
					DrawConStringCenter(x,y,yellow->r,yellow->g,yellow->b,"- THROWING -");
					y -= ystep;
				}
				if(atype == 32)
				{
					DrawConStringCenter(x,y,yellow->r,yellow->g,yellow->b,"- SHIELD TO SIDE -");
					y -= ystep;
				}
				if(atype == 64)
				{
					DrawConStringCenter(x,y,yellow->r,yellow->g,yellow->b,"- SHIELDED -");
					y -= ystep;
				}
				if(atype == 1)
				{
					DrawConStringCenter(x,y,yellow->r,yellow->g,yellow->b,"- SHOOTING -");
					y -= ystep;
				}
				if( atype == 2)
				{
					DrawConStringCenter(x,y,yellow->r,yellow->g,yellow->b,"- RELOADING -");
					y -= ystep;
				}
				if (atype==5 || atype== 16) 
				{ 
					DrawConStringCenter(x,y,yellow->r,yellow->g,yellow->b,"- PLANTING c4 -");
					y -= ystep;
				}
			}
		}
	}

	if (!cvar.rush && cvar.reloadmeter) 
	{
		if(bIsValidEnt(ax))
		{
			if(cvar.espteam || isEnemy(ax))
        	{
				int seqinfo = Cstrike_SequenceInfo[vPlayers[ax].getEnt()->curstate.sequence];
				if( seqinfo == 2)
				{
					oglSubtractive=true;
    				gEngfuncs.pfnFillRGBA(x-26,y+1,53,12,0,0,0,250);
    				oglSubtractive=false;
    				gEngfuncs.pfnFillRGBA(x-25,y+2,(vPlayers[ax].getEnt()->curstate.frame/255)*50,10,0,255,0,255);
    				y-=ystep;
				}
				else if( seqinfo == 16)
				{
    				oglSubtractive=true;
    				gEngfuncs.pfnFillRGBA(x-26,y+1,53,12,0,0,0,250);
    				oglSubtractive=false;
    				gEngfuncs.pfnFillRGBA(x-25,y+2,(vPlayers[ax].getEnt()->curstate.frame/255)*101,10,255,255,0,255);
    				y-=ystep;
				}
			}
		}
	}

	if(!cvar.rush && cvar.playerinfo)
	{
		if(vPlayers[ax].hasbomb)
		{
			DrawConStringCenter(x,y,yellow->r,yellow->g,yellow->b,"-Bomb Carrier-");
			y -= ystep;
		}
		if(vPlayers[ax].vip)
		{
			DrawConStringCenter(x,y,yellow->r,yellow->g,yellow->b,"-VIP-");
			y -= ystep;
		}
	}

/*	if (!cvar.rush && cvar.esp_line)
	{
	   if(cvar.espteam || isEnemy(ax))
       { 
		   if(vPlayers[ax].getEnt()->curstate.sequence == 99 || vPlayers[ax].getEnt()->curstate.sequence == 100)
			   DrawFillTriangle(x,y-text_dist,x-text_dist,y,x+text_dist,y,yellow->r,yellow->g,yellow->b,yellow->a);
		   else
			   DrawFillTriangle(x,y,x-text_dist,y-text_dist,x+text_dist,y-text_dist,color->r,color->g,color->b,color->a);
		   DrawLines(displayCenterX,0,x,y,1,color->r,color->g,color->b,color->a);
		   y -= ystep * 2;
	   }
	}*/
}

//********************************************************************************************************************************** 

void drawesp()
{
	if(cvar.entesp)
		DrawEntEsp();

	if(!cvar.esptype)
		PlayerEsp();

	if(cvar.esptype) //soundesp
	{
		for(int ax=0;ax<vPlayers.size();ax++)
			if(vPlayers[ax].isUpdated() && vPlayers[ax].getAlive())
			{
				drawPlayerEsp(ax);
				vPlayers[ax].SuspectNextOrigin();
			}
	}
}
