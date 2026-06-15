/////
///// CBOBY V2 [Revision by ETK]
/////
///// By [boy_scout][boyscout_etk@hotmail.com]
/////
///// [2011][www.etalking.com.ar]
/////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "client.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool bIsValidEnt(struct cl_entity_s *ent)
{
	if(ent 
		&& ent->player
		&& me.iIndex != ent->index 
		&& ent->curstate.movetype !=6
		&& ent->curstate.movetype != 0  
		&& !(ent->curstate.messagenum<GetLocalPlayer()->curstate.messagenum) 
		&& !(GetLocalPlayer()->curstate.iuser1==4 
		&& GetLocalPlayer()->curstate.iuser2==ent->index)
		&& vPlayers[ent->index].team > 0 && vPlayers[ent->index].team <= 2)
		return true;
	else
		return false;
} 

bool bIsValidEnt(int iIndex)
{
	cl_entity_s *ent = GetEntityByIndex(iIndex);

	if(ent 
		&& ent->player
		&& me.iIndex != ent->index 
		&& ent->curstate.movetype !=6
		&& ent->curstate.movetype != 0  
		&& !(ent->curstate.messagenum<GetLocalPlayer()->curstate.messagenum) 
		&& !(GetLocalPlayer()->curstate.iuser1==4 
		&& GetLocalPlayer()->curstate.iuser2==ent->index)
		&& vPlayers[ent->index].team > 0 && vPlayers[ent->index].team <= 2)
		return true;
	else
		return false;
}

bool isEnemy(int ax)
{
	return (me.team != vPlayers[ax].team);
}
