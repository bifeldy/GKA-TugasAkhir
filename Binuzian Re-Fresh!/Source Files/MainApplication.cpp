/* * * * * * * * * * * * * * * * * * * * * * * *
*	File Name *	MainApplication.cpp			   *
*	   Author *	Basilius Bias Astho Christyono *
* Website URL * bifeldy.blogspot.com		   *
*       Email *	bifeldy@gmail.com              *
* Description *	Starting New Fresh Project!    *
*  Created On *	01/06/2018					   *
* * * * * * * * * * * * * * * * * * * * * * * */
#include "../Header Files/stdafx.h"
#include "../Header Files/GlobalStructAndFunction.h"
#include "../Header Files/CGameApp.h"

LPCSTR iNitMsgBox =
"Hello BetA Tester Participant (^_^\") Wan`na Play ?\n\
\n\
Permainan ini dibuat untuk memenuhi tugas Akhir Grafika Komputer dan Animasi 2018.\n\
\n\
Daftar anggota:\n\
- Steven - 00000013433\n\
- Basilius Bias Astho Christyono - 00000013536\n\
- Reddy Kusuma Jaya - 00000013796\n\
- Rexy Samuel - 00000014136\n\
\n\
(C) Copyleft 2018 By Binuzian' All Right UnReserved!";


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Application entry point
Parameters:
[in] hInstance - Application instance
[in] hPrevInstance - Junk
[in] lpCmdLine - Command line arguments
[in] nCmdShow - Window display flags
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// Game Information
	int StartingGame = MessageBoxA(0, iNitMsgBox, "Game Information (>_<\")", MB_ICONASTERISK | MB_YESNO);

	// Game Info Button On Click
	if (StartingGame == 2 || StartingGame == 7)
	{
		return 0;
	}

	CGameApp* pApplication = new CGameApp();
	CFramework* pFramework = new CFramework((CBaseApp*)pApplication);

	pApplication->SetFramework(pFramework);

	// Initialize any application resources
	if (!pApplication->Initialize())
	{
		return 0;
	}

	// Initialize the Framework
	if (!pFramework->Initialize(APPLICATION_NAME, hInstance, SCREEN_WIDTH, SCREEN_HEIGHT, FALSE))
	{
		return 0;
	}

	// Rock and roll
	pFramework->Run();

	// Clean up resources
	SAFE_RELEASE(pApplication);

	return 0;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*      Tutorial Source * BOOK - Introduction to 3D Game Programming with DirectX 9 - Frank D. Luna  (2003) *
* Programming Language * C++ -- Direct3D 9	(DirectX SDK June 2010) -- Microsoft Visual Studio 2017        *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * *
*      Known BUGS      *
** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*  Animated Mesh Doesn't Works, So The Mesh Loaded Will Going To Be A Static Mesh Only!  *
*  -> Maybe Error When Bone & Framing Or Shader .fx File -- HAHA, I'm So Fucking Idiot!  *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

