/* * * * * * * * * * * * * * * * * * * * * * * *
*	File Name *	CGameApp.cpp	      		   *
*	   Author *	Basilius Bias Astho Christyono *
* Website URL * bifeldy.blogspot.com		   *
*       Email *	bifeldy@gmail.com              *
* Description *	Application Header File		   *
*  Created On *	01/06/2018					   *
* * * * * * * * * * * * * * * * * * * * * * * */
#include "../Header Files/CGameApp.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Default constructor
Parameters:
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
CGameApp::CGameApp()
{
	m_pFramework = NULL;
	CameraJump = false;
	MaxCameraJump = 2.0f;
	MoveWithAutoMouse = false;
	CameraCollision = false;
	GameStatus = 1;
	MainMenuInitialized = false;
	InGameInitialized = false;
	CreditInitialized = false;
	ExitGame = false;
	InGameEscapeIsPressed = true;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Clean up resources
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void CGameApp::Release()
{
	SAFE_RELEASE(m_pFramework);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Sets the CFramework instnace of the application.
Parameters:
[in] pFramework - Pointer to a CFramework instance
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void CGameApp::SetFramework(CFramework* pFramework)
{
	m_pFramework = pFramework;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Initialize application-specific resources and states here.
Returns: TRUE on success, FALSE on failure
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
BOOL CGameApp::Initialize()
{
	// Loading external fonts
	Initialize_CustomFONT();

	// Camera setting
	m_camera.SetMaxVelocity(100.0f);
	m_camera.SetMaxPitch(D3DXToRadian(85.0f));
	m_camera.Update();

	return TRUE;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary:
This callback function will be called immediately after the Direct3D device has been created. This is
the best location to create D3DPOOL_MANAGED resources. Resources created here should be released in
the OnDestroyDevice callback.
Parameters:
[in] pDevice - Pointer to a DIRECT3DDEVICE9 instance
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void CGameApp::OnCreateDevice(LPDIRECT3DDEVICE9 pDevice)
{
	/* If device first start */

	// Create 2D text
	m_font.Initialize(pDevice, L"Advent", 48);
	Total_Time.Initialize(pDevice, L"Advert", 72);

	// Loading / Splash Screen

	D3DXCreateSprite(pDevice, &LoadingAwal);
	D3DXCreateTextureFromFileEx(pDevice, L"Resource Files/User Interface/loading awal.png", m_pFramework->GetWidth(), m_pFramework->GetHeight(),
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 255, 255), NULL, NULL, &LoadingAwalImg);

	D3DXCreateSprite(pDevice, &LoadingHowToPlay);
	D3DXCreateTextureFromFileEx(pDevice, L"Resource Files/User Interface/loading howtoplay.png", m_pFramework->GetWidth(), m_pFramework->GetHeight(),
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 255, 255), NULL, NULL, &LoadingHowToPlayImg);

	D3DXCreateSprite(pDevice, &GamePaused);
	D3DXCreateTextureFromFileEx(pDevice, L"Resource Files/User Interface/pause.png", m_pFramework->GetWidth(), m_pFramework->GetHeight(),
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 255, 255), NULL, NULL, &GamePausedImg);

	D3DXCreateSprite(pDevice, &Congratulations);
	D3DXCreateTextureFromFileEx(pDevice, L"Resource Files/User Interface/congratulations.png", m_pFramework->GetWidth(), m_pFramework->GetHeight(),
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 255, 255), NULL, NULL, &CongratulationsImg);

	D3DXCreateSprite(pDevice, &Credit);
	D3DXCreateTextureFromFileEx(pDevice, L"Resource Files/User Interface/Credit.png", m_pFramework->GetWidth(), m_pFramework->GetHeight(),
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 255, 255), NULL, NULL, &CreditImg);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary:
This callback function will be called immediately after the Direct3D device has been created. This is
the best location to create D3DPOOL_DEFAULT resources. Resources created here should be released in
the OnLostDevice callback.
Parameters:
[in] pDevice - Pointer to a DIRECT3DDEVICE9 instance
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void CGameApp::OnResetDevice(LPDIRECT3DDEVICE9 pDevice)
{
	/* If device going to fullscreen or windowed mode */

	// Set projection
	m_camera.SetAspectRatio((float)m_pFramework->GetWidth() / (float)m_pFramework->GetHeight());
	pDevice->SetTransform(D3DTS_PROJECTION, m_camera.GetProjectionMatrix());


	// Reinitialize Code Here
	m_font.OnResetDevice();


	// Set render states
	pDevice->SetRenderState(D3DRS_FILLMODE, m_pFramework->GetFillMode());
	pDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	pDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(150, 150, 150));
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_INVDESTCOLOR);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);

	// Set sampler state
	pDevice->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, 8);
	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	ZeroMemory(&m_material, sizeof(D3DMATERIAL9));
	m_material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_material.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pDevice->SetMaterial(&m_material);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary:
This callback function will be called immediately after the Direct3D device has entered a lost state
and before IDirect3DDevice9::Reset is called. Resources created in the OnResetDevice callback should
be released here, which generally includes all D3DPOOL_DEFAULT resources.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void CGameApp::OnLostDevice()
{
	m_font.OnLostDevice();
	Total_Time.OnLostDevice();
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary:
This callback function will be called immediately after the Direct3D device has been destroyed.
Resources created in the OnCreateDevice callback should be released here, which generally includes
all D3DPOOL_MANAGED resources.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void CGameApp::OnDestroyDevice()
{
	if (MainMenuInitialized) MainMenu_Release();
	// if (InGameInitialized) InGame_Release();
	// if (CreditInitialized) Credit_Release();

	m_font.Release();

	// Loading Awal
	LoadingAwal->Release();
	LoadingAwalImg->Release();

	// Loading Howtoplay
	LoadingHowToPlay->Release();
	LoadingHowToPlayImg->Release();

	// Game Paused
	GamePaused->Release();
	GamePausedImg->Release();

	// Congratulation
	Congratulations->Release();
	CongratulationsImg->Release();

	// Congratulation
	Credit->Release();
	CreditImg->Release();

}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Updates the current frame.
Parameters:
[in] pDevice - Pointer to a DIRECT3DDEVICE9 instance
[in] elapsedTime - Time elapsed since last frame
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void CGameApp::OnUpdateFrame(LPDIRECT3DDEVICE9 pDevice, float elapsedTime)
{
	/* Logical process before render */

	D3DXMATRIX identity;
	D3DXMatrixIdentity(&identity);

	if (GameStatus == 1)
	{
		if (InGameInitialized) InGame_Release();
		// if (CreditInitialized) Credit_Release();
		if (!MainMenuInitialized) MainMenu_Init(pDevice);
		MainMenu_Update(pDevice, elapsedTime);
	}
	else if (GameStatus == 2)
	{
		if (MainMenuInitialized) MainMenu_Release();
		// if (CreditInitialized) Credit_Release();
		if (!InGameInitialized) InGame_Init(pDevice);
		InGame_Update(pDevice, elapsedTime);
		// Always Check Camera
		CameraPositionChecker(elapsedTime);
	}
	else if (GameStatus == 3)
	{
		// if (MainMenuInitialized) MainMenu_Release();
		// if (InGameInitialized) InGame_Release();
		// if (!CreditInitialized) Credit_Init(pDevice);
		// Credit_Update(pDevice, elapsedTime);
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Renders the current frame.
Parameters:
[in] pDevice - Pointer to a DIRECT3DDEVICE9 instance
[in] elapsedTime - Time elapsed since last frame
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void CGameApp::OnRenderFrame(LPDIRECT3DDEVICE9 pDevice, float elapsedTime)
{
	/* Render after logical update */

	D3DXMATRIX world;
	D3DXMatrixIdentity(&world); //Set to no transform

	pDevice->SetTransform(D3DTS_VIEW, m_camera.GetViewMatrix());
	pDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	pDevice->BeginScene();

	// Render scene here

	if (GameStatus == 1)
	{
		if (InGameInitialized) InGame_Release();
		// if (CreditInitialized) Credit_Release();
		if (!MainMenuInitialized) MainMenu_Init(pDevice);
		MainMenu_Render(pDevice, elapsedTime);
	}
	else if (GameStatus == 2)
	{
		if (MainMenuInitialized) MainMenu_Release();
		// if (CreditInitialized) Credit_Release();
		if (!InGameInitialized) InGame_Init(pDevice);
		InGame_Render(pDevice, elapsedTime);
	}
	else if (GameStatus == 3)
	{
		// if (MainMenuInitialized) MainMenu_Release();
		// if (InGameInitialized) InGame_Release();
		// if (!CreditInitialized) Credit_Init(pDevice);
		Credit_Render(pDevice, elapsedTime);
	}

	pDevice->EndScene();
	pDevice->Present(NULL, NULL, NULL, NULL);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Responds to key presses
Parameters:
[in] xDelta - Change in mouse x-axis since last frame
[in] yDelta - Change in mouse y-axis since last frame
[in] zDelta - Change in mouse z-axis since last frame
[in] pMouseButtons - Mouse button states
[in] pPressedKeys - Keyboard keys that are pressed and not locked
[in] elapsedTime - Time elapsed since last frame
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void CGameApp::ProcessInput(long xDelta, long yDelta, long zDelta, BOOL* pMouseButtons, BOOL* pPressedKeys, float elapsedTime)
{
	if (GameStatus == 1)
	{
		MainMenu_ProcessInput(xDelta, yDelta, zDelta, pMouseButtons, pPressedKeys, elapsedTime);
	}
	else if (GameStatus == 2)
	{
		InGame_ProcessInput(xDelta, yDelta, zDelta, pMouseButtons, pPressedKeys, elapsedTime);
	}
	else if (GameStatus == 3)
	{
		Credit_ProcessInput(xDelta, yDelta, zDelta, pMouseButtons, pPressedKeys, elapsedTime);
	}
	// Graphic Controller
	if (pPressedKeys[DIK_F1])
	{
		m_pFramework->LockKey(DIK_F1);
		if (m_pFramework != NULL)
		{
			m_pFramework->ToggleFullscreen();
		}
	}
	if (pPressedKeys[DIK_F2])
	{
		m_pFramework->LockKey(DIK_F2);
		if (m_pFramework != NULL)
		{
			m_pFramework->ToggleWireframe();
		}
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Your Function Is Under Below
Parameters: -
Notes: Procedural Asset Placement
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

// Jenis Font Sendiri Eksternal
void CGameApp::Initialize_CustomFONT()
{
	AddFontResourceEx(L"Resource Files/Font/Imagination Station.ttf", FR_PRIVATE, 0);
	AddFontResourceEx(L"Resource Files/Font/Advert-Regular.ttf", FR_PRIVATE, 0);

}

void CGameApp::Loading_Screen(LPDIRECT3DDEVICE9 pDevice)
{
	pDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	pDevice->BeginScene();

	if (GameStatus == 2)
	{
		LoadingHowToPlay->Begin(NULL);
		D3DXVECTOR3 LoadingHowToPlayPosition(0.0f, 0.0f, 0.0f);
		LoadingHowToPlay->Draw(LoadingHowToPlayImg, NULL, NULL, &LoadingHowToPlayPosition, D3DCOLOR_XRGB(255, 255, 255));
		LoadingHowToPlay->End();
	}
	else
	{
		if (HP_Ketemu)
		{
			Congratulations->Begin(NULL);
			D3DXVECTOR3 CongratulationsPosition(0.0f, 0.0f, 0.0f);
			Congratulations->Draw(CongratulationsImg, NULL, NULL, &CongratulationsPosition, D3DCOLOR_XRGB(255, 255, 255));
			Congratulations->End();
			HP_Ketemu = false;
		}
		else
		{
			LoadingAwal->Begin(NULL);
			D3DXVECTOR3 LoadingAwalPosition(0.0f, 0.0f, 0.0f);
			LoadingAwal->Draw(LoadingAwalImg, NULL, NULL, &LoadingAwalPosition, D3DCOLOR_XRGB(255, 255, 255));
			LoadingAwal->End();
		}
	}

	pDevice->EndScene();
	pDevice->Present(NULL, NULL, NULL, NULL);
}

void CGameApp::MainMenu_Init(LPDIRECT3DDEVICE9 pDevice)
{
	VOID* pVoid;
	D3DXCreateTextureFromFile(pDevice, L"Resource Files/Main Menu/SkyBox.png", &WorldTexture);

	//create the vertices using the CUSTOMVERTEX struct
	CUSTOMVERTEX2 vertices[] = {

		{ -1000.0f, -1000.0f,  1000.0f,  0.0f,  0.0f,  1.0f, 0.25f, 0.666666f },		//depan
		{  1000.0f, -1000.0f,  1000.0f,  0.0f,  0.0f,  1.0f, 0.00f, 0.666666f },
		{ -1000.0f,  1000.0f,  1000.0f,  0.0f,  0.0f,  1.0f, 0.25f, 0.333333f },
		{  1000.0f,  1000.0f,  1000.0f,  0.0f,  0.0f,  1.0f, 0.00f, 0.333333f },
		{ -1000.0f, -1000.0f, -1000.0f,  0.0f,  0.0f, -1.0f, 0.50f, 0.666666f },	//belakang
		{ -1000.0f,  1000.0f, -1000.0f,  0.0f,  0.0f, -1.0f, 0.50f, 0.333333f },
		{  1000.0f, -1000.0f, -1000.0f,  0.0f,  0.0f, -1.0f, 0.75f, 0.666666f },
		{  1000.0f,  1000.0f, -1000.0f,  0.0f,  0.0f, -1.0f, 0.75f, 0.333333f },
		{ -1000.0f,  1000.0f, -1000.0f,  0.0f,  1.0f,  0.0f, 0.75f, 0.000000f },		//atas
		{ -1000.0f,  1000.0f,  1000.0f,  0.0f,  1.0f,  0.0f, 0.75f, 0.333333f },
		{  1000.0f,  1000.0f, -1000.0f,  0.0f,  1.0f,  0.0f, 0.50f, 0.000000f },
		{  1000.0f,  1000.0f,  1000.0f,  0.0f,  1.0f,  0.0f, 0.50f, 0.333333f },
		{ -1000.0f, -1000.0f, -1000.0f,  0.0f, -1.0f,  0.0f, 0.50f, 0.666666f },	    //bawah
		{  1000.0f, -1000.0f, -1000.0f,  0.0f, -1.0f,  0.0f, 0.75f, 0.666666f },
		{ -1000.0f, -1000.0f,  1000.0f,  0.0f, -1.0f,  0.0f, 0.50f, 1.000000f },
		{  1000.0f, -1000.0f,  1000.0f,  0.0f, -1.0f,  0.0f, 0.75f, 1.000000f },
		{  1000.0f, -1000.0f, -1000.0f,  1.0f,  0.0f,  0.0f, 0.75f, 0.666666f },		//kiri
		{  1000.0f,  1000.0f, -1000.0f,  1.0f,  0.0f,  0.0f, 0.75f, 0.333333f },
		{  1000.0f, -1000.0f,  1000.0f,  1.0f,  0.0f,  0.0f, 1.00f, 0.666666f },
		{  1000.0f,  1000.0f,  1000.0f,  1.0f,  0.0f,  0.0f, 1.00f, 0.333333f },
		{ -1000.0f, -1000.0f, -1000.0f, -1.0f,  0.0f,  0.0f, 0.50f, 0.666666f },  	//kanan
		{ -1000.0f, -1000.0f,  1000.0f, -1.0f,  0.0f,  0.0f, 0.25f, 0.666666f },
		{ -1000.0f,  1000.0f, -1000.0f, -1.0f,  0.0f,  0.0f, 0.50f, 0.333333f },
		{ -1000.0f,  1000.0f,  1000.0f, -1.0f,  0.0f,  0.0f, 0.25f, 0.333333f },
	};

	// Buat vertex buffer dapat menampung 8 titik
	pDevice->CreateVertexBuffer(24 * sizeof(CUSTOMVERTEX2), 0, CUSTOMFVF2, D3DPOOL_MANAGED, &v_buffer, NULL);

	v_buffer->Lock(0, 0, &pVoid, 0);
	memcpy(pVoid, vertices, sizeof(vertices));
	v_buffer->Unlock();

	// index urutan vertex yang digambar
	short indices[] = {

		0, 1, 2, // sisi 1
		2, 1, 3,

		4, 5, 6, // sisi 2
		6, 5, 7,

		8, 9, 10, // sisi 3
		10, 9, 11,

		12, 13, 14, // sisi 4
		14, 13, 15,

		16, 17, 18, // sisi 5
		18, 17, 19,

		20, 21, 22, // sisi 6
		22, 21, 23,
	};

	// Membuat buffer pada device untuk menampung index
	pDevice->CreateIndexBuffer(36 * sizeof(short), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &i_buffer, NULL);

	// Pindahkan informasi array ke buffer device
	i_buffer->Lock(0, 0, &pVoid, 0);
	memcpy(pVoid, indices, sizeof(indices));
	i_buffer->Unlock();

	// BGM
	PlaySound(L"Resource Files/Audio/BGM_MainMenu.wav", GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC | SND_NOSTOP);

	// Loading
	Loading_Screen(pDevice);

	// Cursor Settings
	ShowCursor(TRUE);

	// Create the light
	ZeroMemory(&m_light, sizeof(D3DLIGHT9));
	m_light.Type = D3DLIGHT_POINT;
	m_light.Range = 5.0f;
	m_light.Attenuation0 = 0.0f;    // no constant inverse attenuation
	m_light.Attenuation1 = 0.125f;    // only .125 inverse attenuation
	m_light.Attenuation2 = 0.0f;    // no square inverse attenuation
	m_light.Diffuse.r = 255;
	m_light.Diffuse.g = 0;
	m_light.Diffuse.b = 0;
	m_light.Position = D3DXVECTOR3(5.0f, 0.5f, -15.0f);
	pDevice->SetLight(0, &m_light);
	pDevice->LightEnable(0, TRUE);

	// Clearing Array Vector
	MeshObject.clear();
	MeshInstance.clear();
	DistanceFrom_.clear();

	// Camera Settings
	m_camera.SetPosition(new D3DXVECTOR3(0.0f, 5.0f, -25.0f));
	m_camera.SetLookAt(new D3DXVECTOR3(3.0f, 9.0f, 27.0f));
	m_camera.Update();

	// Alice
	m_Alice.Load(pDevice, L"Resource Files/Characters/Alice/Alice.x");
	m_pAlice.SetMesh(&m_Alice);
	m_pAlice.SetXPosition(8.0f);
	m_pAlice.SetYPosition(0.0f);
	m_pAlice.SetZPosition(0.0f);
	MeshObject.push_back(&m_Alice);
	MeshInstance.push_back(&m_pAlice);

	// Lilith
	m_Lilith.Load(pDevice, L"Resource Files/Characters/Lilith/Lilith.x");
	m_pLilith.SetMesh(&m_Lilith);
	m_pLilith.SetXPosition(5.0f);
	m_pLilith.SetYPosition(0.0f);
	m_pLilith.SetZPosition(0.0f);
	// m_pLilith.RotateAbs(0.0f, 90.0f, 0.0f);
	MeshObject.push_back(&m_Lilith);
	MeshInstance.push_back(&m_pLilith);

	// Land
	m_Land.Load(pDevice, L"Resource Files/Main Menu/Land.x");
	m_pLand.SetMesh(&m_Land);
	m_pLand.ScaleAbs(5.0f, 5.0f, 5.0f);

	// FarmHouse
	m_FarmHouse.Load(pDevice, L"Resource Files/Main Menu/apart.x");
	m_pFarmHouse.SetMesh(&m_FarmHouse);
	m_pFarmHouse.SetXPosition(-20.0f);
	// m_pFarmHouse.SetYPosition(5.0f);
	m_pFarmHouse.SetYPosition(-2.5f);
	m_pFarmHouse.SetZPosition(20.0f);
	m_pFarmHouse.ScaleAbs(10.0f, 10.0f, 10.0f);
	m_pFarmHouse.RotateAbs(0.0f, D3DXToRadian(135), 0.0f);

	// Wood 1
	m_Wood1.Load(pDevice, L"Resource Files/Main Menu/Wood.x");
	m_pWood1.SetMesh(&m_Wood1);
	m_pWood1.SetXPosition(12.5f);
	m_pWood1.SetYPosition(0.5f);
	m_pWood2.SetZPosition(-5.0f);
	m_pWood1.ScaleAbs(0.5f, 0.5f, 0.5f);

	// Wood 2
	m_Wood2.Load(pDevice, L"Resource Files/Main Menu/Wood.x");
	m_pWood2.SetMesh(&m_Wood2);
	m_pWood2.SetXPosition(12.5f);
	m_pWood2.SetYPosition(0.5f);
	m_pWood2.SetZPosition(-10.0f);
	m_pWood2.ScaleAbs(0.5f, 0.5f, 0.5f);
	m_pWood2.RotateAbs(0.0f, D3DXToRadian(45.0f), 0.0f);

	// FirePlace
	m_FirePlace.Load(pDevice, L"Resource Files/Main Menu/FirePlace.x");
	m_pFirePlace.SetMesh(&m_FirePlace);
	m_pFirePlace.SetXPosition(5.0f);
	m_pFirePlace.SetYPosition(0.5f);
	m_pFirePlace.SetZPosition(-15.0f);
	m_pFirePlace.ScaleAbs(0.25f, 0.25f, 0.25f);

	D3DXCreateSprite(pDevice, &TheThruth);
	D3DXCreateTextureFromFile(pDevice, L"Resource Files/User Interface/The Truth.png", &TheThruthImg);

	D3DXCreateSprite(pDevice, &Binuzian);
	D3DXCreateTextureFromFile(pDevice, L"Resource Files/User Interface/logo binuzian.png", &BinuzianImg);

	D3DXCreateSprite(pDevice, &PlayButton);
	D3DXCreateTextureFromFile(pDevice, L"Resource Files/User Interface/Play-.png", &PlayButtonImg);
	D3DXCreateTextureFromFile(pDevice, L"Resource Files/User Interface/Play-Hover.png", &PlayButtonImgHover);

	D3DXCreateSprite(pDevice, &InfoButton);
	D3DXCreateTextureFromFile(pDevice, L"Resource Files/User Interface/Info-.png", &InfoButtonImg);
	D3DXCreateTextureFromFile(pDevice, L"Resource Files/User Interface/Info-Hover.png", &InfoButtonImgHover);

	D3DXCreateSprite(pDevice, &ExitButton);
	D3DXCreateTextureFromFile(pDevice, L"Resource Files/User Interface/Exit-.png", &ExitButtonImg);
	D3DXCreateTextureFromFile(pDevice, L"Resource Files/User Interface/Exit-Hover.png", &ExitButtonImgHover);

	MainMenuInitialized = true;
}

void CGameApp::MainMenu_Update(LPDIRECT3DDEVICE9 pDevice, float elapsedTime)
{
	// Rotate Characters
	// m_pAlice.RotateRel(0.0f, D3DXToRadian(10.0f) * elapsedTime, 0.0f);
	// m_pLilith.RotateRel(0.0f, D3DXToRadian(-10.0f) * elapsedTime, 0.0f);
}

void CGameApp::MainMenu_Render(LPDIRECT3DDEVICE9 pDevice, float elapsedTime)
{
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// Draw
	pDevice->SetStreamSource(0, v_buffer, 0, sizeof(CUSTOMVERTEX2));
	pDevice->SetFVF(CUSTOMFVF2);

	// Gunakan cara baca index
	pDevice->SetIndices(i_buffer);

	// set texture ke urutan 0
	pDevice->SetTexture(0, WorldTexture);

	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 24, 0, 12);

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// Alice
	m_pAlice.Render(pDevice);

	// Lilith
	m_pLilith.Render(pDevice);

	m_pLand.Render(pDevice);

	m_pFarmHouse.Render(pDevice);

	m_pWood1.Render(pDevice);

	m_pWood2.Render(pDevice);

	m_pFirePlace.Render(pDevice);

	TheThruth->Begin(D3DXSPRITE_ALPHABLEND);
	D3DXVECTOR3 TheThruthCenter(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 TheThruthPosition(50, 50, 0.0f);
	TheThruth->Draw(TheThruthImg, NULL, &TheThruthCenter, &TheThruthPosition, D3DCOLOR_XRGB(255, 255, 255));
	TheThruth->End();

	Binuzian->Begin(D3DXSPRITE_ALPHABLEND);
	D3DXVECTOR3 BinuzianCenter(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 BinuzianPosition(m_pFramework->GetWidth()-300, 25, 0.0f);
	Binuzian->Draw(BinuzianImg, NULL, &BinuzianCenter, &BinuzianPosition, D3DCOLOR_XRGB(255, 255, 255));
	Binuzian->End();
	
	PlayButton->Begin(D3DXSPRITE_ALPHABLEND);
	D3DXVECTOR3 PlayCenter(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 PlayPosition(m_pFramework->GetWidth() * 2 / 3 - 125, m_pFramework->GetHeight() / 3, 0.0f);
	if (m_pFramework->GetXCursor() >= m_pFramework->GetWidth() * 3 / 4 - 200 &&
		m_pFramework->GetXCursor() <= m_pFramework->GetWidth() * 3 / 4 + 150 &&
		m_pFramework->GetYCursor() >= m_pFramework->GetHeight() / 3 &&
		m_pFramework->GetYCursor() <= m_pFramework->GetHeight() / 3 + 125)
	{
		PlayButton->Draw(PlayButtonImgHover, NULL, &PlayCenter, &PlayPosition, D3DCOLOR_XRGB(255, 255, 255));
	}
	else
	{
		PlayButton->Draw(PlayButtonImg, NULL, &PlayCenter, &PlayPosition, D3DCOLOR_XRGB(255, 255, 255));
	}
	PlayButton->End();

	InfoButton->Begin(D3DXSPRITE_ALPHABLEND);
	D3DXVECTOR3 InfoCenter(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 InfoPosition(m_pFramework->GetWidth() * 2 / 3 - 125, m_pFramework->GetHeight() / 3 + 200, 0.0f);
	if (m_pFramework->GetXCursor() >= m_pFramework->GetWidth() * 3 / 4 - 250 &&
		m_pFramework->GetXCursor() <= m_pFramework->GetWidth() * 3 / 4 + 200 &&
		m_pFramework->GetYCursor() >= m_pFramework->GetHeight() / 3 + 200 &&
		m_pFramework->GetYCursor() <= m_pFramework->GetHeight() / 3 + 200 + 125)
	{
		InfoButton->Draw(InfoButtonImgHover, NULL, &InfoCenter, &InfoPosition, D3DCOLOR_XRGB(255, 255, 255));
	}
	else
	{
		InfoButton->Draw(InfoButtonImg, NULL, &InfoCenter, &InfoPosition, D3DCOLOR_XRGB(255, 255, 255));
	}
	InfoButton->End();

	ExitButton->Begin(D3DXSPRITE_ALPHABLEND);
	D3DXVECTOR3 ExitCenter(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 ExitPosition(m_pFramework->GetWidth() * 2 / 3 - 125, m_pFramework->GetHeight() / 3 + 400, 0.0f);
	if (m_pFramework->GetXCursor() >= m_pFramework->GetWidth() * 3 / 4 - 150 &&
		m_pFramework->GetXCursor() <= m_pFramework->GetWidth() * 3 / 4 + 125 &&
		m_pFramework->GetYCursor() >= m_pFramework->GetHeight() / 3 + 400 &&
		m_pFramework->GetYCursor() <= m_pFramework->GetHeight() / 3 + 400 + 125)
	{
		ExitButton->Draw(ExitButtonImgHover, NULL, &ExitCenter, &ExitPosition, D3DCOLOR_XRGB(255, 255, 255));
	}
	else
	{
		ExitButton->Draw(ExitButtonImg, NULL, &ExitCenter, &ExitPosition, D3DCOLOR_XRGB(255, 255, 255));
	}
	ExitButton->End();
}

void CGameApp::MainMenu_ProcessInput(long xDelta, long yDelta, long zDelta, BOOL* pMouseButtons, BOOL* pPressedKeys, float elapsedTime)
{
	if (pMouseButtons[0])
	{
		if (m_pFramework->GetXCursor() >= m_pFramework->GetWidth() * 3 / 4 - 200 &&
			m_pFramework->GetXCursor() <= m_pFramework->GetWidth() * 3 / 4 + 150 &&
			m_pFramework->GetYCursor() >= m_pFramework->GetHeight() / 3 &&
			m_pFramework->GetYCursor() <= m_pFramework->GetHeight() / 3 + 125)
		{
			GameStatus = 2;
		}
		else if (m_pFramework->GetXCursor() >= m_pFramework->GetWidth() * 3 / 4 - 250 &&
			m_pFramework->GetXCursor() <= m_pFramework->GetWidth() * 3 / 4 + 200 &&
			m_pFramework->GetYCursor() >= m_pFramework->GetHeight() / 3 + 200 &&
			m_pFramework->GetYCursor() <= m_pFramework->GetHeight() / 3 + 200 + 125)
		{
			GameStatus = 3;
		}
		else if (m_pFramework->GetXCursor() >= m_pFramework->GetWidth() * 3 / 4 - 150 &&
			m_pFramework->GetXCursor() <= m_pFramework->GetWidth() * 3 / 4 + 125 &&
			m_pFramework->GetYCursor() >= m_pFramework->GetHeight() / 3 + 400 &&
			m_pFramework->GetYCursor() <= m_pFramework->GetHeight() / 3 + 400 + 125)
		{
			PostQuitMessage(0);
		}
	}
}

void CGameApp::MainMenu_Release()
{
	i_buffer->Release();
	WorldTexture->Release();
	v_buffer->Release();

	m_Land.Release();
	m_pLand.Release();

	m_FarmHouse.Release();
	m_pFarmHouse.Release();

	m_Wood1.Release();
	m_pWood1.Release();

	m_Wood2.Release();
	m_pWood2.Release();

	m_FirePlace.Release();
	m_pFirePlace.Release();

	Binuzian->Release();
	BinuzianImg->Release();

	TheThruth->Release();
	TheThruthImg->Release();

	PlayButtonImg->Release();
	PlayButtonImgHover->Release();

	InfoButtonImg->Release();
	InfoButtonImgHover->Release();

	ExitButtonImg->Release();
	ExitButtonImgHover->Release();

	MainMenuInitialized = false;

	// Cursor Settings
	ShowCursor(FALSE);
}

/**/

void CGameApp::InGame_Init(LPDIRECT3DDEVICE9 pDevice)
{
	PlaySound(NULL, 0, 0);

	srand(time(0));
	LokasiSpawnHP = rand() % 3;
	if (LokasiSpawnHP <= 0)
	{
		LokasiSpawnHP = 1;
	}
	else if(LokasiSpawnHP >= 3)
	{
		LokasiSpawnHP = 2;
	}
	HP_Ketemu = false;

	// Loading
	Loading_Screen(pDevice);

	// Cursor Settings
	ShowCursor(FALSE);

	// Create the light
	ZeroMemory(&m_light, sizeof(D3DLIGHT9));
	m_light.Type = D3DLIGHT_POINT;
	m_light.Range = 50.0f;
	m_light.Attenuation0 = 0.0f;    // no constant inverse attenuation
	m_light.Attenuation1 = 0.125f;    // only .125 inverse attenuation
	m_light.Attenuation2 = 0.0f;    // no square inverse attenuation
	m_light.Diffuse.r = 1.0f;
	m_light.Diffuse.g = 1.0f;
	m_light.Diffuse.b = 1.0f;
	m_light.Position = D3DXVECTOR3(-12.75f, 4.0f, -6.75f);
	pDevice->SetLight(0, &m_light);
	pDevice->LightEnable(0, TRUE);

	// Clearing Array Vector
	MeshObject.clear();
	MeshInstance.clear();
	DistanceFrom_.clear();

	// Crosshair
	D3DXCreateSprite(pDevice, &Crosshair);
	D3DXCreateTextureFromFile(pDevice, L"Resource Files/User Interface/Crosshair.png", &CrosshairImg);

	// Floor
	m_Floor.Load(pDevice, L"Resource Files/House/Floor.x");
	m_pFloor.SetMesh(&m_Floor);
	m_pFloor.ScaleAbs(2.0f, 2.0f, 2.0f);
	
	// Roof
	m_Roof.Load(pDevice, L"Resource Files/House/Roof.x");
	m_pRoof.SetMesh(&m_Roof);
	m_pRoof.ScaleAbs(2.0f, 2.0f, 2.0f);
	m_pRoof.SetXPosition(-0.125f);
	m_pRoof.SetYPosition(2.3f);
	m_pRoof.SetZPosition(-0.125f);
	
	// Wall
	m_Wall.Load(pDevice, L"Resource Files/House/lorong.x");
	m_pWall.SetMesh(&m_Wall);
	m_pWall.ScaleAbs(2.0f, 2.5f, 2.0f);
	
	// Table
	m_Table.Load(pDevice, L"Resource Files/House/Table.x");
	m_pTable.SetMesh(&m_Table);
	m_pTable.ScaleAbs(1.5f, 1.5f, 1.5f);
	m_pTable.SetXPosition(-12.0f);
	m_pTable.SetYPosition(1.5f);
	m_pTable.SetZPosition(-5.0f);
	MeshObject.push_back(&m_Table);
	MeshInstance.push_back(&m_pTable);
	
	// Chair
	m_Chair.Load(pDevice, L"Resource Files/House/Chair.x");
	m_pChair.SetMesh(&m_Chair);
	m_pChair.ScaleAbs(1.5f, 1.5f, 1.5f);
	m_pChair.SetXPosition(-10.0f);
	m_pChair.SetYPosition(1.125f);
	m_pChair.SetZPosition(-5.0f);
	MeshObject.push_back(&m_Chair);
	MeshInstance.push_back(&m_pChair);
	
	// BookShelf 1
	m_Bookshelf1.Load(pDevice, L"Resource Files/House/Bookshelf1.x");
	m_pBookshelf1.SetMesh(&m_Bookshelf1);
	m_pBookshelf1.ScaleAbs(2.0f, 2.0f, 2.0f);
	m_pBookshelf1.SetXPosition(-13.25f);
	m_pBookshelf1.SetYPosition(4.0f);
	m_pBookshelf1.SetZPosition(11.5f);
	MeshObject.push_back(&m_Bookshelf1);
	MeshInstance.push_back(&m_pBookshelf1);
	
	// BookShelf 2
	m_Bookshelf2.Load(pDevice, L"Resource Files/House/Bookshelf2.x");
	m_pBookshelf2.SetMesh(&m_Bookshelf2);
	m_pBookshelf2.ScaleAbs(2.0f, 2.0f, 2.0f);
	m_pBookshelf2.SetXPosition(-13.25f);
	m_pBookshelf2.SetYPosition(4.0f);
	m_pBookshelf2.SetZPosition(6.0f);
	MeshObject.push_back(&m_Bookshelf2);
	MeshInstance.push_back(&m_pBookshelf2);
	
	// Books
	m_Books.Load(pDevice, L"Resource Files/House/Books.x");
	m_pBooks.SetMesh(&m_Books);
	m_pBooks.ScaleAbs(2.0f, 2.0f, 2.0f);
	m_pBooks.SetXPosition(-13.25f);
	m_pBooks.SetYPosition(3.75f);
	m_pBooks.SetZPosition(8.5f);
	MeshObject.push_back(&m_Books);
	MeshInstance.push_back(&m_pBooks);
	
	// Photo Frame 1
	m_PhotoFrame1.Load(pDevice, L"Resource Files/House/PhotoFrame1.x");
	m_pPhotoFrame1.SetMesh(&m_PhotoFrame1);
	m_pPhotoFrame1.ScaleAbs(2.0f, 2.0f, 2.5f);
	m_pPhotoFrame1.SetXPosition(-14.0f);
	m_pPhotoFrame1.SetYPosition(7.0f);
	m_pPhotoFrame1.SetZPosition(0.0f);
	MeshObject.push_back(&m_PhotoFrame1);
	MeshInstance.push_back(&m_pPhotoFrame1);
	
	// Fan
	m_Fan.Load(pDevice, L"Resource Files/House/Fan.x");
	m_pFan.SetMesh(&m_Fan);
	m_pFan.ScaleAbs(1.5f, 1.5f, 1.5f);
	m_pFan.SetYPosition(10.0f);
	
	// TV Table Ground
	m_TVTable_Ground.Load(pDevice, L"Resource Files/House/TV-Table_Ground.x");
	m_pTVTable_Ground.SetMesh(&m_TVTable_Ground);
	m_pTVTable_Ground.ScaleAbs(2.5f, 2.5f, 2.5f);
	m_pTVTable_Ground.SetYPosition(1.25f);
	m_pTVTable_Ground.SetZPosition(12.0f);
	MeshObject.push_back(&m_TVTable_Ground);
	MeshInstance.push_back(&m_pTVTable_Ground);
	
	// TV Table Top
	m_TVTable_Top.Load(pDevice, L"Resource Files/House/TV-Table_Top.x");
	m_pTVTable_Top.SetMesh(&m_TVTable_Top);
	m_pTVTable_Top.ScaleAbs(2.5f, 2.5f, 2.5f);
	m_pTVTable_Top.SetYPosition(2.5f);
	m_pTVTable_Top.SetZPosition(12.0f);
	MeshObject.push_back(&m_TVTable_Top);
	MeshInstance.push_back(&m_pTVTable_Top);
	
	// TV
	m_TV.Load(pDevice, L"Resource Files/House/TV.x");
	m_pTV.SetMesh(&m_TV);
	m_pTV.SetYPosition(5.0f);
	m_pTV.SetZPosition(12.0f);
	MeshObject.push_back(&m_TV);
	MeshInstance.push_back(&m_pTV);
	
	// Content TV
	m_ContentTV.Load(pDevice, L"Resource Files/House/TV-Content.x");
	m_pContentTV.SetMesh(&m_ContentTV);
	m_pContentTV.SetYPosition(5.575f);
	m_pContentTV.SetZPosition(11.8f);
	MeshObject.push_back(&m_ContentTV);
	MeshInstance.push_back(&m_pContentTV);
	
	// Bed Frame
	m_BedFrame.Load(pDevice, L"Resource Files/House/BedFrame.x");
	m_pBedFrame.SetMesh(&m_BedFrame);
	m_pBedFrame.SetXPosition(10.5f);
	m_pBedFrame.SetYPosition(1.5f);
	m_pBedFrame.SetZPosition(-10.0f);
	MeshObject.push_back(&m_BedFrame);
	MeshInstance.push_back(&m_pBedFrame);
	
	// Bed
	m_Bed.Load(pDevice, L"Resource Files/House/Bed.x");
	m_pBed.SetMesh(&m_Bed);
	m_pBed.SetXPosition(10.5f);
	m_pBed.SetYPosition(1.5f);
	m_pBed.SetZPosition(-9.5f);
	MeshObject.push_back(&m_Bed);
	MeshInstance.push_back(&m_pBed);
	
	// Pillow
	m_Pillow.Load(pDevice, L"Resource Files/House/Pillow.x");
	m_pPillow.SetMesh(&m_Pillow);
	m_pPillow.SetXPosition(10.5f);
	m_pPillow.SetYPosition(2.5f);
	m_pPillow.SetZPosition(-12.0f);
	MeshObject.push_back(&m_Pillow);
	MeshInstance.push_back(&m_pPillow);
	
	// Table Lamp
	m_TableLamp.Load(pDevice, L"Resource Files/House/TableLamp.x");
	m_pTableLamp.SetMesh(&m_TableLamp);
	m_pTableLamp.ScaleAbs(5.0f, 5.0f, 5.0f);
	m_pTableLamp.SetXPosition(-12.75f);
	m_pTableLamp.SetYPosition(3.5f);
	m_pTableLamp.SetZPosition(-6.75f);
	MeshObject.push_back(&m_TableLamp);
	MeshInstance.push_back(&m_pTableLamp);
	
	// Table Book 1
	m_TableBook.Load(pDevice, L"Resource Files/House/TableBook.x");
	m_pTableBook.SetMesh(&m_TableBook);
	m_pTableBook.ScaleAbs(3.0f, 3.0f, 3.0f);
	m_pTableBook.SetXPosition(-12.0f);
	m_pTableBook.SetYPosition(2.75f);
	m_pTableBook.SetZPosition(-4.0f);
	MeshObject.push_back(&m_TableBook);
	MeshInstance.push_back(&m_pTableBook);
	
	// KODINGAN BARU!!!  --------------------------------------------------------------------------------------------------------
	// Iron Shelf
	m_IronShelf.Load(pDevice, L"Resource Files/House/IronShelf.x");
	m_pIronShelf.SetMesh(&m_IronShelf);
	m_pIronShelf.ScaleAbs(2.5f, 2.5f, 2.5f);
	m_pIronShelf.SetXPosition(-51.5f);
	m_pIronShelf.SetYPosition(4.75f);
	m_pIronShelf.SetZPosition(-39.2f);
	MeshObject.push_back(&m_IronShelf);
	MeshInstance.push_back(&m_pIronShelf);
	
	// Broom
	m_Broom.Load(pDevice, L"Resource Files/House/Broom.x");
	m_pBroom.SetMesh(&m_Broom);
	m_pBroom.ScaleAbs(5.0f, 5.0f, 5.0f);
	m_pBroom.SetXPosition(-44.5f);
	m_pBroom.SetYPosition(0.9f);
	m_pBroom.SetZPosition(-45.5f);
	MeshObject.push_back(&m_Broom);
	MeshInstance.push_back(&m_pBroom);
	
	// Vase 1
	m_Vase1.Load(pDevice, L"Resource Files/House/Vase1.x");
	m_pVase1.SetMesh(&m_Vase1);
	m_pVase1.ScaleAbs(3.0f, 3.0f, 3.0f);
	m_pVase1.SetXPosition(26.0f);
	m_pVase1.SetYPosition(-0.7f);
	m_pVase1.SetZPosition(8.9f);
	MeshObject.push_back(&m_Vase1);
	MeshInstance.push_back(&m_pVase1);
	
	// Vase 2
	m_Vase2.Load(pDevice, L"Resource Files/House/Vase2.x");
	m_pVase2.SetMesh(&m_Vase2);
	m_pVase2.ScaleAbs(3.0f, 3.0f, 3.0f);
	m_pVase2.SetXPosition(-28.0f);
	m_pVase2.SetYPosition(-0.7f);
	m_pVase2.SetZPosition(8.9f);
	MeshObject.push_back(&m_Vase2);
	MeshInstance.push_back(&m_pVase2);
	
	// Janitor Door
	m_JanitorDoor.Load(pDevice, L"Resource Files/House/pintujanitor.x");
	m_pJanitorDoor.SetMesh(&m_JanitorDoor);
	m_pJanitorDoor.ScaleAbs(2.0f, 2.8f, 2.8f);
	m_pJanitorDoor.SetXPosition(0.0f);
	m_pJanitorDoor.SetYPosition(-0.7f);
	m_pJanitorDoor.SetZPosition(11.8f);
	MeshObject.push_back(&m_JanitorDoor);
	MeshInstance.push_back(&m_pJanitorDoor);
	 
	// Janitor Door 2
	m_JanitorDoor2.Load(pDevice, L"Resource Files/House/pintujanitor.x");
	m_pJanitorDoor2.SetMesh(&m_JanitorDoor2);
	m_pJanitorDoor2.ScaleAbs(2.0f, 3.0f, 2.8f);
	m_pJanitorDoor2.SetXPosition(42.2f);
	m_pJanitorDoor2.SetYPosition(-0.7f);
	m_pJanitorDoor2.SetZPosition(27.85f);
	MeshObject.push_back(&m_JanitorDoor2);
	MeshInstance.push_back(&m_pJanitorDoor2);
	
	// Pintu Tutup 1
	m_PintuTutup1.Load(pDevice, L"Resource Files/House/pintututup.x");
	m_pPintuTutup1.SetMesh(&m_PintuTutup1);
	m_pPintuTutup1.ScaleAbs(2.0f, 3.0f, 2.8f);
	m_pPintuTutup1.SetXPosition(39.0f);
	m_pPintuTutup1.SetYPosition(-0.7f);
	m_pPintuTutup1.SetZPosition(11.9f);
	MeshObject.push_back(&m_PintuTutup1);
	MeshInstance.push_back(&m_pPintuTutup1);
	
	// Pintu Tutup 2
	m_PintuTutup2.Load(pDevice, L"Resource Files/House/pintututup.x");
	m_pPintuTutup2.SetMesh(&m_PintuTutup2);
	m_pPintuTutup2.ScaleAbs(2.0f, 3.0f, 2.8f);
	m_pPintuTutup2.SetXPosition(85.0f);
	m_pPintuTutup2.SetYPosition(-0.7f);
	m_pPintuTutup2.SetZPosition(11.9f);
	MeshObject.push_back(&m_PintuTutup2);
	MeshInstance.push_back(&m_pPintuTutup2);
	
	// Pintu Tutup 3
	m_PintuTutup3.Load(pDevice, L"Resource Files/House/pintututup.x");
	m_pPintuTutup3.SetMesh(&m_PintuTutup3);
	m_pPintuTutup3.ScaleAbs(2.0f, 3.0f, 2.8f);
	m_pPintuTutup3.SetXPosition(84.9f);
	m_pPintuTutup3.SetYPosition(-0.7f);
	m_pPintuTutup3.SetZPosition(27.85f);
	MeshObject.push_back(&m_PintuTutup3);
	MeshInstance.push_back(&m_pPintuTutup3);
	
	// Kardus 1
	m_Kardus1.Load(pDevice, L"Resource Files/House/kardus.x");
	m_pKardus1.SetMesh(&m_Kardus1);
	m_pKardus1.ScaleAbs(2.0f, 2.0f, 2.0f);
	m_pKardus1.SetXPosition(42.0f); // ke belakang ++ | ke depan --
	m_pKardus1.SetYPosition(2.25f);
	m_pKardus1.SetZPosition(-27.0f); // ke kanan ++ | ke kiri --
	MeshObject.push_back(&m_Kardus1);
	MeshInstance.push_back(&m_pKardus1);
	
	// Kardus 2
	m_Kardus2.Load(pDevice, L"Resource Files/House/kardus2.x");
	m_pKardus2.SetMesh(&m_Kardus2);
	m_pKardus2.ScaleAbs(2.0f, 2.0f, 2.0f);
	m_pKardus2.SetXPosition(31.0f);
	m_pKardus2.SetYPosition(2.0f);
	m_pKardus2.SetZPosition(-17.0f);
	MeshObject.push_back(&m_Kardus2);
	MeshInstance.push_back(&m_pKardus2);
	
	// Box Gajelas
	m_BoxGaJelas.Load(pDevice, L"Resource Files/House/kardus.x");
	m_pBoxGaJelas.SetMesh(&m_BoxGaJelas);
	m_pBoxGaJelas.ScaleAbs(3.0f, 3.0f, 3.0f);
	m_pBoxGaJelas.SetXPosition(-18.0f);
	m_pBoxGaJelas.SetYPosition(2.5f);
	m_pBoxGaJelas.SetZPosition(-18.0f);
	MeshObject.push_back(&m_BoxGaJelas);
	MeshInstance.push_back(&m_pBoxGaJelas);
	
	// Fire Hose
	m_FireHose.Load(pDevice, L"Resource Files/House/firehose.x");
	m_pFireHose.SetMesh(&m_FireHose);
	m_pFireHose.ScaleAbs(2.5f, 2.5f, 2.5f);
	m_pFireHose.SetXPosition(46.8f); // ke belakang ++ | ke depan --
	m_pFireHose.SetYPosition(3.5f);
	m_pFireHose.SetZPosition(-33.5f); // ke kiri ++ | ke kanan --
	//m_pFireHose.RotateAbs(0.0f, 0.2f, 0.0f);
	MeshObject.push_back(&m_FireHose);
	MeshInstance.push_back(&m_pFireHose);
	
	// Karpet
	m_Karpet.Load(pDevice, L"Resource Files/House/karpet.x");
	m_pKarpet.SetMesh(&m_Karpet);
	m_pKarpet.ScaleAbs(2.5f, 2.5f, 2.5f);
	m_pKarpet.SetXPosition(0.0f); // ke belakang ++ | ke depan --
	m_pKarpet.SetYPosition(0.5f);
	m_pKarpet.SetZPosition(0.0f); // ke kiri ++ | ke kanan --
	
	// Lemari Baju
	m_LemariBaju.Load(pDevice, L"Resource Files/House/lemaribaju.x");
	m_pLemariBaju.SetMesh(&m_LemariBaju);
	m_pLemariBaju.ScaleAbs(4.5f, 4.5f, 4.5f);
	m_pLemariBaju.SetXPosition(12.2f); // ke belakang ++ | ke depan --
	m_pLemariBaju.SetYPosition(0.35f);
	m_pLemariBaju.SetZPosition(10.0f); // ke kiri ++ | ke kanan --
	MeshObject.push_back(&m_LemariBaju);
	MeshInstance.push_back(&m_pLemariBaju);
	
	// Sofa
	m_Sofa.Load(pDevice, L"Resource Files/House/Sofa.x");
	m_pSofa.SetMesh(&m_Sofa);
	m_pSofa.ScaleAbs(3.0f, 3.0f, 3.0f);
	m_pSofa.SetYPosition(1.75f);
	m_pSofa.SetZPosition(-9.5f);
	m_pSofa.RotateAbs(0.0f, D3DXToRadian(180.0f), 0.0f);
	MeshObject.push_back(&m_Sofa);
	MeshInstance.push_back(&m_pSofa);
	 
	// HP
	m_HP.Load(pDevice, L"Resource Files/House/Hape.x");
	m_pHP.SetMesh(&m_HP);
	m_pHP.ScaleAbs(0.2f, 0.2f, 0.2f);
	m_pHP.SetXPosition(-2.0f);
	m_pHP.SetYPosition(0.75f);
	m_pHP.SetZPosition(12.0f);
	MeshObject.push_back(&m_HP);
	MeshInstance.push_back(&m_pHP);

	// HP2
	m_HP2.Load(pDevice, L"Resource Files/House/Hape.x");
	m_pHP2.SetMesh(&m_HP2);
	m_pHP2.ScaleAbs(0.2f, 0.2f, 0.2f);
	m_pHP2.SetXPosition(-51.5f);
	m_pHP2.SetYPosition(0.25f);
	m_pHP2.SetZPosition(-35.0f);
	MeshObject.push_back(&m_HP2);
	MeshInstance.push_back(&m_pHP2);

	// BGM
	PlaySound(L"Resource Files/Audio/BGM_InGame.wav", GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC | SND_NOSTOP);

	D3DXCreateSprite(pDevice, &ResumeButton);
	D3DXCreateTextureFromFile(pDevice, L"Resource Files/User Interface/continue.png", &ResumeButtonImg);
	D3DXCreateTextureFromFile(pDevice, L"Resource Files/User Interface/continuehover.png", &ResumeButtonImgHover);

	D3DXCreateSprite(pDevice, &MainMenuButton);
	D3DXCreateTextureFromFile(pDevice, L"Resource Files/User Interface/backto.png", &MainMenuButtonImg);
	D3DXCreateTextureFromFile(pDevice, L"Resource Files/User Interface/backtohover.png", &MainMenuButtonImgHover);

	for (int i = 0; i<MeshInstance.size(); i++)
	{
		DistanceFrom_.push_back(hypot(hypot(m_camera.GetPosition()->x - MeshInstance[i]->GetXPosition(), 0 - MeshInstance[i]->GetYPosition()), m_camera.GetPosition()->z - MeshInstance[i]->GetZPosition()));
	}

	// Mouse Camera Movement
	MoveWithAutoMouse = true;

	// Camera Settings
	m_camera.SetPosition(new D3DXVECTOR3(52.0f, 4.0f, -39.0f));
	// m_camera.SetLookAt(new D3DXVECTOR3(m_pHP.GetXPosition(), m_pHP.GetYPosition(), m_pHP.GetZPosition()));
	m_camera.SetLookAt(new D3DXVECTOR3(52.0f, 4.0f, -30.0f));
	m_camera.Update();

	// Stopwatch
	stopwatch.Hours = 0;
	stopwatch.Minutes = 0;
	stopwatch.Seconds = 0;

	InGameEscapeIsPressed = false;
	InGameInitialized = true;
}

void CGameApp::InGame_Update(LPDIRECT3DDEVICE9 pDevice, float elapsedTime)
{
	// Rotate Fan
	m_pFan.RotateRel(0.0f, D3DXToRadian(1000.0f) * elapsedTime, 0.0f);

	// Update Stopwatch
	if (stopwatch.Seconds > 59)
	{
		stopwatch.Minutes++;
		stopwatch.Seconds -= 59;
		if (stopwatch.Minutes > 59)
		{
			stopwatch.Hours++;
			stopwatch.Minutes -= 59;
			if (stopwatch.Hours > 23)
			{
				stopwatch.Hours -= 23;
			}
		}
	}
	if (LokasiSpawnHP == 1)
	{
		DistanceFromHP = hypot(hypot(m_camera.GetPosition()->x - m_pHP.GetXPosition(), 
			0 - m_pHP.GetYPosition()),
			m_camera.GetPosition()->z - m_pHP.GetZPosition());
	}
	else if (LokasiSpawnHP == 2)
	{
		DistanceFromHP = hypot(hypot(m_camera.GetPosition()->x - m_pHP2.GetXPosition(),
			0 - m_pHP2.GetYPosition()),
			m_camera.GetPosition()->z - m_pHP2.GetZPosition());
	}

}

void CGameApp::InGame_Render(LPDIRECT3DDEVICE9 pDevice, float elapsedTime)
{
	// Stopwatch
	wstringstream hr, mn, sc;
	hr << stopwatch.Hours;
	mn << stopwatch.Minutes;
	sc << stopwatch.Seconds;

	std::wstring A(hr.str().c_str());
	std::wstring B(mn.str().c_str());
	std::wstring C(sc.str().c_str());
	std::wstring Hasil = L"Time Elapsed\n" + B + L":" + C;
	Test = Hasil.c_str();

	// if (!HP_Ketemu)
	// {
	// 	m_font.Print(Test, 0, 0, D3DCOLOR_XRGB(0, 200, 0));
	// }

	// Crosshair
	Crosshair->Begin(D3DXSPRITE_ALPHABLEND);
	D3DXVECTOR3 CrosshairCenter(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 CrosshairPosition(m_pFramework->GetWidth()/2 - 25, m_pFramework->GetHeight()/2 - 25, 0.0f);
	Crosshair->Draw(CrosshairImg, NULL, &CrosshairCenter, &CrosshairPosition, D3DCOLOR_XRGB(255, 255, 255));
	Crosshair->End();

	// Floor
	m_pFloor.Render(pDevice);

	// Roof
	m_pRoof.Render(pDevice);

	// Wall
	m_pWall.Render(pDevice);

	// Table
	m_pTable.Render(pDevice);

	// Chair
	m_pChair.Render(pDevice);

	// Bookshelf 1
	m_pBookshelf1.Render(pDevice);

	// Bookshelf 2
	m_pBookshelf2.Render(pDevice);

	// Books
	m_pBooks.Render(pDevice);

	// Photo Frame 1
	m_pPhotoFrame1.Render(pDevice);

	// Fan
	m_pFan.Render(pDevice);

	// TV Table Top
	m_pTVTable_Top.Render(pDevice);

	// TV Table Ground
	m_pTVTable_Ground.Render(pDevice);

	// TV
	m_pTV.Render(pDevice);

	// TV Content
	m_pContentTV.Render(pDevice);

	// Bed Frame
	m_pBedFrame.Render(pDevice);

	// Bed
	m_pBed.Render(pDevice);

	// Pillow
	m_pPillow.Render(pDevice);

	// Table Lamp
	m_pTableLamp.Render(pDevice);

	// Table Book 1
	m_pTableBook.Render(pDevice);

	//KODINGAN BARUUUUUUUUUUU!! ------------------------------------------------------------------------------------------------
	// Iron Shelf
	m_pIronShelf.Render(pDevice);

	// Broom
	m_pBroom.Render(pDevice);

	// Vase 1
	m_pVase1.Render(pDevice);

	// Vase 2
	m_pVase2.Render(pDevice);

	// Janitor Door
	m_pJanitorDoor.Render(pDevice);
	
	// Janitor Door 2
	m_pJanitorDoor2.Render(pDevice);
	
	// Pintu Tutup 1
	m_pPintuTutup1.Render(pDevice);
	
	// Pintu Tutup 2
	m_pPintuTutup2.Render(pDevice);
	
	// Pintu Tutup 3
	m_pPintuTutup3.Render(pDevice);
	
	// Kardus 1
	m_pKardus1.Render(pDevice);
	
	// Kardus 2
	m_pKardus2.Render(pDevice);

	// Box Ga Jelas
	m_pBoxGaJelas.Render(pDevice);

	// Fire Hose
	m_pFireHose.Render(pDevice);

	// Karpet
	m_pKarpet.Render(pDevice);

	// Lemari Baju
	m_pLemariBaju.Render(pDevice);

	// Sofa
	m_pSofa.Render(pDevice);

	// HP
	if (LokasiSpawnHP == 1) m_pHP.Render(pDevice);
	else if (LokasiSpawnHP == 2) m_pHP2.Render(pDevice);

	if (HP_Ketemu)
	{
		GameStatus = 1;
	}
	else if (InGameEscapeIsPressed)
	{
		GamePaused->Begin(NULL);
		D3DXVECTOR3 GamePausedPosition(0.0f, 0.0f, 0.0f);
		GamePaused->Draw(GamePausedImg, NULL, NULL, &GamePausedPosition, D3DCOLOR_XRGB(255, 255, 255));
		GamePaused->End();

		ResumeButton->Begin(D3DXSPRITE_ALPHABLEND);
		D3DXVECTOR3 ResumeButtonCenter(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 ResumeButtonPosition(m_pFramework->GetWidth() / 2 - 250, m_pFramework->GetHeight() / 2 - 50, 0.0f);
		if (m_pFramework->GetXCursor() >= m_pFramework->GetWidth() / 2 - 220 &&
			m_pFramework->GetXCursor() <= m_pFramework->GetWidth() / 2 + 220 &&
			m_pFramework->GetYCursor() >= m_pFramework->GetHeight() / 2 - 50 &&
			m_pFramework->GetYCursor() <= m_pFramework->GetHeight() / 2 + 75)
		{
			ResumeButton->Draw(ResumeButtonImgHover, NULL, &ResumeButtonCenter, &ResumeButtonPosition, D3DCOLOR_XRGB(255, 255, 255));
		}
		else
		{
			ResumeButton->Draw(ResumeButtonImg, NULL, &ResumeButtonCenter, &ResumeButtonPosition, D3DCOLOR_XRGB(255, 255, 255));
		}
		ResumeButton->End();

		MainMenuButton->Begin(D3DXSPRITE_ALPHABLEND);
		D3DXVECTOR3 MainMenuButtonCenter(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 MainMenuButtonPosition(m_pFramework->GetWidth() / 2 - 250, m_pFramework->GetHeight() / 2 + 100, 0.0f);
		if (m_pFramework->GetXCursor() >= m_pFramework->GetWidth() / 2 - 240 &&
			m_pFramework->GetXCursor() <= m_pFramework->GetWidth() / 2 + 240 &&
			m_pFramework->GetYCursor() >= m_pFramework->GetHeight() / 2 - 50 + 150 &&
			m_pFramework->GetYCursor() <= m_pFramework->GetHeight() / 2 + 75 + 150)
		{
			MainMenuButton->Draw(MainMenuButtonImgHover, NULL, &MainMenuButtonCenter, &MainMenuButtonPosition, D3DCOLOR_XRGB(255, 255, 255));
		}
		else
		{
			MainMenuButton->Draw(MainMenuButtonImg, NULL, &MainMenuButtonCenter, &MainMenuButtonPosition, D3DCOLOR_XRGB(255, 255, 255));
		}
		MainMenuButton->End();
	}

	// Update Stopwatch
	if (!InGameEscapeIsPressed) stopwatch.Seconds += elapsedTime;
}

void CGameApp::InGame_ProcessInput(long xDelta, long yDelta, long zDelta, BOOL* pMouseButtons, BOOL* pPressedKeys, float elapsedTime)
{
	// Camera Movement Controller (Movement Speed)
	float cameraSpeed = 9.0f;
	if (pMouseButtons[0] && !MoveWithAutoMouse && !InGameEscapeIsPressed)
	{
		/*
			http://howthingsfly.si.edu/flight-dynamics/roll-pitch-and-yaw
			Roll = Rotation around the front-to-back axis (Z Line)
			Pitch = Rotation around the side-to-side axis (X Line)
			Yaw = Rotation around the vertical axis (Y Line)
		*/
		m_camera.Yaw(xDelta * elapsedTime);
		m_camera.Pitch(yDelta * elapsedTime);
	}
	else if (MoveWithAutoMouse && !InGameEscapeIsPressed)
	{
		m_camera.Yaw(xDelta / 4 * elapsedTime);     // Mouse Sensivity
		m_camera.Pitch(yDelta / 4 * elapsedTime);
	}
	if (!CameraCollision && !InGameEscapeIsPressed)
	{
		if (pPressedKeys[DIK_W])
		{
			m_camera.MoveForward(cameraSpeed * elapsedTime);
		}
		if (pPressedKeys[DIK_A])
		{
			m_camera.Strafe(-cameraSpeed * elapsedTime);
		}
		if (pPressedKeys[DIK_S])
		{
			m_camera.MoveForward(-cameraSpeed * elapsedTime);
		}
		if (pPressedKeys[DIK_D])
		{
			m_camera.Strafe(cameraSpeed * elapsedTime);
		}
	}
	if (pPressedKeys[DIK_SPACE] && !InGameEscapeIsPressed)
	{
		m_pFramework->LockKey(DIK_SPACE);
		if (!CameraJump)
		{
			CameraJump = true;
		}
	}
	if (pPressedKeys[DIK_ESCAPE])
	{
		m_pFramework->LockKey(DIK_ESCAPE);
		if (!InGameEscapeIsPressed)
		{
			InGameEscapeIsPressed = true;
			ShowCursor(TRUE);
		}
		else
		{
			InGameEscapeIsPressed = false;
			ShowCursor(FALSE);
		}
	}
	if (pMouseButtons[0] && !HP_Ketemu && DistanceFromHP <= 5.0f)
	{
		// Sprite Game Kelar
		HP_Ketemu = true;
	}
	if (pMouseButtons[0])
	{
		if (m_pFramework->GetXCursor() >= m_pFramework->GetWidth() / 2 - 220 &&
			m_pFramework->GetXCursor() <= m_pFramework->GetWidth() / 2 + 220 &&
			m_pFramework->GetYCursor() >= m_pFramework->GetHeight() / 2 - 50 &&
			m_pFramework->GetYCursor() <= m_pFramework->GetHeight() / 2 + 75)
		{
			if (InGameEscapeIsPressed)
			{
				InGameEscapeIsPressed = false;
				ShowCursor(FALSE);
			}
		}
		else if (m_pFramework->GetXCursor() >= m_pFramework->GetWidth() / 2 - 240 &&
			m_pFramework->GetXCursor() <= m_pFramework->GetWidth() / 2 + 240 &&
			m_pFramework->GetYCursor() >= m_pFramework->GetHeight() / 2 - 50 + 150 &&
			m_pFramework->GetYCursor() <= m_pFramework->GetHeight() / 2 + 75 + 150)
		{
			GameStatus = 1;
		}
	}
}

void CGameApp::InGame_Release()
{
	PlaySound(NULL, 0, 0);

	// Floor
	m_Floor.Release();
	m_pFloor.Release();

	// Roof
	m_Roof.Release();
	m_pRoof.Release();

	// Wall
	m_Wall.Release();
	m_pWall.Release();

	// Table
	m_Table.Release();
	m_pTable.Release();

	// Chair
	m_Chair.Release();
	m_pChair.Release();

	// Bookshelf 1
	m_Bookshelf1.Release();
	m_pBookshelf1.Release();

	// Bookshelf 2
	m_Bookshelf2.Release();
	m_pBookshelf2.Release();

	// Books
	m_Books.Release();
	m_pBooks.Release();

	// Photo Frame 1
	m_PhotoFrame1.Release();
	m_pPhotoFrame1.Release();

	// Fan
	m_Fan.Release();
	m_pFan.Release();

	// TV Table Top
	m_TVTable_Top.Release();
	m_pTVTable_Top.Release();

	// TV Table Ground
	m_TVTable_Ground.Release();
	m_pTVTable_Ground.Release();

	// TV
	m_TV.Release();
	m_pTV.Release();

	// TV Content
	m_ContentTV.Release();
	m_pContentTV.Release();

	// Bed Frame
	m_BedFrame.Release();
	m_pBedFrame.Release();

	// Bed
	m_Bed.Release();
	m_pBed.Release();

	// Pillow
	m_Pillow.Release();
	m_pPillow.Release();

	// Table Lamp
	m_TableLamp.Release();
	m_pTableLamp.Release();

	// Table Book 1
	m_TableBook.Release();
	m_pTableBook.Release();

	//KODINGAN BARUUUU!!! ----------------------------------------------------------------------------------------------------
	// Iron Shelf
	m_IronShelf.Release();
	m_pIronShelf.Release();

	// Broom
	m_Broom.Release();
	m_pBroom.Release();

	// Vase 1
	m_Vase1.Release();
	m_pVase1.Release();

	// Vase 2
	m_Vase2.Release();
	m_pVase2.Release();

	// Janitor Door
	m_JanitorDoor.Release();
	m_pJanitorDoor.Release();

	// Janitor Door 2
	m_JanitorDoor2.Release();
	m_pJanitorDoor2.Release();

	// Pintu Tutup 1
	m_PintuTutup1.Release();
	m_pPintuTutup1.Release();

	// Pintu Tutup 2
	m_PintuTutup2.Release();
	m_pPintuTutup2.Release();

	// Pintu Tutup 3
	m_PintuTutup3.Release();
	m_pPintuTutup3.Release();

	// Kardus 1
	m_Kardus1.Release();
	m_pKardus1.Release();

	// Kardus 2
	m_Kardus2.Release();
	m_pKardus2.Release();

	// Box Ga Jelas
	m_BoxGaJelas.Release();
	m_pBoxGaJelas.Release();

	// Fire Hose
	m_FireHose.Release();
	m_pFireHose.Release();

	// Karpet
	m_Karpet.Release();
	m_pKarpet.Release();

	// Lemari Baju
	m_LemariBaju.Release();
	m_pLemariBaju.Release();

	// HP
	m_Sofa.Release();
	m_pSofa.Release();

	// HP
	m_HP.Release();
	m_pHP.Release();

	InGameInitialized = false;

	// Mouse Camera Movement
	MoveWithAutoMouse = false;

	// Cursor Settings
	ShowCursor(TRUE);
}

/**/

// void CGameApp::Credit_Init(LPDIRECT3DDEVICE9 pDevice)
// {
// 	// Loading
// 	Loading_Screen(pDevice);
// 
// 	// Cursor Settings
// 	ShowCursor(TRUE);
// 
// 	// Clearing Array Vector
// 	MeshObject.clear();
// 	MeshInstance.clear();
// 	DistanceFrom_.clear();
// 
// 	CreditInitialized = true;
// }
// 
// void CGameApp::Credit_Update(LPDIRECT3DDEVICE9 pDevice, float elapsedTime)
// {
// 
// }

void CGameApp::Credit_Render(LPDIRECT3DDEVICE9 pDevice, float elapsedTime)
{
	Credit->Begin(NULL);
	D3DXVECTOR3 CreditPosition(0.0f, 0.0f, 0.0f);
	Credit->Draw(CreditImg, NULL, NULL, &CreditPosition, D3DCOLOR_XRGB(255, 255, 255));
	Credit->End();
}

void CGameApp::Credit_ProcessInput(long xDelta, long yDelta, long zDelta, BOOL* pMouseButtons, BOOL* pPressedKeys, float elapsedTime)
{
	if (pPressedKeys[DIK_ESCAPE])
	{
		GameStatus = 1;
	}
}

// void CGameApp::Credit_Release()
// {
// 	CreditInitialized = false;
// 
// 	// Cursor Settings
// 	ShowCursor(FALSE);
// }

/**/

void CGameApp::CameraPositionChecker(float elapsedTime)
{
	// Save Last Camera Position For Object Collision
	CameraPosBeforeCollision = *m_camera.GetPosition();

	// Camera Move For Jump
	if (CameraJump && MaxCameraJump >= 0)
	{
		m_camera.SetPosition(new D3DXVECTOR3(m_camera.GetPosition()->x, m_camera.GetPosition()->y += MaxCameraJump * 4.0f * elapsedTime, m_camera.GetPosition()->z));
		MaxCameraJump -= 8.0f * elapsedTime;
	}

	// Camera Gravity
	m_camera.SetPosition(new D3DXVECTOR3(m_camera.GetPosition()->x, m_camera.GetPosition()->y -= 24.0f * elapsedTime, m_camera.GetPosition()->z));

	// Camera Face Height From Ground
	if (m_camera.GetPosition()->y <= 4.0f)
	{
		m_camera.SetPosition(new D3DXVECTOR3(m_camera.GetPosition()->x, 4.0f, m_camera.GetPosition()->z));
		CameraJump = false;
		MaxCameraJump = 10.0f;
		CameraCollision = false;
	}

	// Update Camera Logic Above
	m_camera.Update();

	// Check Collision
	if (MeshInstance.size() != 0 && MeshObject.size() != 0 && DistanceFrom_.size() != 0)
	{
		for (int i = 0; i<MeshInstance.size(); i++)
		{
			DistanceFrom_[i] = hypot(hypot(m_camera.GetPosition()->x - MeshInstance[i]->GetXPosition(), 0 - MeshInstance[i]->GetYPosition()), m_camera.GetPosition()->z - MeshInstance[i]->GetZPosition());
		}

		for (int i = 0; i<DistanceFrom_.size(); i++)
		{
			if ((DistanceFrom_[i] < MeshInstance[i]->GetBoundingRadius() &&
				!CameraCollision) ||
				m_camera.GetPosition()->x < -14.0f && m_camera.GetPosition()->z > -14.0f && m_camera.GetPosition()->z < 14.0f ||
				m_camera.GetPosition()->x > 13.0f && m_camera.GetPosition()->z > -14.0f && m_camera.GetPosition()->z < 14.0f ||
				m_camera.GetPosition()->z > 13.0f && m_camera.GetPosition()->x > -14.0f && m_camera.GetPosition()->x < 14.0f ||
				m_camera.GetPosition()->z > -15.0f && m_camera.GetPosition()->z < -13.0f && m_camera.GetPosition()->x > -8.0f && m_camera.GetPosition()->x < 14.0f ||
				m_camera.GetPosition()->z > -45.0f && m_camera.GetPosition()->z < -15.0f && m_camera.GetPosition()->x > 57.0f ||
				m_camera.GetPosition()->z > -45.0f && m_camera.GetPosition()->z < -15.0f && m_camera.GetPosition()->x < -53.0f ||
				m_camera.GetPosition()->z < -29.0f && m_camera.GetPosition()->x > -50.0f && m_camera.GetPosition()->x < 47.0f ||
				m_camera.GetPosition()->z < -40.0f && m_camera.GetPosition()->x > -53.0f && m_camera.GetPosition()->x < -50.0f ||
				m_camera.GetPosition()->z < -40.0f && m_camera.GetPosition()->x > 47.0f && m_camera.GetPosition()->x < 57.0f
				)
			{
				CameraCollision = true;
				// If Collision Move To Position Before
				m_camera.SetPosition(new D3DXVECTOR3(CameraPosBeforeCollision.x, CameraPosBeforeCollision.y, CameraPosBeforeCollision.z));
				m_camera.Update();
			}
		}
	}
}