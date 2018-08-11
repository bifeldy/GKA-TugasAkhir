/* * * * * * * * * * * * * * * * * * * * * * * *
*	File Name *	CTerrain.h				 	   *
*	   Author *	Basilius Bias Astho Christyono *
* Website URL * bifeldy.blogspot.com		   *
*       Email *	bifeldy@gmail.com              *
* Description *	Terrain Generator			   *
*  Created On *	13/06/2018					   *
* * * * * * * * * * * * * * * * * * * * * * * */
#pragma once
#include "../Header Files/stdafx.h"
#include "../Header Files/CWorldTransform.h"
#include "../Header Files/CTriangleStripPlane.h"
#include "../Header Files/CVertexBuffer.h"
#include "../Header Files/CIndexBuffer.h"
#include "../Header Files/CustomVertex.h"

class CTerrain : public CWorldTransform
{
public:

	CTerrain();
	~CTerrain() { Release(); }

	BOOL Initialize(LPDIRECT3DDEVICE9 pDevice, LPCWSTR rawFile, LPCWSTR baseTexture, LPCWSTR detailTexture);
	void Render(LPDIRECT3DDEVICE9 pDevice);
	void Release();
	UINT getNumIndices() { return m_numIndices; }
	UINT getNumVertices() { return m_numVertices; }

private:
	CVertexBuffer m_vb;
	CIndexBuffer m_ib;
	LPDIRECT3DTEXTURE9 m_pTextureBase;
	LPDIRECT3DTEXTURE9 m_pTextureDetail;
	UCHAR* m_pHeight;
	UINT m_numVertices;
	UINT m_numIndices;
};