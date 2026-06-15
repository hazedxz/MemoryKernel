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

#include "client.h"

//**********************************************************************************************************************************

static int (*OrigStudioDrawPlayer)(int flags, struct entity_state_s* pplayer);
static int NewStudioDrawPlayer(int flags, struct entity_state_s* pplayer)
{
	vec3_t vMin, vMax, playerAngles;
	cl_entity_s* m_pCurrentEntity = IEngineStudio.GetCurrentEntity();
	if (m_pCurrentEntity->index < 0 || m_pCurrentEntity->index > gEngfuncs.GetMaxClients()) return 0;
	int retval = (*OrigStudioDrawPlayer)(flags, pplayer);
	return retval;
}

//**********************************************************************************************************************************

static int	( *OrigStudioDrawModel	)( int flags );
static int NewStudioDrawModel( int flags )
{
	int ret = OrigStudioDrawModel(flags);
	return ret;
}

//**********************************************************************************************************************************

void HUD_GetStudioModelInterface(int version, struct r_studio_interface_s** ppinterface, struct engine_studio_api_s* pstudio)
{
	 if(ppinterface && *ppinterface)
	 {
		OrigStudioDrawPlayer = (*ppinterface)->StudioDrawPlayer;
	    (*ppinterface)->StudioDrawPlayer = NewStudioDrawPlayer;

		OrigStudioDrawModel = (*ppinterface)->StudioDrawModel;
	    (*ppinterface)->StudioDrawModel = NewStudioDrawModel;
	 }
}

//**********************************************************************************************************************************


