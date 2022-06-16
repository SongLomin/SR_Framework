#include "stdafx.h"
#include "Bullet.h"
#include "GameInstance.h"
#include "CameraPosin.h"


CBullet::CBullet()
{
}

CBullet::CBullet(const CBullet& Prototype)
{
	*this = Prototype;
}

HRESULT CBullet::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CBullet::Initialize(void* pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_pRendererCom = Add_Component<CRenderer>();
	m_pRendererCom->Set_WeakPtr(&m_pRendererCom);


	m_pVIBufferCom = Add_Component<CVIBuffer_Rect>();
	m_pVIBufferCom->Set_WeakPtr(&m_pVIBufferCom);

	return S_OK;
}

void CBullet::Tick(_float fTimeDelta)
{
	m_pTransformCom->Go_BackAndForth(80.f, fTimeDelta);
	m_pTransformCom->Turn(m_pTransformCom->Get_State(CTransform::STATE_LOOK), 10.f,fTimeDelta);
}

void CBullet::LateTick(_float fTimeDelta)
{
	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_NONALPHABLEND, this);
}

HRESULT CBullet::Render()
{
	m_pTransformCom->Bind_WorldMatrix();

	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	m_pRendererCom->Bind_Texture(1);
	m_pVIBufferCom->Render();
	m_pRendererCom->UnBind_Texture();

	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	return S_OK;
}



void CBullet::Link_CameraPosinTransform(CTransform* pTransform)
{
	m_pCameraPosinTransformCom = pTransform;

	m_pCameraPosinTransformCom->Set_WeakPtr(&m_pTransformCom);

	_float4x4 PosinMatrix = m_pCameraPosinTransformCom->Get_WorldMatrix();

	m_pTransformCom->Set_State(CTransform::STATE::STATE_RIGHT, _float3(PosinMatrix.m[0][0], PosinMatrix.m[0][1], PosinMatrix.m[0][2]));
	m_pTransformCom->Set_State(CTransform::STATE::STATE_UP, _float3(PosinMatrix.m[1][0], PosinMatrix.m[1][1], PosinMatrix.m[1][2]));
	m_pTransformCom->Set_State(CTransform::STATE::STATE_LOOK, _float3(PosinMatrix.m[2][0], PosinMatrix.m[2][1], PosinMatrix.m[2][2]));
	m_pTransformCom->Set_State(CTransform::STATE::STATE_POSITION, _float3(PosinMatrix.m[3][0], PosinMatrix.m[3][1], PosinMatrix.m[3][2]));
}

inline HRESULT CBullet::SetUp_Components()
{
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();

	m_pTransformCom = Get_Component<CTransform>();
	m_pTransformCom->Set_WeakPtr((void**)&m_pTransformCom);

	m_pTransformCom->Scaling(_float3(0.2f, 10.0f, 0.2f));

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



CBullet* CBullet::Create()
{
	CBullet* pInstance = new CBullet();

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CBullet");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CBullet::Clone(void* pArg)
{
	CBullet* pInstance = new CBullet();

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CBullet");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CBullet::Free()
{
	__super::Free();

	delete this;
}
