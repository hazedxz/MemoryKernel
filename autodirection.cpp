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

AutoDirection autodirection;
extern double pisobre180;
float relativeSpeed(void);

//**********************************************************************************************************************************

#define PM_NORMAL			0x00000000
#define PM_STUDIO_IGNORE	0x00000001		// Skip studio models
#define PM_STUDIO_BOX		0x00000002		// Use boxes for non-complex studio models (even in traceline)
#define PM_GLASS_IGNORE		0x00000004		// Ignore entities with non-normal rendermode
#define PM_WORLD_ONLY		0x00000008		// Only trace against the world

// Values for flags parameter of PM_TraceLine
#define PM_TRACELINE_ANYVISIBLE		0
#define PM_TRACELINE_PHYSENTSONLY	1

//**********************************************************************************************************************************

bool AutoDirection::wayFree1(float* from,float* to)
{
	pmtrace_t tr;
	gEngfuncs.pEventAPI->EV_SetTraceHull( 2 );
	gEngfuncs.pEventAPI->EV_PlayerTrace ( from, to, PM_NORMAL, -1, &tr );
	return ( tr.fraction == 1.0 ); 
}

//**********************************************************************************************************************************

bool AutoDirection::wayFree2(float* from,float* to)
{
	pmtrace_t tr;
	gEngfuncs.pEventAPI->EV_SetTraceHull ( 2 );
	gEngfuncs.pEventAPI->EV_PlayerTrace ( from, to, PM_STUDIO_BOX, -1, &tr );
	int iEntity = gEngfuncs.pEventAPI->EV_IndexFromTrace ( &tr );
	cl_entity_s* ent = gEngfuncs.GetEntityByIndex ( iEntity );
	if(!ent->player || ent->index == me.ent->index) return true;// true=libre
	return ( tr.fraction == 1.0 ); 
}

//**********************************************************************************************************************************

bool AutoDirection::wayFree3(float* from,float* to)
{
	pmtrace_t tr;
	gEngfuncs.pEventAPI->EV_SetTraceHull ( 2 );
	gEngfuncs.pEventAPI->EV_PlayerTrace ( from, to, PM_NORMAL, -1, &tr );
	return ( tr.fraction == 1.0 ); 
}

//**********************************************************************************************************************************

void AutoDirection::NextStepPos(float* nowpos,float* viewangles,float step,float* newpos)
{
	float dx,dy,dz,dxy;
	dx=0;
	dy=0;
	dz=0;
	dxy=step;

	if( viewangles[1]>90 && viewangles[1]<=180 )
		dx = dxy * -cos((180.0-viewangles[1])*pisobre180);
	else if( viewangles[1]>=0 && viewangles[1]<=90 )
		dx = dxy * cos(viewangles[1]*pisobre180);
	else if( viewangles[1]>=-90 && viewangles[1]<0 )
		dx = dxy * cos((-viewangles[1])*pisobre180);
	else if( viewangles[1]>=-180 && viewangles[1]<-90)
		dx = dxy * -cos((180.0+viewangles[1])*pisobre180);
	if( viewangles[1]>90 && viewangles[1]<=180 )
		dy = dxy * sin((180.0-viewangles[1])*pisobre180);
	else if( viewangles[1]>=0 && viewangles[1]<=90 )
		dy = dxy * sin(viewangles[1]*pisobre180);
	else if( viewangles[1]>=-90 && viewangles[1]<0 )
		dy = dxy * -sin((-viewangles[1])*pisobre180);
	else if( viewangles[1]>=-180 && viewangles[1]<-90)
		dy = dxy * -sin((180.0+viewangles[1])*pisobre180);

	newpos[0]=nowpos[0]+dx;
	newpos[1]=nowpos[1]+dy;
	newpos[2]=nowpos[2]+dz;
}

//**********************************************************************************************************************************

void AutoDirection::SetAngle(float* viewangles)
{
	if( viewangles[0]>180 )
		viewangles[0]=viewangles[0]-360;
	else if( viewangles[0]<-180 )
		viewangles[0]=viewangles[0]+360;	
	if( viewangles[1]>180 )
		viewangles[1]=viewangles[1]-360;
	else if( viewangles[1]<-180 )
		viewangles[1]=viewangles[1]+360;
	if( viewangles[2]>180 )
		viewangles[2]=viewangles[2]-360;
	else if( viewangles[2]<-180 )
		viewangles[2]=viewangles[2]+360;
}

//**********************************************************************************************************************************

bool AutoDirection::IsMyWayFree1(float step,float userangle)
{
	float src[3],src1[3],src2[3];
	float dst[3],dst1[3],dst2[3];
	float angles[3];
	bool free,free1,free2;
	src[0]=me.ent->origin[0];
	src[1]=me.ent->origin[1];
	src[2]=me.ent->origin[2];
	angles[0]=0;angles[2]=0;
	angles[1]=userangle;
	NextStepPos(src,angles,step,dst);
	angles[0]=0;angles[2]=0;
	angles[1]=userangle+90;
	NextStepPos(src,angles,cvar.direction_step,src1);
	angles[0]=0;angles[2]=0;
	angles[1]=userangle;
	NextStepPos(src1,angles,step,dst1);
	angles[0]=0;angles[2]=0;
	angles[1]=userangle-90;
	NextStepPos(src,angles,cvar.direction_step,src2);
	angles[0]=0;angles[2]=0;
	angles[1]=userangle;
	NextStepPos(src2,angles,step,dst2);
	free=wayFree1(src,dst);
	free1=wayFree1(src1,dst1);
	free2=wayFree1(src2,dst2);
	if( free&free1&free2 )return true;
	return false;
}

//**********************************************************************************************************************************

bool AutoDirection::IsMyWayFree2(float step,float userangle)
{
	float src[3],src1[3],src2[3];
	float dst[3],dst1[3],dst2[3];
	float angles[3];
	bool free,free1,free2;
	src[0]=me.ent->origin[0];
	src[1]=me.ent->origin[1];
	src[2]=me.ent->origin[2];
	angles[0]=0;angles[2]=0;
	angles[1]=userangle;
	NextStepPos(src,angles,step,dst);
	angles[0]=0;angles[2]=0;
	angles[1]=userangle+90;
	NextStepPos(src,angles,cvar.direction_step,src1);
	angles[0]=0;angles[2]=0;
	angles[1]=userangle;
	NextStepPos(src1,angles,step,dst1);
	angles[0]=0;angles[2]=0;
	angles[1]=userangle-90;
	NextStepPos(src,angles,cvar.direction_step,src2);
	angles[0]=0;angles[2]=0;
	angles[1]=userangle;
	NextStepPos(src2,angles,step,dst2);
	free=wayFree2(src,dst);
	free1=wayFree2(src1,dst1);
	free2=wayFree2(src2,dst2);
	if( free&free1&free2 )return true;
	return false;
}

//**********************************************************************************************************************************

inline void adjustAngle(float *angle){
	if( (*angle)>180 )(*angle)=(*angle)-360;
	else if( (*angle)<-180 )(*angle)=(*angle)+360;
}

//**********************************************************************************************************************************

bool AutoDirection::adjustMyDirection1(struct usercmd_s* usercmd)
{
	float userangle;
	float stepangle=0;// no hace falta inicializar..

    if(usercmd->forwardmove==0){
		if(usercmd->sidemove>=0){
			stepangle = 90;}
		else{
			stepangle = -90;}}
	else{
		if(usercmd->forwardmove>=0){
			stepangle = atan(usercmd->sidemove/usercmd->forwardmove);}
		else{
			stepangle = 180-atan(usercmd->sidemove/(-(usercmd->forwardmove)));}}

	/////////////////////////////////////////////////////
	//stepangle siempre es inicializado arriba..!!
	///////////////////////////////////////////////////////////
	userangle = usercmd->viewangles[1]-stepangle;
	adjustAngle(&userangle);
	float newangle;
	float newangle1,newangle2;
	float da;
	bool free1,free2;
	int step=cvar.action_step;
	if( IsMyWayFree1(step,userangle) )return false;

#define ANGLE_ADD 45
#define ANGLE_LIMIT 135
	for(da=ANGLE_ADD;da<=ANGLE_LIMIT;da=da+ANGLE_ADD){// no tiene sentido ser cero porque luego se debe sumar
		
		newangle1=userangle+da;
		adjustAngle(&newangle1);
		if( IsMyWayFree1(step,newangle1) ) 
			free1=true; 
		else free1=false;
		
		newangle2=userangle-da;
		adjustAngle(&newangle2);
		if( IsMyWayFree1(step,newangle2) )
			free2=true; 
		else free2=false;
		
		if( free1 && !free2 )goto aimnewangle1;
		if( !free1 && free2 )goto aimnewangle2;
		if( free1 && free2 )goto aimnewangle1;
	}

	//////////////////////////////////////////////////
	// si los dos lados estan trabados..
	newangle=userangle-180;
	goto adjust;
	///////////////////////////////////
aimnewangle1:
	newangle=newangle1;
	goto adjust;
aimnewangle2:
	newangle=newangle2;
	goto adjust;
adjust:
	float angle;
	angle=newangle-usercmd->viewangles[1];
	if(angle>=180) angle-=360;
	if(angle<=-180) angle+=360;
	float fm,sm;
	fm = (float)cos(angle*pisobre180)*cvar.rush_step;
	sm = (float)-sin(angle*pisobre180)*cvar.rush_step;
	usercmd->forwardmove = fm;
	usercmd->sidemove = sm;
	return true;
}

//**********************************************************************************************************************************

bool AutoDirection::adjustMyDirection2(struct usercmd_s* usercmd)
{
	float userangle;
	float stepangle;

    if(usercmd->forwardmove==0){
		if(usercmd->sidemove>=0){
			stepangle = 90;}
		else{
			stepangle = -90;}}
	else{
		if(usercmd->forwardmove>=0){
			stepangle = atan(usercmd->sidemove/usercmd->forwardmove);}
		else{
			stepangle = 180-atan(usercmd->sidemove/(-(usercmd->forwardmove)));}}

	userangle = usercmd->viewangles[1]-stepangle;
	adjustAngle(&userangle);
	float newangle;
	float newangle1,newangle2;
	float da;
	bool free1,free2;
	int step=cvar.action_step;
	if( IsMyWayFree2(step,userangle) )return false;
	for(da=45;da<=135;da=da+45){
		newangle1=userangle+da;
		adjustAngle(&newangle1);
		if( IsMyWayFree2(step,newangle1) ) free1=true; else free1=false;
		newangle2=userangle-da;
		adjustAngle(&newangle2);
		if( IsMyWayFree2(step,newangle2) )free2=true; else free2=false;
		if( free1 && !free2 )goto aimnewangle1;
		if( !free1 && free2 )goto aimnewangle2;
		if( free1 && free2 )goto aimnewangle1;}
	newangle=userangle-180;
	goto adjust;
aimnewangle1:
	newangle=newangle1;
	goto adjust;
aimnewangle2:
	newangle=newangle2;
	goto adjust;
adjust:
	float angle;
	angle=newangle-usercmd->viewangles[1];
	if(angle>=180) angle-=360;
	if(angle<=-180) angle+=360;
	float fm,sm;
	fm = cvar.rush_step*cos(angle*pisobre180);
	sm = -cvar.rush_step*sin(angle*pisobre180);
	usercmd->forwardmove = fm;
	usercmd->sidemove = sm;
	return true;
}

//**********************************************************************************************************************************

bool AutoDirection::IsMyWayFree3(float step,float* viewangles)
{
	float src[3],src1[3],src2[3];
	float dst[3],dst1[3],dst2[3];
	float angles[3];
	bool free,free1,free2;
	src[0]=me.pmEyePos[0];
	src[1]=me.pmEyePos[1];
	src[2]=me.pmEyePos[2];
	angles[0]=0;angles[2]=0;
	angles[1]=viewangles[1];
	SetAngle(angles);
	NextStepPos(src,angles,step,dst);
	angles[0]=0;angles[2]=0;
	angles[1]=viewangles[1]+90;
	SetAngle(angles);
	NextStepPos(src,angles,cvar.direction_step,src1);
	angles[0]=0;angles[2]=0;
	angles[1]=viewangles[1];
	SetAngle(angles);
	NextStepPos(src1,angles,step,dst1);
	angles[0]=0;angles[2]=0;
	angles[1]=viewangles[1]-90;
	SetAngle(angles);
	NextStepPos(src,angles,cvar.direction_step,src2);
	angles[0]=0;angles[2]=0;
	angles[1]=viewangles[1];
	SetAngle(angles);
	NextStepPos(src2,angles,step,dst2);
	free=wayFree3(src,dst);
	free1=wayFree3(src1,dst1);
	free2=wayFree3(src2,dst2);
	if( free&free1&free2 )return true;
	return false;
}

//**********************************************************************************************************************************

bool AutoDirection::adjustMyAngles(float* viewangles)
{
	float oldviews[3],newview1[3],newview2[3];
	float da;
	bool free1,free2;
	int step=30;
	oldviews[0]=viewangles[0];
	oldviews[1]=viewangles[1];
	oldviews[2]=viewangles[2];
	if( IsMyWayFree3(step,oldviews) )return false;
	for(da=15;da<=165;da=da+15)
	{
		newview1[0]=oldviews[0];
		newview1[1]=oldviews[1]+da;
		newview1[2]=oldviews[2];
		SetAngle(newview1);
		if( IsMyWayFree3(step,newview1) ) free1=true; else free1=false;

		newview2[0]=oldviews[0];
		newview2[1]=oldviews[1]-da;
		newview2[2]=oldviews[2];
		SetAngle(newview2);
		if( IsMyWayFree3(step,newview2) )free2=true; else free2=false;
		if( free1 && !free2 )goto aimnewview1;
		if( !free1 && free2 )goto aimnewview2;
		if( free1 && free2 )
				goto aimnewview1; 
	}
	viewangles[0]=oldviews[0];
	viewangles[1]=oldviews[1]-180;
	viewangles[2]=oldviews[2];
	SetAngle(viewangles);
	return true;
    aimnewview1:
	viewangles[0]=newview1[0];
	viewangles[1]=newview1[1];
	viewangles[2]=newview1[2];
	return true;
    aimnewview2:
	viewangles[0]=newview2[0];
	viewangles[1]=newview2[1];
	viewangles[2]=newview2[2];
	return true;
}

//**********************************************************************************************************************************

void AutoDirection::adjustJump(struct usercmd_s* usercmd){
	
	if (me.ent->curstate.usehull) return;	// in duck
	
	int auto_jump_h1=23;
	int auto_jump_h2=-28;
	int auto_jump_h3=0;
	int auto_jump_distance=cvar.jump_dist+20;
	bool free1,free2;
	float src[3],src1[3],src2[3],dst[3],dst1[3],dst2[3];
	float angles[3];
	src[0]=me.ent->origin[0];
	src[1]=me.ent->origin[1];
	src[2]=me.ent->origin[2];
	src1[0]=src[0];
	src1[1]=src[1];
	src1[2]=src[2]+auto_jump_h1;
	src2[0]=src[0];
	src2[1]=src[1];
	src2[2]=src[2]+auto_jump_h2;
	angles[0]=0;
	angles[1]=me.viewAngles[1];//usercmd->viewangles[1];
	angles[2]=0;
	NextStepPos(src,angles,auto_jump_distance,dst);
	dst1[0]=dst[0];
	dst1[1]=dst[1];
	dst1[2]=dst[2]+auto_jump_h1;
	dst2[0]=dst[0];
	dst2[1]=dst[1];
	dst2[2]=dst[2]+auto_jump_h3;
	free1=wayFree1(src1,dst1);
	free2=wayFree1(src2,dst2);	
	if( free1&&!free2 )
	{
		usercmd->buttons |= IN_JUMP;
		
		if ( (usercmd->buttons & IN_JUMP) && !(me.pmFlags & FL_ONGROUND) ) usercmd->buttons &= ~IN_JUMP;
	}
}

//**********************************************************************************************************************************

