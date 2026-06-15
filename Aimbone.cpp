#include "client.h"

CAimbone Aimbone;

typedef float TransformMatrix[MAXSTUDIOBONES][3][4];
typedef float BoneMatrix_t[MAXSTUDIOBONES][3][4]; 

model_t *pModel; 
studiohdr_t *pStudioHeader; 
BoneMatrix_t *pBoneMatrix; 
mstudiobbox_t *pHitbox;
TransformMatrix* pbonetransform;

void CAimbone::CalculateHitbox( cl_entity_s *pEnt )
{
	int ax = pEnt->index;
	
	pModel = IEngineStudio.SetupPlayerModel(ax); 
	pStudioHeader = (studiohdr_t*)IEngineStudio.Mod_Extradata(pModel); 
	pBoneMatrix = (BoneMatrix_t*)IEngineStudio.StudioGetBoneTransform(); 
	pHitbox = (mstudiobbox_t*)((byte*)pStudioHeader + pStudioHeader->hitboxindex);
	pbonetransform = (TransformMatrix*)IEngineStudio.StudioGetBoneTransform();

	if(!vPlayers[ax].bGotHead)
	{
		vec3_t pos,vCubePoints[8],vCubePointsTrans[8];
		
		vCubePoints[0] = (pHitbox[11].bbmin); 
        vCubePoints[1] = Vector(pHitbox[11].bbmin.x, pHitbox[11].bbmax.y, pHitbox[11].bbmin.z); 
        vCubePoints[2] = Vector(pHitbox[11].bbmax.x, pHitbox[11].bbmax.y, pHitbox[11].bbmin.z); 
        vCubePoints[3] = Vector(pHitbox[11].bbmax.x, pHitbox[11].bbmin.y, pHitbox[11].bbmin.z); 
        vCubePoints[4] = (pHitbox[11].bbmax); 
        vCubePoints[5] = Vector(pHitbox[11].bbmin.x, pHitbox[11].bbmax.y, pHitbox[11].bbmax.z); 
        vCubePoints[6] = Vector(pHitbox[11].bbmin.x, pHitbox[11].bbmin.y, pHitbox[11].bbmax.z); 
        vCubePoints[7] = Vector(pHitbox[11].bbmax.x, pHitbox[11].bbmin.y, pHitbox[11].bbmax.z); 
 
		UINT uiBoneIndex,uiBoneAxis;
        for(uiBoneIndex=1;uiBoneIndex<55;uiBoneIndex++)
        {
            for(uiBoneAxis^=uiBoneAxis;uiBoneAxis<3;uiBoneAxis++)
                pos[uiBoneAxis]=(*pbonetransform)[uiBoneIndex][uiBoneAxis][3];
            VectorCopy(pos, vPlayers[ax].vBone[uiBoneIndex]);
        }
		UINT uiHitboxIndex,uiHitboxAxis;
		for(uiHitboxIndex=0;uiHitboxIndex<8;uiHitboxIndex++)
        {
            for(uiHitboxAxis^=uiHitboxAxis;uiHitboxAxis<3;uiHitboxAxis++)
				vCubePointsTrans[uiHitboxIndex][uiHitboxAxis] = DotProduct(vCubePoints[uiHitboxIndex], (*pBoneMatrix)[pHitbox[11].bone][uiHitboxAxis]) + (*pBoneMatrix)[pHitbox[11].bone][uiHitboxAxis][3]; 
			VectorCopy(vCubePointsTrans[uiHitboxIndex], vPlayers[ax].vHitbox[uiHitboxIndex]);
        }

		vPlayers[ax].bGotHead = true;
	}
}

void CAimbone::Draw()
{
	for(int ax=0;ax<MAX_VPLAYERS;ax++) 
	{
		if(cvar.espteam || isEnemy(ax))
		{
			if(bIsValidEnt(ax))  
			{
				float distancebone = vPlayers[ax].distance/22.0f;
				extern float fCurrentFOV;
				int   boxradiusbone = (300.0*90.0) / (distancebone*fCurrentFOV);	 
				BOUND_VALUE(boxradiusbone,1,000);
				int text_distbone = (int)(boxradiusbone);	 
				
				ColorEntry *color = PlayerColor(ax);

				if(vPlayers[ax].bGotHead)
				{
					vec3_t EntBone[54],EntHitbox[8];

					for(int i=0;i<54;i++)
						VectorCopy(vPlayers[ax].vBone[i],EntBone[i]);
					
					for(i=0;i<8;i++)
						VectorCopy(vPlayers[ax].vHitbox[i],EntHitbox[i]);

					static BYTE byHitboxMatrix[12][2]=
					{
						{0,1},{1,2},{2,3},{2,4},{4,5},{5,6},{6,7},{1,5},{0,6},{3,7},{7,4},{0,3},//Head
					};
					
					static BYTE byBoneMatrix[2][28][2]=
					{
						{
							{1,2},{2,3},{3,4},{4,5},{5,6},{6,7},{7,8},//Back Bone
							{6,10},{10,11},{11,12},{12,13},{13,14},{13,15},{15,16},//Left Arm
							{6,25},{25,26},{26,27},{27,28},{28,29},{28,30},{30,31},//Right Arm
							{40,41},//Waist
							{41,43},{43,44},{44,45},//Left Foot
							{40,49},{49,50},{50,51},//Right Foot
						},

						{
							{1,2},{2,3},{3,4},{4,5},{5,6},{6,7},{7,8},//Back Bone
							{6,10},{10,11},{11,12},{12,13},{13,14},{13,15},{15,16},//Left Arm
							{6,24},{24,25},{25,26},{26,27},{27,28},{27,29},{29,30},//Right Arm
							{38,39},//Waist
							{39,41},{41,42},{42,43},//Left Foot
							{38,47},{47,48},{48,49},//Right Foot
						}
					};
					
					cl_entity_s *ent =GetEntityByIndex(ax);
					hud_player_info_t PlayerInfo;
					gEngfuncs.pfnGetPlayerInfo ( ent->index, &PlayerInfo );

					if(strstr ( PlayerInfo.model, "arctic\0" ) 
					|| strstr ( PlayerInfo.model, "leet\0" ) 
					|| strstr ( PlayerInfo.model, "sas\0" ) )
					{
						for(i=0;i<28;i++)
							DrawVectorLine(EntBone[byBoneMatrix[0][i][0]],EntBone[byBoneMatrix[0][i][1]],text_distbone,color);
						for(i=0;i<12;i++)
							DrawVectorLine(EntHitbox[byHitboxMatrix[i][0]],EntHitbox[byHitboxMatrix[i][1]],text_distbone,color);
					}

					if(strstr ( PlayerInfo.model, "guerilla\0" ) 
					|| strstr ( PlayerInfo.model, "terror\0" ) 
					|| strstr ( PlayerInfo.model, "gign\0" ) 
					|| strstr ( PlayerInfo.model, "gsg9\0" ) 
					|| strstr ( PlayerInfo.model, "urban\0" ) )
					{
						for(i=0;i<28;i++)
							DrawVectorLine(EntBone[byBoneMatrix[1][i][0]],EntBone[byBoneMatrix[1][i][1]],text_distbone,color);
						for(i=0;i<12;i++)
							DrawVectorLine(EntHitbox[byHitboxMatrix[i][0]],EntHitbox[byHitboxMatrix[i][1]],text_distbone,color);
					}
				}
			}
		}
	}
}

