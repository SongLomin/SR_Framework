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

	m_iTexture_Max = 47;
		
	return S_OK;
}

void CBomb_Effect::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
	++m_iTexture_Min;

	if (m_iTexture_Min == m_iTexture_Max)
	{
		Set_Dead();
	}
}

void CBomb_Effect::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);
}

HRESULT CBomb_Effect::Render_Begin(ID3DXEffect** Shader)
{
	return S_OK;
}

HRESULT CBomb_Effect::Render()
{
	m_pTransformCom->Bind_WorldMatrix();


	m_pRendererCom->Bind_Texture(m_iTexture_Min);

	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	DEVICE->SetRenderState(D3DRS_ALPHAREF, 253);
	DEVICE->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	__super::Render();

	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	m_pRendererCom->UnBind_Texture();
	
	return S_OK;
}

void CBomb_Effect::SetUp_Components_For_Child()
{
	m_pRendererCom->Set_Textures_From_Key(TEXT("Bomb_Effect"), MEMORY_TYPE::MEMORY_STATIC);
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
