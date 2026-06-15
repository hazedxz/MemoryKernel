#include "client.h"

StrafeBot Strafebot;

static bool balance_bh = false;
#define PLAYER_MAX_SAFE_FALL_SPEED	580// approx 20 feet
static bool rand_strafe;
static float fMaxPspeed = 0.0;
float FrameCnt;
float FpsCnt;
float InterpFps;
float PreStrafe;
float JumpOff;

//***************************************************************************

bool Strafe = false;

bool Fastrun = false;

bool Gstrafe = false;

bool StrafeBhop = false;

bool Jumpbug = false;

//***************************************************************************

void func_strafe_on() 
{
	Strafe = true; 
}

void func_strafe_off()
{
	Strafe = false; 
}

void func_jumpbug_on() 
{
	Jumpbug = true;
}

void func_jumpbug_off()
{
	Jumpbug = false;
}
void func_bhop_on() 
{
	StrafeBhop = true;
}

void func_bhop_off()
{
	StrafeBhop = false;
}

void func_gstrafe_on() 
{
	Gstrafe = true;
}

void func_gstrafe_off()
{
	Gstrafe = false;
}

void func_fastrun_on() 
{
	Fastrun = true;
}

void func_fastrun_off()
{
	Fastrun = false;
}

//***************************************************************************

void StrafeBot::commands()
{
	cmd.AddCommand( "strafe_on", func_strafe_on);
	cmd.AddCommand( "strafe_off", func_strafe_off);

	cmd.AddCommand( "bhop_on", func_bhop_on);
	cmd.AddCommand( "bhop_off", func_bhop_off);

	cmd.AddCommand( "gstrafe_on", func_gstrafe_on);
	cmd.AddCommand( "gstrafe_off", func_gstrafe_off);

	cmd.AddCommand( "jumpbug_on", func_jumpbug_on);
	cmd.AddCommand( "jumpbug_off", func_jumpbug_off);

	cmd.AddCommand( "fastrun_on", func_fastrun_on);
	cmd.AddCommand( "fastrun_off", func_fastrun_off);
}

//***************************************************************************

bool BindStrafe = true;
bool UnBindStrafe = false;

bool BindBhop = true;
bool UnBindBhop = false;

bool BindGstrafe = true;
bool UnBindGstrafe = false;

bool BindSlowDown = true;
bool UnBindSlowDown = false;

bool BindJumpBug = true;
bool UnBindJumpBug = false;

bool BindFastRun = true;
bool UnBindFastRun = false;

bool RunOnce = true;

//**********************************************************************************************************************************

void Bind()
{
	if(cvar.strafehack && BindStrafe)
	{
		cmd.exec("bindstrafe");
		BindStrafe = false;
		UnBindStrafe = true;
	}
	if(!cvar.strafehack && UnBindStrafe)
	{
		cmd.exec("unbindstrafe");
		BindStrafe = true;
		UnBindStrafe = false;
	}
	if(cvar.bhop && BindBhop)
	{
		cmd.exec("bindbhop");
		BindBhop = false;
		UnBindBhop = true;
	}
	if(!cvar.bhop && UnBindBhop)
	{
		cmd.exec("unbindbhop");
		BindBhop = true;
		UnBindBhop = false;
	}
	if(cvar.groundstrafe && BindGstrafe)
	{
		cmd.exec("bindgstrafe");
		BindGstrafe = false;
		UnBindGstrafe = true;
	}
	if(!cvar.groundstrafe && UnBindGstrafe)
	{
		cmd.exec("unbindgstrafe");
		BindGstrafe = true;
		UnBindGstrafe = false;
	}
	if(cvar.slowdown && BindSlowDown)
	{
		cmd.exec("bindslowdown");
		BindSlowDown = false;
		UnBindSlowDown = true;
	}
	if(!cvar.slowdown && UnBindSlowDown)
	{
		cmd.exec("unbindslowdown");
		BindSlowDown = true;
		UnBindSlowDown = false;
	}
	if(cvar.jumpbug && BindJumpBug)
	{
		cmd.exec("bindjumpbug");
		BindJumpBug = false;
		UnBindJumpBug = true;
	}
	if(!cvar.jumpbug && UnBindJumpBug)
	{
		cmd.exec("unbindjumpbug");
		BindJumpBug = true;
		UnBindJumpBug = false;
	}

	if(cvar.fastrun && BindFastRun)
	{
		cmd.exec("bindfastrun");
		BindFastRun = false;
		UnBindFastRun = true;
	}
	if(!cvar.fastrun && UnBindFastRun)
	{
		cmd.exec("unbindfastrun");
		BindFastRun = true;
		UnBindFastRun = false;
	}
	if(RunOnce)
	{
		cmd.exec("alias +strafe \"strafe_on\"");
		cmd.exec("alias -strafe \"strafe_off\"");
		cmd.exec("alias +bhop \"bhop_on\"");
		cmd.exec("alias -bhop \"bhop_off\"");
		cmd.exec("alias +gstrafe \"gstrafe_on\"");
		cmd.exec("alias -gstrafe \"gstrafe_off\"");
		cmd.exec("alias +jumpbug \"jumpbug_on\"");
		cmd.exec("alias -jumpbug \"jumpbug_off\"");
		cmd.exec("alias +fastrun \"fastrun_on\"");
		cmd.exec("alias -fastrun \"fastrun_off\"");
		cmd.exec("alias Speed01 \"wavspeed 0.1;.wait;.wait;alias Speed+ Speed02;alias Speed- Speed01\"");
		cmd.exec("alias Speed02 \"wavspeed 0.2;.wait;.wait;alias Speed+ Speed03;alias Speed- Speed01\"");
		cmd.exec("alias Speed03 \"wavspeed 0.3;.wait;.wait;alias Speed+ Speed04;alias Speed- Speed02\"");
		cmd.exec("alias Speed04 \"wavspeed 0.4;.wait;.wait;alias Speed+ Speed05;alias Speed- Speed03\"");
		cmd.exec("alias Speed05 \"wavspeed 0.5;.wait;.wait;alias Speed+ Speed06;alias Speed- Speed04\"");
		cmd.exec("alias Speed06 \"wavspeed 0.6;.wait;.wait;alias Speed+ Speed07;alias Speed- Speed05\"");
		cmd.exec("alias Speed07 \"wavspeed 0.7;.wait;.wait;alias Speed+ Speed08;alias Speed- Speed06\"");
		cmd.exec("alias Speed08 \"wavspeed 0.8;.wait;.wait;alias Speed+ Speed09;alias Speed- Speed07\"");
		cmd.exec("alias Speed09 \"wavspeed 0.9;.wait;.wait;alias Speed+ Speed1 ;alias Speed- Speed08\"");
		cmd.exec("alias Speed1 \"wavspeed 1;.wait;.wait;alias Speed+ Speed1;alias Speed- Speed09\"");
		cmd.exec("alias Speed+ \"Speed1\"");
		cmd.exec("alias Speed- \"Speed1\"");
		
		RunOnce = false;
	}
}

//**********************************************************************************************************************************

inline float EndSpeed(float StartSpeed,float gravity,float frametime,float distance)
{
	while(distance>0)
	{
		StartSpeed+=gravity*frametime;
		float dist=StartSpeed*frametime;
		distance-=dist;
	}
	return StartSpeed;
}

//**********************************************************************************************************************************

inline float interp(float s1,float s2,float s3,float f1,float f3)
{
	if(s2==s1)return f1;
	if(s2==s3)return f3;
	if(s3==s1)return f1;
	return f1+((s2-s1)/(s3-s1))*((f3-f1)/*/1*/);
}

//**********************************************************************************************************************************

float Damage()
{
	Vector start=me.pmvOrigin;
	vec3_t vForward, vecEnd;
	float va[3];
	GetViewAngles(va);
	gEngfuncs.pfnAngleVectors(va, vForward, NULL, NULL);
	vecEnd[0] = start[0] + vForward[0] * 8192; vecEnd[1] = start[1] + vForward[1] * 8192; vecEnd[2] = start[2] + vForward[2] * 8192;
	pmtrace_t *trace = PM_TraceLine(start, vecEnd, 1, 2, -1);
	float fDistance=((start.z)-(trace->endpos.z))-(me.pmiUseHull==0?(36):(18));
	float endSpeed=EndSpeed(me.pmflFallSpeed,800,1/1000.0f,fDistance);
	if(interp(504.80001,endSpeed,1000,1,100) > 0)
		return interp(504.80001,endSpeed,1000,1,100);
	else return 0;
}

//**********************************************************************************************************************************

inline float EdgeDistance(){
#define TraceEdge(x,y){\
	Vector start=me.pmvOrigin;\
	start[2]-=0.1f;\
	Vector end=start;\
	end[1]+=x*mind;\
	end[0]+=y*mind;\
	pmtrace_s* t1 = PM_TraceLine(end,start,1,me.pmiUseHull,-1);\
	if(!(t1->startsolid))mind=(t1->endpos-start).Length2D();\
}
	float mind=250;
	TraceEdge(-1,0);
	TraceEdge(1,0);
	TraceEdge(0,1);
	TraceEdge(0,-1);
	TraceEdge(-1,-1);
	TraceEdge(1,1);
	TraceEdge(1,-1);
	TraceEdge(-1,1);
	/*if(mind == 250)
		return 0;*/
	return mind;
}

//**********************************************************************************************************************************

void StrafeBot::InitCreatemove(float frametime, struct usercmd_s *cmd)
{
	me.pmframeTime = frametime;

	if(cvar.strafehack == 1) 
		Strafebot.StrafeHacker(frametime,cmd,cvar.strafe_invisible,cvar.strafe_crazy);
	if(cvar.strafehack == 2) 
		Strafebot.StrafeHack(frametime, cmd);
	if(cvar.strafeautodir)
		Strafebot.AutoDir(cmd);
	if(cvar.fastrun == 1)
		Strafebot.FastRunner(cmd);
	if(cvar.fastrun == 2)
		Strafebot.FastRun(frametime, cmd);
	if(cvar.groundstrafe == 1)
		Strafebot.GroundStrafer(cmd);
	if(cvar.groundstrafe == 2)
		Strafebot.GroundStrafe(cmd);
	if(cvar.bhop == 1)
		Strafebot.Bhopper(frametime, cmd);
		if((GetClientTime() - me.flDuckTimeMax ) >= 0.8 && balance_bh == true)
		{
			gEngfuncs.pfnClientCmd("-duck");
			balance_bh = false;
		}
	if(cvar.bhop == 2)
		Strafebot.Bhop(frametime, cmd);
	if(cvar.jumpbug == 1)
		Strafebot.JumpBugger(frametime, cmd);
	if(cvar.jumpbug == 2)
		Strafebot.JumpBug(frametime, cmd);
	if(cvar.strafe_helper)
		if( me.pmfSpeed > 0 )
		{
			Strafebot.StrafeHelper(frametime,cmd);
		}
	if(cvar.fps_helper > 0)
		Speedbot.AdjustSpeed(((1/frametime)/cvar.fps_helper));
	if(me.bJumped && (me.pmFlags&FL_ONGROUND||me.pmMoveType == 5))
	{
		Vector endpos=me.pmvOrigin;
		endpos.z-=me.pmiUseHull==0?36.0:18.0;
		me.vt2=endpos;
		if(endpos.z==me.StartJumpPos.z)
		{
			Vector lj=endpos-me.StartJumpPos;
			float dist=lj.Length()+32.0625f+0.003613;
			if(dist>=200)
			{
				InterpFps = FpsCnt / FrameCnt;
				FpsCnt = 0;
				FrameCnt = 0;
				me.flJumpDist=dist;
				me.flJumpMessTime=GetClientTime()+7.0;
			}
		}
		me.bJumped=false;
	}
	if(!me.bJumped && (me.pmFlags&FL_ONGROUND) && cmd->buttons&IN_JUMP)
	{
		PreStrafe = me.pmfSpeed;
		if(EdgeDistance() !=250)
			JumpOff = EdgeDistance();
		else JumpOff = 0;
		me.StartJumpPos=me.pmvOrigin;
		me.StartJumpPos.z-=me.pmiUseHull==0?36.0:18.0;
		me.vt1=me.StartJumpPos;
		me.bJumped=true;
	}
	Bind();
}

//***************************************************************************

void StrafeBot::InitHud()
{
	if(me.bJumped)
	{
		FrameCnt += 1;
		FpsCnt += (1/me.pmframeTime);
	}
	if(cvar.show_kz)
	{
		static float Y = iStringHeight();
		if(me.flJumpMessTime > GetClientTime())
		{
			ColorEntry* color = colorList.get(32);
			register DWORD colors = 0xFF0000FF;
			float ft1[2];
			float ft2[2];
			gDrawFilledBoxAtLocation(me.vt1,colors,2);
			gDrawFilledBoxAtLocation(me.vt2,colors,2);
			DrawStrippledVectorLine(me.vt1,me.vt2,2,4,0xAAAA,color);
			if(CalcScreen(me.vt1,ft1))
			{
				gFont.drawString( true, ft1[0], ft1[1]-14, 255, 255, 255, "Start");
			}
			if(CalcScreen(me.vt2,ft2))
			{
				gFont.drawString( true, ft2[0], ft2[1]-14, 255, 255, 255, "Length: %.3f", me.flJumpDist);
			}
			gFont.drawString( true,screeninfo.iWidth / 2, screeninfo.iHeight * 0.22 + Y * 1.0, 255,0,255, "LongJump: %.3f", me.flJumpDist);
			gFont.drawString( true,screeninfo.iWidth / 2, screeninfo.iHeight * 0.22 + Y * 2.0, 255,0,255, "PreStrafe: %.3f", PreStrafe);
			gFont.drawString( true,screeninfo.iWidth / 2, screeninfo.iHeight * 0.22 + Y * 3.0, 255,0,255, "JumpOff: %.3f", JumpOff);
			gFont.drawString( true,screeninfo.iWidth / 2, screeninfo.iHeight * 0.22 + Y * 4.0, 255,0,255, "Fps: %.3f", InterpFps);
		}
		if(me.pmfSpeed == 0)
			fMaxPspeed = 0.0;
		if(me.pmfSpeed > fMaxPspeed)
			fMaxPspeed = me.pmfSpeed;
		gFont.drawString( true,screeninfo.iWidth / 2, screeninfo.iHeight * 0.22 + Y * 5.0, 255, 255, 255, "Speed: %.3f", me.pmfSpeed );
		gFont.drawString( true,screeninfo.iWidth / 2, screeninfo.iHeight * 0.22 + Y * 6.0, 255, 255, 255, "SpeedMax: %.3f", fMaxPspeed );
		gFont.drawString( true,screeninfo.iWidth / 2, screeninfo.iHeight * 0.22 + Y * 7.0, 255, 255, 255, "Height: %.3f", me.pmflHeight );
		gFont.drawString( true,screeninfo.iWidth / 2, screeninfo.iHeight * 0.22 + Y * 8.0, 255, 255, 255, "Fallspeed: %.3f", me.pmflFallSpeed );
		gFont.drawString( true,screeninfo.iWidth / 2, screeninfo.iHeight * 0.22 + Y * 9.0, 255, 255, 255, "GroundAngle: %.3f", me.pmflGroundAngle );
		int color[3];
		color[0] = 255;
		color[1] = 255;
		color[2] = 255;
		if(Damage() >= me.pmhealth)
		{
			color[0] = 255;
			color[1] = 0;
			color[2] = 0;
		}
		gFont.drawString( true,screeninfo.iWidth / 2, screeninfo.iHeight * 0.22 + Y * 10.0, color[0],color[1],color[2], "Damage: %.1f", Damage());
		gFont.drawString( true,screeninfo.iWidth / 2, screeninfo.iHeight * 0.22 + Y * 11.0, 255,0,EdgeDistance(), "Edge: %.3f", EdgeDistance());
	}
	else
		fMaxPspeed = 0.0;
}

//***************************************************************************

void StrafeBot::StrafeHack(float frametime, struct usercmd_s *cmd)
{
	if(Strafe && !(me.pmFlags & FL_ONGROUND) && (me.pmMoveType!=5) && !(cmd->buttons & IN_ATTACK))
	{
		float dir = 0.0f;

		int dir_value = cvar.strafe_dir;

		if(dir_value == 1)dir = 0 * PI / 180.0f;
		else if(dir_value == 2)	dir = 90 * PI / 180.0f;
		else if(dir_value == 3)	dir = 180 * PI / 180.0f;
		else if(dir_value == 4)	dir = -90 * PI / 180.0f;

		if(me.pmfSpeed < 15.0f)
		{
			if(cmd->buttons&IN_FORWARD)
			{
				if(cmd->buttons&IN_MOVELEFT)
				{
					cmd->forwardmove = 900;
					cmd->sidemove = -900;
				}
				else if(cmd->buttons&IN_MOVERIGHT)
				{
					cmd->forwardmove = 900;
					cmd->sidemove = 900;
				}
				else
					cmd->forwardmove = 900;
			}
			else if(cmd->buttons&IN_BACK)
			{
				if(cmd->buttons&IN_MOVELEFT)
				{
					cmd->forwardmove = -900;
					cmd->sidemove = -900;
				}
				else if(cmd->buttons&IN_MOVERIGHT)
				{
					cmd->forwardmove = -900;
					cmd->sidemove = 900;
				}
				else
					cmd->forwardmove = -900;
			}
			else if(cmd->buttons&IN_MOVELEFT)
				cmd->sidemove = -900;
			else if(cmd->buttons&IN_MOVERIGHT)
				cmd->sidemove = 900;
			else
				cmd->forwardmove = 900;
		}
		else
		{
			float va_speed = atan2(me.pmvVelocity.y, me.pmvVelocity.x);

			float va[3] = {0,0,0};
			gEngfuncs.GetViewAngles(va);

			float adif = va_speed - va[1] * PI / 180.0f - dir;

			adif = sin(adif);
			adif = atan2(adif, sqrt(1 - adif*adif));

			
			cmd->sidemove = (cvar.strafe_sidemove)*(adif > 0 ? 1 : -1);
			cmd->forwardmove = 0;

			float angle;
			float osin, ocos, nsin, ncos;

			angle = cmd->viewangles.y * PI / 180.0f;
			osin = sin(angle);
			ocos = cos(angle);

			angle = 2.0f * cmd->viewangles.y * PI / 180.0f - va_speed + dir;
			nsin = sin(angle);
			ncos = cos(angle);

			cmd->forwardmove = cmd->sidemove * (osin * ncos - ocos * nsin);
			cmd->sidemove *= osin * nsin + ocos * ncos;

			float fs = 0;
			if(atan2(cvar.strafe_angle / me.pmfSpeed, 1.0f) >= abs(adif))
			{
				Vector vBodyDirection;

				if(dir_value)
					vBodyDirection = me.pmvForward;
				else
					vBodyDirection = me.pmvRight;

				vBodyDirection[2] = 0;
				vBodyDirection = vBodyDirection.Normalize();

				float vel = POW(vBodyDirection[0] * me.pmvVelocity[0]) + POW(vBodyDirection[1] * me.pmvVelocity[1]);

				fs = sqrt(cvar.strafe_speed * 100000 / vel);
			}
			
			cmd->forwardmove += fs;
		}

		float sdmw = cmd->sidemove;
		float fdmw = cmd->forwardmove;

		switch((int)cvar.strafe_dir)
		{
		case 1:
			cmd->forwardmove = fdmw;
			cmd->sidemove = sdmw;
			break;
		case 2:
			cmd->forwardmove = -sdmw;
			cmd->sidemove = fdmw;
			break;
		case 3:
			cmd->forwardmove = -fdmw;
			cmd->sidemove = -sdmw;
			break;
		case 4:
			cmd->forwardmove = sdmw;
			cmd->sidemove = -fdmw;
			break;
		}
	}
}

//***************************************************************************

float YawForVec(float* fwd)
{
	if (fwd[1] == 0 && fwd[0] == 0)
	{
		return 0;
	}
	else
	{
		float yaw = (atan2(fwd[1], fwd[0]) * 180 / PI);
		if (yaw < 0)
			yaw += 360;
		return yaw;
	}
}

//***************************************************************************

void RotateInvisible(float fixed_yaw, float fixed_pitch, usercmd_s *cmd)
{
	Vector viewforward, viewright, viewup, aimforward, aimright, aimup, vTemp;
	float newforward, newright, newup;
	float forward = cmd->forwardmove;
	float right = cmd->sidemove;
	float up = cmd->upmove;
	Vector tipo_real_va;
	VectorCopy(cmd->viewangles,tipo_real_va);

	gEngfuncs.pfnAngleVectors(Vector(0.0f, tipo_real_va.y, 0.0f), viewforward, viewright, viewup);
	tipo_real_va.y += fixed_yaw;
	gEngfuncs.pfnAngleVectors(Vector(0.0f, tipo_real_va.y, 0.0f), aimforward, aimright, aimup);

	newforward = DotProduct(forward * viewforward.Normalize(), aimforward) + DotProduct(right * viewright.Normalize(), aimforward) + DotProduct(up * viewup.Normalize(), aimforward);
	newright = DotProduct(forward * viewforward.Normalize(), aimright) + DotProduct(right * viewright.Normalize(), aimright) + DotProduct(up * viewup.Normalize(), aimright);
	newup = DotProduct(forward * viewforward.Normalize(), aimup) + DotProduct(right * viewright.Normalize(), aimup) + DotProduct(up * viewup.Normalize(), aimup);

	if (fixed_pitch>81 )
	{cmd->forwardmove = -newforward;}
	else 
	{cmd->forwardmove = newforward;}

	cmd->sidemove = newright;
	cmd->upmove = newup;
}

//***************************************************************************

void StrafeBot::StrafeHacker(float frametime, struct usercmd_s *cmd,float visible,float crazy)
{
	if(Strafe && !(me.pmFlags & FL_ONGROUND) && (me.pmMoveType!=5) && !(cmd->buttons & IN_ATTACK))
	{
		float dir=0;

		int dir_value = cvar.strafe_dir;
		
		if(dir_value == 1)dir = 0;
		else if(dir_value == 2)	dir = 90;
		else if(dir_value == 3)	dir = 180;
		else if(dir_value == 4)	dir = -90;

		if(me.pmfSpeed < 15)
		{	
			cmd->forwardmove=400;
			cmd->sidemove=0;
		}

		float va_real[3]={0,0,0};
		gEngfuncs.GetViewAngles(va_real);va_real[1]+=dir;
		float vspeed[3]={me.pmvVelocity.x/me.pmfVSpeed,me.pmvVelocity.y/me.pmfVSpeed,0.0f};
		float va_speed=YawForVec(vspeed);
		
		float adif=va_speed-va_real[1];
		while(adif<-180)adif+=360;
		while(adif>180)adif-=360;
		cmd->sidemove=(cvar.strafe_sidemove)*(adif>0?1:-1);
		cmd->forwardmove=0;
		bool onlysidemove=(abs(adif)>=atan(cvar.strafe_angle/me.pmfSpeed)/PI*180);
		int aaddtova=0;
	
		if(visible == 0) RotateInvisible(-(adif),0,cmd);
		else cmd->viewangles[1] -= (-(adif)); 

		float fs=0;
		if(!onlysidemove)
		{
			static float lv=0;
			Vector fw=me.pmvForward;fw[2]=0;fw=fw.Normalize();
			float vel=POW(fw[0]*me.pmvVelocity[0])+POW(fw[1]*me.pmvVelocity[1]);

			fs=lv;
			lv=sqrt(cvar.strafe_speed * 100000 / vel);
			static float lastang=0;
			float ca=abs(adif);		
			lastang=ca;
		}

		if(visible == 0) cmd->forwardmove+=fs;
		else 
		{
			float ang = atan(fs/cmd->sidemove)/PI*180;
			cmd->viewangles.y+=ang;
		}

		if(crazy != 0)
		{
			static int _crazy = 1;
			_crazy *= (-1);
			cmd->viewangles.x = 89 * _crazy;
		}

		float sdmw=cmd->sidemove;
		float fdmw=cmd->forwardmove;
		switch((int)cvar.strafe_dir)
		{
		case 1:
			cmd->forwardmove = fdmw;
			cmd->sidemove = sdmw;
			break;
		case 2:
			cmd->forwardmove = -sdmw;
			cmd->sidemove = fdmw;
			break;
		case 3:
			cmd->forwardmove = -fdmw;
			cmd->sidemove = -sdmw;
			break;
		case 4:
			cmd->forwardmove = sdmw;
			cmd->sidemove = -fdmw;
			break;
		}
	}
}

//***************************************************************************

void StrafeBot::AutoDir(struct usercmd_s *cmd)	
{
	if(cmd->buttons&IN_FORWARD)
	{
		cvar.strafe_dir = 1;
	}
	if(cmd->buttons&IN_MOVERIGHT)
	{
		cvar.strafe_dir = 2;
	}
	if(cmd->buttons&IN_BACK)
	{
		cvar.strafe_dir = 3;
	}
	if(cmd->buttons&IN_MOVELEFT)
	{
		cvar.strafe_dir = 4;
	}
}

//***************************************************************************

void StrafeBot::FastRun(float frametime, struct usercmd_s *cmd)
{
	if(cvar.fastrun_nsd)
	{
		if(Fastrun && me.pmFlags&FL_ONGROUND && !Gstrafe )
		{
			if(!(cmd->buttons&(IN_FORWARD | IN_BACK | IN_MOVELEFT | IN_MOVERIGHT))) return;

			if(cmd->buttons&IN_MOVELEFT && cmd->buttons&IN_MOVERIGHT)
				cmd->buttons &= ~(IN_MOVELEFT | IN_MOVERIGHT);

			if(cmd->buttons&IN_FORWARD && cmd->buttons&IN_BACK)
				cmd->buttons &= ~(IN_FORWARD | IN_BACK);

			float aaddtova;

			if(cmd->buttons&IN_FORWARD)
			{
				if(cmd->buttons&IN_MOVELEFT)
					aaddtova = 45.0f;
				else if(cmd->buttons&IN_MOVERIGHT)
					aaddtova = -45.0f;
				else
					aaddtova = 0.0f;
			}
			else if(cmd->buttons&IN_BACK)
			{
				if(cmd->buttons&IN_MOVELEFT)
					aaddtova = 135.0f;
				else if(cmd->buttons&IN_MOVERIGHT)
					aaddtova = -135.0f;
				else
					aaddtova = 180.0f;
			}
			else if(cmd->buttons&IN_MOVELEFT)
				aaddtova = 90.0f;
			else if(cmd->buttons&IN_MOVERIGHT)
				aaddtova = -90.0f;

			if(me.pmfSpeed < 78)
			{
				if(cmd->buttons&IN_FORWARD)
				{
					if(cmd->buttons&IN_MOVELEFT)
					{
						cmd->forwardmove = 900;
						cmd->sidemove = -900;
					}
					else if(cmd->buttons&IN_MOVERIGHT)
					{
						cmd->forwardmove = 900;
						cmd->sidemove = 900;
					}
					else
						cmd->forwardmove = 900;
				}
				else if(cmd->buttons&IN_BACK)
				{
					if(cmd->buttons&IN_MOVELEFT)
					{
						cmd->forwardmove = -900;
						cmd->sidemove = -900;
					}
					else if(cmd->buttons&IN_MOVERIGHT)
					{
						cmd->forwardmove = -900;
						cmd->sidemove = 900;
					}
					else
						cmd->forwardmove = -900;
				}
				else if(cmd->buttons&IN_MOVELEFT)
					cmd->sidemove = -900;
				else if(cmd->buttons&IN_MOVERIGHT)
					cmd->sidemove = 900;

				return;
			}

			bool dir_rig = true;

			float yaw = atan2(me.pmvVelocity.y, me.pmvVelocity.x) * 180.0 / PI;

			yaw -= aaddtova;
			yaw = cmd->viewangles.y - yaw;

			int fadif = yaw;

			fadif = (fadif + 360) % 360;
			dir_rig = fadif <= 180;

			float x = 135.06374825035877480180939653038* (dir_rig ? -1 : +1);
			float y = 267.87643402987823669025530311859;

			float a = DegToRad(aaddtova);
			float sinA = sin(a);
			float cosA = cos(a);

			cmd->sidemove = x*cosA - y*sinA;
			cmd->forwardmove = y*cosA + x*sinA;

			x = cmd->sidemove;
			y = cmd->forwardmove;


			float newa = DegToRad(-yaw);
			sinA = sin(newa);
			cosA = cos(newa);

			cmd->sidemove = x*cosA - y*sinA;
			cmd->forwardmove = y*cosA + x*sinA;
		}
	}
	else
	{
		if(Fastrun && me.pmFlags&FL_ONGROUND && !Gstrafe )
		{
			static bool _FastRun = false;

			if((cmd->buttons&IN_FORWARD && cmd->buttons&IN_MOVELEFT) || (cmd->buttons&IN_BACK && cmd->buttons&IN_MOVERIGHT))
			{
				if(_FastRun)	{ _FastRun = false; cmd->sidemove -= 89.6; cmd->forwardmove -= 89.6; }
				else			{ _FastRun = true;  cmd->sidemove += 89.6; cmd->forwardmove += 89.6; }
			}
			else if((cmd->buttons&IN_FORWARD && cmd->buttons&IN_MOVERIGHT) || (cmd->buttons&IN_BACK && cmd->buttons&IN_MOVELEFT))
			{
				if(_FastRun)	{ _FastRun = false; cmd->sidemove -= 89.6; cmd->forwardmove += 89.6; }
				else			{ _FastRun = true;  cmd->sidemove += 89.6; cmd->forwardmove -= 89.6; }
			}
			else if(cmd->buttons&IN_FORWARD || cmd->buttons&IN_BACK)
			{
				if(_FastRun)	{ _FastRun = false; cmd->sidemove -= 126.6; }
				else			{ _FastRun = true;  cmd->sidemove += 126.6; }
			}
			else if(cmd->buttons&IN_MOVELEFT || cmd->buttons&IN_MOVERIGHT)
			{
				if(_FastRun)	{ _FastRun = false; cmd->forwardmove -= 126.6; }
				else			{ _FastRun = true;  cmd->forwardmove += 126.6; }
			}
		}
	}
}

//***************************************************************************

void StrafeBot::FastRunner(struct usercmd_s *cmd)
{
	if (Fastrun && me.pmfSpeed && me.pmflFallSpeed == 0 && !Gstrafe && me.pmFlags&FL_ONGROUND)
	{
		static bool _FastRun = false;
		if ((cmd->buttons&IN_FORWARD && cmd->buttons&IN_MOVELEFT) || (cmd->buttons&IN_BACK && cmd->buttons&IN_MOVERIGHT)) {
			if (_FastRun)	{ _FastRun = false; cmd->sidemove -= 89.6; cmd->forwardmove -= 89.6; }
			else			{ _FastRun = true;  cmd->sidemove += 89.6; cmd->forwardmove += 89.6; }
		} else if ((cmd->buttons&IN_FORWARD && cmd->buttons&IN_MOVERIGHT) || (cmd->buttons&IN_BACK && cmd->buttons&IN_MOVELEFT)) {
			if (_FastRun)	{ _FastRun = false; cmd->sidemove -= 89.6; cmd->forwardmove += 89.6; }
			else			{ _FastRun = true;  cmd->sidemove += 89.6; cmd->forwardmove -= 89.6; }
		} else if(cmd->buttons&IN_FORWARD || cmd->buttons&IN_BACK) {
			if (_FastRun)	{ _FastRun = false; cmd->sidemove -= 126.6; }
			else			{ _FastRun = true;  cmd->sidemove += 126.6; }
		} else if (cmd->buttons&IN_MOVELEFT || cmd->buttons&IN_MOVERIGHT) {
			if (_FastRun)	{ _FastRun = false; cmd->forwardmove -= 126.6; }
			else			{ _FastRun = true;  cmd->forwardmove += 126.6; }
		}
	}
}

//***************************************************************************

void StrafeBot::GroundStrafer(struct usercmd_s *cmd)
{
	if(Gstrafe && !Jumpbug)
	{
		static int gs_state = 0;
		if(cvar.gstrafe_standup && me.pmflHeight<cvar.gstrafe_standup)
		{
			if(cvar.gstrafe_nsd && (me.pmflGroundAngle<5) && (me.pmflHeight<=0.000001f || me.pmFlags&FL_ONGROUND))
			{
				Speedbot.AdjustSpeed(0.0001);
			}
			cmd->buttons |=IN_DUCK;
		}
		if(gs_state == 0 && me.pmFlags&FL_ONGROUND)
		{
			if((me.pmflGroundAngle<5) && cvar.gstrafe_nsd != 0 &&(me.pmflHeight<=0.000001f || me.pmFlags&FL_ONGROUND))
			{
				Speedbot.AdjustSpeed(0.0001);
			}	
			cmd->buttons |=IN_DUCK;
			gs_state = 1;
		}
		else if(gs_state == 1)
		{
			if((me.pmflGroundAngle<5) && cvar.gstrafe_nsd != 0 && (me.pmflHeight<=0.000001f || me.pmFlags&FL_ONGROUND))
			{
				Speedbot.AdjustSpeed(0.0001);
			}	
			if(cvar.gstrafe_bhop && me.pmiUseHull==0)
			{
				cmd->buttons|=IN_JUMP;
			}
			cmd->buttons &= ~IN_DUCK;
			gs_state = 0;
		}
	}
}

//***************************************************************************

void StrafeBot::GroundStrafe(struct usercmd_s *cmd)
{
	if(Gstrafe && !Jumpbug)
	{
		static int gs_state = 0;

		if(cvar.gstrafe_standup != 0.0f)
		{
			if(me.pmflFallSpeed > 0)
			{
				if(me.pmflGroundAngle < 5.0f && ((me.pmFlags&FL_ONGROUND) || me.pmflHeight < 0.00001f))
				{
					Speedbot.AdjustSpeed(cvar.gstrafe_nsd <= 0.0f ? 0.0000001f : cvar.gstrafe_nsd);
				}

				if(me.pmflFallSpeed >= 140)
					if(me.pmflHeight <= 30)
						cmd->buttons |= IN_DUCK;
			}
		}

		if(gs_state == 0 && (me.pmFlags&FL_ONGROUND))
		{
			if(me.pmflGroundAngle < 5.0f && ((me.pmFlags&FL_ONGROUND) || me.pmflHeight < 0.00001f))
			{
				Speedbot.AdjustSpeed(cvar.gstrafe_nsd <= 0.0f ? 0.000001f : cvar.gstrafe_nsd);
			}

			cmd->buttons |= IN_DUCK;

			gs_state = 1;
		}
		else if(gs_state == 1)
		{
			if(me.pmflGroundAngle < 5.0f && ((me.pmFlags&FL_ONGROUND) || me.pmflHeight < 0.00001f))
			{
				Speedbot.AdjustSpeed(cvar.gstrafe_nsd <= 0.0f ? 0.00001f : cvar.gstrafe_nsd);
			}

			if(cvar.gstrafe_bhop != 0 && ((me.pmFlags&FL_DUCKING) ? 1 : 0) == 0)
				cmd->buttons |= IN_JUMP;

			cmd->buttons &= ~IN_DUCK;

			gs_state = 0;
		}
	}
}

//***************************************************************************

void SlowDownSleep(struct usercmd_s *cmd, float fNeedSpeed)
{
	float redspeed = me.pmfSpeed - fNeedSpeed;

	float degspeed = atan2(me.pmvVelocity[1], me.pmvVelocity[0]);

	if(degspeed < 0)
		degspeed += (PI * 2.0f);

	if(redspeed < 30.0f)
		redspeed = (300.0f / me.pmAirAccelerate);

	cmd->forwardmove = -redspeed * cos(cmd->viewangles.y * PI / 180.0f - degspeed);
	cmd->sidemove = -redspeed * sin(cmd->viewangles.y * PI / 180.0f - degspeed);
}

//***************************************************************************

void StrafeBot::Bhop(float frametime, struct usercmd_s *cmd)
{
	static bool lastFramePressedJump = false;
	static bool JumpInNextFrame = false;
	static int inAirBhopCnt = 0;
	bool isJumped = false;

	if(JumpInNextFrame)
	{
		JumpInNextFrame = false;

		cmd->buttons |= IN_JUMP;

		goto bhopfuncend;
	}

	if(StrafeBhop && !Gstrafe)
	{
		cmd->buttons &= ~IN_JUMP;

		if(cvar.bhop_nsd != 0.0f)
		{
			if(!(me.pmFlags&FL_ONGROUND))
			{
				cmd->buttons &= ~IN_JUMP;

				if(me.pmVelocity[2] < 0)
				{
					float redspeed = me.pmfSpeed - cvar.bhop_nsd;

					int nframes = 0;
					float addFallingSpeed = me.pmflFallSpeed;

					float height = me.pmflHeight;
					while(height > 2.0f)
					{
						height -= addFallingSpeed * me.pmframeTime;
						addFallingSpeed += me.pmgravity * me.pmmovevarsgravity * 0.5 * me.pmframeTime;
						nframes++;
					}

					float nstartframe = me.pmAirAccelerate * redspeed * me.pmframeTime * me.pmfriction;

					if(redspeed > 0.0f)
						SlowDownSleep(cmd, cvar.bhop_nsd);
	
				}
			}
		}

		if(!lastFramePressedJump || (me.pmFlags&FL_ONGROUND) || me.pmwaterlevel >= 2 || (me.pmMoveType == 5) || me.pmflHeight <= 2)
		{
			if(true)
			{
				static int bhop_jump_number = 0;

				bhop_jump_number++;

				if(bhop_jump_number >= RandomFloat(1.6, 3.6))
				{
					bhop_jump_number = 0;

					JumpInNextFrame = true;

					goto bhopfuncend;
				}
			}
			{
				inAirBhopCnt = 4;

				isJumped = true;

				cmd->buttons |= IN_JUMP;
			}
		}
	}

	if(!isJumped)
	{
		if(inAirBhopCnt > 0)
		{
			if(inAirBhopCnt % 2 == 0)
				cmd->buttons |= IN_JUMP;
			else
				cmd->buttons &= ~IN_JUMP;

			inAirBhopCnt--;
		}
	}

    bhopfuncend:

	lastFramePressedJump = (cmd->buttons&IN_JUMP);
}

//***************************************************************************

void StrafeBot::Bhopper(float frametime, struct usercmd_s *cmd)
{
	static bool bhop_standup_state = false;
	static bool lastFramePressedJump=false;
	static bool JumpInNextFrame=false;
	static int inAirBhopCnt=0;
	bool isJumped=false;

	if ( me.pmflHeight <= 20 && bhop_standup_state == true && StrafeBhop !=0 && cvar.bhop_autoduck )
	{
		bhop_standup_state = false;
		gEngfuncs.pfnClientCmd("-duck");
	}
	
	if ( bhop_standup_state == true && (me.pmMoveType == 5))
	{
		gEngfuncs.pfnClientCmd("-duck");
	}

	if(JumpInNextFrame)
	{
		JumpInNextFrame=false;
		cmd->buttons|=IN_JUMP;
		goto bhopfuncend;
	}

	if(StrafeBhop !=0 && !Gstrafe)
	{
		if ( cvar.bhop_autoduck )
		{
			if ( me.pmflHeight >= 30 && me.pmflHeight <= 64 && bhop_standup_state == false && me.pmMoveType != 5)
			{
				gEngfuncs.pfnClientCmd("+duck");
				bhop_standup_state = true;
				me.flDuckTimeMax = GetClientTime();
				balance_bh = true;
			}
		}

		cmd->buttons &= ~IN_JUMP;
		if( ((!lastFramePressedJump)|| me.pmFlags&FL_ONGROUND || me.pmwaterlevel >= 2 || me.pmMoveType==5 || me.pmflHeight<=2)/* && !jumpbug*/)
		{
			if(true)
			{
				if(cvar.bhop_nsd)
				{
					if((int)me.pmfSpeed <= 299 && !Strafe)
					{
						Speedbot.AdjustSpeed(0.0001);
					}
				}
				static int bhop_jump_number=0;
				bhop_jump_number++;
				if(bhop_jump_number>=2)
				{
					bhop_jump_number=0;
					JumpInNextFrame=true; 
					goto bhopfuncend;
				}
			}

			if(cvar.bhop_cnt_rand_min > cvar.bhop_cnt_rand_max)
			{
				cvar.bhop_cnt_rand_min = cvar.bhop_cnt_rand_max;
			}

			if(cvar.bhop_cnt_rand_min <= 1)
			{
				cvar.bhop_cnt_rand_min = 1;
			}

			if(cvar.bhop_cnt_rand_min > 20)
			{
				cvar.bhop_cnt_rand_min = 20;
			}

			if(cvar.bhop_cnt_rand_max > 20)
			{
				cvar.bhop_cnt_rand_max = 20;
			}

			if(cvar.bhop_cnt_rand_max <= 1)
			{
				cvar.bhop_cnt_rand_max = 1;
			}

			if(cvar.bhop_cnt_rand)
				inAirBhopCnt = (int)RandomFloat((int)cvar.bhop_cnt_rand_min,(int)cvar.bhop_cnt_rand_max);
			else
				inAirBhopCnt = cvar.bhop_cnt;

			isJumped=true;
			cmd->buttons |= IN_JUMP;
		} 
	}
	if(!isJumped)
	{
		if(inAirBhopCnt>0)
		{
			if(inAirBhopCnt%2==0) 
			{
				cmd->buttons |= IN_JUMP;
			}
			else cmd->buttons &= ~IN_JUMP;
			inAirBhopCnt--;
		}
	}

    bhopfuncend:

	lastFramePressedJump = cmd->buttons&IN_JUMP;
}

//***************************************************************************

double _my_abs(double n) 
{
	if (n >= 0)return n; //if positive, return without ant change
	else return 0 - n; //if negative, return a positive version
}

void StrafeBot::JumpBugger(float frametime, struct usercmd_s *cmd)
{
	static int state=0;

	bool autojb=false;
	if(cvar.jumpbugauto !=0 && me.pmflFallSpeed>=PLAYER_MAX_SAFE_FALL_SPEED)
		if(me.pmflHeight-(me.pmflFallSpeed*frametime/cvar.wavspeed *15)<=0)
			autojb=true;

	if((Jumpbug||autojb)&& me.pmflFallSpeed>0)
	{
		bool curveang=false;
		float fpheight=0;
		if(me.pmflGroundAngle>1)
		{
			curveang=true;
			Vector vTemp = me.pmvOrigin;
			vTemp[2] -= 8192;
			pmtrace_t *trace = PM_TraceLine(me.pmvOrigin, vTemp, 1, 2, -1);
			fpheight=abs(me.pmvOrigin.z-trace->endpos.z-(me.pmiUseHull==1?18.0f:36.0f));
		}
		else fpheight=me.pmflHeight;
		

		static float last_h=0.0f;
		float cur_frame_zdist=abs((me.pmflFallSpeed+(800*frametime))*frametime);
		cmd->buttons|=IN_DUCK;
		cmd->buttons&=~IN_JUMP;
		switch(state)
		{
		case 1:
			cmd->buttons&=~IN_DUCK;
			cmd->buttons|=IN_JUMP;
			state=2;
			break;
		case 2:
			state=0;
			break;
		default:
			if(_my_abs(fpheight-cur_frame_zdist*1.5)<=(20.0)&&cur_frame_zdist>0.0f)
			{
				float needspd=_my_abs(fpheight-(19.0));
				float scale=abs(needspd/cur_frame_zdist);
				Speedbot.AdjustSpeed(scale);
				state=1;
			}
			break;
		}
		last_h=fpheight;
	}
	else state=0;
}

//***************************************************************************

void SlowVerticalVel(float to, float frametime, usercmd_s *cmd)
{
	float bvel = ((me.pmfVSpeed + me.pmfVSpeed*frametime) - to) / (frametime * 100);
	float vspeed[3] = { me.pmvVelocity.x / me.pmfVSpeed,me.pmvVelocity.y / me.pmfVSpeed,0.0f };
	float va_speed[3]; 
	VectorAngles(vspeed, va_speed);
	float adif = va_speed[1] - cmd->viewangles[1];
	while (adif<-180)adif += 360;
	while (adif>180)adif -= 360;
	cmd->forwardmove = -bvel;
	cmd->sidemove = 0;
	if (!cmd->buttons&IN_JUMP && !cmd->buttons&IN_DUCK) cmd->buttons = 0;
	RotateInvisible(-(va_speed[1] - cmd->viewangles[1]), 0, cmd);
}

void StrafeBot::JumpBug(float frametime, usercmd_s *cmd)
{
	static float NeedOffset;
	static int state;
	bool autojb = false;
	if ((cvar.jumpbugauto != 0 && me.pmflFallSpeed >= 504.8) && (me.pmflHeight - (me.pmflFallSpeed*frametime / cvar.wavspeed * 15) <= 0)) autojb = true;
	if ((autojb || Jumpbug) && me.pmflFallSpeed > 0)
	{
		static float last_h;
		bool curveang = false;
		if (me.pmflGroundAngle == 45.0) NeedOffset = 20.0;
		else NeedOffset = 19.0;
		if (cvar.jumpbugslow)
		{
			if (me.pmflGroundAngle > 1)
			{
				if (me.pmfSpeed > 1 && me.pmflHeight <= cvar.jumpbugslow * 4 + (me.pmfSpeed / me.pmflFallSpeed)) curveang = true;
				if (me.pmfSpeed > 10 && me.pmflHeight <= 504 * frametime * 7) Speedbot.AdjustSpeed(cvar.jumpbugslowspeed);
			}
		}	
		float cur_frame_zdist = abs((me.pmflFallSpeed + (800 * frametime))*frametime);
		cmd->buttons |= IN_DUCK;
		cmd->buttons &= ~IN_JUMP;
		if (cvar.jumpbugslow && curveang) SlowVerticalVel(0, frametime, cmd);
		switch (state)
		{
		case 1:
			cmd->buttons &= ~IN_DUCK;
			cmd->buttons |= IN_JUMP;
			state = 2;
			break;
		case 2:
			state = 0;
			break;
		default:
			if (abs(me.pmflHeight - cur_frame_zdist*1.5) <= 20.0 && cur_frame_zdist > 0.0f)
			{
				float needspd = abs(me.pmflHeight - (me.bPlayerjb ? 19.0 : NeedOffset));
				float scale = abs(needspd / cur_frame_zdist);
				Speedbot.AdjustSpeed(scale);
				state = 1;
			}
			break;
		}
		last_h = me.pmflHeight;
	}
	else state = 0;
}

//***************************************************************************

void StrafeBot::StrafeHelper(float frametime, struct usercmd_s *cmd)
{
	if(me.pmfSpeed > 0)
	{
		static int lastdir=0;
		static int strafe_counter=0;
		static int strafe_num=0;
		if(me.pmFlags&FL_ONGROUND||me.pmMoveType==5||!(me.pmwaterlevel < 2)||(me.pmflGroundAngle>45.9&&me.pmflHeight<50))
		{
			strafe_counter=0;
			lastdir=0;
			if(cvar.strafe_helper_boost)
					Strafe=false;
			rand_strafe = true;
		}
		else
		{
			if(cvar.strafe_helper_boost)
					Strafe=true;
	
			cmd->buttons&=~IN_BACK;
			cmd->buttons&=~IN_FORWARD;

			if(!cmd->buttons&IN_MOVERIGHT && !cvar.strafe_helper_add_strafe)
				cmd->buttons&=~IN_MOVERIGHT;

			if(!cmd->buttons&IN_MOVELEFT && !cvar.strafe_helper_add_strafe)
				cmd->buttons&=~IN_MOVELEFT;			
			
			if( cvar.strafe_helper_max_strafe_rand && cvar.strafe_helper_add_strafe)
			{
				if(cvar.strafe_helper_max_strafe_min > cvar.strafe_helper_max_strafe_max)
				{
					cvar.strafe_helper_max_strafe_min = cvar.strafe_helper_max_strafe_max;
				}
				if( cvar.strafe_helper_max_strafe_min <= 1 )
				{
					cvar.strafe_helper_max_strafe_min = 1;
				}
				if( rand_strafe == true )
				{
					cvar.strafe_helper_max_strafe = RandomFloat(cvar.strafe_helper_max_strafe_min,cvar.strafe_helper_max_strafe_max);
					rand_strafe = false;
				}
			}

			static int nobuttons=0;
			if(lastdir!=-1&&me.pmfAngleSpeed<0)
			{
				lastdir=-1;
				strafe_counter++;
				strafe_num=0;
				nobuttons=3;
			}
			if(lastdir!=1&&me.pmfAngleSpeed>0)
			{
				lastdir=1;
				strafe_counter++;
				strafe_num=0;
				nobuttons=3;
			}
			strafe_num++;

			if(strafe_counter<=(cvar.strafe_helper_max_strafe) && cvar.strafe_helper_add_strafe)
			{
				switch(cvar.strafe_dir)
				{
				case 1://forward
					if(me.pmfAngleSpeed<0){cmd->buttons|=IN_MOVELEFT;cmd->buttons&=~IN_MOVERIGHT;}//mouse left - left
					if(me.pmfAngleSpeed>0){cmd->buttons|=IN_MOVERIGHT;cmd->buttons&=~IN_MOVELEFT;}//mouse right - right
					break;
				case 3: // back
					if(me.pmfAngleSpeed<0){cmd->buttons|=IN_MOVERIGHT;cmd->buttons&=~IN_MOVELEFT;}//mouse left - right
					if(me.pmfAngleSpeed>0){cmd->buttons|=IN_MOVELEFT;cmd->buttons&=~IN_MOVERIGHT;}//mouse right - left
					break;
				case 4://left
					if(me.pmfAngleSpeed<0){cmd->buttons|=IN_BACK;cmd->buttons&=~IN_FORWARD;}//mouse left - back
					if(me.pmfAngleSpeed>0){cmd->buttons|=IN_FORWARD;cmd->buttons&=~IN_BACK;}//mouse right - forward
					break;
				case 2://right
					if(me.pmfAngleSpeed<0){cmd->buttons|=IN_FORWARD;cmd->buttons&=~IN_BACK;}//mouse left - forward
					if(me.pmfAngleSpeed>0){cmd->buttons|=IN_BACK;cmd->buttons&=~IN_FORWARD;}//mouse right - back
					break;
				}
			}
			float sidespeed=0;
			float forwardspeed=0;

			if(cvar.strafe_helper_move_rand && cvar.strafe_helper_add_strafe)
			{
				if(cvar.strafe_helper_move_rand_min > cvar.strafe_helper_move_rand_max)
				{
					cvar.strafe_helper_move_rand_min = cvar.strafe_helper_move_rand_max;
				}

				if(cvar.strafe_helper_move_rand_max > 400)
				{
					cvar.strafe_helper_move_rand_max = 400;
				}

				if(cvar.strafe_helper_move_rand_max <= 1)
				{
					cvar.strafe_helper_move_rand_max = 1;
				}

				if(cvar.strafe_helper_move_rand_min < 50)
				{
					cvar.strafe_helper_move_rand_min = 50;
				}

				if(cvar.strafe_helper_move_rand_min > 400)
				{
					cvar.strafe_helper_move_rand_min = 400;
				}
				cvar.strafe_helper_move = RandomFloat(cvar.strafe_helper_move_rand_min,cvar.strafe_helper_move_rand_max);
			}

			double ms = me.pmfSpeed/me.pmMaxSpeed;
			sidespeed += cvar.strafe_helper_move*(me.pmfAngleSpeed<0?-1:1);
			forwardspeed = cvar.strafe_helper_main/ms;

			if(me.pmfAngleSpeed>0.0f||me.pmfAngleSpeed<0.0f)
			{
				switch(cvar.strafe_dir)
				{
				case 1:
					cmd->forwardmove=forwardspeed;
					cmd->sidemove=sidespeed;
					break;
				case 2:
					cmd->forwardmove=-sidespeed;
					cmd->sidemove=forwardspeed;
					break;
				case 3:
					cmd->forwardmove=-forwardspeed;
					cmd->sidemove=-sidespeed;
					break;
				case 4:
					cmd->forwardmove=sidespeed;
					cmd->sidemove=-forwardspeed;
					break;
				}
			}
		}
	}
}