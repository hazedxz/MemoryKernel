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

#ifndef CVAR_H
#define CVAR_H

//**********************************************************************************************************************************

typedef struct cvar_s
{
	char	*name;
	char	*string;
	int		flags;
	float	value;
	struct cvar_s *next;
} cvar_t;

//**********************************************************************************************************************************

class CVARlist
{

public:
	void init();

public:

	//Used in source and cfg
	int cheatmode;
	
	//Aimbot	
	float aim_fov;
	float aim_distance;
	int aim_team;
	int aim_thru;
	int aim_silent;
	int aim_auto;
	int aim_punch;
	int aim_enable;
	int aim_trigger;
	int aim_tspot;
	int aim_tfov;
	int aim_wall;
	int knf_attack;
	int knf_distattack;
	int knf_distattack2;
	int knf_aimfov;
	int knf_aim;
	float aim_x_duck;
	float aim_y_duck;
	float aim_z_duck;
	float aim_x_stand;
	float aim_y_stand;
	float aim_z_stand;
	float aim_x_jump;
	float aim_y_jump;
	float aim_z_jump;

	//Aimbot extra
	int aim_glow;
	int crosshair;
	int antizoom;
	int spreadvar;
	float recoil;
	int norecoil;
	int nospread;
	int nospread_visible;
	int norecoil_visual;
	int norecoil_visible;
	float ftime;
	float dtime;
	float sdelay;
	float rdelay;

	//pmEyePos Corrections
	float height_correction;
	float forward_correction;
	float right_correction;
	float distance_correction;
	float preshoot;

	//Speed
	float speed;
	float aspeed;
	int rspeed;

	//wavspeed
	float wavspeed;
	int fps_helper;

	//Opengl
	int skeleton;
	int chams;
	int chamswall;
	int chamsglow;
	int reloadmeter;
	int barrel;
	int blood;
	int nosky;

	//Info
	int info;
	int myhud;
	int infobars;

	//ESP
	int name;
	int espteam;
	int weapon;
	int sequence;
	int playerinfo;
	int entesp;
	int esptype;

	//Sound
	int soundesp;
	int soundtol;
	float soundtime;
	int killsound;

	//Radar
	int radar;
	int miniradar;
    int radar_size;
    int miniradar_size;
	int radar_x;
	int radar_y;
	float radar_range;
	int radarpoints;

	//Optimizations
	int noall;
	int norefresh;
	
	//View
	int smallview;
	int view_width;
	int view_height;

	//FX
	int chase;
	float chaseoffs;
	int noflash;
	int nosmoke;

	//Way
	int rush;
	int kniferush;
	int knifeattackdist;
	
	//Direction
	int auto_jump;
	int jump_dist;
	int auto_br;
	float rush_step;
	int action_step;
	int direction_step;
	int auto_direction;

	//Idhook
	int id_mode;

	//GYJ route
    int route_draw;
    int route_mode;
	float routefinddist;
    int autoroute;
	float routedist;

	//strafe main
	int strafehack;
	int strafeautodir;
	int groundstrafe;
	int bhop;
	int jumpbug;
	int fastrun;
	int strafe_helper;
	int slowdown;
	int show_kz;

	//strafe settings
	int strafe_dir;
	int strafe_crazy;
	int strafe_invisible;
	int strafe_speed;
	float strafe_sidemove;
	int strafe_angle;

	int fastrun_nsd;

	int gstrafe_standup;
	int gstrafe_bhop;
	float gstrafe_nsd;

	int bhop_nsd;
	int bhop_autoduck;
	int bhop_cnt_rand_min;
	int bhop_cnt_rand_max;
	int bhop_cnt_rand;
	int bhop_cnt;

	int jumpbugauto;
	int jumpbugslow;
	int jumpbugslowspeed;

	int strafe_helper_boost;
	int strafe_helper_add_strafe;
	int strafe_helper_max_strafe_rand;
	int strafe_helper_max_strafe_min;
	int strafe_helper_max_strafe_max;
	int strafe_helper_max_strafe;
	int strafe_helper_main;
	int strafe_helper_move_rand;
	int strafe_helper_move_rand_min;
	int strafe_helper_move_rand_max;
	int strafe_helper_move;

	int antiaimpitch;
	int antiaimyaw;

	float test;
};

//**********************************************************************************************************************************

extern CVARlist cvar;

//**********************************************************************************************************************************

#endif

//**********************************************************************************************************************************
