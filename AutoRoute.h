/////
///// GYJ HOOK [Revision by ETK]
/////
///// By [boy_scout][boyscout_etk@hotmail.com]
/////
///// [2011][www.etalking.com.ar]
/////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef AUTOWAY_H
#define AUTOWAY_H
typedef struct
{
	vec3_t	origin;
	int	index;
} Way_Point;

typedef struct
{
	Way_Point	point[300]; //300个点
	int	index;
	int	count;
	bool enabled;
} Way_Line;

typedef enum 
{
	WAY_NONE = 0,
	WAY_FROM = 1,
	WAY_END = 2,
	WAY_START = 3,
} WAYMODE;

typedef enum 
{
	WAY_NO_DIRECTION = 0,
	WAY_ASC = 1,
	WAY_DESC = 2,
} WAYDIRECTION;

class AutoWay
{
private:
	int waypointcount;
	int waycount;
	int iWayPoint;
	int iWayLine;
	float me_forwardmove;
	float me_sidemove;
	void GotoWayPoint(float *point, usercmd_s *usercmd);
	bool WayMoveEnough(float *point, usercmd_s *usercmd);
public:
	void CreateMove(usercmd_s *usercmd);
	void FindFowardWay(int lastway);
	void LoadWay(char * sfilename);
	void SaveWay();
	void AddPoint();
	void WayTurn();
	void ClearAllWay();
	void DrawWay();
	void RecordOneWayStart(int index);
	void ClearOneWay(int index);
	void RecordAnyWayStart();
	void RecordWayStop();
	void FindAnyWay(float pointdist,bool userand);
	void drawRadarsPoints();
	bool bContinueAutoWay;
	void commands();
	void Autodir(struct usercmd_s* usercmd);
protected:
	HANDLE hfile;
	char filename[256];
	char levelname[256];
	bool Record;
	WAYMODE way_mode;
	WAYDIRECTION way_direction;
	Way_Line way_line[100];  //100条线
public:
	AutoWay()
	{ 
		waypointcount=300;
		waycount=100;
		hfile = NULL;
		iWayPoint = -1;
	    iWayLine = -1;
		me_forwardmove=0;
		me_sidemove=0;
		Record = false;
		way_direction = WAY_ASC;
		ZeroMemory(way_line, sizeof(way_line));
	}
};

extern AutoWay autoway;
#endif