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

#ifndef DRAWING_H
#define DRAWING_H

//**********************************************************************************************************************************

#include <gl\gl.h>
#include <gl\glu.h>

//**********************************************************************************************************************************

int DrawLen(char* fmt);
void DrawConString (int x, int y, int r, int g, int b, const char* fmt, ... );
void DrawConStringCenter (int x, int y, int r, int g, int b, const char* fmt, ... );
void DrawHudString (int x, int y, int r, int g, int b, const char* fmt, ... );
void DrawHudString2 (int x, int y, int r, int g, int b, const char* fmt, ... );
void DrawHudStringCenter(int x, int y, int r, int g, int b, const char* fmt, ... );
void DrawGlowHudString(int x, int y, int r, int g, int b, const char* fmt, ... );
void DrawGlowHudString2(int x, int y, int r, int g, int b, const char* fmt, ... );

void tintArea(int x,int y,int w,int h, ColorEntry* clr);
void tintArea(int x,int y,int w,int h,int r,int g,int b,int a);
void tintArea2(int x,int y,int w,int h,int r,int g,int b,int a);
void FillRGBA2(int x,int y,int w,int h,int r,int g,int b,int a);
void consoleBorder(int x,int y,int w, int h);
void gDrawFilledBoxAtLocation( float* origin, DWORD color, int radius);

void mDrawConStringCenter (int x, int y, int r, int g, int b, const char* fmt, ... );
void dddBorder3(int x,int y,int w, int h, int a);
void mdddBorder(int x,int y,int w, int h, int a);
void DrawWindow(int x, int y, int w, int h, const char* title, ...);
void blackBorder(int x,int y,int w, int h);
void DrawFillTriangle(int xa,int ya,int xb,int yb,int xc,int yc,int r,int g,int b,int a);
void DrawLines( int ax, int ay, int bx, int by, int width, int r, int g, int b, int a );
void Draw2DBox(cl_entity_t *pEnt,Vector origin,int width,ColorEntry *color);
void Draw3DBox(cl_entity_t *pEnt,Vector origin,int width,ColorEntry *color);
void Draw3DBoxSpinn(cl_entity_t *pEnt,Vector origin,int width,ColorEntry *color);
void DrawLine(float *from, float *to,int r,int g,int b,float d);
void DrawTrace(cl_entity_s *pEnt,ColorEntry *pClr,float life,float width);
void DrawFade(int x, int y, int w, int h);
void DrawStrippledVectorLine(float *flSrc,float *flDestination,int width,GLint factor,GLushort pattern,ColorEntry *color);
void DrawVectorLine(float *flSrc,float *flDestination,int width,ColorEntry *color);
void DrawSpread();
void DrawRecoil();
void DrawString(bool Center, bool DrawBG, float* Pos, ColorEntry *color, char* Text, ...);
int iStringHeight( void );
void gDrawBoxAtScreenXY( int x, int y, int r, int g, int b, int alpha, int radius);
//**********************************************************************************************************************************

#endif

//**********************************************************************************************************************************

