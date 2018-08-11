/* * * * * * * * * * * * * * * * * * * * * * * *
*	File Name *	GlobalStructAndFunction.h	   *
*	   Author *	Basilius Bias Astho Christyono *
* Website URL * bifeldy.blogspot.com		   *
*       Email *	bifeldy@gmail.com              *
* Description *	Animated Struct				   *
*  Created On *	16/06/2018					   *
* * * * * * * * * * * * * * * * * * * * * * * */
#pragma once
#include "../Header Files/stdafx.h"

// Video Player
#define KEYBOARD_SAMPLE_FREQ			100		// Sample user input on an interval
#define CUTSCENE_NAME					TEXT("SplashScreen Video Player\0")

__declspec(selectany) IGraphBuilder  *pGB = NULL;
__declspec(selectany) IMediaControl  *pMC = NULL;
__declspec(selectany) IVideoWindow   *pVW = NULL;
__declspec(selectany) IMediaEvent    *pME = NULL;
__declspec(selectany) BOOL g_bContinue = TRUE;

__declspec(selectany) LPCWSTR VideoIntro = L"Resource Files/Splash Screen/Intro.mp4";

struct StopWatch
{
	float Hours;
	float Minutes;
	float Seconds;
};

struct CUSTOMVERTEX
{
	FLOAT X, Y, Z;
	DWORD COLOR;
	FLOAT U, V;
};
#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

struct CUSTOMVERTEX1
{
	FLOAT X, Y, Z;
	D3DVECTOR NORMAL;
};
#define CUSTOMFVF1 (D3DFVF_XYZ | D3DFVF_NORMAL)

struct CUSTOMVERTEX2
{
	FLOAT X, Y, Z;
	D3DVECTOR NORMAL;
	FLOAT U, V;
};
#define CUSTOMFVF2 (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)

namespace patch {
	template <typename T> std::string to_string(const T&n) {
		std::ostringstream stm;
		stm << n;
		return stm.str();
	}
}

/* Convert String to LPC(W)STR
| std::wstring s2ws(const std::string& s)
| {
| 	int len;
| 	int slength = (int)s.length() + 1;
| 	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
| 	wchar_t* buf = new wchar_t[len];
| 	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
| 	std::wstring r(buf);
| 	delete[] buf;
| 	return r;
| }
|
*/