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

	if (0.f > m_CameraRoute.fTime)
	{
		if (!m_listRoute.empty())
		{
			m_CameraRoute = m_listRoute.front();
			m_listRoute.pop_front();
			GAMEINSTANCE->Add_Shaking(m_CameraRoute.m_fShakeOffset, m_CameraRoute.m_fShakeInclination);
		}
		else
		{
			GAMEINSTANCE->Swap_Camera();
			m_bFlag = false;
		}
	}

	

	m_CameraRoute.fTime -= fTimeDelta;
	m_pTransformCom->Update_WorldMatrix();
	/*if (CAMERAMOVING::CAMERA_STAY == m_CameraRoute.eMoveType)
	{
		return;
	}*/
	_float3 vPosition = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
	m_CameraRoute.m_vSpeed += m_CameraRoute.m_vAccel; 
	vPosition += m_CameraRoute.m_vSpeed*fTimeDelta;

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, vPosition);
	if(m_CameraRoute.m_pEndTransform)
		m_pTransformCom->LookAt(m_CameraRoute.m_pEndTransform, true);

}

void CMovingCamera::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

}

HRESULT CMovingCamera::Render_Begin(ID3DXEffect** Shader)
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

	_tagRoute.m_pEndTransform = _pEndTarget;
	_tagRoute.m_pStartTransform = _pStartTarget;

	//if (CMovingCamera::CAMERAMOVING::CAMERA_MOVE == _tagRoute.eMoveType)
	//{
	//	_float3 vecStartPos = _pStartTarget->Get_World_State(CTransform::STATE_POSITION);
	//	_float3 vecEndPos = _pEndTarget->Get_World_State(CTransform::STATE_POSITION);

	//	_float3 vRoute = vecEndPos - vecStartPos;

	//	_tagRoute.m_vSpeed = -1.f * vRoute * 2 / (_tagRoute.fTime);
	//	_tagRoute.m_vAccel = 2 * vRoute / (_tagRoute.fTime * _tagRoute.fTime);
	//}

	//else if (CMovingCamera::CAMERAMOVING::CAMERA_STAY == _tagRoute.eMoveType)
	//{

	//	m_pTransformCom->Set_World_State(CTransform::STATE_POSITION,_pStartTarget->Get_World_State(CTransform::STATE_POSITION));
	//	_tagRoute.m_vSpeed = _tagRoute.m_vAccel = _float3(0.f, 0.f, 0.f);
	//}

	m_listRoute.push_back(_tagRoute);
}

void CMovingCamera::Add_Movement(_float _fTime, _float _fAngle,_float3 _vSpeed, _float3 _vAccel, CTransform* _pEndTransform, CTransform* _pStartTransform, _float _fShakeOffSet, _float _fShakeInclination)
{
	CAMERAROUTE	tagCameraroute;
	tagCameraroute.fTime = _fTime;
	tagCameraroute.fAngle = _fAngle;

	tagCameraroute.m_vSpeed = _vSpeed;
	tagCameraroute.m_vAccel = _vAccel;

	tagCameraroute.m_pEndTransform = _pEndTransform;
	tagCameraroute.m_pStartTransform = _pStartTransform;

	tagCameraroute.m_fShakeOffset = _fShakeOffSet;
	tagCameraroute.m_fShakeInclination = _fShakeInclination;
	m_listRoute.push_back(tagCameraroute);
	m_bFlag = true;
}

void CMovingCamera::Boss_Cinematic(CTransform* _pBossTarget)
{
	m_CameraRoute.m_pEndTransform = _pBossTarget;

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


	m_CameraRoute.fTime = 5.f;
	m_CameraRoute.fAngle = D3DXToRadian(30.f);

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

