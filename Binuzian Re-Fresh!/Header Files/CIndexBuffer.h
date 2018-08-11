/* * * * * * * * * * * * * * * * * * * * * * * *
*	File Name *	CIndexBuffer.h		      	   *
*	   Author *	Basilius Bias Astho Christyono *
* Website URL * bifeldy.blogspot.com		   *
*       Email *	bifeldy@gmail.com              *
* Description *	Index Buffer Wrapper		   *
*  Created On *	02/06/2018					   *
* * * * * * * * * * * * * * * * * * * * * * * */
#pragma once
#include "stdafx.h" 

class CIndexBuffer
{
public:
	CIndexBuffer();
	~CIndexBuffer() { Release(); }
	BOOL CreateBuffer(LPDIRECT3DDEVICE9 pDevice, UINT numIndices, D3DFORMAT format, BOOL dynamic = FALSE);
	void Release();
	BOOL SetData(UINT numIndices, void *pIndices, DWORD flags = D3DLOCK_DISCARD);
	LPDIRECT3DINDEXBUFFER9 GetBuffer() { return m_pIB; }

private:
	LPDIRECT3DINDEXBUFFER9  m_pIB;
	UINT                    m_numIndices;
};