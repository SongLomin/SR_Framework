#include "stdafx.h"
#include "Terrain.h"
#include "GameInstance.h"
#include "Mesh_Cube.h"

CTerrain::CTerrain(const CTerrain& Prototype)
{
	*this = Prototype;
	Add_Component<CTransform>();
}

HRESULT CTerrain::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CTerrain::Initialize(void* pArg)
{
	m_pRendererCom = Add_Component<CRenderer>();
	m_pRendererCom->Set_WeakPtr(&m_pRendererCom);

	m_pRendererCom->Set_Textures_From_Key(TEXT("Tex_Terrain"), MEMORY_TYPE::MEMORY_DYNAMIC);

	m_pTransformCom = Get_Component<CTransform>();
	m_pTransformCom->Set_WeakPtr(&m_pTransformCom);

	_point TerrainCnt;
	TerrainCnt.x = 100;
	TerrainCnt.y = 100;

	m_pVIBufferCom = Add_Component<CVIBuffer_Terrain>(&TerrainCnt);
	m_pVIBufferCom->Set_WeakPtr(&m_pVIBufferCom);

	m_pMeshCom = Add_Component<CMesh_Terrain>(&TerrainCnt);
	m_pMeshCom->Set_WeakPtr(&m_pMeshCom);
	m_pMeshCom->Set_Texture(TEXT("Mesh_Cube"), MEMORY_TYPE::MEMORY_STATIC);

	//m_pTransformCom->Set_State(CTransform::STATE::STATE_POSITION, _float3(2.f, 0.f, 0.f));

	return S_OK;
}

void CTerrain::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
}

void CTerrain::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_NONALPHABLEND, this);
}

HRESULT CTerrain::Render()
{
	

	m_pTransformCom->Bind_WorldMatrix();

	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	DEVICE->SetRenderState(D3DRS_FILLMODE, D3DFILLMODE::D3DFILL_WIREFRAME);
	m_pRendererCom->Bind_Texture(0);

	__super::Render();
	
	
	//m_pMeshCom->Render_Mesh();

	DEVICE->SetRenderState(D3DRS_FILLMODE, D3DFILLMODE::D3DFILL_SOLID);

	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	m_pRendererCom->UnBind_Texture();


	return S_OK;
}

CTerrain* CTerrain::Create()
{
	CREATE_PIPELINE(CTerrain);
}

CGameObject* CTerrain::Clone(void* pArg)
{
	CLONE_PIPELINE(CTerrain);
}

void CTerrain::Free()
{
	__super::Free();

	delete this;
}
