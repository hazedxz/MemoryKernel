#pragma once

#include "client.h"

struct aimbot_s
{
	Vector vCalcOriginOffset(int iIndex);
	static int iTargetID;
	static float fCalcFOV(Vector one,Vector two,float lena=0,float lenb=0);
	static bool bVisible(int iIndex);
	static bool bCheckTeam(int iIndex);
	static bool bIsValidEnt(int iIndex);
	static void SortTargetByFov(int iIndex);
	static void SortTargetByDistance(int iIndex);
	static void ApplySilentAngles(float *angles,usercmd_s *cmd);
	static void MyVectorAngles(const float *forward,float *angles);
	void CL_CreateMove(usercmd_s *cmd);
	void Hud_Redraw();
	void bTriggerBot(usercmd_s *cmd);
};

void VectorAngles( const float *forward, float *angles );

extern aimbot_s g_Aimbot;