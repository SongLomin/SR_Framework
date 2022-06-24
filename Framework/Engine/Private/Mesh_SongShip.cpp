#include "Mesh_SongShip.h"
#include "GameInstance.h"

CMesh_SongShip::CMesh_SongShip()
{
}

CMesh_SongShip::CMesh_SongShip(const CMesh_SongShip& Prototype)
{
	*this = Prototype;
}

HRESULT CMesh_SongShip::Initialize_Prototype()
{
	m_iNumVertices = 12;
	m_iNumPrimitive = 4;
	m_dwFVF = VTXCOLOR::FVF;

	m_dwNumSubsets = 1;
	if (FAILED(Create_EmptyMesh()))
	{
		MSG_BOX("Failed to Create_EmptyMesh : CMesh_Cube");
		return E_FAIL;
	}
	VTXCOLOR* vertices = nullptr;
	m_pMesh->LockVertexBuffer(0, (void**)&vertices);

	vertices[0] = VTXCOLOR(_float3(0, -12.3017, 88.1518), _float3(0.5, 0, -0.187598), D3DCOLOR_ARGB(255, 40, 40, 40));
	vertices[1] = VTXCOLOR(_float3(-93.1207, 0.5, 1), _float3(20.0352, 12.3017, -88.1518), D3DCOLOR_ARGB(255, 40, 40, 40));
	vertices[2] = VTXCOLOR(_float3(1, 20.0352, 12.3017), _float3(-88.1518, 0.698002, 1), D3DCOLOR_ARGB(255, 40, 40, 40));
	vertices[3] = VTXCOLOR(_float3(-4.57144, -90.5064, 1), _float3(1, 0, -12.3017), D3DCOLOR_ARGB(255, 40, 40, 40));
	vertices[4] = VTXCOLOR(_float3(0.5, 0, -18.2943), _float3(12.3017, -88.1518, 0.311778), D3DCOLOR_ARGB(255, 40, 40, 40));
	vertices[5] = VTXCOLOR(_float3(-0.187598, -23.8369, -93.1207), _float3(0.5, 1, 0), D3DCOLOR_ARGB(255, 40, 40, 40));
	vertices[6] = VTXCOLOR(_float3(88.1518, 0.5, 0), _float3(-56.2963, -4.57144, -90.5064), D3DCOLOR_ARGB(255, 40, 40, 40));
	vertices[7] = VTXCOLOR(_float3(1, -18.2943, 12.3017), _float3(-88.1518, 0.311778, 1), D3DCOLOR_ARGB(255, 40, 40, 40));
	vertices[8] = VTXCOLOR(_float3(-12.3017, 88.1518, 0.5), _float3(0, 0, 0), D3DCOLOR_ARGB(255, 40, 40, 40));
	vertices[9] = VTXCOLOR(_float3(-3.58732e-43, 0, 0), _float3(0, 0, 0), D3DCOLOR_ARGB(255, 40, 40, 40));
	vertices[10] = VTXCOLOR(_float3(0, 0, 0), _float3(0, 0, 0), D3DCOLOR_ARGB(255, 40, 40, 40));
	vertices[11] = VTXCOLOR(_float3(0, 0, 0), _float3(0, 0, 0), D3DCOLOR_ARGB(255, 40, 40, 40));
	m_pMesh->UnlockVertexBuffer();

	WORD* indices = 0;
	m_pMesh->LockIndexBuffer(0, (void**)&indices);

	indices[0] = 2;	indices[1] = 1;	indices[2] = 0;
	indices[3] = 5;	indices[4] = 4;	indices[5] = 3;
	indices[6] = 8;	indices[7] = 7;	indices[8] = 6;
	indices[9] = 11;	indices[10] = 10;	indices[11] = 9;
	m_pMesh->UnlockIndexBuffer();

	DWORD* attributeBuffer = 0;
	m_pMesh->LockAttributeBuffer(0, &attributeBuffer);

	for (int i = 0; i < 4; ++i)
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

	return S_OK;




}

HRESULT CMesh_SongShip::Initialize(void* pArg)
{
	return S_OK;
}

CMesh_SongShip* CMesh_SongShip::Create()
{
	CREATE_PIPELINE(CMesh_SongShip);
}

CComponent* CMesh_SongShip::Clone(void* pArg)
{
	CLONE_PIPELINE(CMesh_SongShip);
}

void CMesh_SongShip::Free()
{
	__super::Free();

	delete this;
}
