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

void gDrawFilledBoxAtLocation( float* origin, DWORD color, int radius)
{
	float vecScreen[2]; 
	if( !CalcScreen(origin, vecScreen) ) { return; }
	int red   = (color>>24);
	int green = (color>>16)&0xFF;
	int blue  = (color>>8)&0xFF;
	int alpha = (color)&0xFF;
	int radius2 = radius<<1;
	tintArea(vecScreen[0]-radius,vecScreen[1]-radius,radius2,radius2,red,green,blue,alpha);
}

//**********************************************************************************************************************************

int DrawLen(char* fmt)
{
	int len=0;
	for ( char * p = fmt; *p; p++ ) len+=screeninfo.charWidths[*p]; 
	return len;
}

//**********************************************************************************************************************************

#define GET_VA_ARGS(text, buffer) va_list valist; \
								  va_start(valist, text); \
								  _vsnprintf(buffer, 2048, text, valist); \
							  	  va_end(valist);

//**********************************************************************************************************************************

int GetStringWidth(char* Text, ...)

{
	int w, h;
	char szBuffer[1024];
	GET_VA_ARGS(Text, szBuffer);
	gEngfuncs.pfnDrawConsoleStringLen(szBuffer, &w, &h);
	return w;
}

//**********************************************************************************************************************************

int GetStringHeight()
{
	int w, h;
	gEngfuncs.pfnDrawConsoleStringLen("Aj", &w, &h);
	return h;
}

//**********************************************************************************************************************************

int iStringHeight( void )
{
	int iWidth, iHeight;
	DrawConsoleStringLen( "F", &iWidth, &iHeight );
	return iHeight;
}

//**********************************************************************************************************************************

void DrawString(bool Center, bool DrawBG, float* Pos, ColorEntry *color, char* Text, ...)
{
	int x = (int)Pos[0];
	int y = (int)Pos[1];

	char szBuffer[1024];
	GET_VA_ARGS(Text, szBuffer);
	if (Center) x -= GetStringWidth(szBuffer) / 2;
	if (DrawBG) FillRGBA(x - 2, y - 1, GetStringWidth(szBuffer) + 4, GetStringHeight() + 2, 0, 0, 0, 128);
	gEngfuncs.pfnDrawSetTextColor(((float)color->r / 255.0f), ((float)color->g / 255.0f), ((float)color->b / 255.0f));
	gEngfuncs.pfnDrawConsoleString(x, y, szBuffer);
}

//**********************************************************************************************************************************

void DrawConString (int x, int y, int r, int g, int b, const char* fmt, ... )
{
	va_list va_alist;
	char buf[256];
	va_start (va_alist, fmt);
	_vsnprintf (buf, sizeof(buf), fmt, va_alist);
	va_end (va_alist);
	int length, height;
	y += 4;
	gEngfuncs.pfnDrawConsoleStringLen( buf, &length, &height );
	gEngfuncs.pfnDrawSetTextColor(r/255.0f, g/255.0f, b/255.0f);
	gEngfuncs.pfnDrawConsoleString(x,y,buf);
}

//**********************************************************************************************************************************

void DrawConStringCenter (int x, int y, int r, int g, int b, const char* fmt, ... )
{
	va_list va_alist;
	char buf[256];
	va_start (va_alist, fmt);
	_vsnprintf (buf, sizeof(buf), fmt, va_alist);
	va_end (va_alist);
	int length, height;
	gEngfuncs.pfnDrawConsoleStringLen( buf, &length, &height );
	x -= length/2;
	y += 4;
	gEngfuncs.pfnDrawSetTextColor(r/255.0f, g/255.0f, b/255.0f);
	gEngfuncs.pfnDrawConsoleString(x,y,buf);
}

//**********************************************************************************************************************************

void DrawHudString (int x, int y, int r, int g, int b, const char* fmt, ... )
{
	va_list va_alist;
	char buf[256];
	va_start (va_alist, fmt);
	_vsnprintf (buf, sizeof(buf), fmt, va_alist);
	va_end (va_alist);
	int borderY = displayCenterY*2-18;
	if( y<0 || y>borderY ) { return; }
	bool needSingleCheck=false;
	int borderX = displayCenterX*2-11;
	int drawLen = DrawLen(buf);
	if( x<1 ){ needSingleCheck=true; }
	else
	{
		int maxX = x+drawLen;
		needSingleCheck = (maxX>borderX);
	}
	if( needSingleCheck )
	{
		for ( char * p = buf; *p; p++ )
		{
			int next = x + screeninfo.charWidths[*p];
			// IMPORTANT NOTE: when drawing admin-mod style charactters
			//    you MAY NOT provide x/y coordinates that cause drawing
			//    off screen. This causes HL to crash or just quit
			if( x>0 && x<borderX )
				gEngfuncs.pfnDrawCharacter (x, y, *p, r, g, b);
			x = next;
		}
	}else {
		for ( char * p = buf; *p; p++ )
		{
			int next = x + screeninfo.charWidths[*p];
			// IMPORTANT NOTE: when drawing admin-mod style charactters
			//    you MAY NOT provide x/y coordinates that cause drawing
			//    off screen. This causes HL to crash or just quit
			gEngfuncs.pfnDrawCharacter (x, y, *p, r, g, b);
			x = next;
		}
	}	
}

//**********************************************************************************************************************************

void DrawHudString2 (int x, int y, int r, int g, int b, const char* fmt, ... )
{
	va_list va_alist;
	char buf[256];
	va_start (va_alist, fmt);
	_vsnprintf (buf, sizeof(buf), fmt, va_alist);
	va_end (va_alist);
	gEngfuncs.pfnDrawSetTextColor(/*(float)*/r/255.0,/*(float)*/g/255.0,/*(float)*/b/255.0);
	gEngfuncs.pfnDrawConsoleString(x,y,buf);
}

//**********************************************************************************************************************************

void DrawHudStringCenter(int x, int y, int r, int g, int b, const char* fmt, ... )
{
	va_list va_alist;
	char buf[256];
	va_start (va_alist, fmt);
	_vsnprintf (buf, sizeof(buf), fmt, va_alist);
	va_end (va_alist);
	int length, height;
	gEngfuncs.pfnDrawConsoleStringLen( buf, &length, &height );
	x = x - length/2;
	gEngfuncs.pfnDrawSetTextColor(/*(float)*/r/255.0,/*(float)*/g/255.0,/*(float)*/b/255.0);
	gEngfuncs.pfnDrawConsoleString(x,y,buf);
}

//**********************************************************************************************************************************

void DrawGlowHudString(int x, int y, int r, int g, int b, const char* fmt, ... )
{
	va_list va_alist;
	char buf[256];
	va_start (va_alist, fmt);
	_vsnprintf (buf, sizeof(buf), fmt, va_alist);
	va_end (va_alist);
	DrawHudStringCenter(x-2,y,r,g,b,buf);
	DrawHudStringCenter(x+2,y,r,g,b,buf);
	DrawHudStringCenter(x,y+2,r,g,b,buf);
	DrawHudStringCenter(x,y-2,r,g,b,buf);
	DrawHudStringCenter(x-1,y-1,r,g,b,buf);
	DrawHudStringCenter(x+1,y+1,r,g,b,buf);
	DrawHudStringCenter(x+1,y-1,r,g,b,buf);
	DrawHudStringCenter(x-1,y+1,r,g,b,buf);
	DrawHudStringCenter(x,y,255,255,255,buf);
}

//**********************************************************************************************************************************

void DrawGlowHudString2(int x, int y, int r, int g, int b, const char* fmt, ... )
{
	va_list va_alist;
	char buf[256];
	va_start (va_alist, fmt);
	_vsnprintf (buf, sizeof(buf), fmt, va_alist);
	va_end (va_alist);
	DrawHudString2(x-2,y,r,g,b,buf);
	DrawHudString2(x+2,y,r,g,b,buf);
	DrawHudString2(x,y+2,r,g,b,buf);
	DrawHudString2(x,y-2,r,g,b,buf);
	DrawHudString2(x-1,y-1,r,g,b,buf);
	DrawHudString2(x+1,y+1,r,g,b,buf);
	DrawHudString2(x+1,y-1,r,g,b,buf);
	DrawHudString2(x-1,y+1,r,g,b,buf);
	DrawHudString2(x,y,255,255,255,buf);
}

//**********************************************************************************************************************************

void tintArea(int x,int y,int w,int h, ColorEntry* clr)
{
	oglSubtractive = true;
	gEngfuncs.pfnFillRGBA(x,y,w,h,clr->r,clr->g,clr->b,clr->a);
	oglSubtractive = false;
}

//**********************************************************************************************************************************

void tintArea(int x,int y,int w,int h,int r,int g,int b,int a)
{
	oglSubtractive = true;
	gEngfuncs.pfnFillRGBA(x,y,w,h,r,g,b,a);
	oglSubtractive = false;
}

//**********************************************************************************************************************************

void tintArea2(int x,int y,int w,int h,int r,int g,int b,int a)
{
	gEngfuncs.pfnFillRGBA(x,y,w,h,r,g,b,a);
}

//**********************************************************************************************************************************

void FillRGBA2(int x,int y,int w,int h,int r,int g,int b,int a) { gEngfuncs.pfnFillRGBA(x,y,w,h,r,g,b,a); }

//**********************************************************************************************************************************

void consoleBorder(int x,int y,int w, int h)
{
	tintArea( x, y, w, h , 94 ,120 ,152,60);   
}

//**********************************************************************************************************************************

void mDrawConStringCenter (int x, int y, int r, int g, int b, const char* fmt, ... )
{
	va_list va_alist;
	char buf[256];
	va_start (va_alist, fmt);
	_vsnprintf (buf, sizeof(buf), fmt, va_alist);
	va_end (va_alist);
	int length, height;
	gEngfuncs.pfnDrawConsoleStringLen( buf, &length, &height );
	x -= length/2;
	y += 4;
	gEngfuncs.pfnDrawSetTextColor(r/255.0f, g/255.0f, b/255.0f);
	gEngfuncs.pfnDrawConsoleString(x,y,buf);
}

//**********************************************************************************************************************************

void dddBorder3(int x,int y,int w, int h, int a)
{
	tintArea( x-1, y-1, w+2, 1 ,255,255,255,a );
	tintArea( x-1, y, 1, h-1 ,255,255,255,a );
}

//**********************************************************************************************************************************

void mdddBorder(int x,int y,int w, int h, int a) // Lineas del titulo del menu
{
	tintArea( x-1, y-1, w+2, 1 ,255,255,255,a );
	tintArea( x-1, y, 1, h-1 ,255,255,255,a );
}

//**********************************************************************************************************************************

void DrawWindow(int x, int y, int w, int h, const char* title, ...)
{
	va_list va_alist;
	char buf[256];
	va_start(va_alist, title);
	_vsnprintf(buf, sizeof(buf), title, va_alist);
	va_end(va_alist);
	tintArea( x, y-20, w, 1 ,255,255,255,200 ); //top main box
	tintArea( x, y, w, 1 ,255,255,255,200 ); //bottom main box
	tintArea( x,y-19,w,20-1 ,51,51,204,180); //body
	DrawConString(x+18, y-21, 255,255,255, buf);
	tintArea(x,y+1,w,h,51,51,204,100); //body
}

//**********************************************************************************************************************************

void blackBorder(int x,int y,int w, int h)
{
	oglSubtractive = true;
	gEngfuncs.pfnFillRGBA( x-1, y-1, w+2, 1 ,0,0,0,254 ); //top
	gEngfuncs.pfnFillRGBA( x-1, y, 1, h-1 ,0,0,0,254 );	//left
	gEngfuncs.pfnFillRGBA( x+w, y, 1, h-1 ,0,0,0,254 );	//right
	gEngfuncs.pfnFillRGBA( x-1, y+h-1, w+2, 1 ,0,0,0,254 ); //bottom
	oglSubtractive = false;
}

//**********************************************************************************************************************************

void DrawFillTriangle(int xa,int ya,int xb,int yb,int xc,int yc,int r,int g,int b,int a)
{
	glPushMatrix();
	glLoadIdentity();
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glShadeModel(GL_SMOOTH);
	glColor4ub(r,g,b,a);
	glBegin(GL_TRIANGLES);
	glVertex2f(xa,ya);
	glVertex2f(xb,yb);
	glVertex2f(xc,yc);
	glEnd();
	glDisable(GL_BLEND);
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
}

//**********************************************************************************************************************************

void DrawLines( int ax, int ay, int bx, int by, int width, int r, int g, int b, int a )
{
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4ub( r, g, b, a);

    glLineWidth(width);
    glBegin(GL_LINES);
    glVertex2i( ax, ay);
    glVertex2i( bx, by);
    glEnd();

    glDisable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);
}

//**********************************************************************************************************************************

void DrawStrippledLines(int x1,int y1,int x2,int y2,int width,GLint factor,GLushort pattern,ColorEntry *color)
{
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glColor4ub(color->r,color->g,color->b,color->a);
	glLineWidth((float)width);
	glLineStipple(factor, pattern);
	glEnable(GL_LINE_STIPPLE);
	glBegin(GL_LINES);
	glVertex2i(x1,y1);
	glVertex2i(x2,y2);
	glEnd();
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glDisable(GL_LINE_STIPPLE);
}

//**********************************************************************************************************************************

void DrawStrippledVectorLine(float *flSrc,float *flDestination,int width,GLint factor,GLushort pattern,ColorEntry *color)
{
	vec3_t vScreenSrc,vScreenDest;
	if(!CalcScreen(flSrc,vScreenSrc) | !CalcScreen(flDestination,vScreenDest))
		return;
	DrawStrippledLines((int)vScreenSrc[0],(int)vScreenSrc[1],(int)vScreenDest[0],(int)vScreenDest[1],width,factor,pattern,color);
}

//**********************************************************************************************************************************

void DrawLines(int x1,int y1,int x2,int y2,int width,ColorEntry *color)
{
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glColor4ub(color->r,color->g,color->b,color->a);
	glLineWidth((float)width);
	glBegin(GL_LINES);
	glVertex2i(x1,y1);
	glVertex2i(x2,y2);
	glEnd();
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

//**********************************************************************************************************************************

void DrawVectorLine(float *flSrc,float *flDestination,int width,ColorEntry *color)
{
	vec3_t vScreenSrc,vScreenDest;
	if(!CalcScreen(flSrc,vScreenSrc) | !CalcScreen(flDestination,vScreenDest))
		return;
	DrawLines((int)vScreenSrc[0],(int)vScreenSrc[1],(int)vScreenDest[0],(int)vScreenDest[1],width,color);
}

//**********************************************************************************************************************************

int Count = 0;	
void Draw3DBoxSpinn(cl_entity_t *pEnt,Vector origin,int width,ColorEntry *color)
{
	if(!pEnt || !color)
		return;
	
	vec3_t vF,vR,vU;
	Count++; 
	if(Count == 0)
	{
		gEngfuncs.pfnAngleVectors(Vector(0.0f,pEnt->angles[1],0.0f),vF,vR,vU);
	}
	else if(Count == 1)
	{
		gEngfuncs.pfnAngleVectors(Vector(-36.0f,pEnt->angles[1],360.0f),vF,vR,vU);
	}
	else if(Count == 2)
	{
		gEngfuncs.pfnAngleVectors(Vector(-72.0f,pEnt->angles[1],324.0f),vF,vR,vU);
	}else if(Count == 3)
	{
		gEngfuncs.pfnAngleVectors(Vector(-108.0f,pEnt->angles[1],288.0f),vF,vR,vU);
	}else if(Count == 4)
	{
		gEngfuncs.pfnAngleVectors(Vector(-180.0f,pEnt->angles[1],252.0f),vF,vR,vU);
	}else if(Count == 5)
	{
		gEngfuncs.pfnAngleVectors(Vector(-216.0f,pEnt->angles[1],216.0f),vF,vR,vU);
	}else if(Count == 6)
	{
		gEngfuncs.pfnAngleVectors(Vector(-252.0f,pEnt->angles[1],180.0f),vF,vR,vU);
	}else if(Count == 7)
	{
		gEngfuncs.pfnAngleVectors(Vector(-288.0f,pEnt->angles[1],108.0f),vF,vR,vU);
	}else if(Count == 8)
	{
		gEngfuncs.pfnAngleVectors(Vector(-324.0f,pEnt->angles[1],72.0f),vF,vR,vU);
	}
	else if(Count == 9)
	{
		gEngfuncs.pfnAngleVectors(Vector(-360.0f,pEnt->angles[1],36.0f),vF,vR,vU);
		Count = 0;
	}

	//If you want only the hitbox of the player. simply make it only maxs & mins instead of adding numbers:P
	//3d
	float flForward=pEnt->curstate.maxs.y+25.0f;
	float flBack=pEnt->curstate.mins.y-25.0f;
	float flRight=pEnt->curstate.maxs.x+25.0f;
	float flLeft=pEnt->curstate.mins.x-25.0f;

	//3d
	vec3_t vUFLeft=origin + vU*pEnt->curstate.maxs.z + vF*flForward + vR*flLeft; // vUFLeft = Top left front
	vec3_t vUFRight=origin + vU*pEnt->curstate.maxs.z + vF*flForward + vR*flRight; // vUFRight = Top right front
	vec3_t vUBLeft=origin + vU*pEnt->curstate.maxs.z + vF*flBack + vR*flLeft; // vUBLeft = Top left back
	vec3_t vUBRight=origin + vU*pEnt->curstate.maxs.z + vF*flBack + vR*flRight; // vUBRight = Top right back
	vec3_t vBFLeft=origin + vU*pEnt->curstate.mins.z + vF*flForward + vR*flLeft; // vBFLeft = Bottom left front
	vec3_t vBFRight=origin + vU*pEnt->curstate.mins.z + vF*flForward + vR*flRight; // vBFRight = Bottom right front
	vec3_t vBBLeft=origin + vU*pEnt->curstate.mins.z + vF*flBack + vR*flLeft; // vBBLeft = Bottom left back
	vec3_t vBBRight=origin + vU*pEnt->curstate.mins.z + vF*flBack + vR*flRight; // vBBRight = Bottom right back

	//Top Box
	DrawVectorLine(vUBLeft,vUBRight,width,color); // Back left -> Back right
	DrawVectorLine(vUBRight,vUFRight,width,color); // Back right -> Front right
	DrawVectorLine(vUFRight,vUFLeft,width,color); // Front right -> Front left
	DrawVectorLine(vUFLeft,vUBLeft,width,color); // Front left -> Back right
	//Mid Box
	DrawVectorLine(vUBLeft,vBBLeft,width,color); // Top left -> Bottom left
	DrawVectorLine(vUBRight,vBBRight,width,color); // Top right -> Bottom right
	DrawVectorLine(vUFRight,vBFRight,width,color); // Top right -> Bottom right
	DrawVectorLine(vUFLeft,vBFLeft,width,color); // Top left -> Bottom left
	//Bottom Box
	DrawVectorLine(vBBLeft,vBBRight,width,color); // Back left -> Back right
	DrawVectorLine(vBBRight,vBFRight,width,color); // Back right -> Front right
	DrawVectorLine(vBFRight,vBFLeft,width,color); // Front right -> Front left
	DrawVectorLine(vBFLeft,vBBLeft,width,color); // Front left -> Back right
}

//**********************************************************************************************************************************

void Draw3DBox(cl_entity_t *pEnt,Vector origin,int width,ColorEntry *color)
{
	if(!pEnt || !color)
		return;
	
	vec3_t vF,vR,vU;
	
	gEngfuncs.pfnAngleVectors(Vector(0.0f,pEnt->angles[1],0.0f),vF,vR,vU);
	
	//If you want only the hitbox of the player. simply make it only maxs & mins instead of adding numbers:P
	//3d
	float flForward=pEnt->curstate.maxs.y+0.0f;
	float flBack=pEnt->curstate.mins.y-0.0f;
	float flRight=pEnt->curstate.maxs.x+0.0f;
	float flLeft=pEnt->curstate.mins.x-0.0f;

	//3d
	vec3_t vUFLeft=origin + vU*pEnt->curstate.maxs.z + vF*flForward + vR*flLeft; // vUFLeft = Top left front
	vec3_t vUFRight=origin + vU*pEnt->curstate.maxs.z + vF*flForward + vR*flRight; // vUFRight = Top right front
	vec3_t vUBLeft=origin + vU*pEnt->curstate.maxs.z + vF*flBack + vR*flLeft; // vUBLeft = Top left back
	vec3_t vUBRight=origin + vU*pEnt->curstate.maxs.z + vF*flBack + vR*flRight; // vUBRight = Top right back
	vec3_t vBFLeft=origin + vU*pEnt->curstate.mins.z + vF*flForward + vR*flLeft; // vBFLeft = Bottom left front
	vec3_t vBFRight=origin + vU*pEnt->curstate.mins.z + vF*flForward + vR*flRight; // vBFRight = Bottom right front
	vec3_t vBBLeft=origin + vU*pEnt->curstate.mins.z + vF*flBack + vR*flLeft; // vBBLeft = Bottom left back
	vec3_t vBBRight=origin + vU*pEnt->curstate.mins.z + vF*flBack + vR*flRight; // vBBRight = Bottom right back
	
	//Top Box
	DrawVectorLine(vUBLeft,vUBRight,width,color); // Back left -> Back right
	DrawVectorLine(vUBRight,vUFRight,width,color); // Back right -> Front right
	DrawVectorLine(vUFRight,vUFLeft,width,color); // Front right -> Front left
	DrawVectorLine(vUFLeft,vUBLeft,width,color); // Front left -> Back right
	//Mid Box
	DrawVectorLine(vUBLeft,vBBLeft,width,color); // Top left -> Bottom left
	DrawVectorLine(vUBRight,vBBRight,width,color); // Top right -> Bottom right
	DrawVectorLine(vUFRight,vBFRight,width,color); // Top right -> Bottom right
	DrawVectorLine(vUFLeft,vBFLeft,width,color); // Top left -> Bottom left
	//Bottom Box
	DrawVectorLine(vBBLeft,vBBRight,width,color); // Back left -> Back right
	DrawVectorLine(vBBRight,vBFRight,width,color); // Back right -> Front right
	DrawVectorLine(vBFRight,vBFLeft,width,color); // Front right -> Front left
	DrawVectorLine(vBFLeft,vBBLeft,width,color); // Front left -> Back right
}

//**********************************************************************************************************************************

void Draw2DBox(cl_entity_t *pEnt,Vector origin,int width,ColorEntry *color)
{
	if(!pEnt || !color)
		return;
	
	vec3_t vF,vR,vU;
	
	gEngfuncs.pfnAngleVectors(Vector(90.0f,pEnt->angles[1],0.0f),vF,vR,vU);
	
	//If you want only the hitbox of the player. simply make it only maxs & mins instead of adding numbers:P

	//2d
	float flForward2=pEnt->curstate.maxs.y+50.0f;
	float flBack2=pEnt->curstate.mins.y-50.0f;
	float flRight2=pEnt->curstate.maxs.x+25.0f;
	float flLeft2=pEnt->curstate.mins.x-25.0f;
	
	//2d
	vec3_t vUBLeft2=origin + vU*pEnt->curstate.maxs.z + vF*flBack2 + vR*flLeft2; // vUBLeft = Top left back
	vec3_t vUBRight2=origin + vU*pEnt->curstate.maxs.z + vF*flBack2 + vR*flRight2; // vUBRight = Top right back
	vec3_t vUFLeft2=origin + vU*pEnt->curstate.maxs.z + vF*flForward2 + vR*flLeft2; // vUFLeft = Top left front
	vec3_t vUFRight2=origin + vU*pEnt->curstate.maxs.z + vF*flForward2 + vR*flRight2; // vUFRight = Top right front

    //Top Box2d
	DrawVectorLine(vUBLeft2,vUBRight2,width,color); // Back left -> Back right
	DrawVectorLine(vUBRight2,vUFRight2,width,color); // Back right -> Front right
	DrawVectorLine(vUFRight2,vUFLeft2,width,color); // Front right -> Front left
	DrawVectorLine(vUFLeft2,vUBLeft2,width,color); // Front left -> Back right
}

//**********************************************************************************************************************************

void DrawLine(float *from, float *to,int r,int g,int b,float d)
{
	int beamindex = 0;
	if(!beamindex)
		beamindex = gEngfuncs.pEventAPI->EV_FindModelIndex("sprites/laserbeam.spr");
	gEngfuncs.pEfxAPI->R_BeamPoints(from,to,beamindex,d,1.2f,0,32,2,0,0,r/255,g/255,b/255);
}

//**********************************************************************************************************************************

//when drawing using BeamPoints, dont draw with BeamFollow 
void DrawTrace(cl_entity_s *pEnt,ColorEntry *pClr,float life,float width)
{
	if( pEnt )
	{
		int beamindex = 0;
		if(!beamindex)
		beamindex = gEngfuncs.pEventAPI->EV_FindModelIndex("sprites/laserbeam.spr");
	    gEngfuncs.pEfxAPI->R_BeamFollow(pEnt->index, beamindex, life, width, pClr->r/255, pClr->g/255, pClr->b/255, 255);
	}
}

//**********************************************************************************************************************************

void DrawSpread()
{
	Vector spreadangles, forward, screen;

	if(!me.bBadWeapon && currentWeaponID!=WEAPON_KNIFE)
	{
		pmtrace_t tr;

		VectorAdd(me.cmdViewAngles, me.vNoSpreadAng, spreadangles);

		gEngfuncs.pfnAngleVectors(spreadangles, forward, NULL, NULL);

		gEngfuncs.pEventAPI->EV_SetTraceHull(2);
		gEngfuncs.pEventAPI->EV_PlayerTrace(me.vEye, me.vEye + (forward * playerItems.CurDistance()), PM_GLASS_IGNORE, -1, &tr);

		if(CalcScreen(tr.endpos, screen))
		{
			screen.x = screeninfo.iWidth - screen.x;
			screen.y = screeninfo.iHeight - screen.y;

			me.vNoSpreadAngScr = screen;

			oglSubtractive=true;
			gEngfuncs.pfnFillRGBA(screen.x-0.5, screen.y, 3, 3, 255, 0, 255, 255);
			oglSubtractive=false;
			blackBorder(screen.x-0.5,screen.y,3,4);
	
		}
	/*	float xx = me.vNoSpreadAng[1];
	    float yy = me.vNoSpreadAng[0];

	    float x = (screeninfo.iWidth / 2.0f) - (xx * 10);
	    float y = (screeninfo.iHeight / 2.0f) + (yy * 10);

	    oglSubtractive=true;
	    FillRGBA(x-0.5, y, 3, 3, 255, 0, 255, 255);
	    oglSubtractive=false;
		blackBorder(x-0.5,y,3,4);*/
	}
}

void DrawRecoil()
{
	if(!me.bBadWeapon && currentWeaponID!=WEAPON_KNIFE)
	{
		float xx = me.vNoRecoilAng[1];
	    float yy = me.vNoRecoilAng[0];

	    float x = (screeninfo.iWidth / 2.0f) - (xx * 10);
	    float y = (screeninfo.iHeight / 2.0f) + (yy * 10);

	    oglSubtractive=true;
	    FillRGBA(x-0.5, y, 3, 3, 0, 255, 0, 255);
	    oglSubtractive=false;
		blackBorder(x-0.5,y,3,4);
	}
}

void gDrawBoxAtScreenXY( int x, int y, int r, int g, int b, int alpha, int radius=1)
{
	int radius2 = radius<<1;
	oglSubtractive = true;
	gEngfuncs.pfnFillRGBA(x-radius+2, y-radius, radius2-2,2,r,g,b,alpha);
	gEngfuncs.pfnFillRGBA(x-radius, y-radius, 2,radius2,r,g,b,alpha);
	gEngfuncs.pfnFillRGBA(x-radius, y+radius, radius2,2,r,g,b,alpha);
	gEngfuncs.pfnFillRGBA(x+radius, y-radius, 2,radius2+2,r,g,b,alpha);
	oglSubtractive = false;
}