#include "stdafx.h"
#include "Bomb_Effect.h"
#include "GameInstance.h"

CBomb_Effect::CBomb_Effect()
{
}

CBomb_Effect::CBomb_Effect(const CBomb_Effect& Prototype)
{
	*this = Prototype;
}

HRESULT CBomb_Effect::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CBomb_Effect::Initialize(void* pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_iTexture_Max = 90;
		
	return S_OK;
}

void CBomb_Effect::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
	++m_iTexture_Min;

	if (m_iTexture_Min == m_iTexture_Max)
	{
		Set_Enable(false);
		m_iTexture_Min = 0;
	}
}

void CBomb_Effect::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_NONALPHABLEND, this);
}

HRESULT CBomb_Effect::Render_Begin(ID3DXEffect** Shader)
{
	return S_OK;
}

HRESULT CBomb_Effect::Render()
{
	m_pTransformCom->Scaling(_float3(30.f, 30.f, 30.f), true);
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

void CBomb_Effect::SetUp_Components_For_Child()
{
	m_pRendererCom->Set_Textures_From_Key(TEXT("Bomb_Effect"), MEMORY_TYPE::MEMORY_STATIC);

	m_pVIBufferCom = Add_Component<CVIBuffer_Rect>();
	WEAK_PTR(m_pVIBufferCom);
}

CBomb_Effect* CBomb_Effect::Create()
{
	CREATE_PIPELINE(CBomb_Effect);
}

CGameObject* CBomb_Effect::Clone(void* pArg)
{
	CLONE_PIPELINE(CBomb_Effect);
}

void CBomb_Effect::Free()
{
	__super::Free();

	delete this;
}
