/* * * * * * * * * * * * * * * * * * * * * * * *
*	File Name *	CFramework.cpp        		   *
*	   Author *	Basilius Bias Astho Christyono *
* Website URL * bifeldy.blogspot.com		   *
*       Email *	bifeldy@gmail.com              *
* Description *	Main Controller Point		   *
*  Created On *	01/06/2018					   *
* * * * * * * * * * * * * * * * * * * * * * * */
#include "../Header Files/CFramework.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Default constructor
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
CFramework::CFramework(CBaseApp* pGameApp)
{
	m_pGameApp = pGameApp;
	m_active = TRUE;
	m_renderingPaused = FALSE;
	m_timerPaused = FALSE;
	m_closing = FALSE;

	m_pGraphics = new CGraphics();
	m_pTimer = new CTimer();
	m_fillMode = D3DFILL_SOLID;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Destructor
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void CFramework::Release()
{
	m_closing = TRUE;
	SAFE_RELEASE(m_pGraphics);
	OnLostDevice();
	OnDestroyDevice();
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Creates the window and initializes DirectX Graphics.
Parameters:
[in] szTitle - Title of the window
[in] hInstance - Application instance.
[in] iWidth - Window width.
[in] iHeight - Window height.
[in] bWindowed - Window mode (TRUE). Fullscreen mode (FALSE).
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
BOOL CFramework::Initialize(LPCWSTR title, HINSTANCE hInstance, int width, int height, BOOL windowed)
{
	// Get the size of screen to the variable desktop
	GetWindowRect(hDesktop, &desktop);

	m_hInstance = hInstance;
	m_windowWidth = width;
	m_windowHeight = height;

	// Define the window
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_DBLCLKS;
	wcex.lpfnWndProc = (WNDPROC)CFramework::StaticWndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BINUZIANREFRESH));
	wcex.hCursor = LoadCursorFromFile(APPLICATION_CURSOR);
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = title;
	wcex.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SMALL));

	// Register the window
	RegisterClassEx(&wcex);

	// Create the window
	m_hWnd = CreateWindow(title, title, windowed ? WS_OVERLAPPEDWINDOW : WS_EX_TOPMOST, CW_USEDEFAULT,
		0, width, height, NULL, NULL, hInstance, this);

	// Adjust to desired size
	RECT rect = { 0, 0, width, height };
	AdjustWindowRect(&rect, GetWindowLong(m_hWnd, GWL_STYLE), FALSE);
	SetWindowPos(m_hWnd, HWND_TOP, 0, 0, rect.right - rect.left, rect.bottom - rect.top,
		SWP_NOZORDER | SWP_NOMOVE);

	// Video Intro
	// VideoIntroPlayer(m_hWnd);

	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	// Save current location/size
	ZeroMemory(&m_wp, sizeof(WINDOWPLACEMENT));
	m_wp.length = sizeof(WINDOWPLACEMENT);
	GetWindowPlacement(m_hWnd, &m_wp);

	// Initialize Direct3D
	if (!m_pGraphics->Initialize(m_hWnd, windowed))
	{
		return FALSE;
	}

	// Initialize DirectInput
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDI, NULL)))
	{
		SHOWERROR("DirectInput8() - Failed", __FILE__, __LINE__);
		return FALSE;
	}
	if (!m_mouse.Initialize(m_pDI, m_hWnd, DIT_MOUSE))
	{
		return FALSE;
	}
	if (!m_keyboard.Initialize(m_pDI, m_hWnd, DIT_KEYBOARD))
	{
		return FALSE;
	}

	m_fullscreenWidth = m_pGraphics->GetDisplayMode()->Width;
	m_fullscreenHeight = m_pGraphics->GetDisplayMode()->Height;

	OnCreateDevice();
	OnResetDevice();

	// Start the timer
	Pause(FALSE, FALSE);

	return TRUE;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Runs the application
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void CFramework::Run()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		// Did we recieve a message, or are we idling ?
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// Advance Game Frame.
			if (m_pGraphics->GetDevice() != NULL && m_active)
			{
				OnUpdateFrame();
				OnRenderFrame();
			}
		}
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Called after the device is created. Create D3DPOOL_MANAGED resources here.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void CFramework::OnCreateDevice()
{
	if (m_pGameApp != NULL && m_pGraphics != NULL)
	{
		m_pGameApp->OnCreateDevice(m_pGraphics->GetDevice());
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Called after the device is reset. Create D3DPOOL_DEFAULT resources here.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void CFramework::OnResetDevice()
{
	// Start the timer
	Pause(FALSE, FALSE);
	if (m_pGameApp != NULL && m_pGraphics != NULL)
	{
		m_pGameApp->OnResetDevice(m_pGraphics->GetDevice());
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Called when the device is lost. Release D3DPOOL_DEFAULT resources here.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void CFramework::OnLostDevice()
{
	if (!m_closing)
	{
		// Stop the timer only if we're not closing down
		// or else stack corruption on return from Pause
		Pause(TRUE, TRUE);
	}
	if (m_pGameApp != NULL)
	{
		m_pGameApp->OnLostDevice();
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Called after the device is destroyed. Release D3DPOOL_MANAGED resources here.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void CFramework::OnDestroyDevice()
{
	if (m_pGameApp != NULL)
	{
		m_pGameApp->OnDestroyDevice();
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Updates the current frame.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void CFramework::OnUpdateFrame()
{
	if (m_pTimer != NULL)
	{
		m_pTimer->Update();
	}
	if (m_pGameApp != NULL && m_pGraphics != NULL && m_pTimer != NULL)
	{
		float elapsedTime = m_pTimer->GetElapsedTime();
		// Send out input data
		m_mouse.Read();
		m_keyboard.Read();
		long xDelta = m_mouse.GetXDelta();
		long yDelta = m_mouse.GetYDelta();
		long zDelta = m_mouse.GetZDelta();
		BOOL* pMouseButtons = m_mouse.GetButtons();
		BOOL* pPressedKeys = m_keyboard.GetKeys();
		m_pGameApp->ProcessInput(xDelta, yDelta, zDelta, pMouseButtons, pPressedKeys, elapsedTime);

		// Send out OnUpdateFrame
		m_pGameApp->OnUpdateFrame(m_pGraphics->GetDevice(), elapsedTime);
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Renders the current frame.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void CFramework::OnRenderFrame()
{
	if (!m_active || (m_pGraphics->GetDevice() == NULL))
	{
		return;
	}

	// Check for lost device
	HRESULT result = m_pGraphics->GetDevice()->TestCooperativeLevel();
	if (FAILED(result))
	{
		if (result == D3DERR_DEVICELOST)
		{
			Sleep(50);
			return;
		}
		else
		{
			OnLostDevice();
			if (m_pGraphics->Reset() == D3DERR_DEVICELOST)
			{
				// Device is lost still
				Sleep(50);
				return;
			}
			else
			{
				OnResetDevice();
			}
		}
	}

	if (m_pGameApp != NULL && !m_renderingPaused && m_pTimer != NULL)
	{
		m_pGameApp->OnRenderFrame(m_pGraphics->GetDevice(), m_pTimer->GetElapsedTime());
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Toggles between fullscreen and windowed mode.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void CFramework::ToggleFullscreen()
{
	if (m_pGraphics == NULL || !m_active)
	{
		return;
	}

	Pause(TRUE, TRUE);
	m_pGraphics->Windowed = !m_pGraphics->Windowed;

	// Set new window style
	if (!m_pGraphics->Windowed)
	{
		// Going to fullscreen mode
		SetWindowLongPtr(m_hWnd, GWL_STYLE, WS_EX_TOPMOST);
		
		// Save current location/size
		ZeroMemory(&m_wp, sizeof(WINDOWPLACEMENT));
		m_wp.length = sizeof(WINDOWPLACEMENT);
		m_wp.ptMinPosition.x = 0;
		m_wp.ptMinPosition.y = 0;
		m_wp.rcNormalPosition.right = desktop.right;
		m_wp.rcNormalPosition.bottom = desktop.bottom;
		m_wp.showCmd = SW_HIDE;
		GetWindowPlacement(m_hWnd, &m_wp);

		// Update Window Setting
		UpdateWindow(m_hWnd);
	}

	// Reset the Device
	OnLostDevice();
	m_pGraphics->Reset();
	OnResetDevice();

	if (m_pGraphics->Windowed)
	{
		// Going to windowed mode
		SetWindowLongPtr(m_hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);

		// Restore the window location/size
		ZeroMemory(&m_wp, sizeof(WINDOWPLACEMENT));
		m_wp.length = sizeof(WINDOWPLACEMENT);
		m_wp.ptMinPosition.x = 0;
		m_wp.ptMinPosition.y = 0;
		m_wp.rcNormalPosition.right = SCREEN_WIDTH;
		m_wp.rcNormalPosition.bottom = SCREEN_HEIGHT;
		m_wp.showCmd = SW_SHOW;
		SetWindowPlacement(m_hWnd, &m_wp);

		// Update Window Setting
		UpdateWindow(m_hWnd);
	}

	Pause(FALSE, FALSE);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Toggles between wireframe and solid fill modes
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void CFramework::ToggleWireframe()
{
	m_fillMode = (m_fillMode == D3DFILL_SOLID) ? D3DFILL_WIREFRAME : D3DFILL_SOLID;
	m_pGraphics->GetDevice()->SetRenderState(D3DRS_FILLMODE, m_fillMode);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Pauses or unpauses rendering and the timer.
Parameters:
[in] rendering - TRUE to pause rendering, FALSE to unpause rendering.
[in] timer - TRUE to pause the timer, FALSE to unpause the timer.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void CFramework::Pause(BOOL rendering, BOOL timer)
{
	m_renderingPauseCount += rendering ? 1 : -1;
	m_renderingPauseCount = (m_renderingPauseCount < 0) ? 0 : m_renderingPauseCount;

	m_timerPauseCount += timer ? 1 : -1;
	m_timerPauseCount = (m_timerPauseCount < 0) ? 0 : m_timerPauseCount;

	m_renderingPaused = (m_renderingPauseCount > 0);
	m_timerPaused = (m_timerPauseCount > 0);

	if (m_timerPaused && m_pTimer != NULL)
	{
		m_pTimer->Stop();
	}
	else if (!m_timerPaused && m_pTimer != NULL)
	{
		m_pTimer->Start();
	}
}

void CFramework::VideoIntroPlayer(HWND m_hWnd)
{
	// Initialize COM
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	// Instantiate filter graph interface
	CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC, IID_IGraphBuilder, (void **)&pGB);
	// Get interfaces to control playback & screensize
	pGB->QueryInterface(IID_IMediaControl, (void **)&pMC);
	pGB->QueryInterface(IID_IVideoWindow, (void **)&pVW);
	// Get interface to allow the app to wait for completion of playback
	pGB->QueryInterface(IID_IMediaEventEx, (void **)&pME);
	BOOL bSleep = TRUE;
	// Allow DirectShow to create the FilterGraph for this media file
	pGB->RenderFile(VideoIntro, NULL);
	// Set the message drain of the video window to point to our hidden
	// application window.  This allows keyboard input to be transferred
	// to our main window for processing.
	//
	// If this is an audio-only or MIDI file, then put_MessageDrain will fail.
	//
	pVW->put_MessageDrain((OAHWND)m_hWnd);
	LONG lMode;
	static HWND hDrain = 0;
	// Read current state
	pVW->get_FullScreenMode(&lMode);
	if (lMode == 0)  /* OAFALSE */ {
		// Save current message drain
		pVW->get_MessageDrain((OAHWND *)&hDrain);
		// Set message drain to application main window
		pVW->put_MessageDrain((OAHWND)m_hWnd);
		// Switch to full-screen mode
		lMode = -1;  /* OATRUE */
		pVW->put_FullScreenMode(lMode);
	}
	// Display first frame of the movie
	pMC->Pause();
	// Start playback
	pMC->Run();
	// Update state variables
	g_bContinue = TRUE;
	// Enter a loop of checking for events and sampling keyboard input
	while (g_bContinue)
	{
		long lEventCode;
		LONG_PTR lpParam1, lpParam2;
		// Reset sleep flag
		bSleep = TRUE;
		// Has there been a media event?  Look for end of stream condition.
		if (E_ABORT != pME->GetEvent(&lEventCode, &lpParam1,
			&lpParam2, 0))
		{
			// Is this the end of the movie?
			if (lEventCode == EC_COMPLETE)
			{
				g_bContinue = FALSE;
				bSleep = FALSE;
			}
			// Free the media event resources
			pME->FreeEventParams(lEventCode, lpParam1, lpParam2);
		}
		// Give system threads time to run (and don't sample user input madly)
		if (bSleep)
			Sleep(KEYBOARD_SAMPLE_FREQ);
	}
	// Release
	pGB->Release();
	pMC->Release();
	pVW->Release();
	pME->Release();
	CoUninitialize();
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Locks a key so it is only read once per key down.
Parameters:
[in] key - Key to lock. DIK_code
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void CFramework::LockKey(DWORD key)
{
	m_keyboard.LockKey(key);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Event handler. Routes messages to appropriate instance.
Parameters:
[in] hWnd - Unique handle to the window.
[in] message - Incoming message.
[in] wParam - Parameter of the message (unsigned int).
[in] lParam - Parameter of the message (long).
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
LRESULT CALLBACK CFramework::StaticWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_CREATE:
		SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG)((CREATESTRUCT *)lParam)->lpCreateParams);		
		CFramework *targetApp = (CFramework*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
		if (targetApp)
		{
			return targetApp->WndProc(hWnd, msg, wParam, lParam);
		}	
	}	

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Application event handler.
Parameters:
[in] hWnd - Unique handle to the window.
[in] message - Incoming message.
[in] wParam - Parameter of the message (unsigned int).
[in] lParam - Parameter of the message (long).
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
LRESULT CALLBACK CFramework::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
		if (m_pGraphics->GetDevice())
		{
			OnUpdateFrame();
			OnRenderFrame();
		}
		ValidateRect(hWnd, 0);
		return 0;
	case WM_SIZE:
		if (wParam == SIZE_MINIMIZED)
		{
			// Disable application on minimized
			m_active = FALSE;
		}
		else
		{
			m_active = TRUE;
			m_windowWidth = LOWORD(lParam);
			m_windowHeight = HIWORD(lParam);
			if (m_pGraphics->GetDevice())
			{
				OnLostDevice();
				m_pGraphics->Reset();
				OnResetDevice();
				OnUpdateFrame();
				OnRenderFrame();
			}
		}
		return 0;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Gets x coordinate of the mouse in client coordinates.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
long CFramework::GetXCursor()
{
	return m_mouse.GetX();
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Gets y coordinate of the mouse in client coordinates.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
long CFramework::GetYCursor()
{
	return m_mouse.GetY();
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Gets the current fill mode.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
DWORD CFramework::GetFillMode()
{
	return m_fillMode;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Gets the current client width.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int CFramework::GetWidth()
{
	if (m_pGraphics->Windowed)
	{
		return m_windowWidth;
	}

	return m_fullscreenWidth;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Gets the current client height.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int CFramework::GetHeight()
{
	if (m_pGraphics->Windowed)
	{
		return m_windowHeight;
	}

	return m_fullscreenHeight;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Gets the framerate
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
float CFramework::GetFPS()
{
	if (m_pTimer != NULL)
	{
		return m_pTimer->GetFPS();
	}
	return 0.0f;
}