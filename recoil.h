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

#ifndef RECOIL_H
#define RECOIL_H

//**********************************************************************************************************************************

float GetVecSpread(float* velocity);
void GetSpreadXY(unsigned int seed, int future, float* velocity, float* vec);
void GetRecoilOffset(unsigned int seed, int future, float* inangles, float* velocity, float* outangles);
void DefaultSpreadVar(int weaponid);
void recoil(struct usercmd_s* usercmd);
void nospread(struct usercmd_s* usercmd);
//**********************************************************************************************************************************

#endif

//**********************************************************************************************************************************


/*
talk to valve about this.

ask them why on lan servers the aim cone for pistol increases, while on 
internet servers it doesn't.

and specifically make sure you tell them about the spreadvars.
*/

/*
NoSpread fixes 
AWP:
-----
Wenn zoomt:
im Sprung: 0.85
iSpeed > 140: 0.25
iSpeed > 10: 0.1
duckend: 0.000
ansonsten: 0.001

Wenn nicht gezoomt:
im Sprung: 0.85 + 0.08
iSpeed > 140: 0.25 + 0.08
iSpeed > 10: 0.1 + 0.08
duckend: 0.000 + 0.08
ansonsten: 0.001 + 0.08

FAMAS:
-------
Wenn Burst:
iSpeed > 140 m_flAccuracy * 0.07f 
ansonsten ( m_flAccuracy * 0.02f )

Wenn Burst und im Sprung:
( m_flAccuracy * 0.3f )

Wenn kein Burst:
iSpeed > 140 m_flAccuracy * 0.07f + 0.01
ansonsten ( m_flAccuracy * 0.02f ) + 0.01

Wenn Burst und im Sprung:
( m_flAccuracy * 0.3f ) + 0.01

G3SG1:
-------
Wenn zoomt:
Wenn im Sprung: ((0.45) * (1 - m_flAccuracy))
iSpeed > 5: 0.15 + 0.025;
duckend: ((0.035) * (1 - m_flAccuracy))
ansonsten: ((0.055) * (1 - m_flAccuracy))

Wenn nicht gezoomt:
im Sprung: ((0.45) * (1 - m_flAccuracy)) + 0.025
iSpeed > 5: 0.15 + 0.025;
duckend: ((0.035) * (1 - m_flAccuracy)) + 0.025
ansonsten: ((0.055) * (1 - m_flAccuracy)) + 0.025

M4A1: 
------
Wenn silenced:
im Sprung: ( (0.035f) + (0.4f) *(m_flAccuracy))
iSpeed > 140: ( (0.035f) + (0.07f)*(m_flAccuracy))
duckend: ( (0.095f)*(1 - m_flAccuracy));
ansonsten: ( (0.025f) *(m_flAccuracy)) 

Wenn nicht silenced:
im Sprung: ( (0.035f) + (0.4f)*(m_flAccuracy))
iSpeed > 140: ( (0.035f) + (0.07f)*(m_flAccuracy)) 
duckend: ( (0.095f)*(1 - m_flAccuracy))
ansonsten: ( (0.02f)*(m_flAccuracy)) 

SCOUT:
-------
Wenn zoomt:
im Sprung: 0.2
iSpeed > 170: 0.075
duckend: 0.000
ansonsten: 0.007

Wenn nicht zoomt:
im Sprung: 0.2 + 0.025
iSpeed > 170: 0.075 + 0.025
duckend: 0.000 + 0.025
ansonsten: 0.007 + 0.025;

SG550:
------
Wenn zoomt:
im sprung: ((0.45) * (1 - m_flAccuracy))
iSpeed > 5: 0.15 + 0.025
duckend: ((0.04) * (1 - m_flAccuracy))
ansonsten: ((0.05) * (1 - m_flAccuracy))

Wenn nicht zoomt:
im Sprung: ((0.45) * (1 - m_flAccuracy)) + 0.025
iSpeed > 5: 0.15 + 0.025
duckend: ((0.04) * (1 - m_flAccuracy)) + 0.025
ansonsten: ((0.05) * (1 - m_flAccuracy)) + 0.025

USP45:
------
Wenn silenced:
im Spung: ((1.3) * (1 - m_flAccuracy))
iSpeed > 5: ((0.25) * (1 - m_flAccuracy))
duckend: ((0.125) * (1 - m_flAccuracy))
ansonsten: ((0.15) * (1 - m_flAccuracy))

Wenn nicht silenced:
im Sprung: ((1.2) * (1 - m_flAccuracy))
iSpeed > 5: ((0.225) * (1 - m_flAccuracy))
duckend: ((0.08) * (1 - m_flAccuracy))
ansonsten: ((0.1) * (1 - m_flAccuracy))

This information is as always subject to change.
*/





