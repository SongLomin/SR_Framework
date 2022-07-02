#include "Mesh_Terrain.h"
#include "GameInstance.h"

CMesh_Terrain::CMesh_Terrain()
{
}

CMesh_Terrain::CMesh_Terrain(const CMesh_Terrain& Prototype)
{
	*this = Prototype;
}

HRESULT CMesh_Terrain::Initialize_Prototype()
{

	return S_OK;
}

HRESULT CMesh_Terrain::Initialize(void* pArg)
{
	_point* pTerrainCnt = (_point*)pArg;

	if (nullptr == pTerrainCnt)
	{
		assert(false);
		return E_FAIL;
	}

	m_Terrain_Count = (*pTerrainCnt);
	m_dwNumSubsets = 0;
	//Bake_Terrain_Mesh();

	return S_OK;
}

HRESULT CMesh_Terrain::Render_Mesh()
{
	return S_OK;
}


CMesh_Terrain* CMesh_Terrain::Create()
{
	CREATE_PIPELINE(CMesh_Terrain);
}

CComponent* CMesh_Terrain::Clone(void* pArg)
{
	CLONE_PIPELINE(CMesh_Terrain);
}

void CMesh_Terrain::Free()
{
	__super::Free();

	delete this;
}

void CMesh_Terrain::Bake_Terrain_Mesh()
{
	int Max_Terrain_Count = m_Terrain_Count.x * m_Terrain_Count.y;

	m_iNumVertices = Max_Terrain_Count;
	m_iNumPrimitive = (m_Terrain_Count.x - 1) * (m_Terrain_Count.y - 1) * 2;
	m_dwFVF = VTXTEX::FVF;

	//m_dwNumSubsets = 1;

	//m_vTextures = CGameInstance::Get_Instance()->Get_Textures_From_Key(TEXT("Mesh_Cube"), MEMORY_TYPE::MEMORY_STATIC);

	if (FAILED(Create_EmptyMesh()))
	{
		MSG_BOX("Failed to Create_EmptyMesh : CMesh_Cube");
		return;
	}


	VTXTEX* vertices = nullptr;

	m_pMesh->LockVertexBuffer(0, (void**)&vertices);

	int index = 0;

	for (int i = 0; i < m_Terrain_Count.x; i++)
	{
		for (int j = 0; j < m_Terrain_Count.y; j++)
		{
			vertices[index].vPosition = _float3(2.f * i, 0.f, 2.f * j);
			vertices[index].vTexUV = _float2(i / (m_Terrain_Count.x - 1.f) * 20.f, j / (m_Terrain_Count.y - 1.f) * 20.f);

			index++;
		}
	}

	m_pMesh->UnlockVertexBuffer();

	FACEINDICES16* Indices = nullptr;

	m_pMesh->LockIndexBuffer(0, (void**)&Indices);


	for (int i = 0; i < m_Terrain_Count.x - 1; i++)
	{

		for (int j = 0; j < m_Terrain_Count.y - 1; j++)
		{
			Indices[index * 2]._1 = j + ((_ushort)m_Terrain_Count.y * i);
			Indices[index * 2]._2 = j + 1 + ((_ushort)m_Terrain_Count.y * i);
			Indices[index * 2]._3 = j + 1 + ((_ushort)m_Terrain_Count.y * (i + 1));

			Indices[index * 2 + 1]._1 = j + 1 + ((_ushort)m_Terrain_Count.y * (i + 1));
			Indices[index * 2 + 1]._2 = j + ((_ushort)m_Terrain_Count.y * (i + 1));
			Indices[index * 2 + 1]._3 = j + ((_ushort)m_Terrain_Count.y * i);

			index++;
		}
	}

	m_pMesh->UnlockIndexBuffer();

	DWORD* attributeBuffer = 0;
	m_pMesh->LockAttributeBuffer(0, &attributeBuffer);

	for (_uint i = 0; i < m_iNumPrimitive; ++i)
	{
		attributeBuffer[i] = 0;
	}

	m_pMesh->UnlockAttributeBuffer();

	vector<DWORD> adjacencyBuffer(m_iNumPrimitive * 3);
	m_pMesh->GenerateAdjacency(0.f, &adjacencyBuffer[0]);

	m_pMesh->OptimizeInplace(
		D3DXMESHOPT_ATTRSORT |
		D3DXMESHOPT_COMPACT |
		D3DXMESHOPT_VERTEXCACHE,
		&adjacencyBuffer[0],
		0, 0, 0
	);

}
