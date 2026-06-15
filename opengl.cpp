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

#pragma comment(lib, "opengl32.lib")
#include "client.h"

//**********************************************************************************************************************************

typedef void(__stdcall* t_glBegin)(GLenum);
typedef void(__stdcall* t_glEnd)(void);
typedef void(__stdcall* t_glBlendFunc)(GLenum, GLenum);
typedef void(__stdcall* t_glClear)(GLbitfield);
typedef void(__stdcall* t_glVertex3f)(GLfloat,GLfloat,GLfloat);
typedef void(__stdcall* t_glVertex3fv)(const GLfloat *);
typedef void(__stdcall* t_glViewport)(GLint,GLint,GLsizei,GLsizei);
typedef BOOL(__stdcall* t_wglSwapBuffers)(HDC);
typedef void(__stdcall* t_glEnable)(GLenum);
typedef void(__stdcall* t_glDisable)(GLenum);
typedef void(__stdcall* t_glPopMatrix)();
typedef void(__stdcall* t_glPushMatrix)();
typedef void(__stdcall* t_glRotatef)(GLfloat,GLfloat,GLfloat,GLfloat);
typedef void(__stdcall* t_glColor4f)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
t_glColor4f pOrig_glColor4f = NULL;
t_glBegin pOrig_glBegin = NULL;
t_glEnd pOrig_glEnd = NULL;
t_glBlendFunc pOrig_glBlendFunc = NULL;
t_glClear pOrig_glClear = NULL;
t_glVertex3f pOrig_glVertex3f = NULL;
t_glVertex3fv pOrig_glVertex3fv = NULL;
t_glViewport pOrig_glViewport = NULL;
t_wglSwapBuffers pOrig_wglSwapBuffers = NULL;
t_glEnable pOrig_glEnable = NULL;
t_glEnable pOrig_glDisable = NULL;
t_glPopMatrix pOrig_glPopMatrix = NULL;
t_glPushMatrix pOrig_glPushMatrix = NULL;
t_glRotatef pOrig_glRotatef = NULL;

bool oglSubtractive = false;
bool bDrawingSmoke=false;
int noSky = false;
float curcol[4];
bool bDrawingFlash=false;
bool bDrawingSky=false;

float chams_render_r;
float chams_render_g;
float chams_render_b;

//**********************************************************************************************************************************

void opengl_ClearBackground()
{
	if(&glClearColor && &glClear)
	{
		glClearColor(0.0f,0.0f,0.0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
}

//**********************************************************************************************************************************

void __stdcall sys_glBegin(GLenum mode)
{

	GLfloat linecol[4];
	glGetFloatv(GL_CURRENT_COLOR, linecol);
	//smoke and nosky
	if (mode==GL_QUADS)
	{
		if(cvar.nosmoke==1)
			if ((linecol[0]==linecol[1])&&(linecol[0]==linecol[2]) && (linecol[0]!=0.0) && (linecol[0]!=1.0))
				bDrawingSmoke = true;

		if(cvar.nosky)
			bDrawingSky=true;	
	}
	else 
	{
		bDrawingSmoke = false; 
		bDrawingSky=false;
	}
	(*pOrig_glBegin)(mode);

}

//**********************************************************************************************************************************

void __stdcall sys_glClear (GLbitfield mask)
{
	if(mask==GL_DEPTH_BUFFER_BIT && cvar.nosky)
	{
		mask+=GL_COLOR_BUFFER_BIT;
		ColorEntry* color = colorList.get(26);
		float r = float(color->r)/255.0f;
		float g = float(color->g)/255.0f;
		float b = float(color->b)/255.0f;
		float a = float(color->a)/255.0f;
		glClearColor(r,g,b,a);
		(*pOrig_glClear)(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
	}
	(*pOrig_glClear)(mask);
}

//**********************************************************************************************************************************

void __stdcall sys_glVertex3f(GLfloat x,GLfloat y,GLfloat z)
{
	if(cvar.noall)
		if(cvar.rush == 1)
			return;
	(*pOrig_glVertex3f)(x, y, z);
}

//**********************************************************************************************************************************

void __stdcall sys_glVertex3fv (const GLfloat* var)
{
	if (bDrawingSky && var[2]>3000) return;

	if (bDrawingSmoke) return;

	(*pOrig_glVertex3fv)(var);
}

//**********************************************************************************************************************************

void __stdcall sys_glBlendFunc(GLenum sfactor, GLenum dfactor)
{
	if(oglSubtractive)
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	else
		glBlendFunc(sfactor,dfactor);
}

//**********************************************************************************************************************************

void __stdcall sys_glColor4f(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
	cl_entity_s *ent=IEngineStudio.GetCurrentEntity();
	if(bIsValidEnt(ent) && !cvar.rush){
		if(cvar.espteam || isEnemy(ent->index))
		{
			if(cvar.chams == 1||cvar.chams == 3)
			{
				red = chams_render_r / 255;
			    green = chams_render_g / 255;
			    blue = chams_render_b / 255;
			}
			if(cvar.chams == 2){
			    red = (chams_render_r / 255) * red;
			    green = (chams_render_g / 255) * green;
			    blue = (chams_render_b / 255) * blue;
			}
		}
	}
	(*pOrig_glColor4f)(red, green, blue, alpha);
}

//**********************************************************************************************************************************

void __stdcall sys_glPushMatrix(void)
{
	(*pOrig_glPushMatrix)();
} 

//**********************************************************************************************************************************

void __stdcall sys_glEnable (GLenum cap)
{
	(*pOrig_glEnable)(cap);
}
//**********************************************************************************************************************************

void __stdcall sys_glPopMatrix(void)
{
	(*pOrig_glPopMatrix)();
}

//**********************************************************************************************************************************

void __stdcall sys_glViewport( GLint x,GLint y,GLsizei width,GLsizei height )
{
	static bool bStart=false;
	if (!bStart)
	{
		optimization();
		bStart=true;
	}
	static bool bStart2=false;
	if (!bStart2)
	{
		gEngfuncs.pfnConsolePrint( "\n      Multihack by:" );
		gEngfuncs.pfnConsolePrint( "\n                  [..         [..    [....     [..      " );
		gEngfuncs.pfnConsolePrint( "\n                   [..       [..   [..    [..  [..      " );
		gEngfuncs.pfnConsolePrint( "\n           [..      [..     [..  [..        [..[..      " );
		gEngfuncs.pfnConsolePrint( "\n         [.   [..    [..   [..   [..        [..[..      " );
		gEngfuncs.pfnConsolePrint( "\n        [..... [..    [.. [..    [..        [..[..      " );
		gEngfuncs.pfnConsolePrint( "\n        [.             [....       [..     [.. [..      " );
		gEngfuncs.pfnConsolePrint( "\n          [....         [..          [....     [........" );
		gEngfuncs.pfnConsolePrint( "\n         " );                                               
		gEngfuncs.pfnConsolePrint( "\n      " );
		gEngfuncs.pfnConsolePrint( "\n      Credits: FT5, 123, 85, ASD, BloodSharp, 007 and 17 "  );
		gEngfuncs.pfnConsolePrint( "\n      Code by: Ripped from public sources" );
		gEngfuncs.pfnConsolePrint( "\n      Coder: eVOL"                         );
		gEngfuncs.pfnConsolePrint( "\n      www.cstrikenoobhackers.com"          );
		gEngfuncs.pfnConsolePrint( "\n      www.qipilang.88448.com"              );
		gEngfuncs.pfnConsolePrint( "\n      www.unknowncheats.me"              );
		gEngfuncs.pfnConsolePrint( "\n                               23-05-2018" );
		gEngfuncs.pfnConsolePrint( "\n                                         \n" );
		gEngfuncs.pfnConsolePrint( "\n      Ins Menu\n"      );
		gEngfuncs.pfnConsolePrint( "\n      Del Console\n"      );
		gEngfuncs.pfnConsolePrint( "\n      P IdHook\n"      );
		gEngfuncs.pfnConsolePrint( "\n      J Mode\n"      );
		gEngfuncs.pfnClientCmd("fs_lazy_precache 1");
		gEngfuncs.pfnClientCmd("toggleconsole");
		bStart2=true;
	}
	if(cvar.smallview && me.alive)
		if(cvar.rush)
			(*pOrig_glViewport)((width-cvar.view_width)/2,(height-cvar.view_height)/2,cvar.view_width,cvar.view_height);
		else
			(*pOrig_glViewport)(x,y,width,height);
}

//**********************************************************************************************************************************

void CheckForOpenGlHook(FARPROC* pProc,LPCTSTR lpProcName)
{
	if (!strcmp(lpProcName,"glBegin"))
	{
		pOrig_glBegin = (t_glBegin)*pProc;
		*pProc = (FARPROC)&sys_glBegin;
	}

	else if(!strcmp(lpProcName,"glClear"))
	{
			pOrig_glClear = (t_glClear)*pProc;
			*pProc = (FARPROC)&sys_glClear;
	}
	else if(!strcmp(lpProcName,"glVertex3f"))
	{
			pOrig_glVertex3f = (t_glVertex3f)*pProc;
			*pProc = (FARPROC)&sys_glVertex3f;
	}

	else if(!strcmp(lpProcName,"glVertex3fv"))
	{
			pOrig_glVertex3fv = (t_glVertex3fv)*pProc;
			*pProc = (FARPROC)&sys_glVertex3fv;
	}

	else if(!strcmp(lpProcName,"glBlendFunc"))
	{
			pOrig_glBlendFunc = (t_glBlendFunc)*pProc;
			*pProc = (FARPROC)&sys_glBlendFunc;
	}

	else if(!strcmp(lpProcName,"glPopMatrix")) 
	{
			pOrig_glPopMatrix = (t_glPopMatrix)*pProc;
			*pProc = (FARPROC)&sys_glPopMatrix;
	}

	else if(!strcmp(lpProcName,"glPushMatrix")) 
	{
			pOrig_glPushMatrix = (t_glPushMatrix)*pProc;
			*pProc = (FARPROC)&sys_glPushMatrix;
	}

	else if(!strcmp(lpProcName,"glViewport"))
	{
			pOrig_glViewport = (t_glViewport)*pProc;
			*pProc = (FARPROC)&sys_glViewport;
	}

	else if(!strcmp(lpProcName,"glColor4f"))
	{
			pOrig_glColor4f = (t_glColor4f)*pProc;
			*pProc = (FARPROC)&sys_glColor4f;
	}

	else if(!strcmp(lpProcName,"glEnable"))
	{
			pOrig_glEnable = (t_glEnable)*pProc;
			*pProc = (FARPROC)&sys_glEnable;
	}
}

//**********************************************************************************************************************************
