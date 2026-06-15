#include "client.h"

char ogcdir [256]="";

std::string getOgcDirFile(const char* basename)
{
	if(strstr(basename,"..")){ return ":*?\\/<>\""; }
	string ret = ogcdir;
	return (ret+basename);
}

void ogc_exec(const char* filename)
{
	string file = getOgcDirFile(filename);
	file += ".cfg";
	cmd.execFile( file.c_str() );
}

//**********************************************************************************************************************************

void func_play(){ sndPlaySound(getOgcDirFile(cmd.argC(1)).c_str(), SND_ASYNC); }

//**********************************************************************************************************************************

void func_alias()
{
	const char* name = cmd.argC(1);
	string& content = cmd.argS(2);
	cmd.AddAlias(name,content);
}

//**********************************************************************************************************************************

void func_bind()
{
	keyBindManager.addBind(cmd.argC(1),cmd.argC(2));
}

//**********************************************************************************************************************************

void func_unbind()
{
	keyBindManager.removeBind(cmd.argC(1));
}

//**********************************************************************************************************************************

void func_remap()
{
	keyBindManager.remapKey(cmd.argC(1),cmd.argC(2));
}

//**********************************************************************************************************************************

void func_savecvar()
{
	string filepath = getOgcDirFile(cmd.argC(1));
	ofstream ofs( filepath.c_str(), ios::binary );
	if( !ofs ){ Con_Echo( "file: %s &rsave failed.",filepath.c_str() ); return; }
	ofs.write( (char*)&cvar, sizeof(cvar) );
	ofs.close();
}

//**********************************************************************************************************************************

void func_loadcvar()
{
	string filepath = getOgcDirFile(cmd.argC(1));
	ifstream ifs( filepath.c_str(), ios::binary );
	if( !ifs )	
	{
		Con_Echo( "&rfile: &w%s &rload failed.\n",filepath.c_str() ); 
		return;
	}
	ifs.read( (char*)&cvar, sizeof(cvar) );
	ifs.close();
}

//**********************************************************************************************************************************

void func_exec()     
{ 
	ogc_exec( cmd.argC(1) ); 
}

//**********************************************************************************************************************************

void func_menu_toggle()
{
	gMenu.Active = !gMenu.Active;
	cmd.exec("savecvar cvar.bin");
}

//**********************************************************************************************************************************

void func_console_toggle()
{
	gConsole.active = !gConsole.active;
	cmd.exec("savecvar cvar.bin");
}

//**********************************************************************************************************************************

void func_txt()
{
	string s;
	cmd.collectArguments(s);
	gSetHudMessage( s.c_str() );
}

//**********************************************************************************************************************************

void collectArguments(char* dest)
{
	int i=1;
	dest[0]=0;

	do
	{
		char* arg = gEngfuncs.Cmd_Argv(i++);
		if(!arg || !*arg) { break;}
		strcat(dest, arg);
		strcat(dest, " ");

	}while(1);
}

void func_later()
{
	if(cmd.argS(1).empty())
	{
		list<ScheduledCommand>::iterator pos;
		for(pos=scheduleList.begin();pos!=scheduleList.end();++pos)
		{
			Con_Echo("%6.2f sec: \"%s\"", (*pos).timer.timeleft(), (*pos).cmd.c_str() );
		}
		return;
	}
	if(cmd.argS(1)=="clear")
	{
		scheduleList.erase(scheduleList.begin(),scheduleList.end());
		return;
	}
	float time = cmd.argF(1);
	ScheduledCommand tmp;
	cmd.collectArguments( tmp.cmd, 2); 
	tmp.timer.countdown(time);
	if(scheduleList.size()<32) scheduleList.push_back(tmp);
}

//**********************************************************************************************************************************

bool func_eval_condition(int& refArgIndex)
{
	char* test  = cmd.argC(refArgIndex++);
	char* szArg = cmd.argC(refArgIndex++);
	if(!*test||!*szArg){ return false; }
	if( !strcmp(test,"has"   )) { return  playerItems.hasWeapon(szArg);}
	if( !strcmp(test,"hasno" )) { return !playerItems.hasWeapon(szArg);}
	if( !strcmp(test,"is"    ))  
	{ 
		if(!strcmp(szArg,"t"    )) { return me.team==1; }
		if(!strcmp(szArg,"ct"   )) { return me.team!=1; }
		if(!strcmp(szArg,"alive")) { return (me.alive); }
	}
	if(!strcmp(test,"money<" )){ return (playerItems.money<atoi(szArg)); }
	if(!strcmp(test,"money>="))
	{ 
		bool condition = (playerItems.money>=atoi(szArg)); 
		if(!condition){ strcpy(gHudMessage,"[OGC] Not enough money.");gHudTimer.countdown(1.5); }
		return condition;
	}
	if( !strcmp(test,"armor<" ) ){ return (playerItems.armor< atoi(szArg));}
	if( !strcmp(test,"armor>=") ){ return (playerItems.armor>=atoi(szArg));}
	if( !strcmp(test,"speed<") ){ return (cvar.speed< atoi(szArg));}
	if( !strcmp(test,"speed>=") ){ return (cvar.speed>= atoi(szArg));}

	return false;
}

//**********************************************************************************************************************************

void func_if()
{
	int  pos = 1;
	bool final_condition = func_eval_condition(pos);
	while(1){ 
		if( *cmd.argC(pos)=='&' ) {
			final_condition &= func_eval_condition(pos);
		} else if( *cmd.argC(pos)=='|' ) {
			final_condition |= func_eval_condition(pos);
		} else {
			break;
		} 
	}
	int truepos = pos;
	int elsepos = 0;
	while(1){
		char* arg = cmd.argC(pos);
		if(!*arg) { break; }
		if(!strcmp(arg,"else")) { elsepos = pos; break; }
		pos++;
	}
	string command;
	if( !elsepos )
	{
		if(final_condition)
		{
			cmd.collectArguments(command,truepos);
			cmd.exec( const_cast<char*>( command.c_str() ) );
		}
	} else {
		if(final_condition)
		{
			cmd.collectArguments(command,truepos,elsepos-1);
			cmd.exec( const_cast<char*>( command.c_str() ) );
		} else {
			cmd.collectArguments(command,elsepos+1);
			cmd.exec( const_cast<char*>( command.c_str() ) );
		}
	}
}

//**********************************************************************************************************************************

static void func_color()
{
	int arg=1;
	while(*cmd.argC(arg))
	{
		colorList.set( cmd.argC(arg), cmd.argC(arg+1), cmd.argC(arg+2), cmd.argC(arg+3), cmd.argC(arg+4));
		arg+=5;
	}
}

//**********************************************************************************************************************************

void Init_Command_Interpreter()
{
	cmd.init();
	cvar.init();
	cmd.AddCvarInt( "alive", (int*)&me.alive );
	#define REGISTER_COMMAND(name) cmd.AddCommand( #name, func_##name);
	REGISTER_COMMAND(alias)
	REGISTER_COMMAND(bind)
	REGISTER_COMMAND(unbind)
	REGISTER_COMMAND(remap)
	REGISTER_COMMAND(exec)
	REGISTER_COMMAND(later)
	REGISTER_COMMAND(color)
	REGISTER_COMMAND(console_toggle)
	REGISTER_COMMAND(menu_toggle)
	REGISTER_COMMAND(if)
	REGISTER_COMMAND(loadcvar)
	REGISTER_COMMAND(savecvar)
	REGISTER_COMMAND(play)
	REGISTER_COMMAND(first_kill_mode)
	REGISTER_COMMAND(addplayer)
	REGISTER_COMMAND(relistplayer)
	REGISTER_COMMAND(clearallplayer)
	REGISTER_COMMAND(player_toggle)
	REGISTER_COMMAND(txt)

	Strafebot.commands();
	autoway.commands();
}