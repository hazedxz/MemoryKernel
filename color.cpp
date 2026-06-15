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

#define BOUND_INTEGER(var,min,max) if((var)>(max)){(var)=(max);};if((var)<(min)){(var)=(min);}
ColorManager colorList;

//**********************************************************************************************************************************

void ColorManager::init()
{
	indexes.clear();
	list.clear();
	insertpos = 0;
	//   identifer           R   G   B   A                     Access Index
	add("cross"           , 80,150, 30,110               ); // index: 0
	add("team1"           ,255, 40, 40                   ); // index: 1
	add("team2"           , 40, 80,255                   ); // index: 2
	add("hud"             ,250,250, 22,254               ); // index: 3
	add("back"            ,  0,  0,  0,128               ); // index: 4
	add("radar1"          , 80,150, 30,110               ); // index: 5
	add("text"            ,255,255,255,255               ); // index: 6
	add("con_back"        , 15, 50,255, 50               ); // index: 7
	add("con_text"        ,220,220,220 	                 ); // index: 8
	add("con_text2"       ,  0,128,  0    	             ); // index: 9
	add("con_edit"        ,255,255,255,255               ); // index: 10
	add("menu_text"       ,220,220,220,200               ); // index: 11
	add("nade"            ,100,255,160                   ); // index: 12
	add("menu1"           , 51, 51,204,180               ); // index: 13
	add("menu2"           , 51, 51,204,100               ); // index: 14
	add("menu3"           , 51, 51,204,118               ); // index: 15
	add("gui"             , 51, 51,204,100               ); // index: 16
	add("snd_step"        ,255,255,255,255				 ); // index: 17
	add("snd_weapon"      ,144,155,255,255				 ); // index: 18
	add("snd_hit"         ,222,100, 61,254				 ); // index: 19
	add("snd_special"     ,222,111,111,254				 ); // index: 20
	add("snd_default"     ,222,255,222,255				 ); // index: 21
	add("tsound"          ,255, 40, 40,150               ); // index: 22
	add("ctsound"         , 40, 80,255,150               ); // index: 23
	add("sound"           , 68, 68,255                   ); // index: 24
	add("wpt"             ,  0,128,  0                   ); // index: 25
	add("sky"             ,255,000,255,255               ); // index: 26
	add("yellow"          ,255,255,000,255               ); // index: 27
	add("target"          ,000,255,000,255               ); // index: 28
	add("ent"             ,255,000,255,255               ); // index: 29
	add("way"             ,255,000,255,255               ); // index: 30
} 

//**********************************************************************************************************************************

void ColorEntry::fill_missing()
{
	compiled = (r<<24) + (g<<16) + (b<<8) + a;
	fr= float(r)/255.0/30.0;
	fg= float(g)/255.0/30.0;
	fb= float(b)/255.0/30.0;
	onebased_r=float(r)/255.0;
	onebased_g=float(g)/255.0;
	onebased_b=float(b)/255.0;
	onebased_a=float(a)/255.0;
}

//**********************************************************************************************************************************

void ColorManager::add(const char* name,int r, int g, int b, int a)
{
	indexes.add(name,insertpos);
	ColorEntry tmp;
	tmp.r=r;
	tmp.g=g;
	tmp.b=b;
	tmp.a=a;
	tmp.fill_missing();
	list.push_back(tmp);
	insertpos++;
}

//**********************************************************************************************************************************

void ColorManager::set(char* name, char* red, char* green, char* blue, char* alpha)
{
	if( !indexes.find(name) ){ return; }
	int index = indexes.num;
	char format[]="%d";
	ColorEntry tmp;
	sscanf(red   ,format,&tmp.r);
	sscanf(green ,format,&tmp.g);
	sscanf(blue  ,format,&tmp.b);
	sscanf(alpha ,format,&tmp.a);
	tmp.fill_missing();
	BOUND_INTEGER(index,0,int(list.size()-1));
	list[index] = tmp;
}

//**********************************************************************************************************************************

ColorEntry* PlayerColor(int ax)
{
	static ColorEntry colorDefault;

	if(cvar.aim_glow && ax == g_Aimbot.iTargetID && me.alive) { return colorList.get(28); }
	if(vPlayers[ax].vip || vPlayers[ax].hasbomb)           { return colorList.get(27); }
	if(vPlayers[ax].team == 1)                             { return colorList.get(1); }
	else                                                   { return colorList.get(2); }
}

//**********************************************************************************************************************************
