/* * * * * * * * * * * * * * * * * * * * * * * *
*   File Name * CGameApp.h                     *
*      Author * Basilius Bias Astho Christyono *
*       Email * bias.astho@gmail.com           *
* Description * Application Header File        *
*  Created On * 01/06/2018                     *
* * * * * * * * * * * * * * * * * * * * * * * */
#pragma once
#include "../Header Files/stdafx.h"
#include "../Header Files/GlobalStructAndFunction.h"
#include "../Header Files/CBaseApp.h"
#include "../Header Files/CFramework.h"
#include "../Header Files/CWorldTransform.h"
#include "../Header Files/CFont.h"
#include "../Header Files/CMesh.h"
#include "../Header Files/CCamera.h"

class CGameApp : public CBaseApp
{
public:
	CGameApp();
	~CGameApp() { Release(); }
	void SetFramework(CFramework* pFramework);
	BOOL Initialize();
	virtual void Release();
	virtual void OnCreateDevice(LPDIRECT3DDEVICE9 pDevice);
	virtual void OnResetDevice(LPDIRECT3DDEVICE9 pDevice);
	virtual void OnLostDevice();
	virtual void OnDestroyDevice();
	virtual void OnUpdateFrame(LPDIRECT3DDEVICE9 pDevice, float elapsedTime);
	virtual void OnRenderFrame(LPDIRECT3DDEVICE9 pDevice, float elapsedTime);
	virtual void ProcessInput(long xDelta, long yDelta, long zDelta,
	BOOL* pMouseButtons, BOOL* pPressedKeys, float elapsedTime);

	/* Your Function In Here And Publicly Can Be Accessed By Everyone */

	void Initialize_CustomFONT();
	void Loading_Screen(LPDIRECT3DDEVICE9 pDevice);

	void MainMenu_Init(LPDIRECT3DDEVICE9 pDevice);
	void MainMenu_Update(LPDIRECT3DDEVICE9 pDevice, float elapsedTime);
	void MainMenu_Render(LPDIRECT3DDEVICE9 pDevice, float elapsedTime);
	void MainMenu_ProcessInput(long xDelta, long yDelta, long zDelta,
		BOOL* pMouseButtons, BOOL* pPressedKeys, float elapsedTime);
	void MainMenu_Release();

	void InGame_Init(LPDIRECT3DDEVICE9 pDevice);
	void InGame_Update(LPDIRECT3DDEVICE9 pDevice, float elapsedTime);
	void InGame_Render(LPDIRECT3DDEVICE9 pDevice, float elapsedTime);
	void InGame_ProcessInput(long xDelta, long yDelta, long zDelta, BOOL* pMouseButtons, BOOL* pPressedKeys, float elapsedTime);
	void InGame_Release();

	// void Credit_Init(LPDIRECT3DDEVICE9 pDevice);
	// void Credit_Update(LPDIRECT3DDEVICE9 pDevice, float elapsedTime);
	void Credit_ProcessInput(long xDelta, long yDelta, long zDelta, BOOL* pMouseButtons, BOOL* pPressedKeys, float elapsedTime);
	void Credit_Render(LPDIRECT3DDEVICE9 pDevice, float elapsedTime);
	// void Credit_Release();


private:
	CFramework*				m_pFramework;

	D3DLIGHT9				m_light, m_LightTable;
	D3DMATERIAL9			m_material;

	CCamera					m_camera;

	bool					CameraJump;
	float					MaxCameraJump;
	bool					MoveWithAutoMouse;

	vector<CMesh*>			MeshObject;
	vector<CMeshInstance*>	MeshInstance;
	vector<float>			DistanceFrom_;

	D3DXVECTOR3				CameraPosBeforeCollision;
	bool					CameraCollision;
	void					CameraPositionChecker(float elapsedTime);

	/* Your Variable Under Here And Privately Acessed By Only This Class */

	CMesh					m_Alice, m_Lilith;
	CMeshInstance			m_pAlice, m_pLilith;

	/* 
		Game Status 
		1. Main Menu
		2. In Game
		3. Credit
	*/
	int GameStatus;
	bool MainMenuInitialized, InGameInitialized, CreditInitialized;
	bool ExitGame, InGameEscapeIsPressed;
	bool HP_Ketemu;
	float DistanceFromHP;


	/* Splash Screen */

	LPD3DXSPRITE			LoadingAwal, LoadingHowToPlay, GamePaused, Congratulations, Credit;
	LPDIRECT3DTEXTURE9      LoadingAwalImg, LoadingHowToPlayImg, GamePausedImg, CongratulationsImg, CreditImg;

	/* Main Menu */

	CMesh					m_Land, m_FarmHouse, m_Wood1, m_Wood2, m_FirePlace;
	CMeshInstance			m_pLand, m_pFarmHouse, m_pWood1, m_pWood2, m_pFirePlace;

	LPD3DXSPRITE			TheThruth, Binuzian;
	LPDIRECT3DTEXTURE9      TheThruthImg, BinuzianImg;

	LPD3DXSPRITE			PlayButton;
	LPDIRECT3DTEXTURE9      PlayButtonImg, PlayButtonImgHover;
	LPD3DXSPRITE			InfoButton;
	LPDIRECT3DTEXTURE9      InfoButtonImg, InfoButtonImgHover;
	LPD3DXSPRITE			ExitButton;
	LPDIRECT3DTEXTURE9      ExitButtonImg, ExitButtonImgHover;

	LPDIRECT3DVERTEXBUFFER9 v_buffer;
	LPDIRECT3DINDEXBUFFER9  i_buffer;
	LPDIRECT3DTEXTURE9		WorldTexture;

	/* In Game */

	CMesh					m_Roof, m_Floor, m_Wall, m_PhotoFrame1, m_Bookshelf1, m_Chair, m_TableLamp, m_TableBook, m_ContentTV, m_BedFrame, m_Jeans, m_HP, m_HP2, m_BoxGaJelas, m_Sofa,
							m_Bookshelf2, m_TVTable_Ground, m_TVTable_Top, m_TV, m_Fan, m_Table, m_Bed, m_Pillow, m_Books, m_IronShelf, m_Broom, m_Vase1, m_Vase2, m_JanitorDoor, m_JanitorDoor2, m_PintuTutup1, m_PintuTutup2, m_PintuTutup3, m_Kardus1, m_Kardus2, m_FireHose, m_Karpet, m_LemariBaju;
																																																
	CMeshInstance			m_pRoof, m_pFloor, m_pWall, m_pPhotoFrame1, m_pBookshelf1, m_pChair, m_pTableLamp, m_pTableBook, m_pBedFrame, m_pBooks, m_pJeans, m_pHP, m_pHP2, m_pBoxGaJelas, m_pSofa,
							m_pBookshelf2, m_pTVTable_Ground, m_pTVTable_Top, m_pTV, m_pFan, m_pTable, m_pContentTV, m_pBed, m_pPillow, m_pIronShelf, m_pBroom, m_pVase1, m_pVase2, m_pJanitorDoor, m_pJanitorDoor2, m_pPintuTutup1, m_pPintuTutup2, m_pPintuTutup3, m_pKardus1, m_pKardus2, m_pFireHose, m_pKarpet, m_pLemariBaju;
																																																					
	LPD3DXSPRITE			Crosshair;
	LPDIRECT3DTEXTURE9      CrosshairImg;

	CFont					m_font, Total_Time;
	StopWatch				stopwatch;

	int						LokasiSpawnHP;
	LPCWSTR					Test, Test1;

	LPD3DXSPRITE			ResumeButton;
	LPDIRECT3DTEXTURE9      ResumeButtonImg, ResumeButtonImgHover;
	LPD3DXSPRITE			MainMenuButton;
	LPDIRECT3DTEXTURE9      MainMenuButtonImg, MainMenuButtonImgHover;

};
