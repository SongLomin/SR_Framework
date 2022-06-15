#include "..\Public\VIBuffer_Terrain.h"

CVIBuffer_Terrain::CVIBuffer_Terrain(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CVIBuffer(pGraphic_Device)
{
}

CVIBuffer_Terrain::CVIBuffer_Terrain(const CVIBuffer_Terrain & Prototype)
	: CVIBuffer(Prototype)
	, m_iNumVerticesX(Prototype.m_iNumVerticesX)
	, m_iNumVerticesZ(Prototype.m_iNumVerticesZ)
{
}

HRESULT CVIBuffer_Terrain::Initialize_Prototype(_uint iNumVerticesX, _uint iNumVerticesZ)
{
	m_iStride = sizeof(VTXTEX);
	m_iNumVertices = iNumVerticesX * iNumVerticesZ;
	m_dwFVF = D3DFVF_XYZ | D3DFVF_TEX1;
	m_iNumPrimitive = (iNumVerticesX - 1) * (iNumVerticesZ - 1) * 2;
	m_iNumVerticesX = iNumVerticesX;
	m_iNumVerticesZ = iNumVerticesZ;
	
	/* 정점배열이 할당된다. */
	if (FAILED(__super::Create_VertexBuffer()))
		return E_FAIL;

	VTXTEX*			pVertices = nullptr;

	m_pVB->Lock(0, m_iStride * m_iNumVertices, (void**)&pVertices, 0);

	for (_uint i = 0; i < iNumVerticesZ; ++i)
	{
		for (_uint j = 0; j < iNumVerticesX; ++j)
		{
			_uint iIndex = i * iNumVerticesX + j;

			pVertices[iIndex].vPosition = _float3(j, 0.f, i);
			pVertices[iIndex].vTexUV = _float2(j / (iNumVerticesX - 1.f) * 20.f, i / (iNumVerticesZ - 1.f) * 20.f);
		}
	}	
	
	m_pVB->Unlock();

	m_iIndicesSizePerPrimitive = sizeof(FACEINDICES32);
	m_eFormat = D3DFMT_INDEX32;
	m_ePrimitiveType = D3DPT_TRIANGLELIST;

	if (FAILED(__super::Create_IndexBuffer()))
		return E_FAIL;

	FACEINDICES32*		pIndices = nullptr;

	_uint			iNumFaces = 0;

	m_pIB->Lock(0, 0, (void**)&pIndices, 0);

	for (_uint i = 0; i < iNumVerticesZ - 1; ++i)
	{
		for (_uint j = 0; j < iNumVerticesX - 1; ++j)
		{
			_uint	iIndex = i * iNumVerticesX + j;

			_uint	iIndices[] = {
				iIndex + iNumVerticesX, 
				iIndex + iNumVerticesX + 1,
				iIndex + 1, 
				iIndex
			};

			pIndices[iNumFaces]._1 = iIndices[0];
			pIndices[iNumFaces]._2 = iIndices[1];
			pIndices[iNumFaces]._3 = iIndices[2];
			++iNumFaces;

			pIndices[iNumFaces]._1 = iIndices[0];
			pIndices[iNumFaces]._2 = iIndices[2];
			pIndices[iNumFaces]._3 = iIndices[3];
			++iNumFaces;
		}
	}

	m_pIB->Unlock();

	return S_OK;
}

HRESULT CVIBuffer_Terrain::Initialize(void * pArg)
{
	return S_OK;
}

CVIBuffer_Terrain * CVIBuffer_Terrain::Create(LPDIRECT3DDEVICE9 pGraphic_Device, _uint iNumVerticesX, _uint iNumVerticesZ)
{
	CVIBuffer_Terrain*		pInstance = new CVIBuffer_Terrain(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype(iNumVerticesX, iNumVerticesZ)))
	{
		MSG_BOX("Failed to Created : CVIBuffer_Rect");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent * CVIBuffer_Terrain::Clone(void * pArg)
{
	CVIBuffer_Terrain*		pInstance = new CVIBuffer_Terrain(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CVIBuffer_Rect");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CVIBuffer_Terrain::Free()
{
	__super::Free();

}
