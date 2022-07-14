#include "Cam_Free.h"
#include "GameInstance.h"

CCam_Free::CCam_Free(const CCam_Free& Prototype)
{
	*this = Prototype;

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

	/*m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(0.0, 3.f, -3.f));
	m_pTransformCom->LookAt(_float3(0.f, 0.f, 0.f));*/

	return S_OK;
}

void CCam_Free::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	//if (!m_bFlag)
	//	return;//안 해주면 Weak_ptr계속 걸림

	//if (m_bSwitchPlayer)
	//{
	//	Switch_PlayerCamera(fTimeDelta);
	//}
	//else
	//{
	//	Swap_Camera(fTimeDelta);
	//}

	_float3 vDir = m_pNextCameraTransform->Get_State(CTransform::STATE::STATE_POSITION, true);
	D3DXVec3Normalize(&vDir, &vDir);

	m_pTransformCom->Add_Position(vDir * fTimeDelta, true);
	
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

//void CCam_Free::Set_RouteCamera(CCamera* _pCurCamera, const _tchar* _NextCameraTag, _float _fTime)
//{
//	m_NextCameraTag = _NextCameraTag;
//	CCamera* pCamera = GAMEINSTANCE->Get_Camera(_NextCameraTag);
//	m_pNextCameraTransform = pCamera->Get_Owner()->Get_Component<CTransform>();
//	m_pCurCameraTransform = _pCurCamera->Get_Owner()->Get_Component<CTransform>()->Get_WorldMatrix();
//
//	m_fTime = _fTime;
//
//	Make_Route();
//	m_bFlag = true;
//}
//
//void CCam_Free::Switch_Player(_float4x4 _pCurCamera, CTransform* _pNextCamera, const _tchar* _NextCameraTag, _float fTime)
//{
//	m_NextCameraTag = _NextCameraTag;
//	m_pCurCameraTransform = _pCurCamera;
//	if (m_pNextCameraTransform)
//		RETURN_WEAKPTR(m_pNextCameraTransform);
//	m_pNextCameraTransform = _pNextCamera;
//	WEAK_PTR(m_pNextCameraTransform);
//	m_fTime = fTime;
//
//	m_bFlag = true;
//	m_bSwitchPlayer = true;
//	Make_Route();
//}
//
//void CCam_Free::Make_Route()
//{
//	if (m_fTime)//m_fTime이 0이 아닌 경우가 없
//	{
//		m_vLook = *(_float3*)& m_pCurCameraTransform.m[2];
//		m_vUp = *(_float3*)&m_pCurCameraTransform.m[1];
//		m_vRight = *(_float3*)&m_pCurCameraTransform.m[0];
//		m_vPos = *(_float3*)&m_pCurCameraTransform.m[3];
//		if (m_bSwitchPlayer)
//		{
//			m_pNextCameraTransform->Get_Owner()->Set_Controller(CONTROLLER::LOCK);
//			m_pNextCameraTransform->Get_Owner()->Get_Component<CRigid_Body>()->Reset_Force();
//			m_pNextCameraTransform->Set_State(CTransform::STATE_LOOK, m_vLook);
//			m_pNextCameraTransform->Set_State(CTransform::STATE_UP, m_vUp);
//			m_pNextCameraTransform->Set_State(CTransform::STATE_RIGHT, m_vRight);
//
//			/*m_vPos -= m_vLook * 15.f;
//			m_vPos += m_vUp * 3.f;*/
//			m_fTime = m_fLerpTime;
//		}
//
//	}
//}
//
//void CCam_Free::Switch_PlayerCamera(_float fTimeDelta)
//{
//	POINT pt{};
//
//	GRAPHICDESC GraphicDesc = GAMEINSTANCE->Get_Graphic_Desc();
//	
//	pt.x = GraphicDesc.iWinCX * 0.5f;
//	pt.y = GraphicDesc.iWinCY * 0.5f;
//
//	ClientToScreen(GraphicDesc.hWnd, &pt);
//	SetCursorPos(pt.x, pt.y);
//
//	m_pNextCameraTransform->Set_State(CTransform::STATE_LOOK, m_vLook);
//	m_pNextCameraTransform->Set_State(CTransform::STATE_UP, m_vUp);
//	m_pNextCameraTransform->Set_State(CTransform::STATE_RIGHT, m_vRight);
//
//	_float3 vPos = m_pNextCameraTransform->Get_State(CTransform::STATE_POSITION);
//	_float3 vLook = m_pNextCameraTransform->Get_State(CTransform::STATE_LOOK);
//	_float3 vUp = m_pNextCameraTransform->Get_State(CTransform::STATE_UP);
//	
//	vPos -= vLook * 15.f;
//	vPos += vUp * 3.f;
//
//	
//
//	_float fDistance = D3DXVec3Length(&(m_vPos - vPos));
//	if (!(0.1f < fDistance))
//	{
//		m_pNextCameraTransform->Get_Owner()->Set_Controller(CONTROLLER::PLAYER);
//		m_bFlag = false;
//		m_bSwitchPlayer = false;
//		return;
//	}
//
//	m_fTime -= fTimeDelta;
//	if (0.f > m_fTime)
//	{
//		m_vPos.x = CMath_Utillity::fLerp(m_vPos.x, vPos.x, 0.5f);
//		m_vPos.y = CMath_Utillity::fLerp(m_vPos.y, vPos.y, 0.5f);
//		m_vPos.z = CMath_Utillity::fLerp(m_vPos.z, vPos.z, 0.5f);
//				
//		m_fTime = m_fLerpTime;
//	}
//
//	
//	m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_vPos);
//
//}
//
//void CCam_Free::Swap_Camera(_float fTimeDelta)
//{
//	m_fTime -= fTimeDelta;
//
//	if (0.f > m_fTime)
//	{
//		GAMEINSTANCE->Add_Shaking(0.f, 0.f);
//		m_pNextCameraTransform->Get_Owner()->Set_Controller(CONTROLLER::PLAYER);
//		GAMEINSTANCE->Set_Current_Camera(m_NextCameraTag);
//		m_fTime = 0.f;
//		m_bFlag = false;
//		m_bSwitchPlayer = false;
//		return;
//	}
//
//
//	_float3 vLook = m_pNextCameraTransform->Get_World_State(CTransform::STATE_LOOK);
//	_float3 vUp = m_pNextCameraTransform->Get_World_State(CTransform::STATE_UP);
//
//	m_vdLook = vLook - m_vLook;
//	m_vdUp = vUp - m_vUp;
//	m_vdRight = m_pNextCameraTransform->Get_World_State(CTransform::STATE_RIGHT) - m_vRight;
//	m_vdPos = m_pNextCameraTransform->Get_World_State(CTransform::STATE_POSITION);
//	m_vdPos += vUp * 3.f;
//	
//	m_vdPos -= m_vPos;
//
//	m_vdLook /= m_fTime;
//	m_vdUp /= m_fTime;
//	m_vdRight /= m_fTime;
//	m_vdPos /= m_fTime;
//
//	m_vLook += m_vdLook * fTimeDelta;
//	m_vUp += m_vdUp * fTimeDelta;
//	m_vRight += m_vdRight * fTimeDelta;
//	m_vPos += m_vdPos * fTimeDelta;
//
//	m_pTransformCom->Set_State(CTransform::STATE_LOOK, m_vLook);
//	m_pTransformCom->Set_State(CTransform::STATE_UP, m_vUp);
//	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, m_vRight);
//	m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_vPos);
//}


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

	RETURN_WEAKPTR(m_pNextCameraTransform);

	delete this;
}
