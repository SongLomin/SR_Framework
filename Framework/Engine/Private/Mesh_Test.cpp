#include "Mesh_Test.h"
#include"GameInstance.h"

CMesh_Test::CMesh_Test()
{
}

CMesh_Test::CMesh_Test(const CMesh_Test& Prototype)
{
    *this = Prototype;
}

HRESULT CMesh_Test::Initialize_Prototype()
{


	return S_OK;
}

HRESULT CMesh_Test::Initialize(void* pArg)
{
	D3DXCreateBox(DEVICE, 1, 1, 1, &m_pMesh, nullptr);

    return S_OK;
}

HRESULT CMesh_Test::Render_Mesh()
{
	DEVICE->SetFVF(D3DFVF_XYZ | D3DFVF_NORMAL);
	m_pMesh->DrawSubset(0);

	return S_OK;
}

CMesh_Test* CMesh_Test::Create()
{
	CREATE_PIPELINE(CMesh_Test);
}

CComponent* CMesh_Test::Clone(void* pArg)
{
	CLONE_PIPELINE(CMesh_Test);
}

void CMesh_Test::Free()
{
	__super::Free();

	delete this;

}
