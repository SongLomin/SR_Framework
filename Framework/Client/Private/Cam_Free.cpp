#include "stdafx.h"
#include "Cam_Free.h"
#include "GameInstance.h"

CCam_Free::CCam_Free(const CCam_Free& Prototype)
{
}

HRESULT CCam_Free::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CCam_Free::Initialize(void* pArg)
{
	CTransform::TRANSFORMDESC		TransformDesc;
	TransformDesc.fSpeedPerSec = 5.0f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);

	m_pTransformCom = Add_Component<CTransform>(&TransformDesc);
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
	/*if (GetKeyState('W') & 0x8000)
	{
		m_pTransformCom->Go_Straight(fTimeDelta);
	}

	if (GetKeyState('S') & 0x8000)
	{
		m_pTransformCom->Go_Backward(fTimeDelta);
	}

	if (GetKeyState('A') & 0x8000)
	{
		m_pTransformCom->Go_Left(fTimeDelta);
	}

	if (GetKeyState('D') & 0x8000)
	{
		m_pTransformCom->Go_Right(fTimeDelta);
	}*/

	if (FAILED(m_pCameraCom->Bind_PipeLine()))
		return;
}

void CCam_Free::LateTick(_float fTimeDelta)
{

}

HRESULT CCam_Free::Render()
{
	return S_OK;
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
