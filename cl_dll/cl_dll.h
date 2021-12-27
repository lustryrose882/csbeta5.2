/***
*
*	Copyright (c) 1999, Valve LLC. All rights reserved.
*	
*	This product contains software technology licensed from Id 
*	Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc. 
*	All Rights Reserved.
*
*   Use, distribution, and modification of this source code and/or resulting
*   object code is restricted to non-commercial enhancements to products from
*   Valve LLC.  All other use, distribution, or modification is prohibited
*   without written permission from Valve LLC.
*
****/
//
//  cl_dll.h
//

// 4-23-98  JOHN

//
//  This DLL is linked by the client when they first initialize.
// This DLL is responsible for the following tasks:
//		- Loading the HUD graphics upon initialization
//		- Drawing the HUD graphics every frame
//		- Handling the custum HUD-update packets
//

typedef unsigned char byte;
typedef unsigned short word;
typedef float vec_t;

typedef int (*pfnUserMsgHook)(const char *pszName, int iSize, void *pbuf);

#include "util_vector.h"

#include "../engine/cdll_int.h"

#define MAX_WEAPONS		32		// ???

#define MAX_WEAPON_SLOTS		5	// hud item selection slots
#define MAX_ITEM_TYPES			6	// hud item selection slots

#define MAX_ITEMS				5	// hard coded item types

#define	HIDEHUD_WEAPONS		( 1<<0 )
#define	HIDEHUD_FLASHLIGHT	( 1<<1 )
#define	HIDEHUD_ALL			( 1<<2 )
#define 	HIDEHUD_HEALTH		( 1<<3 )

#define	MAX_AMMO_TYPES	32		// ???
#define MAX_AMMO_SLOTS  32		// not really slots

#define HUD_PRINTNOTIFY		1
#define HUD_PRINTCONSOLE	2
#define HUD_PRINTTALK		3
#define HUD_PRINTCENTER		4


#define WEAPON_SUIT			31

extern cl_enginefunc_t gEngfuncs;
