#include "client.h"

void gSetHudMessage(const char* message)
{
	strcpy(gHudMessage2,message);
	gHudTimer2.countdown(4);
}

char  gHudMessage[256]="";
char  gHudMessage2[256]="";

void hudDrawInfoTexts()
{
	if(cvar.rush) return;

	int line_y = displayCenterY*2-180;
	int line_x = 20;
    #define DECREMENT_LINE_Y { line_y-=16; }
		
	if (cvar.info)
	{
		ColorEntry* clr=colorList.get(6);
		if(gHudTimer.running())
		{
			DrawHudString2(line_x,line_y,clr->r,clr->g,clr->b, gHudMessage );
			DECREMENT_LINE_Y
		}
		if( gHudTimer2.running() )
		{
			DrawHudString2(line_x,line_y,clr->r,clr->g,clr->b,gHudMessage2 );
			DECREMENT_LINE_Y
		}
	}
}

//**********************************************************************************************************************************

