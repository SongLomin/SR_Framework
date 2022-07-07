#include "stdafx.h"
#include "Teleport_Effect.h"
#include "GameInstance.h"

CTeleport_Effect::CTeleport_Effect()
{
}

CTeleport_Effect::CTeleport_Effect(const CTeleport_Effect& Prototype)
{
	*this = Prototype;
}

HRESULT CTeleport_Effect::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CTeleport_Effect::Initialize(void* pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_iTexture_Max = 7;

	return S_OK;
}

void CTeleport_Effect::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
	++m_iTexture_Min;

	if (m_iTexture_Min == m_iTexture_Max)
	{
		Set_Enable(false);
		m_iTexture_Min = 0;
	}
}

void CTeleport_Effect::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_NONALPHABLEND, this);
}

HRESULT CTeleport_Effect::Render_Begin(ID3DXEffect** Shader)
{
	return S_OK;
}

HRESULT CTeleport_Effect::Render()
{

	//m_pTransformCom->Scaling(_float3(15.f, 15.f, 15.f), true);
	m_pTransformCom->Bind_WorldMatrix();


	m_pRendererCom->Bind_Texture(m_iTexture_Min);

	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	DEVICE->SetRenderState(D3DRS_ALPHAREF, 0);
	DEVICE->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	__super::Render();


	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	m_pRendererCom->UnBind_Texture();

	return S_OK;
}

void CTeleport_Effect::SetUp_Components_For_Child()
{
	m_pRendererCom->Set_Textures_From_Key(TEXT("Teleport_Effect"), MEMORY_TYPE::MEMORY_STATIC);

	m_pVIBufferCom = Add_Component<CVIBuffer_Rect>();
	WEAK_PTR(m_pVIBufferCom);
}

CTeleport_Effect* CTeleport_Effect::Create()
{
	CREATE_PIPELINE(CTeleport_Effect);
}

CGameObject* CTeleport_Effect::Clone(void* pArg)
{
	CLONE_PIPELINE(CTeleport_Effect);
}

void CTeleport_Effect::Free()
{
	__super::Free();

	delete this;
}
