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

cMenu gMenu;

void TrapezoidalMenu(int x, int y, int w, int h);

//**********************************************************************************************************************************

int cMenu::AddEntry_FLOAT(int n, char title[200], char content[200], float* value, float min, float max, float step)
{
	strcpy( menuEntry[n].title,title);
	strcpy( menuEntry[n].content,content);
	menuEntry[n].value_f = value;
	menuEntry[n].min_f = min;
	menuEntry[n].max_f = max;
	menuEntry[n].step_f = step;
	return (n+1);
}

//**********************************************************************************************************************************

int cMenu::AddEntry_INT(int n, char title[200], char content[200], int* value, int min, int max, int step)
{
	strcpy( menuEntry[n].title,title);
	strcpy( menuEntry[n].content,content);
	menuEntry[n].value_i = value;
	menuEntry[n].min_i = min;
	menuEntry[n].max_i = max;
	menuEntry[n].step_i = step;
	return (n+1);
} 

//**********************************************************************************************************************************

float aimbot = 0;
float burst = 0;
float esp = 0;
float fps = 0;
float kz = 0;
float mics = 0;
float opengl = 0;
float chams = 0;
float bone = 0;
float way = 0;
float maxrecord = 0;
float maxadd = 0;
float maxclear = 0;
float maxset = 0;
float waymisc = 0;
float antiaim = 0;

int menuadd = 0;

void cMenu::Init()
{
	if(!Active) return;

	int i = 0;

	{
		i = AddEntry_INT(i, "=> AimBot", "", (int*)&aimbot, 0, 1, 1);
		if(aimbot)
		{
			if (!cvar.aim_enable)
			{
				i = AddEntry_INT(i, " NoRecoil_Visual", "norecoil_visual change", &menuadd, 0, 0, 0);
				i = AddEntry_INT(i, " KnifeAim", "knf_aim change", &menuadd, 0, 0, 0);
				i = AddEntry_INT(i, " KnifeAttack", "knf_attack change", &menuadd, 0, 0, 0);
			}
			
			if (cvar.aim_enable)
			{
				i = AddEntry_INT(i, " AimAuto", "aim_auto change", &menuadd, 0, 0, 0);
				i = AddEntry_INT(i, " AimSilent", "aim_silent change", &menuadd, 0, 0, 0);
				i = AddEntry_INT(i, " AimTeam", "aim_team change", &menuadd, 0, 0, 0);
				i = AddEntry_INT(i, " AimTrigger", "aim_trigger change", &menuadd, 0, 0, 0);
				i = AddEntry_INT(i, " AimTrue", "aim_thru change", &menuadd, 0, 0, 0);
				i = AddEntry_INT(i, " AimPunch", "aim_punch change", &menuadd, 0, 0, 0);
				if(!burst)i = AddEntry_INT(i, "+ Burst", "", (int*)&burst, 0, 1, 1); 
				else i = AddEntry_INT(i, "- Burst", "", (int*)&burst, 0, 1, 1); 
				if(burst)
				{
					i = AddEntry_INT(i, " Off",  "off", &menuadd, 0, 0, 0);
					i = AddEntry_INT(i, " Short",  "short", &menuadd, 0, 0, 0);
					i = AddEntry_INT(i, " Medium",  "medium", &menuadd, 0, 0, 0);
					i = AddEntry_INT(i, " Fast",  "fast", &menuadd, 0, 0, 0);
				}
				i = AddEntry_INT(i, " CrossHair",  "crosshair change", &menuadd, 0, 0, 0);
				i = AddEntry_INT(i, " KnifeAim", "knf_aim change", &menuadd, 0, 0, 0);
				i = AddEntry_INT(i, " KnifeAttack", "knf_attack change", &menuadd, 0, 0, 0);
				i = AddEntry_INT(i, " NoRecoil", "norecoil change", &menuadd, 0, 0, 0);
				i = AddEntry_INT(i, " NoRecoil_Visible", "norecoil_visible change", &menuadd, 0, 0, 0);
				i = AddEntry_INT(i, " NoRecoil_Visual", "norecoil_visual change", &menuadd, 0, 0, 0);
				i = AddEntry_INT(i, " NoSpread", "nospread change", &menuadd, 0, 0, 0);
				i = AddEntry_INT(i, " NoSpread_Visible", "nospread_visible change", &menuadd, 0, 0, 0);
				if(cvar.cheatmode == 2)i = AddEntry_INT(i, " ReloadSpeed", "rspeed change", &menuadd, 0, 0, 0);
			}
		}

		i = AddEntry_INT(i, "=> AntiAim", "", (int*)&antiaim, 0, 1, 1);
		if(antiaim)
		{
			i = AddEntry_INT(i, " Pitch",  "antiaimpitchchange", &menuadd, 0, 0, 0);
			i = AddEntry_INT(i, " Yaw",  "antiaimyawchange", &menuadd, 0, 0, 0);
		}

		i = AddEntry_INT(i, "=> Bone", "", (int*)&bone, 0, 1, 1); 
		if (bone)
		{
			i = AddEntry_INT(i, " Skeleton",  "skeleton change", &menuadd, 0, 0, 0);
		}

		i = AddEntry_INT(i, "=> Chams", "", (int*)&chams, 0, 1, 1); 
		if (chams)
		{
			i = AddEntry_INT(i, " Chams",  "chamschange", &menuadd, 0, 0, 0);
			i = AddEntry_INT(i, " ChamsGlow",  "chamsglow change", &menuadd, 0, 0, 0);
			i = AddEntry_INT(i, " Chamswall",  "chamswall change", &menuadd, 0, 0, 0);
		}

		i = AddEntry_INT(i, "=> Esp", "", (int*)&esp, 0, 1, 1);
		if(esp)
		{
			i = AddEntry_INT(i, " Esptype",  "esptype change", &menuadd, 0, 0, 0);
			i = AddEntry_INT(i, " EntEsp",  "entesp change", &menuadd, 0, 0, 0);
			i = AddEntry_INT(i, " EspTeam",  "espteam change", &menuadd, 0, 0, 0);
			i = AddEntry_INT(i, " Name",  "name change", &menuadd, 0, 0, 0);
			i = AddEntry_INT(i, " PlayerInfo", "playerinfo change", &menuadd, 0, 0, 0);
			i = AddEntry_INT(i, " Radar",  "Radar change", &menuadd, 0, 0, 0);
			i = AddEntry_INT(i, " RadarMini",  "Miniradar change", &menuadd, 0, 0, 0);
			i = AddEntry_INT(i, " Reloadmeter", "reloadmeter change", &menuadd, 0, 0, 0);
			i = AddEntry_INT(i, " Sequence", "sequence change", &menuadd, 0, 0, 0);
			if(cvar.esptype)i = AddEntry_INT(i, " SoundEsp", "soundesp change", &menuadd, 0, 0, 0);
			i = AddEntry_INT(i, " Weapon", "weapon change", &menuadd, 0, 0, 0);
		}

		i = AddEntry_INT(i, "=> FpsMax", "", (int*)&fps, 0, 1, 1);
		if(fps)
		{
			i = AddEntry_INT(i, " 100",  "#fps_max 100;#fps_modem 100", &menuadd, 0, 0, 0);
			i = AddEntry_INT(i, " 200",  "#fps_max 200;#fps_modem 200", &menuadd, 0, 0, 0);
			i = AddEntry_INT(i, " 300",  "#fps_max 300;#fps_modem 300", &menuadd, 0, 0, 0);
			i = AddEntry_INT(i, " 400",  "#fps_max 400;#fps_modem 400", &menuadd, 0, 0, 0);
			i = AddEntry_INT(i, " 500",  "#fps_max 500;#fps_modem 500", &menuadd, 0, 0, 0);
			i = AddEntry_INT(i, " 600",  "#fps_max 600;#fps_modem 600", &menuadd, 0, 0, 0);
			i = AddEntry_INT(i, " 700",  "#fps_max 700;#fps_modem 700", &menuadd, 0, 0, 0);
			i = AddEntry_INT(i, " 800",  "#fps_max 800;#fps_modem 800", &menuadd, 0, 0, 0);
			i = AddEntry_INT(i, " 900",  "#fps_max 900;#fps_modem 900", &menuadd, 0, 0, 0);
			i = AddEntry_INT(i, " 1000", "#fps_max 1000;#fps_modem 1000", &menuadd, 0, 0, 0);
		}

		i = AddEntry_INT(i, "=> KZ", "", (int*)&kz, 0, 1, 1);
		if(kz)
		{
			i = AddEntry_INT(i, " Bhop",  "bhop change", &menuadd, 0, 0, 0);
			i = AddEntry_INT(i, " BhopAutoDuck",  "bhop_autoduck change", &menuadd, 0, 0, 0);
			i = AddEntry_INT(i, " BhopSlowDown",  "bhop_nsd change", &menuadd, 0, 0, 0);
			i = AddEntry_INT(i, " Fastrun",  "fastrun change", &menuadd, 0, 0, 0);
			i = AddEntry_INT(i, " FastrunNoSlowDown",  "fastrun_nsd change", &menuadd, 0, 0, 0);
			i = AddEntry_INT(i, " Gstrafe",  "groundstrafe change", &menuadd, 0, 0, 0);
			i = AddEntry_INT(i, " GstrafeBhop",  "gstrafe_bhop change", &menuadd, 0, 0, 0);
			i = AddEntry_INT(i, " GstrafeNoSlowDown",  "gstrafe_nsd change", &menuadd, 0, 0, 0);
			i = AddEntry_INT(i, " GstrafeStandUp",  "gstrafe_standup change", &menuadd, 0, 0, 0);
			i = AddEntry_INT(i, " Jumpbug",  "jumpbug change", &menuadd, 0, 0, 0);
			i = AddEntry_INT(i, " JumpbugAuto",  "jumpbugauto change", &menuadd, 0, 0, 0);
			i = AddEntry_INT(i, " JumpbugSlowSpeed",  "jumpbugslowspeed change", &menuadd, 0, 0, 0);
			i = AddEntry_INT(i, " ShowKZ",  "show_kz change", &menuadd, 0, 0, 0);
			i = AddEntry_INT(i, " SlowDown",  "slowdown change", &menuadd, 0, 0, 0);
			i = AddEntry_INT(i, " Strafe",  "strafehack change", &menuadd, 0, 0, 0);
			i = AddEntry_INT(i, " StrafeAutoDir",  "strafeautodir change", &menuadd, 0, 0, 0);
			i = AddEntry_INT(i, " StrafeCrazy",  "strafe_crazy change", &menuadd, 0, 0, 0);
			i = AddEntry_INT(i, " StrafeHelp",  "strafe_helper change", &menuadd, 0, 0, 0);
			i = AddEntry_INT(i, " StrafeBoost",  "strafe_helper_boost change", &menuadd, 0, 0, 0);
			i = AddEntry_INT(i, " StrafeInvis",  "strafe_invisible change", &menuadd, 0, 0, 0);
		}

		i = AddEntry_INT(i, "=> Misc", "", (int*)&mics, 0, 1, 1); 
		if(mics)
		{
			i = AddEntry_INT(i, " Chase",  "chase change", &menuadd, 0, 0, 0);
			i = AddEntry_INT(i, " KillSound",  "killsound change", &menuadd, 0, 0, 0);
			i = AddEntry_INT(i, " NewHud",  "infobars change", &menuadd, 0, 0, 0);
		}

		i = AddEntry_INT(i, "=> OpenGL", "", (int*)&opengl, 0, 1, 1); 
		if (opengl)
		{
			i = AddEntry_INT(i, " Laser",  "barrel change", &menuadd, 0, 0, 0);
			i = AddEntry_INT(i, " NoSmoke", "nosmoke change", &menuadd, 0, 0, 0);
			i = AddEntry_INT(i, " NoSky", "nosky change", &menuadd, 0, 0, 0);
			i = AddEntry_INT(i, " NoFlash", "noflash change", &menuadd, 0, 0, 0);
		}

        i = AddEntry_INT(i, "=> Way", "", (int*)&way, 0, 1, 1);
		if (way)
		{
			
			i = AddEntry_INT(i, "+ Record", "", (int*)&maxrecord, 0, 1, 1); 
			if (maxrecord)
			{
				i = AddEntry_INT(i, " Start",  "route_record_start;txt Record start!", &menuadd, 0, 0, 0);
				i = AddEntry_INT(i, " Stop",  "route_record_stop;txt Record stop!", &menuadd, 0, 0, 0);
				i = AddEntry_INT(i, " Addpoint",  "route_record_add;txt Add point!", &menuadd, 0, 0, 0);
				i = AddEntry_INT(i, " Clear",  "route_clear;txt All lines cleared!", &menuadd, 0, 0, 0);
				i = AddEntry_INT(i, " Save",  "route_save;txt Route saved!", &menuadd, 0, 0, 0);
			}

			i = AddEntry_INT(i, "+ Add", "", (int*)&maxadd, 0, 1, 1); 
			if (maxadd)
			{
				i = AddEntry_INT(i, " Add 1",  "route_record_line 1;txt Record start line 1", &menuadd, 0, 0, 0);
				i = AddEntry_INT(i, " Add 2",  "route_record_line 2;txt Record start line 2", &menuadd, 0, 0, 0);
				i = AddEntry_INT(i, " Add 3",  "route_record_line 3;txt Record start line 3", &menuadd, 0, 0, 0);
				i = AddEntry_INT(i, " Add 4",  "route_record_line 4;txt Record start line 4", &menuadd, 0, 0, 0);
				i = AddEntry_INT(i, " Add 5",  "route_record_line 5;txt Record start line 5", &menuadd, 0, 0, 0);
			}

			i = AddEntry_INT(i, "+ Clear", "", (int*)&maxclear, 0, 1, 1); 
			if (maxclear)
			{
				i = AddEntry_INT(i, " Clear 1",  "route_clear_line 1;txt Clear line 1", &menuadd, 0, 0, 0);
				i = AddEntry_INT(i, " Clear 2",  "route_clear_line 2;txt Clear line 2", &menuadd, 0, 0, 0);
				i = AddEntry_INT(i, " Clear 3",  "route_clear_line 3;txt Clear line 3", &menuadd, 0, 0, 0);
				i = AddEntry_INT(i, " Clear 4",  "route_clear_line 4;txt Clear line 4", &menuadd, 0, 0, 0);
				i = AddEntry_INT(i, " Clear 5",  "route_clear_line 5;txt Clear line 5", &menuadd, 0, 0, 0);
			}

			i = AddEntry_INT(i, "+ Set", "", (int*)&maxset, 0, 1, 1); 
			if (maxset)
			{
				i = AddEntry_INT(i, " RouteMode",  "route_mode change", &menuadd, 0, 0, 0);
			}

			if (!waymisc)i = AddEntry_INT(i, "+ Misc", "", (int*)&waymisc, 0, 1, 1); 
			else i = AddEntry_INT(i, "- Misc", "", (int*)&waymisc, 0, 1, 1); 
			if (waymisc)
			{
				i = AddEntry_INT(i, " AutoDir",  "auto_direction change", &menuadd, 0, 0, 0);
				i = AddEntry_INT(i, " AutoBr",  "auto_br change", &menuadd, 0, 0, 0);
				i = AddEntry_INT(i, " AutoJump", "auto_jump change", &menuadd, 0, 0, 0);
				i = AddEntry_INT(i, " FPSHelper", "fps_helper change", &menuadd, 0, 0, 0);
				i = AddEntry_INT(i, " KnifeRush",  "kniferush change", &menuadd, 0, 0, 0);
				i = AddEntry_INT(i, " NoAll",  "noall change", &menuadd, 0, 0, 0);
				i = AddEntry_INT(i, " NoRefresh",  "norefresh change", &menuadd, 0, 0, 0);
				i = AddEntry_INT(i, " SmallView",  "smallview change", &menuadd, 0, 0, 0);
				i = AddEntry_INT(i, " RadarPoints",  "radarpoints change", &menuadd, 0, 0, 0);
			}
		}
	}

	menuItems = i;
}
//**********************************************************************************************************************************

void cMenu::Draw()
{
	if(!Active) return;

	int w = 180;
	int h = 20;
	int x;
	int y = 60;
	x = screeninfo.iWidth - w - 80;
	{
		TrapezoidalMenu(x,y,w,h);
	}
}

//**********************************************************************************************************************************

int cMenu::KeyEvent(int keynum)
{
	if( keynum == 128 || keynum == 240) //uparrow || mwheelup
	{
		if( menuSelect>0 ) menuSelect--;
		else menuSelect = menuItems - 1;
		return 0;
	}
	else if( keynum == 129 || keynum == 239) //downarrow || mwheeldown
	{
		if( menuSelect<menuItems-1 ) menuSelect++;
		else menuSelect = 0;
		return 0;
	}
	else if( keynum == 130 || keynum == 241 ) //leftarrow || leftbutton
	{
		if( menuEntry[menuSelect].value_i )
		{
			menuEntry[menuSelect].value_i[0] -= menuEntry[menuSelect].step_i;
			if( menuEntry[menuSelect].value_i[0] < menuEntry[menuSelect].min_i )
				menuEntry[menuSelect].value_i[0] = menuEntry[menuSelect].max_i;
		}
		cmd.exec(menuEntry[menuSelect].content); //note if used with menu open close item you will get out of possition
		return 0;
	}
	else if( keynum == 131 || keynum == 242 ) //rightarrow || rightbutton
	{
		if( menuEntry[menuSelect].value_i )
		{
			menuEntry[menuSelect].value_i[0] += menuEntry[menuSelect].step_i;
			if( menuEntry[menuSelect].value_i[0] > menuEntry[menuSelect].max_i )
				menuEntry[menuSelect].value_i[0] = menuEntry[menuSelect].min_i;
		}
		cmd.exec(menuEntry[menuSelect].content); //note if used with menu open close item you will get out of possition
		return 0;
	}
	return 1;
}

//**********************************************************************************************************************************


