/* * * * * * * * * * * * * * * * * * * * * * * *
*	File Name *	CInput.h				 	   *
*	   Author *	Basilius Bias Astho Christyono *
* Website URL * bifeldy.blogspot.com		   *
*       Email *	bifeldy@gmail.com              *
* Description *	Input Controller			   *
*  Created On *	13/06/2018					   *
* * * * * * * * * * * * * * * * * * * * * * * */
#pragma once
#include "../Header Files/stdafx.h"

// Device types
enum DIRECTINPUTTYPE
{
	DIT_KEYBOARD,
	DIT_MOUSE,
	DIT_FORCE_DWORD = 0x7fffffff
};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
CInputDevice
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
class CInputDevice
{
public:
	CInputDevice();
	~CInputDevice() { Release(); }

	BOOL Initialize(LPDIRECTINPUT8 pDI, HWND hWnd, DIRECTINPUTTYPE type);
	void Release();
	void Read();
	void LockKey(DWORD key);

	long GetX() { return m_x; }
	long GetY() { return m_y; }
	long GetXDelta() { return m_mouseState.lX; }
	long GetYDelta() { return m_mouseState.lY; }
	long GetZDelta() { return m_mouseState.lZ; }
	BOOL* GetButtons() { return m_pressedButtons; }
	BOOL* GetKeys() { return m_pressedKeys; }

private:
	LPDIRECTINPUTDEVICE8  m_pDevice;
	HWND                  m_hWnd;
	DIRECTINPUTTYPE       m_type;
	char                  m_keyboardState[256];
	BOOL                  m_pressedKeys[256];
	DIMOUSESTATE          m_mouseState;
	BOOL                  m_pressedButtons[4];
	BOOL                  m_keyLock[256];
	long                  m_x, m_y;
};