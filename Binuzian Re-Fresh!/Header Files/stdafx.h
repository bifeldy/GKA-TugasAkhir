// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
#pragma once

// Exclude rarely-used stuff from Windows headers
// #define WIN32_LEAN_AND_MEAN		
#define DIRECTINPUT_VERSION 0x0800

// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <ctime>
#include <time.h>
#include <fstream>
#include <vector>
#include <strsafe.h>
#include <string>
#include <sstream>

// DirectX Header Files
#include <d3d9.h>
#include <d3dx9.h>
#include <dshow.h>
#include <dinput.h>

#include "../Header Files/resource.h"

// Direct3D Library
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "Winmm.lib")
#pragma comment (lib, "Gdi32.lib")
#pragma comment (lib, "strmiids.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxerr.lib")
#pragma comment (lib, "dxguid.lib")

// Useful macros
#define SAFE_RELEASE(x) if( x ) { (x)->Release(); (x) = NULL; }
#define SAFE_DELETE(x) if( x ) { delete(x); (x) = NULL; }
#define SAFE_DELETE_ARRAY(x) if( x ) { delete [] (x); (x) = NULL; }

// Global Variabel
#define SCREEN_WIDTH		800
#define SCREEN_HEIGHT		600

#define APPLICATION_NAME	L"BINUZIAN Re:Fresh-Up! | Tugas Akhir Grafika Komputer dan Animasi 2018"
#define APPLICATION_CURSOR	L"Resource Files/Mouse.ani"
#define SHOWERROR(s,f,l) char buf[1024]; sprintf_s(buf, "File: %s\nLine: %d\n%s",f,l,s); MessageBoxA( 0, buf, "Error", MB_ICONERROR | MB_OK);

using namespace std;

// Animated Mesh Properties
// __declspec(selectany) string MeshFolder;
// __declspec(selectany) ID3DXEffect* g_pEffect = NULL;

const D3DXCOLOR      WHITE(D3DCOLOR_XRGB(255, 255, 255));
const D3DXCOLOR      BLACK(D3DCOLOR_XRGB(  0  , 0,   0));
const D3DXCOLOR        RED(D3DCOLOR_XRGB(255,   0,   0));
const D3DXCOLOR      GREEN(D3DCOLOR_XRGB(  0, 255,   0));
const D3DXCOLOR       BLUE(D3DCOLOR_XRGB(  0,   0, 255));
const D3DXCOLOR     YELLOW(D3DCOLOR_XRGB(255, 255,   0));
const D3DXCOLOR       CYAN(D3DCOLOR_XRGB(  0, 255, 255));
const D3DXCOLOR    MAGENTA(D3DCOLOR_XRGB(255,   0, 255));
const D3DXCOLOR		  GRAY(D3DCOLOR_XRGB(122, 122, 122));

/* * * * * * * * * * * * * * * * * * * * * * * *
*	File Name *	stdafx.h         			   *
*	   Author *	Basilius Bias Astho Christyono *
* Website URL * bifeldy.blogspot.com		   *
*       Email *	bifeldy@gmail.com              *
* Description *	C++ Header & DirectX 9 Library *
*  Created On *	01/06/2018					   *
* * * * * * * * * * * * * * * * * * * * * * * */