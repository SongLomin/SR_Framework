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

HRESULT CMesh::Render_Mesh()
{
	if (nullptr == LPDEVICE)
		return E_FAIL;

	for (_ulong i = 0; i < m_dwNumSubsets; ++i)
	{
		if(m_vTextures)
			DEVICE->SetTexture(0, (*m_vTextures)[6]);
		//DEVICE->SetMaterial(m_vMtrl[i]);
		m_pMesh->DrawSubset(i);
	}
	DEVICE->SetTexture(0, 0);

	return S_OK;
}

HRESULT CMesh::Set_Texture(const _tchar* _Str_Key, MEMORY_TYPE _eType)
{
	m_vTextures = GAMEINSTANCE->Get_Textures_From_Key(_Str_Key, _eType);

	
	return S_OK;
}

ID3DXMesh* CMesh::Get_Mesh()
{
	return m_pMesh;
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

	if(m_pMesh)
		m_pMesh->Release();

}

