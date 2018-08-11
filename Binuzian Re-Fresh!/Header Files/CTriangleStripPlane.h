/* * * * * * * * * * * * * * * * * * * * * * * *
*	File Name *	CTriangleStripPlane.h      	   *
*	   Author *	Basilius Bias Astho Christyono *
* Website URL * bifeldy.blogspot.com		   *
*       Email *	bifeldy@gmail.com              *
* Description *	Triangle Plane			       *
*  Created On *	11/06/2018					   *
* * * * * * * * * * * * * * * * * * * * * * * */
#pragma once
#include "../Header Files/stdafx.h"
#include "../Header Files/CustomVertex.h"

class CTriangleStripPlane
{
public:
	static void GeneratePositionNormalTextured(cuCustomVertex::PositionNormalTextured** ppVertices, int verticesAlongWidth, int verticesAlongLength);
	static void GeneratePositionTexturedWithHeight(cuCustomVertex::PositionTextured** ppVertices, int verticesAlongWidth, int verticesAlongLength, UCHAR* pHeight);
	static void GeneratePosition2TexturedWithHeight(cuCustomVertex::Position2Textured** ppVertices, int verticesAlongWidth, int verticesAlongLength, UCHAR* pHeight);
	static int GenerateIndices(int** ppIndices, int verticesAlongWidth, int verticesAlongLength);
	static int GenerateIndices(USHORT** ppIndices, int verticesAlongWidth, int verticesAlongLength);
};