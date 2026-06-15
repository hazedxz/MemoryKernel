#ifndef STRAFEBOT
#define STRAFEBOT

class StrafeBot
{
public:

	void StrafeHack(float frametime, struct usercmd_s *cmd);
	void StrafeHacker(float frametime, struct usercmd_s *cmd,float visible,float crazy);
	void AutoDir(struct usercmd_s *cmd);
	void FastRun(float frametime, struct usercmd_s *cmd);
	void FastRunner(struct usercmd_s *cmd);
	void GroundStrafer(struct usercmd_s *cmd);
	void GroundStrafe(struct usercmd_s *cmd);
	void Bhop(float frametime, struct usercmd_s *cmd);
	void Bhopper(float frametime, struct usercmd_s *cmd);
	void JumpBugger(float frametime, struct usercmd_s *cmd);
	void JumpBug(float frametime, usercmd_s *cmd);
	void StrafeHelper(float frametime, struct usercmd_s *cmd);
	void InitCreatemove(float frametime, struct usercmd_s *cmd);
	void InitHud();

	void commands();
};

extern StrafeBot Strafebot;

#endif