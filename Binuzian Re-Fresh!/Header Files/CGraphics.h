/* * * * * * * * * * * * * * * * * * * * * * * *
*	File Name *	CGraphics.h        			   *
*	   Author *	Basilius Bias Astho Christyono *
* Website URL * bifeldy.blogspot.com		   *
*       Email *	bifeldy@gmail.com              *
* Description *	DirectX Graphics wrapper	   *
*  Created On *	01/06/2018					   *
* * * * * * * * * * * * * * * * * * * * * * * */
#pragma once
#include "../Header Files/stdafx.h"

class CGraphics
{
public:
	CGraphics();
	~CGraphics() { Release(); }
	BOOL Initialize(HWND hWnd, BOOL bWindowed);
	void Release();
	BOOL Reset();
	LPDIRECT3D9       GetD3D() { return m_pD3D9; }
	LPDIRECT3DDEVICE9 GetDevice() { return m_pDevice; }
	D3DDISPLAYMODE*   GetDisplayMode() { return &m_displayMode; }
	BOOL Windowed;

private:
	BOOL BuildPresentParameters();
	HWND                    m_hWnd;
	HINSTANCE               m_hInstance;
	LPDIRECT3D9             m_pD3D9;
	LPDIRECT3DDEVICE9       m_pDevice;
	D3DCAPS9                m_caps;
	D3DPRESENT_PARAMETERS   m_pp;
	D3DDISPLAYMODE          m_displayMode;
};