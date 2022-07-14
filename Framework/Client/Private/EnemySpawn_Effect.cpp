#include "stdafx.h"
#include "EnemySpawn_Effect.h"
#include "GameInstance.h"

CEnemySpawn_Effect::CEnemySpawn_Effect()
{
}

CEnemySpawn_Effect::CEnemySpawn_Effect(const CEnemySpawn_Effect& Prototype)
{
	*this = Prototype;
}

HRESULT CEnemySpawn_Effect::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CEnemySpawn_Effect::Initialize(void* pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_iTexture_Max = 0;
	
	return S_OK;
}

void CEnemySpawn_Effect::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
	m_fTime -= fTimeDelta;
	m_fRadian -= 90.f;
	if (m_fTime < 0.f)
	{
		Set_Enable(false);
	}
	m_pTransformCom->Scaling(_float3(20.f, 20.f, 20.f), true);
	_float3 vLook = m_pTransformCom->Get_World_State(CTransform::STATE_LOOK);
	m_pTransformCom->Turn(vLook, D3DXToRadian(m_fRadian), fTimeDelta, true);
	
	
}

void CEnemySpawn_Effect::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);


	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_ALPHABLEND, this);
}

HRESULT CEnemySpawn_Effect::Render_Begin(ID3DXEffect** Shader)
{
	return S_OK;
}

HRESULT CEnemySpawn_Effect::Render()
{
	
	m_pTransformCom->Bind_WorldMatrix();


	m_pRendererCom->Bind_Texture(0);

	//DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//DEVICE->SetRenderState(D3DRS_ALPHAREF, 0);
	//DEVICE->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	__super::Render();


	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	m_pRendererCom->UnBind_Texture();
	
	return S_OK;
}

void CEnemySpawn_Effect::SetUp_Components_For_Child()
{
	m_pRendererCom->Set_Textures_From_Key(TEXT("EnemySpawn_Effect"), MEMORY_TYPE::MEMORY_STATIC);
	

	m_pVIBufferCom = Add_Component<CVIBuffer_Rect>();
	WEAK_PTR(m_pVIBufferCom);
}

CEnemySpawn_Effect* CEnemySpawn_Effect::Create()
{
	CREATE_PIPELINE(CEnemySpawn_Effect);
}

CGameObject* CEnemySpawn_Effect::Clone(void* pArg)
{
	CLONE_PIPELINE(CEnemySpawn_Effect);
}

void CEnemySpawn_Effect::Free()
{
	__super::Free();

	delete this;
}
