#include "stdafx.h"
#include "Cam_TPS.h"
#include "GameInstance.h"

CCam_TPS::CCam_TPS(const CCam_TPS& Prototype)
{
	*this = Prototype;
	Add_Component<CTransform>();
}

HRESULT CCam_TPS::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CCam_TPS::Initialize(void* pArg)
{
	//m_szName = L"Cam_TPS";
	/*CTransform::TRANSFORMDESC		TransformDesc;
	TransformDesc.fSpeedPerSec = 5.0f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f)*/;

	m_pTransformCom = Get_Component<CTransform>();
	m_pTransformCom->Set_WeakPtr(&m_pTransformCom);

	m_pCameraCom = Add_Component<CCamera>();
	m_pCameraCom->Set_WeakPtr(&m_pCameraCom);

	m_pCameraCom->Link_TransformCom(m_pTransformCom);

	/*Rigid_Body::RIGIDBODYDESC		RigidBodyDesc;
	RigidBodyDesc.m_fOwnerSpeed = 10.f;
	RigidBodyDesc.m_fOwnerRadSpeed = D3DXToRadian(90.0f);

	RigidBodyDesc.m_fFrictional = 0.5f;
	RigidBodyDesc.m_fRadFrictional = 0.1f;

	m_pRigidBodyCom = Add_Component<CRigid_Body>(&RigidBodyDesc);
	m_pRigidBodyCom->Set_WeakPtr(&m_pRigidBodyCom);
	m_pRigidBodyCom->Link_TransformCom(m_pTransformCom);

	m_pRigidBodyCom->Set_Camera();*/

	//m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(0.0, 0.f, 0.f));
	//m_pTransformCom->LookAt(_float3(0.f, 1.f, 0.f));



	return S_OK;
}

void CCam_TPS::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	_float3 vLook = m_pCameraCom->Get_Target()->Get_State(CTransform::STATE_LOOK, true);
	_float3 vPos = m_pCameraCom->Get_Target()->Get_State(CTransform::STATE_POSITION, true);
	_float3 vPlayerPos = vPos;
	_float3 vUp = _float3(0.f, 1.f, 0.f);
	_float3 vRight;

	vPos -= vLook*10.f;
	vPos += vUp*2.f;

	D3DXVec3Cross(&vRight, &vUp, &vLook);
	D3DXVec3Cross(&vUp, &vLook, &vRight);

	
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, vLook);
	m_pTransformCom->Set_State(CTransform::STATE_UP, vUp);
	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, vRight);

	
	//m_pRigidBodyCom->Set_DirVector();

	if (GAMEINSTANCE->Get_Camera(CURRENT_CAMERA) == m_pCameraCom)
	{

		POINT ptMouse{ 0, 0 };

		POINT pt{};
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		_float fDirX = pt.x - g_iWinCX*0.5f;
		_float fDirY = pt.y - g_iWinCY*0.5f;

		vPos += vRight*fDirX*0.01f;
		vPos -= vUp*fDirY*0.01f;

	}
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, vPos);
	//m_pTransformCom->LookAt(vPlayerPos);
	m_pTransformCom->Update_WorldMatrix();
}

void CCam_TPS::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);
	
	//m_pRigidBodyCom->Update_Transform(fTimeDelta);
}

HRESULT CCam_TPS::Render()
{
	__super::Render();

	return S_OK;
}

CCam_TPS* CCam_TPS::Create()
{
	CREATE_PIPELINE(CCam_TPS);
}

CGameObject* CCam_TPS::Clone(void* pArg)
{
	CLONE_PIPELINE(CCam_TPS);
}

void CCam_TPS::Free()
{
	__super::Free();

	delete this;
}
