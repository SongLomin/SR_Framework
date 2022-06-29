#include "VIBuffer_Rect.h"

CVIBuffer_Rect::CVIBuffer_Rect()
{
}

CVIBuffer_Rect::CVIBuffer_Rect(const CVIBuffer_Rect& Prototype)
{
	*this = Prototype;
}

HRESULT CVIBuffer_Rect::Initialize_Prototype()
{
	


	return S_OK;
}

HRESULT CVIBuffer_Rect::Initialize(void* pArg)
{
	m_iStride = sizeof(VTXTEX);
	m_iNumVertices = 4;
	m_dwFVF = VTXTEX::FVF; /* | D3DFVF_TEXCOORDSIZE2(0) */
	m_iNumPrimitive = 2;

	/* 정점배열이 할당된다. */
	if (FAILED(__super::Create_VertexBuffer()))
		return E_FAIL;

	//m_pVerticesPos = new _float3[m_iNumVertices];

	VTXTEX* pVertices = nullptr;

	m_pVB->Lock(0, m_iStride * m_iNumVertices, (void**)&pVertices, 0);

	pVertices[0] = VTXTEX({ -0.5f, 0.5f, 0.0f }, { 0.0f, 0.0f });
	//m_pVerticesPos[0] = pVertices[0].vPosition;

	pVertices[1] = VTXTEX({ 0.5f, 0.5f, 0.0f }, { 1.0f, 0.0f });
	//m_pVerticesPos[1] = pVertices[1].vPosition;

	pVertices[2] = VTXTEX({ 0.5f, -0.5f, 0.0f }, { 1.0f, 1.0f });
	//m_pVerticesPos[2] = pVertices[2].vPosition;

	pVertices[3] = VTXTEX({ -0.5f, -0.5f, 0.0f }, { 0.0f, 1.0f });
	//m_pVerticesPos[2] = pVertices[3].vPosition;

	m_pVB->Unlock();

	m_iIndicesSizePerPrimitive = sizeof(FACEINDICES16);
	m_eFormat = D3DFMT_INDEX16;
	m_ePrimitiveType = D3DPT_TRIANGLELIST;

	if (FAILED(__super::Create_IndexBuffer()))
		return E_FAIL;


	//m_pIndices = new FACEINDICES16[m_iNumPrimitive];
	FACEINDICES16* pIndices = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndices, 0);

	pIndices[0]._1 = 0;
	pIndices[0]._2 = 1;
	pIndices[0]._3 = 2;

	pIndices[1]._1 = 0;
	pIndices[1]._2 = 2;
	pIndices[1]._3 = 3;

	//memcpy(m_pIndices, pIndices, sizeof(FACEINDICES16) * m_iNumPrimitive);

	m_pIB->Unlock();

	return S_OK;
}

CVIBuffer_Rect* CVIBuffer_Rect::Create()
{
	CREATE_PIPELINE(CVIBuffer_Rect);
}

CComponent* CVIBuffer_Rect::Clone(void* pArg)
{
	CLONE_PIPELINE(CVIBuffer_Rect);
}

void CVIBuffer_Rect::Free()
{
	__super::Free();

	delete this;
}