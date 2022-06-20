#include "stdafx.h"
#include "Cam_Shoulder.h"
#include "GameInstance.h"

CCam_Shoulder::CCam_Shoulder(const CCam_Shoulder& Prototype)
{
	*this = Prototype;
	//m_szName = L"Cam_Shoulder";
	Add_Component<CTransform>();
}

HRESULT CCam_Shoulder::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CCam_Shoulder::Initialize(void* pArg)
{

	m_pTransformCom = Get_Component<CTransform>();
	m_pTransformCom->Set_WeakPtr(&m_pTransformCom);

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(0.f, 1.f, 0.f));
	m_pTransformCom->LookAt(_float3(0.f, 1.f, 1.f));

	m_pCameraCom = Add_Component<CCamera>();
	m_pCameraCom->Set_WeakPtr(&m_pCameraCom);
	m_pCameraCom->Link_TransformCom(m_pTransformCom);

	////////////////
	//CRigid_Body::RIGIDBODYDESC		RigidBodyDesc;
	//RigidBodyDesc.m_fOwnerSpeed = 7.f;
	//RigidBodyDesc.m_fOwnerRadSpeed = D3DXToRadian(90.0f);
	//
	//RigidBodyDesc.m_fFrictional = 0.1f;
	//RigidBodyDesc.m_fRadFrictional = 0.1f;
	//
	//m_pRigidBodyCom = Add_Component<CRigid_Body>(&RigidBodyDesc);
	//m_pRigidBodyCom->Set_WeakPtr(&m_pRigidBodyCom);
	//m_pRigidBodyCom->Link_TransformCom(m_pTransformCom);
	//////////////////

	return S_OK;
}


void CCam_Shoulder::Tick(_float fTimeDelta)
{
	m_pTransformCom->Update_WorldMatrix();

	if (GAMEINSTANCE->Get_Camera(CURRENT_CAMERA) == m_pCameraCom)
	{
		_float3 pos = m_pTransformCom->Get_State(CTransform::STATE_POSITION);

		if (pos.x > 0.99f || pos.z < -0.99f || m_fAngle < 30.f)
		{
			
			m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(1.f, 1.f, -1.f));
			m_pTransformCom->LookAt(_float3(1.f, 1.f, 0.f));
		}
		else
		{
			pos.x += 0.01f;
			pos.z -= 0.01f;
			m_fAngle -= 2.f;
			m_pCameraCom->Set_Param(D3DXToRadian(m_fAngle), (_float)g_iWinCX / g_iWinCY, 0.2f, 300.f);
			m_pTransformCom->Set_State(CTransform::STATE_POSITION, pos);
		}
		/*if (FAILED(m_pCameraCom->Bind_PipeLine()))
			return;*/
	}
	else
	{
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(0.f, 1.f, 0.f));
		m_pTransformCom->LookAt(_float3(0.f, 1.f, 1.f));
		m_fAngle = 65.f;
	}
}

void CCam_Shoulder::LateTick(_float fTimeDelta)
{
}

HRESULT CCam_Shoulder::Render()
{
	return S_OK;
}


CCam_Shoulder* CCam_Shoulder::Create()
{
	CREATE_PIPELINE(CCam_Shoulder);
}

CGameObject* CCam_Shoulder::Clone(void* pArg)
{
	CLONE_PIPELINE(CCam_Shoulder);
}

void CCam_Shoulder::Free()
{
	__super::Free();

	delete this;
}
