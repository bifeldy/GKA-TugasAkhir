/* * * * * * * * * * * * * * * * * * * * * * * *
*   File Name * CFramework.h                   *
*      Author * Basilius Bias Astho Christyono *
*       Email * bias.astho@gmail.com           *
* Description * Main Controller Point          *
*  Created On * 01/06/2018                     *
* * * * * * * * * * * * * * * * * * * * * * * */
#pragma once
#include "../Header Files/stdafx.h"
#include "../Header Files/GlobalStructAndFunction.h"
#include "../Header Files/CBaseApp.h"
#include "../Header Files/CGraphics.h"
#include "../Header Files/CTimer.h"
#include "../Header Files/CInput.h"

/* * * * * * * * * * * * * * * * *
* Summary: Main framework class  *
* * * * * * * * * * * * * * * * */
class CFramework
{
public:
	CFramework(CBaseApp* pGameApp);
	~CFramework() { Release(); }
	BOOL Initialize(LPCWSTR title, HINSTANCE hInstance, int width, int height, BOOL windowed = TRUE);
	void Run();
	void Release();
	void ToggleFullscreen();
	void ToggleWireframe();
	static LRESULT CALLBACK StaticWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void LockKey(DWORD key);
	long GetXCursor();
	long GetYCursor();
	DWORD GetFillMode();
	int GetWidth();
	int GetHeight();
	float GetFPS();

private:
	LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void OnCreateDevice();
	void OnResetDevice();
	void OnLostDevice();
	void OnDestroyDevice();
	void OnUpdateFrame();
	void OnRenderFrame();
	void Pause(BOOL rendering, BOOL timer);

	// Video Intro
	void VideoIntroPlayer(HWND hWnd);

	HWND            m_hWnd;
	HINSTANCE       m_hInstance;
	BOOL            m_active;
	int             m_windowWidth;
	int             m_windowHeight;
	int             m_fullscreenWidth;
	int             m_fullscreenHeight;
	WINDOWPLACEMENT m_wp;
	DWORD           m_fillMode;
	BOOL            m_renderingPaused;
	BOOL            m_timerPaused;
	int             m_renderingPauseCount;
	int             m_timerPauseCount;
	BOOL            m_closing;

	RECT desktop;
	// Get a handle to the desktop window
	const HWND hDesktop = GetDesktopWindow();

	CGraphics*      m_pGraphics;
	CBaseApp*       m_pGameApp;
	CTimer*         m_pTimer;
	CInputDevice    m_mouse;
	CInputDevice    m_keyboard;
	LPDIRECTINPUT8  m_pDI;
};
