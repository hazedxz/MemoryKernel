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

#ifndef MENU_H
#define MENU_H

//**********************************************************************************************************************************

struct menu_entrys
{
	char title[200];
	char content[200];
	float* value_f;
	float min_f;
	float max_f;
	float step_f;
	int* value_i;
	int min_i;
	int max_i;
	int step_i;
};

//**********************************************************************************************************************************

class cMenu
{
private:

	int AddEntry_FLOAT(int n, char title[200], char content[200], float* value, float min, float max, float step);
	int AddEntry_INT(int n, char title[200], char content[200], int* value, int min, int max, int step);
	int menuSelect;
	int menuItems;
	menu_entrys menuEntry[200];

public:

	void Init();
	void Draw();
	int KeyEvent(int keynum);
	int Active;

	int getMenuSelect(){
		return menuSelect;
	}
	int getMenuItems(){
		return menuItems;
	}

	menu_entrys getMenuEntry(int i){

		return menuEntry[i];
	}

};

//**********************************************************************************************************************************

extern cMenu gMenu;

//**********************************************************************************************************************************

#endif

//**********************************************************************************************************************************
