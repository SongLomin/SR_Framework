#include "stdafx.h"
#include "Ring.h"
#include "GameInstance.h"

CRing::CRing()
{
}

CRing::CRing(const CRing& Prototype)
{
	*this = Prototype;
}

HRESULT CRing::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CRing::Initialize(void* pArg)
{

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_pRendererCom = Add_Component<CRenderer>();
	m_pRendererCom->Set_WeakPtr(&m_pRendererCom);


	m_pVIBufferCom = Add_Component<CVIBuffer_Rect>();
	m_pVIBufferCom->Set_WeakPtr(&m_pVIBufferCom);

	
	
	return S_OK;
}

void CRing::Tick(_float fTimeDelta)
{
	m_pTransformCom->Go_BackAndForth(8.f, fTimeDelta);
	m_pTransformCom->Turn(_float3(0.f, 1.f, 0.f), 3.f,fTimeDelta);
}

void CRing::LateTick(_float fTimeDelta)
{
	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_NONALPHABLEND, this);
}

HRESULT CRing::Render()
{
	m_pTransformCom->Bind_WorldMatrix();

	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	m_pRendererCom->Bind_Texture(1);
	m_pVIBufferCom->Render();
	m_pRendererCom->UnBind_Texture();

	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	return S_OK;
}



inline HRESULT CRing::SetUp_Components()
{
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();

	m_pTransformCom = Get_Component<CTransform>();
	m_pTransformCom->Set_WeakPtr((void**)&m_pTransformCom);

	m_pTransformCom->Set_State(CTransform::STATE::STATE_POSITION, _float3(-1.5f, 1.0f, 0.f));
	m_pTransformCom->Scaling(_float3(0.5f, 0.5f, 0.5f));


	CRigid_Body::RIGIDBODYDESC		RigidBodyDesc;
	RigidBodyDesc.m_fOwnerSpeed = 10.f;
	RigidBodyDesc.m_fOwnerRadSpeed = D3DXToRadian(90.0f);

	RigidBodyDesc.m_fFrictional = 0.05f;
	RigidBodyDesc.m_fRadFrictional = 0.05f;

	m_pRigidBodyCom = Add_Component<CRigid_Body>(&RigidBodyDesc);
	m_pRigidBodyCom->Set_WeakPtr(&m_pRigidBodyCom);
	m_pRigidBodyCom->Link_TransformCom(m_pTransformCom);

	

	return S_OK;
}



CRing* CRing::Create()
{
	CRing* pInstance = new CRing();

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CRing");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CRing::Clone(void* pArg)
{
	CRing* pInstance = new CRing();

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CRing");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CRing::Free()
{
	__super::Free();

	delete this;
}
