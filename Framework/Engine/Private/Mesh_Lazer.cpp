#include "Mesh_Lazer.h"
#include "GameInstance.h"

CMesh_Lazer::CMesh_Lazer()
{
}

CMesh_Lazer::CMesh_Lazer(const CMesh_Lazer& Prototype)
{
	*this = Prototype;


	if (!m_pMesh)
	{
		return;
	}

	ID3DXMesh* pCloneMesh = nullptr;
	m_pMesh->CloneMeshFVF(m_pMesh->GetOptions(), m_pMesh->GetFVF(), DEVICE, &pCloneMesh);
	m_pMesh = pCloneMesh;
}

HRESULT CMesh_Lazer::Initialize_Prototype()
{

	m_iNumVertices = 12;
	m_iNumPrimitive = 104;
	m_dwFVF = VTXDEFAULT::FVF;

	m_dwNumSubsets = 1;
	if (FAILED(Create_EmptyMesh()))
	{
		MSG_BOX("Failed to Create_EmptyMesh : CMesh_Cube");
		return E_FAIL;
	}
	VTXDEFAULT* vertices = nullptr;
	m_pMesh->LockVertexBuffer(0, (void**)&vertices);


	m_pMesh->UnlockVertexBuffer();

	WORD* indices = 0;
	m_pMesh->LockIndexBuffer(0, (void**)&indices);

	return S_OK;
}

HRESULT CMesh_Lazer::Initialize(void* pArg)
{
	return S_OK;
}

HRESULT CMesh_Lazer::Render_Mesh()
{
	DEVICE->SetFVF(D3DFVF_XYZ | D3DFVF_NORMAL);
	m_pMesh->DrawSubset(0);

	return S_OK;
}

CMesh_Lazer* CMesh_Lazer::Create()
{
	CREATE_PIPELINE(CMesh_Lazer);
}

CComponent* CMesh_Lazer::Clone(void* pArg)
{
	CLONE_PIPELINE(CMesh_Lazer);
}

void CMesh_Lazer::Free()
{
	__super::Free();

	delete this;
}
