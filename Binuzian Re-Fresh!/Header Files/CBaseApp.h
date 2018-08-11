/* * * * * * * * * * * * * * * * * * * * * * * *
*	File Name *	CBaseApp.h		      		   *
*	   Author *	Basilius Bias Astho Christyono *
* Website URL * bifeldy.blogspot.com		   *
*       Email *	bifeldy@gmail.com              *
* Description *	Application Base Class		   *
*  Created On *	01/06/2018					   *
* * * * * * * * * * * * * * * * * * * * * * * */
#pragma once
#include "../Header Files/stdafx.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Interface that the main game application must implement
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
class CBaseApp
{
public:
	virtual ~CBaseApp() {}
	virtual void Release() = 0;
	virtual void OnCreateDevice(LPDIRECT3DDEVICE9 pDevice) = 0;
	virtual void OnResetDevice(LPDIRECT3DDEVICE9 pDevice) = 0;
	virtual void OnLostDevice() = 0;
	virtual void OnDestroyDevice() = 0;
	virtual void OnUpdateFrame(LPDIRECT3DDEVICE9 pDevice, float elapsedTime) = 0;
	virtual void OnRenderFrame(LPDIRECT3DDEVICE9 pDevice, float elapsedTime) = 0;
	virtual void ProcessInput(long xDelta, long yDelta, long zDelta, 
		BOOL* pMouseButtons, BOOL* pPressedKeys, float elapsedTime) = 0;
};