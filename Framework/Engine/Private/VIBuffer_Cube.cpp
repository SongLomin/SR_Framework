#include "VIBuffer_Cube.h"

CVIBuffer_Cube::CVIBuffer_Cube()
{
}

CVIBuffer_Cube::CVIBuffer_Cube(const CVIBuffer_Cube& Prototype)
{
	*this = Prototype;
}

HRESULT CVIBuffer_Cube::Initialize_Prototype()
{
	m_iStride = sizeof(VTXCUBETEX);
	m_iNumVertices = 8;
	m_dwFVF = VTXCUBETEX::SKY; /* | D3DFVF_TEXCOORDSIZE2(0) */
	m_iNumPrimitive = 12;

	/* 정점배열이 할당된다. */
	if (FAILED(__super::Create_VertexBuffer()))
		return E_FAIL;

	VTXCUBETEX* pVertices = nullptr;

	m_pVB->Lock(0, m_iStride * m_iNumVertices, (void**)&pVertices, 0);

	pVertices[0].vPosition = _float3(-0.5f, 0.5f, -0.5f);
	pVertices[0].vTexUV = pVertices[0].vPosition;

	pVertices[1].vPosition = _float3(0.5f, 0.5f, -0.5f);
	pVertices[1].vTexUV = pVertices[1].vPosition;

	pVertices[2].vPosition = _float3(0.5f, -0.5f, -0.5f);
	pVertices[2].vTexUV = pVertices[2].vPosition;

	pVertices[3].vPosition = _float3(-0.5f, -0.5f, -0.5f);
	pVertices[3].vTexUV = pVertices[3].vPosition;

	pVertices[4].vPosition = _float3(-0.5f, 0.5f, 0.5f);
	pVertices[4].vTexUV = pVertices[4].vPosition;

	pVertices[5].vPosition = _float3(0.5f, 0.5f, 0.5f);
	pVertices[5].vTexUV = pVertices[5].vPosition;

	pVertices[6].vPosition = _float3(0.5f, -0.5f, 0.5f);
	pVertices[6].vTexUV = pVertices[6].vPosition;

	pVertices[7].vPosition = _float3(-0.5f, -0.5f, 0.5f);
	pVertices[7].vTexUV = pVertices[7].vPosition;
	//v[0] = VTXTEX({ -1.0f, -1.0f, -1.0f }, { 0.0f, 0.0f });
	//v[1] = VTXTEX({ -1.0f, 1.0f, -1.0f }, { 0.0f, 1.0f });
	//v[2] = VTXTEX({ 1.0f, 1.0f, -1.0f }, { 1.0f, 1.0f });
	//v[3] = VTXTEX({ 1.0f, -1.0f, -1.0f }, { 1.0f, 0.0f });

	//// fill in the back face vertex data
	//v[4] = VTXTEX({ -1.0f, -1.0f, 1.0f }, { 0.0f, 0.0f });
	//v[5] = VTXTEX({ 1.0f, -1.0f, 1.0f }, { 0.0f, 1.0f });
	//v[6] = VTXTEX({ 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f });
	//v[7] = VTXTEX({ -1.0f, 1.0f, 1.0f }, { 1.0f, 0.0f });

	//// fill in the top face VTXTEX data
	//v[8] = VTXTEX({ -1.0f, 1.0f, -1.0f }, { 0.0f, 0.0f });
	//v[9] = VTXTEX({ -1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f });
	//v[10] = VTXTEX({ 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f });
	//v[11] = VTXTEX({ 1.0f, 1.0f, -1.0f }, { 1.0f, 0.0f });

	//// fill in the bottom face VTXTEX data
	//v[12] = VTXTEX({ -1.0f,-1.0f, -1.0f }, { 0.0f, 0.0f });
	//v[13] = VTXTEX({ 1.0f, -1.0f, -1.0f }, { 0.0f, 1.0f });
	//v[14] = VTXTEX({ 1.0f, -1.0f, 1.0f }, { 1.0f, 1.0f });
	//v[15] = VTXTEX({ -1.0f, -1.0f, 1.0f }, { 1.0f, 0.0f });

	//// fill in the left face VTXTEX data
	//v[16] = VTXTEX({ -1.0f, -1.0f, 1.0f }, { 0.0f, 0.0f });
	//v[17] = VTXTEX({ -1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f });
	//v[18] = VTXTEX({ -1.0f, 1.0f, -1.0f }, { 1.0f, 1.0f });
	//v[19] = VTXTEX({ -1.0f, -1.0f, -1.0f }, { 1.0f, 0.0f });

	//// fill in the right face VTXTEX data
	//v[20] = VTXTEX({ 1.0f, -1.0f, -1.0f }, { 0.0f, 0.0f });
	//v[21] = VTXTEX({ 1.0f, 1.0f, -1.0f }, { 0.0f, 1.0f });
	//v[22] = VTXTEX({ 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f });
	//v[23] = VTXTEX({ 1.0f, -1.0f, 1.0f }, { 1.0f, 0.0f });

	m_pVB->Unlock();

	m_iIndicesSizePerPrimitive = sizeof(FACEINDICES16);
	m_eFormat = D3DFMT_INDEX16;
	m_ePrimitiveType = D3DPT_TRIANGLELIST;

	if (FAILED(__super::Create_IndexBuffer()))
		return E_FAIL;

	FACEINDICES16* pIndices = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndices, 0);

	pIndices[0]._1 = 1; pIndices[0]._2 = 5; pIndices[0]._3 = 6;
	pIndices[1]._1 = 1; pIndices[1]._2 = 6; pIndices[1]._3 = 2;

	/* -x */
	pIndices[2]._1 = 4; pIndices[2]._2 = 0; pIndices[2]._3 = 3;
	pIndices[3]._1 = 4; pIndices[3]._2 = 3; pIndices[3]._3 = 7;

	/* +y */
	pIndices[4]._1 = 4; pIndices[4]._2 = 5; pIndices[4]._3 = 1;
	pIndices[5]._1 = 4; pIndices[5]._2 = 1; pIndices[5]._3 = 0;

	/* -y */
	pIndices[6]._1 = 3; pIndices[6]._2 = 2; pIndices[6]._3 = 6;
	pIndices[7]._1 = 3; pIndices[7]._2 = 6; pIndices[7]._3 = 7;

	/* +z */
	pIndices[8]._1 = 5; pIndices[8]._2 = 4; pIndices[8]._3 = 7;
	pIndices[9]._1 = 5; pIndices[9]._2 = 7; pIndices[9]._3 = 6;

	/* -z */
	pIndices[10]._1 = 0; pIndices[10]._2 = 1; pIndices[10]._3 = 2;
	pIndices[11]._1 = 0; pIndices[11]._2 = 2; pIndices[11]._3 = 3;

	/*pIndices[0]._1 = 0; pIndices[0]._2 = 1; pIndices[0]._3 = 2;
	pIndices[1]._1 = 0; pIndices[1]._2 = 2; pIndices[1]._3 = 3;

	pIndices[2]._1 = 4; pIndices[2]._2 = 5; pIndices[2]._3 = 6;
	pIndices[3]._1 = 4; pIndices[3]._2 = 6; pIndices[3]._3 = 7;

	pIndices[4]._1 = 8; pIndices[4]._2 = 9; pIndices[4]._3 = 10;
	pIndices[5]._1 = 8; pIndices[5]._2 = 10; pIndices[5]._3 = 11;

	pIndices[6]._1 = 12; pIndices[6]._2 = 13; pIndices[6]._3 = 14;
	pIndices[7]._1 = 12; pIndices[7]._2 = 14; pIndices[7]._3 = 15;

	pIndices[8]._1 = 16; pIndices[8]._2 = 17; pIndices[8]._3 = 18;
	pIndices[9]._1 = 16; pIndices[9]._2 = 18; pIndices[9]._3 = 19;

	pIndices[10]._1 = 20; pIndices[10]._2 = 21; pIndices[10]._3 = 22;
	pIndices[11]._1 = 20; pIndices[11]._2 = 22; pIndices[11]._3 = 23;*/

	m_pIB->Unlock();

	/*VTXTEX* pVertices = nullptr;

	m_pVB->Lock(0, m_iStride * m_iNumVertices, (void**)&pVertices, 0);

	pVertices[0].vPosition = _float3(-0.5f, 0.5f, 0.f);
	pVertices[0].vTexUV = _float2(0.0f, 0.f);

	pVertices[1].vPosition = _float3(0.5f, 0.5f, 0.f);
	pVertices[1].vTexUV = _float2(2.f, 0.f);

	pVertices[2].vPosition = _float3(0.5f, -0.5f, 0.f);
	pVertices[2].vTexUV = _float2(2.f, 2.f);

	pVertices[3].vPosition = _float3(-0.5f, -0.5f, 0.f);
	pVertices[3].vTexUV = _float2(0.f, 2.f);

	m_pVB->Unlock();

	m_iIndicesSizePerPrimitive = sizeof(FACEINDICES16);
	m_eFormat = D3DFMT_INDEX16;
	m_ePrimitiveType = D3DPT_TRIANGLELIST;

	if (FAILED(__super::Create_IndexBuffer()))
		return E_FAIL;

	FACEINDICES16* pIndices = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndices, 0);

	pIndices[0]._1 = 0;
	pIndices[0]._2 = 1;
	pIndices[0]._3 = 2;

	pIndices[1]._1 = 0;
	pIndices[1]._2 = 2;
	pIndices[1]._3 = 3;

	m_pIB->Unlock();*/

	return S_OK;
}

HRESULT CVIBuffer_Cube::Initialize(void* pArg)
{
	return S_OK;
}

CVIBuffer_Cube* CVIBuffer_Cube::Create()
{
	CREATE_PIPELINE(CVIBuffer_Cube);
}

CComponent* CVIBuffer_Cube::Clone(void* pArg)
{
	CLONE_PIPELINE(CVIBuffer_Cube);
}

void CVIBuffer_Cube::Free()
{
	__super::Free();

	delete this;
}

