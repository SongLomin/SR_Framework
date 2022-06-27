#include "stdafx.h"
#include "..\Public\MovingCamera.h"
#include "GameInstance.h"
#include "Camera_Manager.h"


CMovingCamera::CMovingCamera()
{

}

CMovingCamera::CMovingCamera(const CMovingCamera & Prototype)
{
	*this = Prototype;
}

HRESULT CMovingCamera::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CMovingCamera::Initialize(void * pArg)
{
	m_pTransformCom = Add_Component<CTransform>();
	m_pTransformCom->Set_WeakPtr(&m_pTransformCom);

	m_pCameraCom = Add_Component<CCamera>();
	m_pCameraCom->Set_WeakPtr(&m_pCameraCom);
	m_pCameraCom->Link_TransformCom(m_pTransformCom);

	GAMEINSTANCE->Set_MovingCam(this);

	return S_OK;
}

void CMovingCamera::Tick(_float fTimeDelta)
{

	if (!m_bFlag)
		return;

	if (0.f > m_CameraRoute.fTime )
	{
		GAMEINSTANCE->Swap_Camera();
		m_bFlag = false;
	}


	m_CameraRoute.fTime -= fTimeDelta;
	m_pTransformCom->Update_WorldMatrix();
	

	_float3 vPosition = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
	vPosition += m_CameraRoute.m_vSpeed*fTimeDelta;

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, vPosition);
	m_pTransformCom->LookAt(m_pEndTransform, true);

}

void CMovingCamera::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

}

HRESULT CMovingCamera::Render_Begin()
{
	
	return S_OK;
}

HRESULT CMovingCamera::Render()
{
	__super::Render();

	return S_OK;
}


void CMovingCamera::Add_Movement(CTransform* _pStartTarget, CTransform* _pEndTarget, CAMERAROUTE _tagRoute)
{
	if (CMovingCamera::CAMERAMOVING::CAMERA_MOVE == _tagRoute.eMoveType)
	{
		_float3 vecStartPos = _pStartTarget->Get_World_State(CTransform::STATE_POSITION);
		_float3 vecEndPos = _pEndTarget->Get_World_State(CTransform::STATE_POSITION);

		_float3 vRoute = vecEndPos - vecStartPos;

		_tagRoute.m_vSpeed = -1.f * vRoute * 2 / (_tagRoute.fTime);
		_tagRoute.m_vAccel = 2 * vRoute / (_tagRoute.fTime * _tagRoute.fTime);
	}

	else if (CMovingCamera::CAMERAMOVING::CAMERA_STAY == _tagRoute.eMoveType)
	{
		_tagRoute.m_vSpeed = _tagRoute.m_vAccel = _float3(0.f, 0.f, 0.f);
	}

	m_vecRoute.push_back(_tagRoute);
}

void CMovingCamera::Boss_Cinematic(CTransform* _pBossTarget)
{
	m_pEndTransform = _pBossTarget;

	D3DXMATRIX	matTarget = _pBossTarget->Get_WorldMatrix();

	m_pTransformCom->Set_State(CTransform::STATE_RIGHT,*(_float3*)&matTarget.m[0]);
	m_pTransformCom->Set_State(CTransform::STATE_UP,*(_float3*)&matTarget.m[1]);
	m_pTransformCom->Set_State(CTransform::STATE_LOOK,*(_float3*)&matTarget.m[2]);
	_float3 vRight = *(_float3*)&matTarget.m[0];
	_float3 vPosition = *(_float3*)&matTarget.m[3];
	_float3 vLook = *(_float3*)&matTarget.m[2];
	vPosition += vLook * 15.f;

	m_pTransformCom->Set_State(CTransform::STATE_POSITION,vPosition);
	m_pTransformCom->LookAt(*(_float3*)&matTarget.m[3], true);


	m_CameraRoute.fTime = 10.f;
	m_CameraRoute.fAngle = D3DXToRadian(30.f);

	m_CameraRoute.eMoveType = CAMERAMOVING::CAMERA_END;
	m_CameraRoute.eLookType = CAMERALOOK::LOOK_END;

	m_CameraRoute.m_vAccel =  _float3(0.f, 0.f, 0.f);
	m_CameraRoute.m_vSpeed = vRight;
	GAMEINSTANCE->Update_MovingCam();
	m_bFlag = true;
}

void CMovingCamera::Monster_Cinematic(CTransform* _pBossTarget)
{

}

CMovingCamera * CMovingCamera::Create()
{
	CREATE_PIPELINE(CMovingCamera);
}

CGameObject * CMovingCamera::Clone(void * pArg)
{
	CLONE_PIPELINE(CMovingCamera);
}

void CMovingCamera::Free()
{
	__super::Free();

	delete this;
}

