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

CVARlist cvar;

//**********************************************************************************************************************************

void CVARlist::init()
{
	memset((char*)this, 0, sizeof(*this));
	#define REGISTER_CVAR_FLOAT(name,defaultvalue) cmd.AddCvarFloat(#name, &##name );name=defaultvalue##f;
	#define REGISTER_CVAR_INT(name,defaultvalue) cmd.AddCvarInt(#name, &##name );name=defaultvalue;

    //Used in source and cfg
	REGISTER_CVAR_INT(cheatmode,0)
	
	//Aimbot	
	REGISTER_CVAR_FLOAT(aim_fov,360.0)
	REGISTER_CVAR_FLOAT(aim_distance,8142.0)
	REGISTER_CVAR_INT(aim_team,0)
	REGISTER_CVAR_INT(aim_thru,0)
	REGISTER_CVAR_INT(aim_silent,1)
	REGISTER_CVAR_INT(aim_auto,0)
	REGISTER_CVAR_INT(aim_punch,1)
	REGISTER_CVAR_INT(aim_enable,1)
	REGISTER_CVAR_INT(aim_trigger,1)
	REGISTER_CVAR_INT(aim_tspot,0)
	REGISTER_CVAR_INT(aim_tfov,30)
	REGISTER_CVAR_INT(aim_wall,0)
	REGISTER_CVAR_INT(knf_attack,1)
	REGISTER_CVAR_INT(knf_distattack,72)
	REGISTER_CVAR_INT(knf_distattack2,64)
	REGISTER_CVAR_INT(knf_aimfov,360)
	REGISTER_CVAR_INT(knf_aim,1)
	REGISTER_CVAR_FLOAT(aim_x_duck,5.0)
	REGISTER_CVAR_FLOAT(aim_y_duck,2.0)
	REGISTER_CVAR_FLOAT(aim_z_duck,25.0)
	REGISTER_CVAR_FLOAT(aim_x_stand,5.0)
	REGISTER_CVAR_FLOAT(aim_y_stand,2.0)
	REGISTER_CVAR_FLOAT(aim_z_stand,22.0)
	REGISTER_CVAR_FLOAT(aim_x_jump,2.0)
	REGISTER_CVAR_FLOAT(aim_y_jump,5.0)
	REGISTER_CVAR_FLOAT(aim_z_jump,13.0)

	//Aimbot extra
	REGISTER_CVAR_INT(aim_glow,0)
	REGISTER_CVAR_INT(crosshair,1)
	REGISTER_CVAR_INT(antizoom,0)
	REGISTER_CVAR_INT(spreadvar,1)
	REGISTER_CVAR_FLOAT(recoil,0.0)
	REGISTER_CVAR_INT(norecoil,0)
	REGISTER_CVAR_INT(norecoil_visual,0)
	REGISTER_CVAR_INT(norecoil_visible,0)
	REGISTER_CVAR_INT(nospread,0) 
	REGISTER_CVAR_INT(nospread_visible,0) 
	REGISTER_CVAR_FLOAT(ftime,0.00)
	REGISTER_CVAR_FLOAT(dtime,0.00)
	REGISTER_CVAR_FLOAT(sdelay,0.00)
	REGISTER_CVAR_FLOAT(rdelay,0.00)

	//pmEyePos Corrections
	REGISTER_CVAR_FLOAT(height_correction,4.0)//PM_PlayerMove
	REGISTER_CVAR_FLOAT(forward_correction,0.0)//PM_PlayerMove
	REGISTER_CVAR_FLOAT(right_correction,-0.1)//PM_PlayerMove
	REGISTER_CVAR_FLOAT(distance_correction,0.0)//CreateMove
	REGISTER_CVAR_FLOAT(preshoot,0.0)//PM_PlayerMove

	//Speed
	REGISTER_CVAR_FLOAT(speed,1.0)
	REGISTER_CVAR_FLOAT(aspeed,0.0)
	REGISTER_CVAR_INT(rspeed,1) //reload on off

	//wavspeed
	REGISTER_CVAR_FLOAT(wavspeed,1.0)
	REGISTER_CVAR_INT(fps_helper,0)

	//Opengl
	REGISTER_CVAR_INT(skeleton,0)
	REGISTER_CVAR_INT(chams,0)
	REGISTER_CVAR_INT(chamswall,0)
	REGISTER_CVAR_INT(chamsglow,0)
	REGISTER_CVAR_INT(reloadmeter,0)
	REGISTER_CVAR_INT(barrel,0)
	REGISTER_CVAR_INT(blood,0)
	REGISTER_CVAR_INT(nosky,0)

	//Info
	REGISTER_CVAR_INT(info,1)
	REGISTER_CVAR_INT(myhud,0)
	REGISTER_CVAR_INT(infobars,0)

	//ESP
	REGISTER_CVAR_INT(name,1)
	REGISTER_CVAR_INT(espteam,0)
	REGISTER_CVAR_INT(weapon,0) 
	REGISTER_CVAR_INT(sequence,0)
	REGISTER_CVAR_INT(playerinfo,0)
	REGISTER_CVAR_INT(entesp,0)
	REGISTER_CVAR_INT(esptype,0)

	//Sound
	REGISTER_CVAR_INT(soundesp,1)
	REGISTER_CVAR_INT(soundtol,200)
	REGISTER_CVAR_FLOAT(soundtime,1.0)
	REGISTER_CVAR_INT(killsound,0)

	//Radar
	REGISTER_CVAR_INT(radar,1)
	REGISTER_CVAR_INT(miniradar,1)
    REGISTER_CVAR_INT(radar_size,75)//55
    REGISTER_CVAR_INT(miniradar_size,80)//55
	REGISTER_CVAR_INT(radar_x,102)
	REGISTER_CVAR_INT(radar_y,108)
	REGISTER_CVAR_FLOAT(radar_range,2500.0)
	REGISTER_CVAR_INT(radarpoints,1)

	//Optimizations
	REGISTER_CVAR_INT(noall,0)
	REGISTER_CVAR_INT(norefresh,0)
	
	//View
	REGISTER_CVAR_INT(smallview,0)
	REGISTER_CVAR_INT(view_width,160)//200
	REGISTER_CVAR_INT(view_height,120)//150

	//FX
	REGISTER_CVAR_INT(chase,0)
	REGISTER_CVAR_FLOAT(chaseoffs,0.0)//se pone a cero si chase es 0
	REGISTER_CVAR_INT(noflash,0)
	REGISTER_CVAR_INT(nosmoke,0)

	//Way
	REGISTER_CVAR_INT(rush,0)
	REGISTER_CVAR_INT(kniferush,0)
	REGISTER_CVAR_INT(knifeattackdist,2000)
	
	//Direction
	REGISTER_CVAR_INT(auto_jump,1) 
	REGISTER_CVAR_INT(jump_dist,30)
	REGISTER_CVAR_INT(auto_br,1) 
	REGISTER_CVAR_FLOAT(rush_step,500.0)
	REGISTER_CVAR_INT(action_step,50)
	REGISTER_CVAR_INT(direction_step,15.0)
	REGISTER_CVAR_INT(auto_direction,1)

	//Idhook
	REGISTER_CVAR_INT(id_mode,1)

	//GYJ route
    REGISTER_CVAR_INT(route_draw,2)
    REGISTER_CVAR_INT(route_mode,1)
	REGISTER_CVAR_FLOAT(routefinddist,150.0)
    REGISTER_CVAR_INT(autoroute,0)
	REGISTER_CVAR_FLOAT(routedist,100.0)

	//strafe main
	REGISTER_CVAR_INT(strafehack,0) //1-2
	REGISTER_CVAR_INT(strafeautodir,0)
	REGISTER_CVAR_INT(groundstrafe,0) //1-2
	REGISTER_CVAR_INT(bhop,0) //1-2
	REGISTER_CVAR_INT(jumpbug,0) //1-2
	REGISTER_CVAR_INT(fastrun,0) //1-2
	REGISTER_CVAR_INT(strafe_helper,0)
	REGISTER_CVAR_INT(slowdown,0)
	REGISTER_CVAR_INT(show_kz,0)

	//strafe settings
	REGISTER_CVAR_INT(strafe_dir,1) // 1-4
	REGISTER_CVAR_INT(strafe_crazy,0)
	REGISTER_CVAR_INT(strafe_invisible,1)
	REGISTER_CVAR_INT(strafe_speed,69)
	REGISTER_CVAR_FLOAT(strafe_sidemove,437.8928)
	REGISTER_CVAR_INT(strafe_angle,30)

	REGISTER_CVAR_INT(fastrun_nsd,1)

	REGISTER_CVAR_INT(gstrafe_standup,1)
	REGISTER_CVAR_INT(gstrafe_bhop,1)
	REGISTER_CVAR_FLOAT(gstrafe_nsd,0.0)

	REGISTER_CVAR_INT(bhop_nsd,1)
	REGISTER_CVAR_INT(bhop_autoduck,1)
	REGISTER_CVAR_INT(bhop_cnt_rand_min,0)
	REGISTER_CVAR_INT(bhop_cnt_rand_max,12)
	REGISTER_CVAR_INT(bhop_cnt_rand,1)
	REGISTER_CVAR_INT(bhop_cnt,4)

	REGISTER_CVAR_INT(jumpbugauto,0)
	REGISTER_CVAR_INT(jumpbugslow,100)
	REGISTER_CVAR_INT(jumpbugslowspeed,1)

	REGISTER_CVAR_INT(strafe_helper_boost,0)
	REGISTER_CVAR_INT(strafe_helper_add_strafe,1)
	REGISTER_CVAR_INT(strafe_helper_max_strafe_rand,0)
	REGISTER_CVAR_INT(strafe_helper_max_strafe_min,3)
	REGISTER_CVAR_INT(strafe_helper_max_strafe_max,6)
	REGISTER_CVAR_INT(strafe_helper_max_strafe,6)
	REGISTER_CVAR_INT(strafe_helper_main,30)
	REGISTER_CVAR_INT(strafe_helper_move_rand,1)
	REGISTER_CVAR_INT(strafe_helper_move_rand_min,50)
	REGISTER_CVAR_INT(strafe_helper_move_rand_max,400)
	REGISTER_CVAR_INT(strafe_helper_move,400)

	REGISTER_CVAR_INT(antiaimpitch,0) //1-6
	REGISTER_CVAR_INT(antiaimyaw,0) //1-9
	
	REGISTER_CVAR_FLOAT(test,0.0)
}	

//**********************************************************************************************************************************

void HlEngineCommand(const char* command)
{
	if(!gEngfuncs.pfnClientCmd) { return; }
	gEngfuncs.pfnClientCmd( const_cast<char*>(command) );
}

//**********************************************************************************************************************************

void HandleCvarInt(char* name, int* value)
{
	char* arg1 = cmd.argC(1); 
	if (!strcmp(arg1,"change"))
	{
		if(*value) *value=0; 
		else *value=1; 
		if(cvar.info||gMenu.Active){ 
			sprintf(gHudMessage,"%s changed to %d", name, *value );
			gHudTimer.countdown(3);}
		return;
	}
	if (!strcmp(arg1,"up")){*value += cmd.argI(2);return;}
	if (!strcmp(arg1,"down")){*value -= cmd.argI(2);return;}
	if (!strcmp(arg1,"hide")){*value = cmd.argI(2);return;}
	if (!*arg1)
	{
		Con_Echo( "CVAR &w%s&a = %i\n",name,*value); 
		return;
	}
	*value = cmd.argI(1);
}

//**********************************************************************************************************************************

void HandleCvarFloat(char* name, float* value)
{
	char* arg1 = cmd.argC(1);  
	if (!strcmp(arg1,"change"))
	{
		if(*value) *value=0; 
		else *value=1;
		if(cvar.info||gMenu.Active){ 
			sprintf(gHudMessage,"%s changed to %f", name, *value );
			gHudTimer.countdown(3); }
		return;
	}
	if (!strcmp(arg1,"up")){*value += cmd.argF(2);return;}
	if (!strcmp(arg1,"down")){*value -= cmd.argF(2);return;}
	if (!strcmp(arg1,"hide")){*value = cmd.argI(2);return;}
	if (!*arg1)
	{
		Con_Echo( "CVAR &w%s&a = %f\n",name,*value);
		//Con_Echo( "CVAR &w%s&r = %f\n",name,*value); 
		return;
	}
	*value = cmd.argF(1);
}

//**********************************************************************************************************************************

bool isHlCvar(char* name)
{
	if(!gEngfuncs.pfnGetCvarPointer) { return false; }
	cvar_s* test = gEngfuncs.pfnGetCvarPointer(name);
	return (test!=NULL);
}

//**********************************************************************************************************************************

bool HandleHlCvar(char* name)
{
	if(!gEngfuncs.pfnGetCvarPointer) { return false; }
	cvar_s* ptr = gEngfuncs.pfnGetCvarPointer(name);
	if(!ptr) { return false; }
	HandleCvarFloat(name,&ptr->value);
	return true;
}

//**********************************************************************************************************************************

