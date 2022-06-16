#include "stdafx.h"
#include "Terrain.h"
#include "GameInstance.h"

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

	//m_pTransformCom->Set_State(CTransform::STATE::STATE_POSITION, _float3(2.f, 0.f, 0.f));

	return S_OK;
}

void CTerrain::Tick(_float fTimeDelta)
{
}

void CTerrain::LateTick(_float fTimeDelta)
{
	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_PRIORITY, this);
}

HRESULT CTerrain::Render()
{
	m_pTransformCom->Bind_WorldMatrix();

	m_pRendererCom->Bind_Texture(0);
	
	m_pVIBufferCom->Render();

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
