/* * * * * * * * * * * * * * * * * * * * * * * *
*	File Name *	CTerrain.cpp			 	   *
*	   Author *	Basilius Bias Astho Christyono *
* Website URL * bifeldy.blogspot.com		   *
*       Email *	bifeldy@gmail.com              *
* Description *	Terrain Generator			   *
*  Created On *	13/06/2018					   *
* * * * * * * * * * * * * * * * * * * * * * * */
#include "../Header Files/CTerrain.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Default constructor.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
CTerrain::CTerrain()
{
	m_pHeight = NULL;
	m_pTextureBase = NULL;
	m_pTextureDetail = NULL;
	m_numVertices = m_numIndices = 0;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Create a new Terrain object.
Parameters:
[in] pDevice - D3D Device
[in] rawFile - Name of the height map file
[in] terrainTexture - Texture file name
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
BOOL CTerrain::Initialize(LPDIRECT3DDEVICE9 pDevice, LPCWSTR rawFile, LPCWSTR baseTexture, LPCWSTR detailTexture = NULL)
{
	Release();

	// Load height map
	std::ifstream heightStream;
	heightStream.open(rawFile, std::ios::binary);
	if (heightStream.fail())
	{
		SHOWERROR("Could not open height file.", __FILE__, __LINE__);
		return FALSE;
	}

	// Get number of vertices
	heightStream.seekg(0, std::ios::end);
	m_numVertices = (UINT)heightStream.tellg();
	heightStream.seekg(0, std::ios::beg);

	// Allocate memory and read the data
	m_pHeight = new UCHAR[m_numVertices];
	heightStream.read((char *)m_pHeight, m_numVertices);
	heightStream.close();

	// Generate vertices
	UINT width = (int)sqrt((float)m_numVertices);
	if (!detailTexture)
	{
		cuCustomVertex::PositionTextured* pVertices = NULL;
		CTriangleStripPlane::GeneratePositionTexturedWithHeight(&pVertices, width, width, m_pHeight);
		m_vb.CreateBuffer(pDevice, m_numVertices, D3DFVF_XYZ | D3DFVF_TEX1, sizeof(cuCustomVertex::PositionTextured));
		m_vb.SetData(m_numVertices, pVertices, 0);
	}
	else
	{
		cuCustomVertex::Position2Textured* pVertices = NULL;
		CTriangleStripPlane::GeneratePosition2TexturedWithHeight(&pVertices, width, width, m_pHeight);
		m_vb.CreateBuffer(pDevice, m_numVertices, D3DFVF_XYZ | D3DFVF_TEX2, sizeof(cuCustomVertex::Position2Textured));
		m_vb.SetData(m_numVertices, pVertices, 0);
	}

	// Generate indices
	int* pIndices = NULL;
	m_numIndices = CTriangleStripPlane::GenerateIndices(&pIndices, width, width);
	m_ib.CreateBuffer(pDevice, m_numIndices, D3DFMT_INDEX32);
	m_ib.SetData(m_numIndices, pIndices, 0);
	m_vb.SetIndexBuffer(&m_ib);

	if (FAILED(D3DXCreateTextureFromFile(pDevice, baseTexture, &m_pTextureBase)))
	{
		SHOWERROR("Unable to load base texture.", __FILE__, __LINE__);
		return FALSE;
	}
	if (detailTexture != NULL)
	{
		if (FAILED(D3DXCreateTextureFromFile(pDevice, detailTexture, &m_pTextureDetail)))
		{
			SHOWERROR("Unable to load detail texture.", __FILE__, __LINE__);
			return FALSE;
		}
	}
	return TRUE;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Renders the terrain.
Parameters:
[in] pDevice - D3D Device
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void CTerrain::Render(LPDIRECT3DDEVICE9 pDevice)
{
	pDevice->SetTransform(D3DTS_WORLD, GetTransform());
	pDevice->SetTexture(0, m_pTextureBase);
	if (m_pTextureDetail)
	{
		pDevice->SetTexture(1, m_pTextureDetail);
		pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
		pDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_CURRENT);
		pDevice->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_TEXTURE);
		pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_ADDSIGNED);
	}
	m_vb.Render(pDevice, m_numIndices - 2, D3DPT_TRIANGLESTRIP);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Release resources
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void CTerrain::Release()
{
	SAFE_DELETE_ARRAY(m_pHeight);
	SAFE_RELEASE(m_pTextureBase);
	SAFE_RELEASE(m_pTextureDetail);
	m_vb.Release();
	m_ib.Release();
}