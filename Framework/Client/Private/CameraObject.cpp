#include "stdafx.h"
#include "CameraObject.h"
#include "GameInstance.h"

CCameraObject::CCameraObject(const CCameraObject& Prototype)
{
}

HRESULT CCameraObject::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CCameraObject::Initialize(void* pArg)
{
	m_pTransformCom = Add_Component<CTransform>();
	m_pTransformCom->Set_WeakPtr(&m_pTransformCom);

	m_pCameraCom = Add_Component<CCamera>();
	m_pCameraCom->Set_WeakPtr(&m_pCameraCom);
	
	m_pCameraCom->Set_Transform(m_pTransformCom);

	return S_OK;
}

void CCameraObject::Tick(_float fTimeDelta)
{
}

void CCameraObject::LateTick(_float fTimeDelta)
{
}

HRESULT CCameraObject::Render()
{
	return S_OK;
}

CCameraObject* CCameraObject::Create()
{
	return nullptr;
}

CGameObject* CCameraObject::Clone(void* pArg)
{
	return nullptr;
}

void CCameraObject::Free()
{
	__super::Free();

	delete this;
}
