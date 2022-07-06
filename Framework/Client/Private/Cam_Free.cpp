#include "stdafx.h"
#include "Cam_Free.h"
#include "GameInstance.h"

CCam_Free::CCam_Free(const CCam_Free& Prototype)
{
	*this = Prototype;
	Add_Component<CTransform>();
}

HRESULT CCam_Free::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CCam_Free::Initialize(void* pArg)
{
	m_pTransformCom = Add_Component<CTransform>();
	m_pTransformCom->Set_WeakPtr(&m_pTransformCom);

	m_pCameraCom = Add_Component<CCamera>();
	m_pCameraCom->Set_WeakPtr(&m_pCameraCom);
	
	m_pCameraCom->Link_TransformCom(m_pTransformCom);

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(0.0, 3.f, -3.f));
	m_pTransformCom->LookAt(_float3(0.f, 0.f, 0.f));

	return S_OK;
}

void CCam_Free::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	if (0.f > m_fTime)
	{
		GAMEINSTANCE->Set_Current_Camera(m_NextCameraTag);
		return;
	}
	m_fTime -= fTimeDelta;

	m_vLook += m_vdLook;
	m_vUp+= m_vdUp;
	m_vRight+= m_vdRight;
	m_vPos += m_vdPos;

	m_pTransformCom->Set_State(CTransform::STATE_LOOK, m_vLook);
	m_pTransformCom->Set_State(CTransform::STATE_UP, m_vUp);
	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, m_vRight);
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_vPos);

	m_pTransformCom->Update_WorldMatrix();

}

void CCam_Free::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);
}

HRESULT CCam_Free::Render()
{
	__super::Render();

	return S_OK;
}

void CCam_Free::Set_RouteCamera(CCamera* _pCurCamera, _tchar* _NextCameraTag, _float _fTime)
{
	m_NextCameraTag = _NextCameraTag;
	CCamera* pCamera = GAMEINSTANCE->Get_Camera(_NextCameraTag);
	m_pNextCameraTransform= pCamera->Get_Owner()->Get_Component<CTransform>();
	m_pCurCameraTransform = _pCurCamera->Get_Owner()->Get_Component<CTransform>();

	m_fTime = _fTime;

	Make_Route();
}

void CCam_Free::Make_Route()
{
	if (m_fTime)//m_fTime이 0이 아닌 경우가 없
	{
		m_vLook = m_pCurCameraTransform->Get_World_State(CTransform::STATE_LOOK);
		m_vUp = m_pCurCameraTransform->Get_World_State(CTransform::STATE_UP);
		m_vRight = m_pCurCameraTransform->Get_World_State(CTransform::STATE_RIGHT);
		m_vPos =  m_pCurCameraTransform->Get_World_State(CTransform::STATE_POSITION);

		m_vdLook	 = m_pNextCameraTransform->Get_World_State(CTransform::STATE_LOOK) - m_vLook;
		m_vdUp	 = m_pNextCameraTransform->Get_World_State(CTransform::STATE_UP) - m_vUp;
		m_vdRight = m_pNextCameraTransform->Get_World_State(CTransform::STATE_RIGHT) - m_vRight;
		m_vdPos	 = m_pNextCameraTransform->Get_World_State(CTransform::STATE_POSITION) - m_vPos;

		m_vdLook /= m_fTime;
		m_vdUp/= m_fTime;
		m_vdRight/= m_fTime;
		m_vdPos /= m_fTime;

	}
}

CCam_Free* CCam_Free::Create()
{
	CREATE_PIPELINE(CCam_Free);
}

CGameObject* CCam_Free::Clone(void* pArg)
{
	CLONE_PIPELINE(CCam_Free);
}

void CCam_Free::Free()
{
	__super::Free();

	delete this;
}
