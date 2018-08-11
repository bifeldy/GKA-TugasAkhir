/* * * * * * * * * * * * * * * * * * * * * * * *
*	File Name *	CVertexBuffer.h		      	   *
*	   Author *	Basilius Bias Astho Christyono *
* Website URL * bifeldy.blogspot.com		   *
*       Email *	bifeldy@gmail.com              *
* Description *	Vertex Buffer Wrapper		   *
*  Created On *	02/06/2018					   *
* * * * * * * * * * * * * * * * * * * * * * * */
#pragma once
#include "../Header Files/stdafx.h"
#include "../Header Files/CIndexBuffer.h" 

class CVertexBuffer
{
public:
	CVertexBuffer();
	~CVertexBuffer() { Release(); }

	BOOL CreateBuffer(LPDIRECT3DDEVICE9 pDevice, UINT numVertices, DWORD FVF, UINT vertexSize,
	BOOL dynamic = FALSE);
	void Release();
	BOOL SetData(UINT numVertices, void *pVertices, DWORD flags = D3DLOCK_DISCARD);
	void SetIndexBuffer(CIndexBuffer* pIB);
	void Render(LPDIRECT3DDEVICE9 pDevice, UINT numPrimitives, D3DPRIMITIVETYPE primitiveType);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVB;
	CIndexBuffer*           m_pIB;
	UINT                    m_numVertices;
	UINT                    m_vertexSize;
	DWORD                   m_FVF;
};