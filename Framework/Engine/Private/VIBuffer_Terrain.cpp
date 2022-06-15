#include "VIBuffer_Terrain.h"
#include <cassert>

CVIBuffer_Terrain::CVIBuffer_Terrain(const CVIBuffer_Terrain& Prototype)
{
	*this = Prototype;

}

HRESULT CVIBuffer_Terrain::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CVIBuffer_Terrain::Initialize(void* pArg)
{
	_point* pTerrainCnt = (_point*)pArg;

	if (nullptr == pTerrainCnt)
	{
		assert(false);
		return E_FAIL;
	}
		
	m_Terrain_Count = (*pTerrainCnt);

	Bake_Terrain_Mesh();

	return S_OK;
}

CVIBuffer_Terrain* CVIBuffer_Terrain::Create()
{
	CREATE_PIPELINE(CVIBuffer_Terrain);
}

CComponent* CVIBuffer_Terrain::Clone(void* pArg)
{
	CLONE_PIPELINE(CVIBuffer_Terrain);
}

void CVIBuffer_Terrain::Free()
{
	__super::Free();

	delete this;
}

void CVIBuffer_Terrain::Bake_Terrain_Mesh()
{
	int Max_Terrain_Count = m_Terrain_Count.x * m_Terrain_Count.y;

	m_iStride = sizeof(VTXTEX);
	m_iNumVertices = Max_Terrain_Count;
	m_dwFVF = VTXTEX::FVF; /* | D3DFVF_TEXCOORDSIZE2(0) */
	m_iNumPrimitive = 2 * (m_Terrain_Count.x - 1) * (m_Terrain_Count.y - 1);

	/* 정점배열이 할당된다. */
	if (FAILED(__super::Create_VertexBuffer()))
		assert(false);

	
	VTXTEX* pVertices = nullptr;

	m_pVB->Lock(0, m_iStride * m_iNumVertices, (void**)&pVertices, 0);

	int index = 0;

	for (int i = 0; i < m_Terrain_Count.x; i++)
	{
		for (int j = 0; j < m_Terrain_Count.y; j++)
		{
			pVertices[index].vPosition = _float3(2.f * i, 0.f, 2.f * j);
			pVertices[index].vTexUV = _float2(i / (m_Terrain_Count.x - 1.f) * 20.f, j / (m_Terrain_Count.y - 1.f) * 20.f);

			index++;
		}
	}

	m_pVB->Unlock();

	m_iIndicesSizePerPrimitive = sizeof(FACEINDICES16);
	m_eFormat = D3DFMT_INDEX16;
	m_ePrimitiveType = D3DPT_TRIANGLELIST;

	if (FAILED(__super::Create_IndexBuffer()))
		assert(false);

	FACEINDICES16* pIndices = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndices, 0);

	index = 0;

	for (int i = 0; i < m_Terrain_Count.x - 1; i++)
	{

		for (int j = 0; j < m_Terrain_Count.y - 1; j++)
		{
			pIndices[index * 2]._1 = j + (m_Terrain_Count.y * i);
			pIndices[index * 2]._2 = j + 1 + (m_Terrain_Count.y * i);
			pIndices[index * 2]._3 = j + 1 + (m_Terrain_Count.y * (i + 1));

			pIndices[index * 2 + 1]._1 = j + 1 + (m_Terrain_Count.y * (i + 1));
			pIndices[index * 2 + 1]._2 = j + (m_Terrain_Count.y * (i + 1));
			pIndices[index * 2 + 1]._3 = j + (m_Terrain_Count.y * i);

			index++;
		}
	}

	m_pIB->Unlock();
}
