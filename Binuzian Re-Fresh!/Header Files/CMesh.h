/* * * * * * * * * * * * * * * * * * * * * * * *
*	File Name *	CMesh.h					 	   *
*	   Author *	Basilius Bias Astho Christyono *
* Website URL * bifeldy.blogspot.com		   *
*       Email *	bifeldy@gmail.com              *
* Description *	.X Static Mesh File Wrapper	   *
*  Created On *	12/06/2018					   *
* * * * * * * * * * * * * * * * * * * * * * * */
#pragma once
#include "../Header Files/stdafx.h"
#include "../Header Files/CWorldTransform.h"

class CMesh
{
public:
	CMesh();
	~CMesh() { Release(); }
	BOOL Load(LPDIRECT3DDEVICE9 pDevice, LPCWSTR file);
	void Release();

	LPD3DXMESH GetMesh() { return m_pMesh; }
	DWORD GetNumMaterials() { return m_numMaterials; }
	D3DMATERIAL9* GetMeshMaterial(int i) { return &m_pMeshMaterials[i]; }
	LPDIRECT3DTEXTURE9 GetMeshTexture(int i) { return m_ppMeshTextures[i]; }

private:
	LPD3DXMESH m_pMesh;
	DWORD m_numMaterials;
	D3DMATERIAL9 *m_pMeshMaterials;
	LPDIRECT3DTEXTURE9 *m_ppMeshTextures;
};

class CMeshInstance : public CWorldTransform
{
public:
	CMeshInstance();
	~CMeshInstance() { Release(); }

	void Release();
	void SetMesh(CMesh* pMesh);
	void Render(LPDIRECT3DDEVICE9 pevice);

	float GetBoundingRadius() { return m_boundingRadius; }
	D3DXVECTOR3 GetCenter() { return center; }
	D3DXVECTOR3 GetMin() { return min; }
	D3DXVECTOR3 GetMax() { return max; }
	DWORD GetNumVertices() { return numVertices; }
	DWORD GetFVFSize() { return fvfSize; }
	char* GetpData() { return pData; }

private:
	CMesh* m_pMesh;
	char* pData;
	DWORD numVertices, fvfSize;
	D3DXVECTOR3 center, min, max;
	float m_boundingRadius;
};
