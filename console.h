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

#ifndef CONSOLE_H
#define CONSOLE_H

//**********************************************************************************************************************************

template < typename T, int N >

//**********************************************************************************************************************************

class WrapHistory
{
protected:
	void increase(int& idx) { ++idx; if(idx==N) idx=0;     }
	void decrease(int& idx) { --idx; if(idx<0 ) idx=(N-1); }
public:
	WrapHistory() : readpos(0), writepos(0) {}
	void add(const T& entry) 
	{ 
		increase(writepos);
		entries[writepos]=entry; 
		reset();
	}
	void reset(){ readpos = writepos; }
	T&   read (){ return entries[readpos]; }
	void prev (){ decrease(readpos); if(readpos==writepos) increase(readpos); }
	void next (){ if(readpos!=writepos) increase(readpos);  }
protected:
	int readpos;
	int writepos;
	T entries[N];
};

//**********************************************************************************************************************************

class Console
{
public:
	int  active;
	int con_h;
	int con_w;
	int con_x;
	int con_y;
	int  mode;   enum{ MODE_EXECUTE=0, MODE_CHAT=1 };
	void draw(int x, int y, int w, int h);
	void echo(const char *fmt, ... );
	void say (const char* text, const char* name, int team );
	void key (int ch/*, bool shift*/);
	void setcolortag(unsigned char ch, int r, int g, int b);
	//ColorEntry *colorTags(int idx) { return colorList.get(idx); }
	int scrollbar;
//protected:
	WrapHistory<string,1000> lines;
	WrapHistory<string,1000> history;
	enum { DIR_BACK, DIR_FORWARD } hist_direction;
	enum { EDIT_MAX=160 };
	char  editbuf[EDIT_MAX];
	char* const editline;
	char* cursorpos;
	StopTimer blinkTimer;
	bool  blink;
	ColorEntry colorTags[26];
	int        curColorTag;  // ==0 <=> 'a'
	void drawConsoleLine( const string& str, int x, int y );
	int curHeight;
	EventCounter<0.01> scrollEventCounter;
public:
Console() : editline(editbuf+1) , hist_direction(DIR_BACK)
	{ 
		editbuf[0] = '>';
		editbuf[1] =  0 ;
		editbuf[EDIT_MAX-1] = -1;
		cursorpos = editline;
		curColorTag = 0;
		colorTags['a'-'a'] = *colorList.get(8); // "con_text"  -> 'a'
		colorTags['x'-'a'] = *colorList.get(9); // "con_text2" -> 'x'
		mode = MODE_EXECUTE;
		scrollbar = 0;
	}
};

//**********************************************************************************************************************************

void Consoledraw();
void Con_Echo(const char* fmt, ... );

extern Console gConsole;

//**********************************************************************************************************************************

#endif

//**********************************************************************************************************************************
