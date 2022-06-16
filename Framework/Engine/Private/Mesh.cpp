#include "..\Public\Mesh.h"
#include "GameInstance.h"


CMesh::CMesh()
{
}

CMesh::CMesh(const CMesh & Prototype)
{
	*this = Prototype;
}

HRESULT CMesh::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CMesh::Initialize(void * pArg)
{
	return S_OK;
}

HRESULT CMesh::Render()
{
	if (nullptr == LPDEVICE)
		return E_FAIL;

	for (_ulong i = 0; i < m_dwNumSubsets; ++i)
	{
		DEVICE->SetTexture(0, (*m_vTextures)[i]);
		//DEVICE->SetMaterial(m_vMtrl[i]);
		m_pMesh->DrawSubset(i);
	}
		DEVICE->SetTexture(0, 0);

	return S_OK;
}

HRESULT CMesh::Create_EmptyMesh()
{
	if (nullptr == LPDEVICE)
		return E_FAIL;

	if (FAILED(D3DXCreateMeshFVF(
		m_iNumPrimitive,
		m_iNumVertices,
		D3DXMESH_MANAGED,
		m_dwFVF,
		DEVICE,
		&m_pMesh)))
		return E_FAIL;

	return S_OK;
}

void CMesh::Free()
{
	__super::Free();

	
	m_pMesh->Release();

}

