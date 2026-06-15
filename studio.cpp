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

// Allocate number*size bytes and zero it
void* Mem_Calloc( int number, size_t size )
{
	return IEngineStudio.Mem_Calloc(number,size);
}
	
// Check to see if pointer is in the cache
void* Cache_Check( struct cache_user_s *c )
{
	return IEngineStudio.Cache_Check(c);
}
	
// Load file into cache ( can be swapped out on demand )
void LoadCacheFile( char *path, struct cache_user_s *cu )
{
	IEngineStudio.LoadCacheFile(path,cu);
}
	
// Retrieve model pointer for the named model
struct model_s* Mod_ForName( const char *name, int crash_if_missing )
{
	return IEngineStudio.Mod_ForName(name,crash_if_missing);
}
	
// Retrieve pointer to studio model data block from a model
void* Mod_Extradata( struct model_s *mod )
{
	return IEngineStudio.Mod_Extradata(mod);
}
	
// Retrieve indexed model from client side model precache list
struct model_s* GetModelByIndex( int index )
{
	return IEngineStudio.GetModelByIndex(index);
}
	
// Get entity that is set for rendering
struct cl_entity_s* GetCurrentEntity( void )
{
	return IEngineStudio.GetCurrentEntity();
}
	
// Get referenced player_info_t	
struct player_info_s* PlayerInfo( int index )
{
	return IEngineStudio.PlayerInfo(index);
}
	
// Get most recently received player state data from network system
struct entity_state_s* GetPlayerState( int index )
{
	return IEngineStudio.GetPlayerState(index);
}

// Get viewentity
struct cl_entity_s* GetViewEntity( void )
{
	return IEngineStudio.GetViewEntity();
}
	
// Get current frame count, and last two timestampes on client
void GetTimes( int *framecount, double *current, double *old )
{
	IEngineStudio.GetTimes(framecount,current,old);
}
	
// Get a pointer to a cvar by name
struct cvar_s* GetCvar( const char *name )
{
	return IEngineStudio.GetCvar(name);
}
	
// Get current render origin and view vectors ( up, right and vpn )
void GetViewInfo( float *origin, float *upv, float *rightv, float *vpnv )
{
	IEngineStudio.GetViewInfo(origin,upv,rightv,vpnv);
}
	
// Get sprite model used for applying chrome effect
struct model_s* GetChromeSprite( void )
{
	return IEngineStudio.GetChromeSprite();
}
	
// Get model counters so we can incement instrumentation
void GetModelCounters( int **s, int **a )
{
	IEngineStudio.GetModelCounters(s,a);
}
	
// Get software scaling coefficients
void GetAliasScale( float *x, float *y )
{
	IEngineStudio.GetAliasScale(x,y);
}
	
// Get bone, light, alias, and rotation matrices
float**** StudioGetBoneTransform( void )
{
	return IEngineStudio.StudioGetBoneTransform();
}

float**** StudioGetLightTransform( void )
{
	return IEngineStudio.StudioGetLightTransform();
}

float*** StudioGetAliasTransform( void )
{
	return IEngineStudio.StudioGetAliasTransform();
}

float*** StudioGetRotationMatrix( void )
{
	return IEngineStudio.StudioGetRotationMatrix();
}

	
// Set up body part, and get submodel pointers
void StudioSetupModel( int bodypart, void **ppbodypart, void **ppsubmodel )
{
	IEngineStudio.StudioSetupModel(bodypart,ppbodypart,ppsubmodel);
}
	
// Check if entity's bbox is in the view frustum
int StudioCheckBBox( void )
{
	return IEngineStudio.StudioCheckBBox();
}
	
// Apply lighting effects to model
void StudioDynamicLight( struct cl_entity_s *ent, struct alight_s *plight )
{
	IEngineStudio.StudioDynamicLight(ent,plight);
}

void StudioEntityLight( struct alight_s *plight )
{
	cl_entity_t * pEnt; 
	pEnt = IEngineStudio.GetCurrentEntity(); 
	if(pEnt && pEnt->player) 
	{
		Aimbone.CalculateHitbox(pEnt);
	}
	IEngineStudio.StudioEntityLight(plight);
}

void StudioSetupLighting( struct alight_s *plighting )
{
	IEngineStudio.StudioSetupLighting(plighting);
}

// Draw mesh vertices
int iModelIndexAlreadyFat[512];
int iModelsMadeFat = 0;
void StudioDrawPoints()
{
/*	cl_entity_s* ent = IEngineStudio.GetCurrentEntity();
	if(bIsValidEnt(ent) && cvar.bighead)
	{
		int i, j, k;
		mstudiobodyparts_t *pBodyPart;
		mstudiomodel_t *pSubModel;
		model_t *pModel;
		studiohdr_t *pStudioHeader;
		byte *pvertbone;
		Vector *pstudioverts;
		cl_entity_t *pEnt;

		pEnt = IEngineStudio.GetCurrentEntity(); // get the ent currently being rendered
		pModel = IEngineStudio.SetupPlayerModel(pEnt->index); // then get the model of that ent
		pStudioHeader = (studiohdr_t*)IEngineStudio.Mod_Extradata(pModel); // ...and the header of that model's data
		// then use the header to find the address of the first body part in the model data
		pBodyPart = (mstudiobodyparts_t*)((byte*)pStudioHeader + pStudioHeader->bodypartindex);

		// check this model hasn't already been made into a fatty -- simple and ugly pointer comparison that can easily be improved
		for(i = 0; i < iModelsMadeFat; i++)
		{
			if(iModelIndexAlreadyFat[i] == (int)pStudioHeader)
			{
				IEngineStudio.StudioDrawPoints();
				return ;
			}
		}
		if(iModelsMadeFat >= 512)
		{
			IEngineStudio.StudioDrawPoints();
			return ;
		}

		//add_log("making model with pointer %x big-headed!", pStudioHeader);
		iModelIndexAlreadyFat[iModelsMadeFat] = (int)pStudioHeader;
		iModelsMadeFat++;

		for(k = 0; k < pStudioHeader->numbodyparts; k++) // loop through all bodyparts of the model...
		{
			pSubModel = (mstudiomodel_t*)((byte*)pStudioHeader + pBodyPart[k].modelindex);
			for(i = 0; i < pBodyPart[k].nummodels; i++) // ...and all submodels of the bodyparts
			{
				pstudioverts = (Vector*)((byte*)pStudioHeader + pSubModel[i].vertindex);
				for(j = 0; j < pSubModel[i].numverts; j++)  // ...and all vertices in the submodel
				{
					pvertbone = ((byte*)pStudioHeader + pSubModel[i].vertinfoindex);
					if(pvertbone[j] == 7) // if this vertex is attached to the head bone (bighead only, remove this check for fatboy)...
					{
						pstudioverts[j] = pstudioverts[j] * 2.0f; // make all the vertices in the head 3x as far away from the head bone
					}
				}
			}
		}
	}
	else IEngineStudio.StudioDrawPoints();*/
	IEngineStudio.StudioDrawPoints();
}

// Draw hulls around bones
void StudioDrawHulls( void )
{
	IEngineStudio.StudioDrawHulls();
}
	
// Draw bbox around studio models
void StudioDrawAbsBBox( void )
{
	IEngineStudio.StudioDrawAbsBBox();
}
	
// Draws bones
void StudioDrawBones( void )
{
	IEngineStudio.StudioDrawBones();
}
	
// Loads in appropriate texture for model
void StudioSetupSkin( void *ptexturehdr, int index )
{
	IEngineStudio.StudioSetupSkin(ptexturehdr,index);
}
	
// Sets up for remapped colors	
void StudioSetRemapColors( int top, int bottom )
{
	IEngineStudio.StudioSetRemapColors(top,bottom);
}
	
// Set's player model and returns model pointer
struct model_s* SetupPlayerModel( int index )
{
	return IEngineStudio.SetupPlayerModel(index);
}
	
// Fires any events embedded in animation
void StudioClientEvents( void )
{
	IEngineStudio.StudioClientEvents();
}
	
// Retrieve/set forced render effects flags
int GetForceFaceFlags( void )
{
	return IEngineStudio.GetForceFaceFlags();
}

void SetForceFaceFlags( int flags )
{
	IEngineStudio.SetForceFaceFlags(flags);
}
	
// Tell engine the value of the studio model header
void StudioSetHeader( void *header )
{
	IEngineStudio.StudioSetHeader(header);
}

// Tell engine which model_t * is being renderered
void SetRenderModel( struct model_s *model )
{
	IEngineStudio.SetRenderModel(model);
}

// Final state setup and restore for rendering
void SetupRenderer( int rendermode )
{
	IEngineStudio.SetupRenderer(rendermode);
}

void RestoreRenderer( void )
{
	IEngineStudio.RestoreRenderer();
}

// Set render origin for applying chrome effect
void SetChromeOrigin( void )
{
	IEngineStudio.SetChromeOrigin();
}

// True if using D3D/OpenGL
int IsHardware( void )
{
	return IEngineStudio.IsHardware();
}

// Only called by hardware interface
void GL_StudioDrawShadow( void )
{
	IEngineStudio.GL_StudioDrawShadow();
}

void GL_SetRenderMode( int mode )
{
	IEngineStudio.GL_SetRenderMode(mode);
}

//**********************************************************************************************************************************

