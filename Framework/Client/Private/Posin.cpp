#include "stdafx.h"
#include "Posin.h"
#include "GameInstance.h"

CPosin::CPosin()
{
}

CPosin::CPosin(const CPosin& Prototype)
{
	*this = Prototype;
	Add_Component<CTransform>();
}

HRESULT CPosin::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CPosin::Initialize(void* pArg)
{

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_pRendererCom = Add_Component<CRenderer>();
	m_pRendererCom->Set_WeakPtr(&m_pRendererCom);


	m_pVIBufferCom = Add_Component<CVIBuffer_Rect>();
	m_pVIBufferCom->Set_WeakPtr(&m_pVIBufferCom);

	m_pTransformCom->Set_State(CTransform::STATE::STATE_POSITION, _float3(2.f, 1.5f, 0.f));
	m_pTransformCom->Scaling(_float3(0.5f, 0.5f, 0.5f));
	

	return S_OK;
}

void CPosin::Tick(_float fTimeDelta)
{
	if (GetKeyState('A') & 0x8000) 
	    m_pTransformCom->Turn(_float3(0.f, 1.f, 0.f), 10.f,fTimeDelta*-1);
    
	if (GetKeyState('D') & 0x8000) 
		m_pTransformCom->Turn(_float3(0.f, 1.f, 0.f), 10.f,fTimeDelta);
}

void CPosin::LateTick(_float fTimeDelta)
{
	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_NONALPHABLEND, this);
}

HRESULT CPosin::Render()
{
	m_pTransformCom->Bind_WorldMatrix();

	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	m_pRendererCom->Bind_Texture(1);
	m_pVIBufferCom->Render();
	m_pRendererCom->UnBind_Texture();

	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	return S_OK;
}



inline HRESULT CPosin::SetUp_Components()
{
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();

	/*CTransform::TRANSFORMDESC		TransformDesc;
	TransformDesc.fSpeedPerSec = 100.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(250.0f);*/

	m_pTransformCom = Get_Component<CTransform>();
	m_pTransformCom->Set_WeakPtr((void**)&m_pTransformCom);

	return S_OK;
}

void CPosin::LookAt_CamTPS()
{
}

CPosin* CPosin::Create()
{
	CREATE_PIPELINE(CPosin);
}

CGameObject* CPosin::Clone(void* pArg)
{
	CLONE_PIPELINE(CPosin);
}

void CPosin::Free()
{
	__super::Free();

	delete this;
}
