#include "client.h"

static int optimizeNum = 0;
void optimization(void)
{
	if(optimizeNum < 3)
	{
		cmd.exec("#rate 99999");
		cmd.exec("#ex_interp 0.02");
		cmd.exec("#ex_extrapmax 1.2");
		cmd.exec("#fps_modem 500");
		cmd.exec("#fps_max 500");
		cmd.exec("#developer 1");
		cmd.exec("#hud_fastswitch 1");
		cmd.exec("#d_spriteskip 0");
		cmd.exec("#max_shells 0");
		cmd.exec("#fastsprites 1");
		cmd.exec("#joystick 0");
		cmd.exec("#max_smokepuffs 0");
		cmd.exec("#brightness 30");
		cmd.exec("#gamma 3");
		cmd.exec("#r_mmx 1");
		cmd.exec("#mp_decals 300");
		cmd.exec("#violence_ablood 1"); //needed for cvar.colorblood
		cmd.exec("#violence_agibs 1"); //needed for cvar.colorblood
		cmd.exec("#violence_hblood 1"); //needed for cvar.colorblood
		cmd.exec("#violence_hgibs 1"); //needed for cvar.colorblood
		cmd.exec("#r_dynamic 0");
		cmd.exec("#r_novis 0");
		cmd.exec("#r_traceglow 1");
		cmd.exec("#r_wateralpha 1");
		cmd.exec("#r_mirroralpha 0");
		cmd.exec("#r_bmodelhighfrac 5.0");
		cmd.exec("#r_lightmap 0");
		cmd.exec("#r_fullbright 0");
		cmd.exec("#r_norefresh 0");
		cmd.exec("#r_decals 4096");
		cmd.exec("#cl_showfps 1");
		cmd.exec("#cl_updaterate 99999");
		cmd.exec("#cl_cmdrate 99999");
		cmd.exec("#cl_allowdownload 0");
		cmd.exec("#cl_allowupload 0");
		cmd.exec("#hud_centerid 0");
		cmd.exec("#cl_weather 0");
		cmd.exec("#cl_shadows 0");
		cmd.exec("#cl_nosmooth 1");
		cmd.exec("#cl_smoothtime 0.1");
		cmd.exec("#cl_vsmoothing 0.05");
		cmd.exec("#cl_nopred 1");
		cmd.exec("#cl_minmodels 0");
		cmd.exec("#gl_affinemodels 0");
		cmd.exec("#gl_alphamin 0.25");
		cmd.exec("#gl_clear 1");
		cmd.exec("#gl_dither 1");
		cmd.exec("#gl_flipmatrix 0");
		cmd.exec("#gl_wireframe 0");
		cmd.exec("#gl_cull 1");
		cmd.exec("#gl_keeptjunctions 0");
		cmd.exec("#gl_smoothmodels 0");
		cmd.exec("#gl_palette_tex 0");
		cmd.exec("#gl_round_down 10");
		cmd.exec("#gl_lightholes 0");
		cmd.exec("#gl_texturemode \"GL_LINEAR_MIPMAP_NEAREST\"");
		cmd.exec("#gl_wateramp 0");
		cmd.exec("#net_graph 3");
		cmd.exec("#cl_timeout 999999 0");
	}
	optimizeNum++;
}


//**********************************************************************************************************************************

void Compras()
{ 
	//cfg
	cmd.exec("alias sayon \".voice_inputfromfile 1;.voice_loopback 1;.+voicerecord\"");
	cmd.exec("alias siglive \"route_load\"");
	cmd.exec("alias sigdead \"\"");
	cmd.exec("alias sigswitch \"#impulse 101;#slot2\"");
	cmd.exec("alias sigswitch1 \"#impulse 101;#slot1\"");

	cmd.exec("alias sky01 \"color sky 255 000 255;later 0.1 sky02\"");
	cmd.exec("alias sky02 \"color sky 245 000 255;later 0.1 sky03\"");
	cmd.exec("alias sky03 \"color sky 235 000 255;later 0.1 sky04\"");
	cmd.exec("alias sky04 \"color sky 225 000 255;later 0.1 sky05\"");
	cmd.exec("alias sky05 \"color sky 215 000 255;later 0.1 sky06\"");

	cmd.exec("alias sky06 \"color sky 205 000 255;later 0.1 sky07\"");
	cmd.exec("alias sky07 \"color sky 195 000 255;later 0.1 sky08\"");
	cmd.exec("alias sky08 \"color sky 185 000 255;later 0.1 sky09\"");
	cmd.exec("alias sky09 \"color sky 175 000 255;later 0.1 sky10\"");
	cmd.exec("alias sky10 \"color sky 165 000 255;later 0.1 sky11\"");

	cmd.exec("alias sky11 \"color sky 155 000 255;later 0.1 sky12\"");
	cmd.exec("alias sky12 \"color sky 145 000 255;later 0.1 sky13\"");
	cmd.exec("alias sky13 \"color sky 135 000 255;later 0.1 sky14\"");
	cmd.exec("alias sky14 \"color sky 125 000 255;later 0.1 sky15\"");
	cmd.exec("alias sky15 \"color sky 115 000 255;later 0.1 sky16\"");

	cmd.exec("alias sky16 \"color sky 105 000 255;later 0.1 sky17\"");
	cmd.exec("alias sky17 \"color sky 095 000 255;later 0.1 sky18\"");
	cmd.exec("alias sky18 \"color sky 085 000 255;later 0.1 sky19\"");
	cmd.exec("alias sky19 \"color sky 075 000 255;later 0.1 sky20\"");
	cmd.exec("alias sky20 \"color sky 065 000 255;later 0.1 sky21\"");

	cmd.exec("alias sky21 \"color sky 055 000 255;later 0.1 sky22\"");
	cmd.exec("alias sky22 \"color sky 045 000 255;later 0.1 sky23\"");
	cmd.exec("alias sky23 \"color sky 035 000 255;later 0.1 sky24\"");
	cmd.exec("alias sky24 \"color sky 025 000 255;later 0.1 sky25\"");
	cmd.exec("alias sky25 \"color sky 015 000 255;later 0.1 sky26\"");

	cmd.exec("alias sky26 \"color sky 005 000 255;later 0.1 sky27\"");
	cmd.exec("alias sky27 \"color sky 015 000 255;later 0.1 sky28\"");
	cmd.exec("alias sky28 \"color sky 025 000 255;later 0.1 sky29\"");
	cmd.exec("alias sky29 \"color sky 035 000 255;later 0.1 sky30\"");
	cmd.exec("alias sky30 \"color sky 045 000 255;later 0.1 sky31\"");

	cmd.exec("alias sky31 \"color sky 055 000 255;later 0.1 sky32\"");
	cmd.exec("alias sky32 \"color sky 065 000 255;later 0.1 sky33\"");
	cmd.exec("alias sky33 \"color sky 075 000 255;later 0.1 sky34\"");
	cmd.exec("alias sky34 \"color sky 085 000 255;later 0.1 sky35\"");
	cmd.exec("alias sky35 \"color sky 095 000 255;later 0.1 sky36\"");

	cmd.exec("alias sky36 \"color sky 105 000 255;later 0.1 sky37\"");
	cmd.exec("alias sky37 \"color sky 115 000 255;later 0.1 sky38\"");
	cmd.exec("alias sky38 \"color sky 125 000 255;later 0.1 sky39\"");
	cmd.exec("alias sky39 \"color sky 135 000 255;later 0.1 sky40\"");
	cmd.exec("alias sky40 \"color sky 145 000 255;later 0.1 sky41\"");

	cmd.exec("alias sky41 \"color sky 155 000 255;later 0.1 sky42\"");
	cmd.exec("alias sky42 \"color sky 165 000 255;later 0.1 sky43\"");
	cmd.exec("alias sky43 \"color sky 175 000 255;later 0.1 sky44\"");
	cmd.exec("alias sky44 \"color sky 185 000 255;later 0.1 sky45\"");
	cmd.exec("alias sky45 \"color sky 195 000 255;later 0.1 sky46\"");

	cmd.exec("alias sky46 \"color sky 205 000 255;later 0.1 sky47\"");
	cmd.exec("alias sky47 \"color sky 215 000 255;later 0.1 sky48\"");
	cmd.exec("alias sky48 \"color sky 225 000 255;later 0.1 sky49\"");
	cmd.exec("alias sky49 \"color sky 235 000 255;later 0.1 sky50\"");
	cmd.exec("alias sky50 \"color sky 245 000 255;later 0.1 sky01\"");
	cmd.exec("later 1 sky01");

	cmd.exec("alias way01 \"color way 000 255 255;later 0.1 way02\"");
	cmd.exec("alias way02 \"color way 000 255 245;later 0.1 way03\"");
	cmd.exec("alias way03 \"color way 000 255 235;later 0.1 way04\"");
	cmd.exec("alias way04 \"color way 000 255 225;later 0.1 way05\"");
	cmd.exec("alias way05 \"color way 000 255 215;later 0.1 way06\"");

	cmd.exec("alias way06 \"color way 000 255 205;later 0.1 way07\"");
	cmd.exec("alias way07 \"color way 000 255 195;later 0.1 way08\"");
	cmd.exec("alias way08 \"color way 000 255 185;later 0.1 way09\"");
	cmd.exec("alias way09 \"color way 000 255 175;later 0.1 way10\"");
	cmd.exec("alias way10 \"color way 000 255 165;later 0.1 way11\"");

	cmd.exec("alias way11 \"color way 000 255 155;later 0.1 way12\"");
	cmd.exec("alias way12 \"color way 000 255 145;later 0.1 way13\"");
	cmd.exec("alias way13 \"color way 000 255 135;later 0.1 way14\"");
	cmd.exec("alias way14 \"color way 000 255 125;later 0.1 way15\"");
	cmd.exec("alias way15 \"color way 000 255 115;later 0.1 way16\"");

	cmd.exec("alias way16 \"color way 000 255 105;later 0.1 way17\"");
	cmd.exec("alias way17 \"color way 000 255 095;later 0.1 way18\"");
	cmd.exec("alias way18 \"color way 000 255 085;later 0.1 way19\"");
	cmd.exec("alias way19 \"color way 000 255 075;later 0.1 way20\"");
	cmd.exec("alias way20 \"color way 000 255 065;later 0.1 way21\"");

	cmd.exec("alias way21 \"color way 000 255 055;later 0.1 way22\"");
	cmd.exec("alias way22 \"color way 000 255 045;later 0.1 way23\"");
	cmd.exec("alias way23 \"color way 000 255 035;later 0.1 way24\"");
	cmd.exec("alias way24 \"color way 000 255 025;later 0.1 way25\"");
	cmd.exec("alias way25 \"color way 000 255 015;later 0.1 way26\"");

	cmd.exec("alias way26 \"color way 000 255 005;later 0.1 way27\"");
	cmd.exec("alias way27 \"color way 000 255 015;later 0.1 way28\"");
	cmd.exec("alias way28 \"color way 000 255 025;later 0.1 way29\"");
	cmd.exec("alias way29 \"color way 000 255 035;later 0.1 way30\"");
	cmd.exec("alias way30 \"color way 000 255 045;later 0.1 way31\"");

	cmd.exec("alias way31 \"color way 000 255 055;later 0.1 way32\"");
	cmd.exec("alias way32 \"color way 000 255 065;later 0.1 way33\"");
	cmd.exec("alias way33 \"color way 000 255 075;later 0.1 way34\"");
	cmd.exec("alias way34 \"color way 000 255 085;later 0.1 way35\"");
	cmd.exec("alias way35 \"color way 000 255 095;later 0.1 way36\"");

	cmd.exec("alias way36 \"color way 000 255 105;later 0.1 way37\"");
	cmd.exec("alias way37 \"color way 000 255 115;later 0.1 way38\"");
	cmd.exec("alias way38 \"color way 000 255 125;later 0.1 way39\"");
	cmd.exec("alias way39 \"color way 000 255 135;later 0.1 way40\"");
	cmd.exec("alias way40 \"color way 000 255 145;later 0.1 way41\"");

	cmd.exec("alias way41 \"color way 000 255 155;later 0.1 way42\"");
	cmd.exec("alias way42 \"color way 000 255 165;later 0.1 way43\"");
	cmd.exec("alias way43 \"color way 000 255 175;later 0.1 way44\"");
	cmd.exec("alias way44 \"color way 000 255 185;later 0.1 way45\"");
	cmd.exec("alias way45 \"color way 000 255 195;later 0.1 way46\"");

	cmd.exec("alias way46 \"color way 000 255 205;later 0.1 way47\"");
	cmd.exec("alias way47 \"color way 000 255 215;later 0.1 way48\"");
	cmd.exec("alias way48 \"color way 000 255 225;later 0.1 way49\"");
	cmd.exec("alias way49 \"color way 000 255 235;later 0.1 way50\"");
	cmd.exec("alias way50 \"color way 000 255 245;later 0.1 way01\"");
	cmd.exec("later 1 way01");
	
	cmd.exec("alias blood0 \"blood 0;alias bloodchange blood1;txt blood changed to 0\"");
	cmd.exec("alias blood1 \"blood 1;alias bloodchange blood2;txt blood changed to 1\"");
	cmd.exec("alias blood2 \"blood 2;alias bloodchange blood3;txt blood changed to 2\"");
	cmd.exec("alias blood3 \"blood 3;alias bloodchange blood4;txt blood changed to 3\"");
	cmd.exec("alias blood4 \"blood 4;alias bloodchange blood5;txt blood changed to 4\"");
	cmd.exec("alias blood5 \"blood 5;alias bloodchange blood6;txt blood changed to 5\"");
	cmd.exec("alias blood6 \"blood 6;alias bloodchange blood7;txt blood changed to 6\"");
	cmd.exec("alias blood7 \"blood 7;alias bloodchange blood8;txt blood changed to 7\"");
	cmd.exec("alias blood8 \"blood 8;alias bloodchange blood0;txt blood changed to 8\"");
	cmd.exec("alias bloodchange \"blood1\"");

	cmd.exec("alias chams1 \"chams 1;alias chamschange chams2;txt chams changed to 1\"");
	cmd.exec("alias chams2 \"chams 2;alias chamschange chams3;txt chams changed to 2\"");
	cmd.exec("alias chams3 \"chams 3;alias chamschange chams0;txt chams changed to 3\"");
	cmd.exec("alias chams0 \"chams 0;alias chamschange chams1;txt chams changed to 0\"");
	cmd.exec("alias chamschange \"chams1\"");

	cmd.exec("alias antiaimpitch1 \"antiaimpitch 1;alias antiaimpitchchange antiaimpitch2;txt Pitch changed to DOWN\"");
	cmd.exec("alias antiaimpitch2 \"antiaimpitch 2;alias antiaimpitchchange antiaimpitch3;txt Pitch changed to UP\"");
	cmd.exec("alias antiaimpitch3 \"antiaimpitch 3;alias antiaimpitchchange antiaimpitch4;txt Pitch changed to FAKEDOWN\"");
	cmd.exec("alias antiaimpitch4 \"antiaimpitch 4;alias antiaimpitchchange antiaimpitch5;txt Pitch changed to FAKEUP\"");
	cmd.exec("alias antiaimpitch5 \"antiaimpitch 5;alias antiaimpitchchange antiaimpitch6;txt Pitch changed to SPIN X\"");
	cmd.exec("alias antiaimpitch6 \"antiaimpitch 6;alias antiaimpitchchange antiaimpitch0;txt Pitch changed to STATIC\"");
	cmd.exec("alias antiaimpitch0 \"antiaimpitch 0;alias antiaimpitchchange antiaimpitch1;txt Pitch changed to 0\"");
	cmd.exec("alias antiaimpitchchange \"antiaimpitch1\"");

	cmd.exec("alias antiaimyaw1 \"antiaimyaw 1;alias antiaimyawchange antiaimyaw2;txt Yaw changed to BACKWARDS\"");
	cmd.exec("alias antiaimyaw2 \"antiaimyaw 2;alias antiaimyawchange antiaimyaw3;txt Yaw changed to STATIC LEFT\"");
	cmd.exec("alias antiaimyaw3 \"antiaimyaw 3;alias antiaimyawchange antiaimyaw4;txt Yaw changed to STATIC RIGHT\"");
	cmd.exec("alias antiaimyaw4 \"antiaimyaw 4;alias antiaimyawchange antiaimyaw5;txt Yaw changed to LEFT\"");
	cmd.exec("alias antiaimyaw5 \"antiaimyaw 5;alias antiaimyawchange antiaimyaw6;txt Yaw changed to RIGHT\"");
	cmd.exec("alias antiaimyaw6 \"antiaimyaw 6;alias antiaimyawchange antiaimyaw7;txt Yaw changed to SPIN Y\"");
	cmd.exec("alias antiaimyaw7 \"antiaimyaw 7;alias antiaimyawchange antiaimyaw8;txt Yaw changed to STATIC\"");
	cmd.exec("alias antiaimyaw8 \"antiaimyaw 8;alias antiaimyawchange antiaimyaw9;txt Yaw changed to LOOK BACKWARDS JITTER\"");
	cmd.exec("alias antiaimyaw9 \"antiaimyaw 9;alias antiaimyawchange antiaimyaw0;txt Yaw changed to JITTER\"");
	cmd.exec("alias antiaimyaw0 \"antiaimyaw 0;alias antiaimyawchange antiaimyaw1;txt Yaw changed to 0\"");
	cmd.exec("alias antiaimyawchange \"antiaimyaw1\"");

}