#include "stdafx.h"
#include "Cam_Shoulder.h"
#include "GameInstance.h"

CCam_Shoulder::CCam_Shoulder(const CCam_Shoulder& Prototype)
{
	*this = Prototype;
}

HRESULT CCam_Shoulder::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CCam_Shoulder::Initialize(void* pArg)
{
	return S_OK;
}


void CCam_Shoulder::Tick(_float fTimeDelta)
{
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
