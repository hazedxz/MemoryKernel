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

Console gConsole;

void TrapezoidalConsole(int con_x, int con_y, int con_w, int con_h);

//**********************************************************************************************************************************

void Console::draw(int con_x, int con_y, int con_w, int con_h)
{
	if( !active ) return;

	////////

	if(!active && !curHeight ) return;
	int nscroll = scrollEventCounter.get();
	for(int i=0;i<nscroll;i++)
	{
		if( active ){
			if(curHeight!=con_h) 
			{ 
				curHeight += 999.0f; 
				if(curHeight>con_h) curHeight=con_h; 
			}
		} else {
			curHeight -= 999.0f;
			if(curHeight<=0) { curHeight=0; return; }
		}
	}

	consoleBorder(con_x,con_y-2,con_w,con_h+2);
	
	TrapezoidalConsole(con_x,con_y,con_w,con_h);

	int x = con_x+3;
	int y = con_y+con_h-14;

	if(blinkTimer.expired())
	{
		blink = !blink;
		if(blink) { blinkTimer.countdown(0.2); }
		else      { blinkTimer.countdown(0.2); }
	}
	if(blink)
	{
		int length, height, ch_length;
		char  save;
		save = cursorpos[0]; cursorpos[0]=0;
		gEngfuncs.pfnDrawConsoleStringLen( editbuf, &length, &height );
		cursorpos[0]=save;
		save = cursorpos[1]; cursorpos[1]=0;
		gEngfuncs.pfnDrawConsoleStringLen( cursorpos, &ch_length, &height );
		cursorpos[1]=save;
		if(!*cursorpos) ch_length=5;
        tintArea(x+length,y,ch_length,height-2, colorList.get(9));
	}
	ColorEntry* color2 = colorList.get(10);
	gEngfuncs.pfnDrawSetTextColor(color2->onebased_r,color2->onebased_g,color2->onebased_b);
	gEngfuncs.pfnDrawConsoleString(x,y-1,editbuf);
	lines.reset();
	for(;;)
	{
		y-=14;
		if(y<con_y) break;
		string& curLine = lines.read(); 
		lines.prev();
		drawConsoleLine(curLine,x,y);
	}
}

//**********************************************************************************************************************************

void Console::echo(const char* fmt, ... )
{
	va_list va_alist;
	char buf[384];
	va_start (va_alist, fmt);
	_vsnprintf (buf, sizeof(buf), fmt, va_alist);
	va_end (va_alist);
	lines.add( buf );
}

//**********************************************************************************************************************************

void Console::say(const char* text, const char* name, int team )
{
	if(team==1) { echo("&r%s :", name); echo(" %s",text); }
	else        { echo("&b%s :", name); echo(" %s",text); }
}

//**********************************************************************************************************************************

void Console::setcolortag(unsigned char ch, int r, int g, int b)
{
	ch -= 'a';
	if(ch>=26) { echo("color tags must be labeled \'a\' to \'z\'"); return; }
	colorTags[ch].r = r;
	colorTags[ch].g = g;
	colorTags[ch].b = b;
	colorTags[ch].fill_missing();
}

//**********************************************************************************************************************************

void Console::drawConsoleLine( const string& str, int x, int y )
{
	const char* line = str.c_str();
	char  buf[256];
	char* bufpos;

	for(;;)
	{
		bufpos=buf;
		for(;;) { *bufpos=*line; if(!*line||*line=='&')break;  ++line; ++bufpos; };
		bufpos[0]=0;bufpos[1]=0;
		int length, height;
		gEngfuncs.pfnDrawConsoleStringLen( buf, &length, &height );
		gEngfuncs.pfnDrawSetTextColor(colorTags[curColorTag].onebased_r, colorTags[curColorTag].onebased_g, colorTags[curColorTag].onebased_b);
		gEngfuncs.pfnDrawConsoleString(x,y,buf);
		x+=length;
		if(*line=='&')
		{
			unsigned char ch = *++line - 'a';
			if(ch<26) curColorTag=ch;
			else         break;
			if(!*++line) break;
		}
		else 
		{
			break;
		}
	}
	curColorTag=0;
}

//**********************************************************************************************************************************

void Console::key(int ch/*, bool shift*/)
{
	char* pos;
	{
		switch(ch)
		{
			case -1: // backspace
				if(cursorpos==editline) return;
				pos = --cursorpos;
				while(pos[0]) { pos[0]=pos[1]; ++pos; }
				return;
				
			case -2: // uparrow
				if(hist_direction!=DIR_BACK) { history.prev(); history.prev(); hist_direction=DIR_BACK;}
				strcpy(editline, history.read().c_str());
				cursorpos = editline + strlen(editline);
				history.prev();
				return;

			case -3: // downarrow
				if(hist_direction==DIR_BACK) { history.next(); history.next(); hist_direction=DIR_FORWARD;}
				strcpy(editline, history.read().c_str());
				cursorpos = editline + strlen(editline);
				history.next();
				return;
			
			case -4: // leftarrow
				if(cursorpos!=editline) --cursorpos;
				return;

			case -5: // leftarrow
				if(cursorpos!=(editline+strlen(editline))) ++cursorpos;
				return;

			case '\n':
					if( !strcmp(editline,"===") )
					{
						if(mode==MODE_EXECUTE) { mode=MODE_CHAT;    echo("&b*** &aCONSOLE: &wCHAT MODE &b***"); }
						else                   { mode=MODE_EXECUTE; echo("&b*** &aCONSOLE: &wEXEC MODE &b***"); }
					}
					else if(mode==MODE_EXECUTE)
					{
						echo    ( "&x%s",editbuf );
						if(editline[0])
						{
							cmd.exec( editline );
							history.add(editline);
							history.reset();
						}
					} 
					else if(mode==MODE_CHAT)
					{
						char* text = editline; while(*text==' ')++text;
						char buf[256];sprintf(buf,"say \"%s\"",text);
						gEngfuncs.pfnClientCmd(buf);
					}
					editline[0]=0;
					cursorpos = editline;
					return;
			default:
				// insert character
				if(strlen(editbuf)>(EDIT_MAX-4)) return;
				if(!cursorpos[0]) { cursorpos[0]=ch; ++cursorpos; cursorpos[0]=0; return; }
				pos = editbuf+strlen(editbuf)+1; 
				while(pos>cursorpos) { pos[0]=pos[-1]; --pos; }
				*cursorpos = ch;
				++cursorpos;
				return;
			}
	}
}

//**********************************************************************************************************************************

void Con_Echo(const char* fmt, ... )
{
	va_list va_alist;
	char buf[256];
	va_start (va_alist, fmt);
	_vsnprintf (buf, sizeof(buf), fmt, va_alist);
	va_end (va_alist);
	gConsole.echo("%s",buf);
}

//**********************************************************************************************************************************

void Consoledraw()
{
	int cx=(screeninfo.iWidth/2)-200;
	int cy=(screeninfo.iHeight/2)-150;
    int cw=400;
	int ch=300;
	gConsole.draw(cx,cy,cw,ch);
}