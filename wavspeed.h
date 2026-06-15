#ifndef SPEEDBOT
#define SPEEDBOT

class SpeedBot
{
public:

	bool Initialize(void);
	void AdjustSpeed( double x );
	void *SpeedHackPtr(void);
	void commands();
};

extern DWORD SpeedPtr;

extern SpeedBot Speedbot;

#endif