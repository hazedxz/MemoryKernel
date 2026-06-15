/////
///// GYJ HOOK [Revision by ETK]
/////
///// By [boy_scout][boyscout_etk@hotmail.com]
/////
///// [2011][www.etalking.com.ar]
/////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "client.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AutoWay autoway;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float GetPointDistance(float* pos)
{	
	me.ent = gEngfuncs.GetLocalPlayer();
	double a = pos[0] - me.pmEyePos[0];
	double b = pos[1] - me.pmEyePos[1];
	double c = pos[2] - me.pmEyePos[2];
	return (float)sqrt(a*a + b*b + c*c);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CalcVec_MeToTarget(float *view)
{
	float EntViewOrg[3];
	VectorCopy(view, EntViewOrg);
	view[0] = EntViewOrg[0] - me.pmEyePos[0];
	view[1] = EntViewOrg[1] - me.pmEyePos[1];
	view[2] = EntViewOrg[2] - me.pmEyePos[2];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GetPointAngles(float *point,float *angles)
{
	float vec_to_target[3];
	VectorCopy(point, vec_to_target);
	CalcVec_MeToTarget(vec_to_target);
	VectorAngles(vec_to_target,angles);	
	angles[0] *= -1;
	if (angles[0]>180) angles[0]-=360;
	if (angles[1]>180) angles[1]-=360;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ChangeViewAngle(float *point, usercmd_s *usercmd)
{
	float aim_viewangles[3];
	float vec_to_target[3];
	VectorCopy(point, vec_to_target);
	CalcVec_MeToTarget(vec_to_target);
	VectorAngles(vec_to_target,aim_viewangles);	
	aim_viewangles[0] *= -1;
	if (aim_viewangles[0]>180) aim_viewangles[0]-=360;
	if (aim_viewangles[1]>180) aim_viewangles[1]-=360;
	VectorCopy(aim_viewangles, usercmd->viewangles);
	gEngfuncs.SetViewAngles (aim_viewangles);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool GetPointVisible(float *point)
{
	strace_t tr;
	tr.finished = false;
	TraceThickness(me.pmEyePos, point, 0, &tr);
	return tr.finished;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float CalcTwoAngle(float a,float b)
{
	float c=abs(a-b);
	if(c>180)
		return abs(c-360);
	else
		return c;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float CalcWayAngle(float *point,float *point1)
{
	gEngfuncs.GetViewAngles(me.viewAngles);
	float addvec[2];
	float dodgeDir[3];
	dodgeDir[0]=dodgeDir[1]=dodgeDir[2]=0;
	addvec[0] = point[0] - point1[0];
	addvec[1] = point[1] - point1[1];
	float dist = (float)sqrt(addvec[0]*addvec[0] + addvec[1]*addvec[1]);
	addvec[0] /= dist;
	addvec[1] /= dist;
	dodgeDir[0] -= addvec[0]; 
	dodgeDir[1] -= addvec[1];
	dodgeDir[2] = 0;
	float dodgeAngles[3];
	VectorAngles(dodgeDir,dodgeAngles);
	return  CalcTwoAngle(dodgeAngles[1],me.viewAngles[1]);
}

void AutoWay::CreateMove(usercmd_s *usercmd)
{
	if (Record) 
	{
		if (iWayLine > -1)
		{
			if (iWayPoint == waypointcount){Record = false;return;};
			if (iWayPoint == -1)
			{
				AddPoint();
			}
			else
			{
				float dist = GetPointDistance(way_line[iWayLine].point[iWayPoint].origin);
				if (dist >= cvar.routedist)
				{
					AddPoint();
				}
			}
		}
		return;
	}

	if(bContinueAutoWay)
	{
		if(iWayLine>-1 && iWayPoint>-1 && abs(way_line[iWayLine].point[iWayPoint].origin[2] - me.pmEyePos[2]) < 25 && GetPointVisible(way_line[iWayLine].point[iWayPoint].origin))
		{
			way_mode = WAY_START;
		}
		else
		{
			FindAnyWay(10000,false);
		}
		bContinueAutoWay=false;
	}	

	if (cvar.autoroute)
	{
		if (g_Aimbot.iTargetID!=0)
		{
			if(cvar.route_mode || currentWeaponID==WEAPON_KNIFE) 
			{
				iWayLine = -1; 
				iWayPoint = -1;
				way_mode = WAY_NONE;
				return;
			}
		}
		switch (way_mode)
		{
			case WAY_NONE:
				{
					FindFowardWay(-1);
					if (iWayPoint > -1 && iWayLine > -1)
					{
						GotoWayPoint(way_line[iWayLine].point[iWayPoint].origin, usercmd);
						way_mode = WAY_FROM;
					}
				break;
				}
			case WAY_START:
				{
					GotoWayPoint(way_line[iWayLine].point[iWayPoint].origin, usercmd);
					way_mode = WAY_FROM;
				}
				break;
			case WAY_FROM:
				{
					if (((way_direction == WAY_ASC) && (iWayPoint == way_line[iWayLine].count - 1)) || ((way_direction == WAY_DESC) && (iWayPoint == 0)))
					{
						FindFowardWay(iWayLine);
						if (iWayPoint > -1 && iWayLine > -1)
						{
							GotoWayPoint(way_line[iWayLine].point[iWayPoint].origin, usercmd);
							way_mode = WAY_FROM;
						}
						else
							way_mode = WAY_NONE;
						return;
					}
					
					if( WayMoveEnough(way_line[iWayLine].point[iWayPoint].origin, usercmd) )
					{
						int i = iWayPoint;
						switch (way_direction)
						{
							case WAY_ASC:
							{
								i++;
								if(i==way_line[iWayLine].count - 1 && g_Aimbot.iTargetID == 0)
								{
									ChangeViewAngle(way_line[iWayLine].point[i].origin, usercmd);
								}
							}
							break;
							case WAY_DESC:
							{
								i--;
								if(i==0 && g_Aimbot.iTargetID == 0)
								{
									ChangeViewAngle(way_line[iWayLine].point[i].origin, usercmd); 
								}
							}
							break;
						}
						iWayPoint = i;
						GotoWayPoint(way_line[iWayLine].point[iWayPoint].origin, usercmd);
					}
					return;
				}
				break;
			case WAY_END:
				{
					iWayLine = -1; 
					iWayPoint = -1;
					way_mode = WAY_NONE; 
				}
				break;
		}
	}
	else
	{
		iWayLine = -1; 
		iWayPoint = -1;
		way_mode = WAY_NONE; 
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AutoWay::GotoWayPoint(float *point, usercmd_s *usercmd)
{
	gEngfuncs.GetViewAngles(me.viewAngles);
	float addvec[2];
	float dodgeDir[3];
	dodgeDir[0]=dodgeDir[1]=dodgeDir[2]=0;
	addvec[0] = me.pmEyePos[0] - point[0];
	addvec[1] = me.pmEyePos[1] - point[1];
	float dist = GetPointDistance(point);
	addvec[0] /= dist;
	addvec[1] /= dist;
	dodgeDir[0] -= addvec[0]; 
	dodgeDir[1] -= addvec[1];
	dodgeDir[2] = 0;
	float dodgeAngles[3];
	VectorAngles(dodgeDir,dodgeAngles);
	float angle = dodgeAngles[1] - me.viewAngles[1];
	while(angle<0)   { angle+=360; }
	while(angle>360) { angle-=360; }
	me_forwardmove = (float)cos(angle*(3.1415926/180.0))*dist;
	me_sidemove = (float)-sin(angle*(3.1415926/180.0))*dist;
	usercmd->forwardmove += me_forwardmove;
	usercmd->sidemove += me_sidemove;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool AutoWay::WayMoveEnough(float *point, usercmd_s *usercmd)
{
	gEngfuncs.GetViewAngles(me.viewAngles);
	float addvec[2];
	float dodgeDir[3];
	dodgeDir[0]=dodgeDir[1]=dodgeDir[2]=0;
	addvec[0] = me.pmEyePos[0] - point[0];
	addvec[1] = me.pmEyePos[1] - point[1];
	float dist = GetPointDistance(point);
	addvec[0] /= dist;
	addvec[1] /= dist;
	dodgeDir[0] -= addvec[0]; 
	dodgeDir[1] -= addvec[1];
	dodgeDir[2] = 0;
	float dodgeAngles[3];
	VectorAngles(dodgeDir,dodgeAngles);
	float angle = dodgeAngles[1] - me.viewAngles[1];
	while(angle<0)   { angle+=360; }
	while(angle>360) { angle-=360; }
	me_forwardmove = (float)cos(angle*(3.1415926/180.0))*dist;
	me_sidemove = (float)-sin(angle*(3.1415926/180.0))*dist;
	usercmd->forwardmove = me_forwardmove*2.5f;
	usercmd->sidemove = me_sidemove*2.5f;
	if( usercmd->forwardmove>0-230 && usercmd->forwardmove<230 && usercmd->sidemove>0-230 && usercmd->sidemove<230)
		return true;
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AutoWay::FindFowardWay(int lastway) 
{
	float angles[3];
	float dist1;
	float dist;
	float minangles=50;  
	float minwayangles=30; 
	float pointangles;
	float wayangle;
	iWayLine = -1;
	iWayPoint = -1;
	int i;
	for(i = 0; i < waycount ; i++)
	{
		if (way_line[i].enabled && i!=lastway)
		{
			float mindist=cvar.routefinddist;
			for(int j = 0; j < way_line[i].count; j++)
			{
				dist = GetPointDistance(way_line[i].point[j].origin);
				if(dist < mindist)
				{
					if (abs(way_line[i].point[j].origin[2] - me.pmEyePos[2]) < 25)
					{
						GetPointAngles(way_line[i].point[j].origin, angles);
						pointangles = CalcTwoAngle(me.viewAngles[1],angles[1]);
						if (GetPointVisible(way_line[i].point[j].origin) && pointangles<=50)
						{
							if (j > 0 && j < way_line[i].count - 1)
							{
								dist1 = GetPointDistance(way_line[i].point[j+1].origin);
								if(dist1>=dist)
								{
									wayangle=CalcWayAngle(way_line[i].point[j].origin,way_line[i].point[j+1].origin);
									if(wayangle<minwayangles)
									{
											minwayangles = wayangle;
											way_direction = WAY_ASC;
											iWayLine = i;
											iWayPoint = j;
									}
								}
								else
								{
									wayangle=CalcWayAngle(way_line[i].point[j].origin,way_line[i].point[j-1].origin);
									if(wayangle<minwayangles)
									{
											minwayangles = wayangle;
											way_direction = WAY_DESC;
											iWayLine = i;
											iWayPoint = j;
									}
								}
							}
							else if(j==0)
							{
								dist1 = GetPointDistance(way_line[i].point[j+1].origin);
								if(dist1>=dist)
								{
									wayangle=CalcWayAngle(way_line[i].point[j].origin,way_line[i].point[j+1].origin);
									if(wayangle<minwayangles)
									{
											minwayangles = wayangle;
											way_direction = WAY_ASC;
											iWayLine = i;
											iWayPoint = j;
									}
								}
							}
							else if(j==way_line[i].count - 1)
							{
								dist1 = GetPointDistance(way_line[i].point[j-1].origin);
								if(dist1>=dist)
								{
									wayangle=CalcWayAngle(way_line[i].point[j].origin,way_line[i].point[j-1].origin);
									if(wayangle<minwayangles)
									{
											minwayangles = wayangle;
											way_direction = WAY_DESC;
											iWayLine = i;
											iWayPoint = j;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	if(iWayLine!=-1 && iWayPoint!=-1)return;

	float angles1[3];
	minangles=50;  
	minwayangles=20;
	iWayLine = -1;
	iWayPoint = -1;

	for(i = 0; i < waycount ; i++)
	{
		if (way_line[i].enabled && i!=lastway)
		{
			float mindist=230;
			for(int j = 0; j < way_line[i].count; j++)
			{
				dist = GetPointDistance(way_line[i].point[j].origin);
				if(dist < mindist)
				{
					if (abs(way_line[i].point[j].origin[2] - me.pmEyePos[2]) < 25)
					{
						GetPointAngles(way_line[i].point[j].origin, angles);
						pointangles = CalcTwoAngle(me.viewAngles[1],angles[1]);
						if (GetPointVisible(way_line[i].point[j].origin) && pointangles<=50)
						{
							if (j > 0 && j < way_line[i].count - 1)
							{
								dist1 = GetPointDistance(way_line[i].point[j+1].origin);
								if(dist1>=dist)
								{
									GetPointAngles(way_line[i].point[j + 1].origin, angles1);
									wayangle=CalcTwoAngle(angles1[1],angles[1]);
									if(wayangle<minwayangles && CalcTwoAngle(me.viewAngles[1],angles1[1])<=50)
									{
											mindist=dist;
											minwayangles = wayangle;
											way_direction = WAY_ASC;
											iWayLine = i;
											iWayPoint = j;
									}
								}
								else
								{
									GetPointAngles(way_line[i].point[j - 1].origin, angles1);
									wayangle=CalcTwoAngle(angles1[1],angles[1]);
									if(wayangle<minwayangles && CalcTwoAngle(me.viewAngles[1],angles1[1])<=50)
									{
											mindist=dist;
											minwayangles = wayangle;
											way_direction = WAY_DESC;
											iWayLine = i;
											iWayPoint = j;
									}
								}
							}
							else if(j==0)
							{
								dist1 = GetPointDistance(way_line[i].point[j+1].origin);
								if(dist1>=dist)
								{
									GetPointAngles(way_line[i].point[j + 1].origin, angles1);
									wayangle=CalcTwoAngle(angles1[1],angles[1]);
									if(wayangle<minwayangles && CalcTwoAngle(me.viewAngles[1],angles1[1])<=50)
									{
											mindist=dist;
											minwayangles = wayangle;
											way_direction = WAY_ASC;
											iWayLine = i;
											iWayPoint = j;
									}
								}
							}
							else if(j==way_line[i].count - 1)
							{
								dist1 = GetPointDistance(way_line[i].point[j-1].origin);
								if(dist1>=dist)
								{
									GetPointAngles(way_line[i].point[j - 1].origin, angles1);
									wayangle=CalcTwoAngle(angles1[1],angles[1]);
									if(wayangle<minwayangles  && CalcTwoAngle(me.viewAngles[1],angles1[1])<=50)
									{
											mindist=dist;
											minwayangles = wayangle;
											way_direction = WAY_DESC;
											iWayLine = i;
											iWayPoint = j;
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AutoWay::LoadWay(char * sfilename)
{
	Record = false;
	char tfilename[256];
	if(sfilename[0]=='\0')
	{
		strcpy(levelname, gEngfuncs.pfnGetLevelName() + 5);
		levelname[strlen(levelname)-4] = 0;
		sprintf(tfilename, "gyj/%s.route",levelname); 
		sprintf(filename, "%s%s", ogcdir, tfilename);
	}
	else  
	{
		sprintf(tfilename, "gyj/%s.route",sfilename); 
		sprintf(filename, "%s%s", ogcdir, tfilename);
	}
	ZeroMemory(way_line, sizeof(way_line));
	ifstream ifs(filename);
    while (ifs.good())
    {
        char buf[1024] = {0};
        ifs.getline(buf, sizeof(buf));
        cout << buf << endl;
		int i,j;
		float f1=0,f2=0,f3=0;
		if(sscanf(buf,"way(%d)(%d):%f,%f,%f",&i,&j,&f1,&f2,&f3))
		{	
			if(f1!=0&&f2!=0&&f3!=0)
			{
				way_line[i].point[j].origin[0]=f1;
				way_line[i].point[j].origin[1]=f2;
				way_line[i].point[j].origin[2]=f3;
				way_line[i].enabled = true;
				way_line[i].count ++;
			}
		}
    }
    ifs.close();
	
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AutoWay::SaveWay()
{
	char tfilename[256];
	strcpy(levelname, gEngfuncs.pfnGetLevelName() + 5);
	levelname[strlen(levelname)-4] = 0;
	sprintf(tfilename, "gyj/%s.route", levelname);
	sprintf(filename, "%s%s", ogcdir, tfilename);
	char waypoint[256];
	remove(filename); 
	ofstream ofs(filename, ios::binary | ios::app);
	for(int i = 0; i < waycount ; i++)
	{
		if (way_line[i].enabled)
		{
			for(int j = 0; j < way_line[i].count; j++)
			{
				sprintf(waypoint, "way(%d)(%d):%f,%f,%f",i,j,way_line[i].point[j].origin[0],way_line[i].point[j].origin[1],way_line[i].point[j].origin[2]);
				ofs << waypoint << (char)0x0D << (char)0x0A;
			}
		}
	}
	ofs.close();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AutoWay::AddPoint()
{
	if (iWayLine > -1)
	{
		iWayPoint ++;
		if (iWayPoint == waypointcount)
		{
			iWayPoint = waypointcount - 1; 
			Record = false; 
			return;
		}
		VectorCopy(me.pmEyePos, way_line[iWayLine].point[iWayPoint].origin);
		way_line[iWayLine].count ++;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AutoWay::DrawWay()  
{
	if(cvar.rush > 0.0) return;
	
	if (!me.alive) return;

	if (way_mode == WAY_NONE && !Record)
	{	
		FindFowardWay(-1);
	}

	ColorEntry* color;
	ColorEntry* color2;

	float vecScreen[2];

	for(int i = 0; i < waycount ; i++)
	{
		if (way_line[i].enabled)
		{
			for(int j = 0; j < way_line[i].count; j++)
			{
				float dist = GetPointDistance(autoway.way_line[i].point[j].origin);

				vec3_t vecPoint;
				vecPoint[0] =  way_line[i].point[j].origin[0];
				vecPoint[1] =  way_line[i].point[j].origin[1];
				vecPoint[2] =  way_line[i].point[j].origin[2] - 35;

				if (way_direction == WAY_ASC)
				{
					if (j >= iWayPoint && i == iWayLine)
					{
						color = colorList.get(30);
					}
					else
					{
						color = colorList.get(26);
					}
				}
				else if (way_direction == WAY_DESC)
				{
					if (j <= iWayPoint && i == iWayLine)
					{
						color = colorList.get(30);
					}
					else
					{
						color = colorList.get(26);
					}
				}

				if (cvar.route_draw == 1)
				{
				    if (dist < 800)
					{
					    if (CalcScreen(vecPoint,vecScreen))
						{
						    int x = vecScreen[0];
						    int y = vecScreen[1];

						    DrawHudString2(x, y, color->r, color->g, color->b, "*");
						
						    if(j==0 || j==way_line[i].count-1) 
							{
							    color2 = colorList.get(30);

							    DrawHudString2(x, y - 14, color2->r, color2->g, color2->b , "%i", i + 1); 
							}
						}
					}
				}
				if (cvar.route_draw == 2)
				{
					if (dist < 800)
					{
					    if (j > 0 && j%1 == 0)
						{
						    vec3_t vecBegin,vecEnd;
						    VectorCopy(autoway.way_line[i].point[j-1].origin,vecBegin);
						    vecBegin[2] -= 37;
						    VectorCopy(autoway.way_line[i].point[j].origin,vecEnd);
						    vecEnd[2] -= 37;
										
						    DrawStrippledVectorLine(vecBegin,vecEnd,1,1,0x00ff,color);
						}
						if (CalcScreen(vecPoint,vecScreen))
						{
						    int x = vecScreen[0];
						    int y = vecScreen[1];
						
						    if(j==0 || j==way_line[i].count-1) 
							{
							    color2 = colorList.get(30);

							    DrawHudString2(x-5, y - 14, color2->r, color2->g, color2->b , "%i", i + 1); 
							}
						}
					}
				}
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AutoWay::ClearAllWay()
{
	Record = false;
	ZeroMemory(way_line, sizeof(way_line));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AutoWay::ClearOneWay(int index)
{
	if ( index > -1 && index <= waycount)
	{
		Record = false;
		iWayLine = index;
		iWayPoint = -1;
		way_line[iWayLine].enabled = false;
		way_line[iWayLine].count = 0;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AutoWay::RecordOneWayStart(int index)
{
	if ( index > -1 && index <= waycount)
	{
		iWayLine = index;
		ClearOneWay(iWayLine);
		way_line[iWayLine].enabled = true;
		way_line[iWayLine].count = 0;
		Record = true;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AutoWay::RecordAnyWayStart()
{
	iWayLine=waycount;
	for(int i=0;i<waycount;i++)
	{
		if (!way_line[i].enabled)
		{
			iWayLine = i;
			break;
		}
	}
	iWayPoint=-1;
	way_line[iWayLine].enabled = true;
	way_line[iWayLine].count = 0;
	Record = true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AutoWay::RecordWayStop()
{
	Record = false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AutoWay::FindAnyWay(float pointdist,bool userand) 
{
	iWayLine = -1;
	iWayPoint = -1;
	int iWayLine1 = -1;
	int iWayPoint1 = -1;
	float mindist=pointdist; 
	for(int i=0;i<waycount;i++)
	{
		if (way_line[i].enabled)
		{
			if(way_line[i].count>12)
			{
				for(int j = 0; j < way_line[i].count; j++)
				{
					if(GetPointVisible(way_line[i].point[j].origin))
					{
						float dist = GetPointDistance(way_line[i].point[j].origin);
						if (dist < mindist && abs(way_line[i].point[j].origin[2] - me.pmEyePos[2]) < 25)
						{
							mindist = dist;
							iWayLine1 = i;
							iWayPoint1 = j;
						}
					}
				}
			}
		}
	}
	if(userand)
	{
		int iWayLine2 = -1;
		int iWayPoint2 = -1;
		mindist=pointdist;
		for(i=0;i<waycount;i++)
		{
			if(i==iWayLine1)continue;
			if (way_line[i].enabled)
			{
				if(way_line[i].count>12)
				{
					for(int j = 0; j < way_line[i].count; j++)
					{
						if(GetPointVisible(way_line[i].point[j].origin))
						{
							float dist = GetPointDistance(way_line[i].point[j].origin);
							if (dist < mindist && abs(way_line[i].point[j].origin[2] - me.pmEyePos[2]) < 25)
							{
								mindist = dist;
								iWayLine2 = i;
								iWayPoint2 = j;
							}
						}
					}
				}
			}
		}
		if(iWayLine2==-1)
		{
			iWayLine2 = iWayLine1;
			iWayPoint2 = iWayPoint1;
		}
		int iWayLine3 = -1;
		int iWayPoint3 = -1;
		mindist=pointdist;
		for(int i=0;i<waycount;i++)
		{
			if(i==iWayLine1||i==iWayLine2)continue;
			if (way_line[i].enabled)
			{
				if(way_line[i].count>12)
				{
					for(int j = 0; j < way_line[i].count; j++)
					{
						if(GetPointVisible(way_line[i].point[j].origin))
						{
							float dist = GetPointDistance(way_line[i].point[j].origin);
							if (dist < mindist && abs(way_line[i].point[j].origin[2] - me.pmEyePos[2]) < 25)
							{
								mindist = dist;
								iWayLine3 = i;
								iWayPoint3 = j;
							}
						}
					}
				}
			}
		}
		if(iWayLine3==-1)
		{
			iWayLine3 = iWayLine1;
			iWayPoint3 = iWayPoint1;
		}
		srand( (unsigned)time( NULL ) );
		int randnum=rand()%3+1;
		if(randnum==1)
		{
			iWayLine=iWayLine1;
			iWayPoint=iWayPoint1;
		}
		else if(randnum==2)
		{
			iWayLine=iWayLine2;
			iWayPoint=iWayPoint2;
		}
		else
		{
			iWayLine=iWayLine3;
			iWayPoint=iWayPoint3;
		}
	}
	else
	{
		iWayLine=iWayLine1;
		iWayPoint=iWayPoint1;
	}
	if(iWayLine>-1&&iWayPoint>-1)
	{
		if(iWayPoint<=way_line[iWayLine].count-iWayPoint)
			way_direction = WAY_ASC;
		else
			way_direction = WAY_DESC;
		way_mode = WAY_START;
	}
	else
	{
		way_mode = WAY_NONE;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AutoWay::WayTurn()
{
	if(way_mode==WAY_FROM||way_mode==WAY_START)
	{
		if(way_direction==WAY_ASC)
		{
			way_direction=WAY_DESC;
			if(iWayPoint>0)
				iWayPoint--;
		}
		else if(way_direction==WAY_DESC)
		{
			way_direction=WAY_ASC;
			if(iWayPoint<way_line[iWayLine].count - 1)
				iWayPoint++;
		}
		if(way_line[iWayLine].point[iWayPoint].origin[2] - me.pmEyePos[2] < 25 && way_line[iWayLine].point[iWayPoint].origin[2] - me.pmEyePos[2] > -100 && GetPointVisible(way_line[iWayLine].point[iWayPoint].origin))
			way_mode = WAY_START;
		else
		{
			iWayLine = -1;
			iWayPoint = -1;
			way_mode = WAY_NONE;
			FindAnyWay(10000,false);
		}
	}
	else
	{
		iWayLine = -1;
		iWayPoint = -1;
		way_mode = WAY_NONE;
		FindAnyWay(10000,false);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AutoWay::drawRadarsPoints()
{
	for(int i = 0; i < waycount ; i++)
	{
		if (way_line[i].enabled)
		{
			for(int j = 0; j < way_line[i].count; j++)
			{
				if(!(j%5))
				{
//					if(cvar.radar)drawRadarPoint(ways[i][j].point,255,255,255,3,3,false); //not wanted not used for speedmode
					if(cvar.miniradar)drawMiniRadarPoint(autoway.way_line[i].point[j].origin,255,255,255,3,3,false);
				}
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void func_route_load()
{
	if(cmd.argS(1).empty())
	{
		autoway.LoadWay("");
	}
	else
	{
		char* sfilename = cmd.argC(1);
		autoway.LoadWay(sfilename);
	}
}

//**********************************************************************************************************************************

void func_route_save()
{
	autoway.SaveWay();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void func_route_add_point()
{
	autoway.AddPoint();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void func_route_record_start()
{
	autoway.RecordAnyWayStart();
}

//**********************************************************************************************************************************

void func_route_record_line()
{
	int index = cmd.argI(1) - 1; 
	autoway.RecordOneWayStart(index);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void func_route_clear_line()
{
	int index = cmd.argI(1) - 1; 
	autoway.ClearOneWay(index);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void func_route_clear()
{
	autoway.ClearAllWay();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void func_route_record_stop()
{
	autoway.RecordWayStop();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void func_route_record_add()
{
	autoway.AddPoint();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AutoWay::commands()
{
	cmd.AddCommand( "route_load", func_route_load);
	cmd.AddCommand( "route_save", func_route_save);
	cmd.AddCommand( "route_record_start", func_route_record_start);
	cmd.AddCommand( "route_record_line", func_route_record_line);
	cmd.AddCommand( "route_clear_line", func_route_clear_line);
	cmd.AddCommand( "route_clear", func_route_clear);
	cmd.AddCommand( "route_record_stop", func_route_record_stop);
	cmd.AddCommand( "route_record_add", func_route_record_add);
}

int iTurnMove=0;
int iJumpMove=0;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AutoWay::Autodir(struct usercmd_s* usercmd)
{
	if(cvar.rush && !me.infrozentime && (cvar.auto_jump || cvar.auto_direction) && (usercmd->buttons&IN_FORWARD||usercmd->buttons&IN_BACK||usercmd->buttons&IN_MOVELEFT||usercmd->buttons&IN_MOVERIGHT))
	{
		if(sqrt(me.pmVelocity[0]*me.pmVelocity[0] + me.pmVelocity[1]*me.pmVelocity[1])<cvar.jump_dist)
		{
			iJumpMove++;
			if(iJumpMove>=4) 
			{
				if(cvar.auto_jump)
					usercmd->buttons |= IN_JUMP;
				iJumpMove=0;
			}

			iTurnMove++;
			if(iTurnMove>=4)
			{
				iTurnMove=0;
				if(cvar.auto_direction && g_Aimbot.iTargetID == 0)
				{
					me.viewAngles[1] += 90;
					if( me.viewAngles[1]>360.0 ) 
						me.viewAngles[1] -= 360.0;
					gEngfuncs.SetViewAngles(me.viewAngles);
					autoway.WayTurn();
				}
			}
		}
		else
		{
			iTurnMove=0;
			iJumpMove=0;
		}
	}
}