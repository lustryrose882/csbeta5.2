#include <math.h>
#include "hud.h"
#include "util.h"
#include <string.h>
#include <stdio.h>
#include "parsemsg.h"

DECLARE_MESSAGE( m_Timer, RoundTime )

int CHudTimer::Init()
{
	gHUD.AddHudElem(this);

	HOOK_MESSAGE( RoundTime );
	m_iFlags = 0;
    m_PanicColorChange = false;

	return 1;
}

int CHudTimer::VidInit()
{
	m_TimerIcon = gHUD.GetSpriteIndex( "stopwatch" );
	return 1;
}

int CHudTimer::Draw( float fTime )
{
	int r, g, b;

    if ( gHUD.m_iHideHUDDisplay & HIDEHUD_HEALTH  )
        return 1;

	if ( !(gHUD.m_iWeaponBits & ( 1<<(WEAPON_SUIT) ) ))
		return 1;

	int min = max( 0, (int)( m_Time + m_PlayTime - gHUD.m_flTime ) / 60);
	int sec = max( 0, (int)( m_Time + m_PlayTime - gHUD.m_flTime ) - (min * 60));

	if( min * 60 + sec > 20 )
	{
		UnpackRGB(r,g,b, RGB_YELLOWISH );
	}
	else
	{
		m_PanicTime += gHUD.m_flTimeDelta;
		if( m_PanicTime > ((float)sec / 40.0f) + 0.1f)
		{
			m_PanicTime = 0;
			m_PanicColorChange = !m_PanicColorChange;
		}
		UnpackRGB( r, g, b, m_PanicColorChange ? RGB_YELLOWISH : RGB_REDISH );
	}

	ScaleColors( r, g, b, MIN_ALPHA );

    
    int iWatchWidth = gHUD.GetSpriteRect(m_TimerIcon).right - gHUD.GetSpriteRect(m_TimerIcon).left;
    
	int x = ScreenWidth/2;
	int y = ScreenHeight - 1.5 * gHUD.m_iFontHeight ;
    
    SPR_Set(gHUD.GetSprite(m_TimerIcon), r, g, b);
    SPR_DrawAdditive(0, x, y, &gHUD.GetSpriteRect(m_TimerIcon));

	x = gHUD.DrawHudNumber2( x + iWatchWidth / 4, y, false, 2, min, r, g, b );
	// draw :
	gEngfuncs.pfnFillRGBA(x + iWatchWidth / 4, y + gHUD.m_iFontHeight / 4, 2, 2, r, g, b, 100);
	gEngfuncs.pfnFillRGBA(x + iWatchWidth / 4, y + gHUD.m_iFontHeight - gHUD.m_iFontHeight / 4, 2, 2, r, g, b, 100);

	gHUD.DrawHudNumber2( x + iWatchWidth / 2, y, true, 2, min, r, g, b );
	return 1;
}

int CHudTimer::MsgFunc_RoundTime(const char *pszName, int iSize, void *pbuf)
{
	BEGIN_READ( pbuf, iSize );
	m_Time = READ_SHORT();
	m_PlayTime = gHUD.m_flTime;
	m_iFlags = HUD_ACTIVE;
	return 1;
}

DECLARE_MESSAGE( m_ProgressBar, BarTime )

int CHudProgressBar::Init()
{
	gHUD.AddHudElem(this);

	HOOK_MESSAGE( BarTime );
	m_iFlags = 0;
	m_fStartTime = m_fPercent = 0.0f;

	return 1;
}

int CHudProgressBar::VidInit()
{
	return 1;
}

int CHudProgressBar::Draw( float flTime )
{
	if( (m_fPercent < 0.0f) || (m_fPercent > 1.0f) )
	{
		m_iFlags = 0;
		m_fPercent = 0.0f;
		return 1;
	}

	if( m_iDuration != 0.0f )
	{
		m_fPercent = ((flTime - m_fStartTime) / m_iDuration);
	}
	else
	{
		m_fPercent = 0.0f;
		m_iFlags = 0;
		return 1;
	}

	gEngfuncs.pfnFillRGBA( ScreenWidth/4, ScreenHeight*2/3, ScreenWidth/2, 10, 0, 0, 0, 153 );
	gEngfuncs.pfnFillRGBA( ScreenWidth/4 + 1, ScreenHeight*2/3, ScreenWidth/2 - 1, 1, 255, 140, 0, 255 );
	gEngfuncs.pfnFillRGBA( ScreenWidth/4, ScreenHeight*2/3, 1, 10 - 1, 255, 140, 0, 255 );
	gEngfuncs.pfnFillRGBA( ScreenWidth/4 + ScreenWidth/2 - 1, ScreenHeight*2/3 + 1, 1, 10 - 1, 255, 140, 0, 255 );
	gEngfuncs.pfnFillRGBA( ScreenWidth/4, ScreenHeight*2/3 + 10 - 1, ScreenWidth/2 - 1, 1, 255, 140, 0, 255 );
	gEngfuncs.pfnFillRGBA( ScreenWidth/4+2, ScreenHeight*2/3+2, m_fPercent * (ScreenWidth/2-4), 6, 255, 140, 0, 255 );

	return 1;
}

int CHudProgressBar::MsgFunc_BarTime(const char *pszName, int iSize, void *pbuf)
{
	BEGIN_READ( pbuf, iSize );

	m_iDuration = READ_SHORT();
	m_fPercent = 0.0f;

	m_fStartTime = gHUD.m_flTime;

	m_iFlags = HUD_ACTIVE;
	return 1;
}
