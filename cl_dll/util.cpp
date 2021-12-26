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
// util.cpp
//
// implementation of class-less helper functions
//

#include "STDIO.H"
#include "STDLIB.H"
#include "MATH.H"
#include <string.h>

#include "hud.h"
#include "util.h"

#define _CRT_SECURE_NO_WARNINGS

HSPRITE LoadSprite(const char *pszName)
{
	int i;
	char sz[256]; 

	if (ScreenWidth < 640)
		i = 320;
	else
		i = 640;

	sprintf(sz, pszName, i);

	return SPR_Load(sz);
}

int HUD_GetSpriteIndexByName( const char *sz )
{
	return gHUD.GetSpriteIndex(sz);
}

HSPRITE HUD_GetSprite( int index )
{
	return gHUD.GetSprite(index);
}

wrect_t HUD_GetSpriteRect( int index )
{
	return gHUD.GetSpriteRect( index );
}
