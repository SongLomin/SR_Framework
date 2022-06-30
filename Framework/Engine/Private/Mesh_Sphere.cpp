#include "Mesh_Sphere.h"
#include "GameInstance.h"

CMesh_Sphere::CMesh_Sphere()
{
}

CMesh_Sphere::CMesh_Sphere(const CMesh_Sphere& Prototype)
{
	*this = Prototype;
}

HRESULT CMesh_Sphere::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CMesh_Sphere::Initialize(void* pArg)
{
	D3DXCreateSphere(DEVICE, 1, 20, 20, &m_pMesh, NULL);
	return S_OK;
}

HRESULT CMesh_Sphere::Render_Mesh()
{
	
	DEVICE->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
	m_pMesh->DrawSubset(0);

	return S_OK;
}

CMesh_Sphere* CMesh_Sphere::Create()
{
	CREATE_PIPELINE(CMesh_Sphere);
}

CComponent* CMesh_Sphere::Clone(void* pArg)
{
	CLONE_PIPELINE(CMesh_Sphere);
}

void CMesh_Sphere::Free()
{
	__super::Free();

	delete this;
}
