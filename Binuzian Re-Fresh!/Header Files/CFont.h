/* * * * * * * * * * * * * * * * * * * * * * * *
*	File Name *	CFont.h					 	   *
*	   Author *	Basilius Bias Astho Christyono *
* Website URL * bifeldy.blogspot.com		   *
*       Email *	bifeldy@gmail.com              *
* Description *	2D & 3D Font			       *
*  Created On *	11/06/2018					   *
* * * * * * * * * * * * * * * * * * * * * * * */
#pragma once
#include "stdafx.h"

// Font alignment
enum FONTALIGNMENT { FA_LEFT, FA_CENTER, FA_RIGHT, FA_TOPRIGHT, FA_TOPLEFT, FA_BOTTOMRIGHT, FA_BOTTOMLEFT };

class CFont
{
public:
    CFont();
    ~CFont() { Release(); }

    BOOL Initialize( LPDIRECT3DDEVICE9 pDevice, LPCWSTR faceName, int size, BOOL bold = FALSE,
        BOOL italic = FALSE );
    void Print(LPCWSTR text, int xPosition, int yPosition, DWORD color, LPD3DXSPRITE sprite = NULL,
        int textBoxWidth = 0, int textBoxHeight = 0, FONTALIGNMENT alignment = FA_LEFT );
    void OnLostDevice();
    void OnResetDevice();
    void Release();

private:
    LPD3DXFONT m_pFont;
};