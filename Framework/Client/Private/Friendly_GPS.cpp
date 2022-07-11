#include "stdafx.h"
#include "Friendly_GPS.h"
#include "GameInstance.h"

CFriendly_GPS::CFriendly_GPS()
{
}

CFriendly_GPS::CFriendly_GPS(const CFriendly_GPS& Prototype)
{
}

HRESULT CFriendly_GPS::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CFriendly_GPS::Initialize(void* pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	

	SetUp_Varialbes_For_Child(GPS_TYPE::GPS_FRIENDLY,TEXT("GPS_Friendly"));

	return S_OK;
}

void CFriendly_GPS::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
}

void CFriendly_GPS::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);
}

HRESULT CFriendly_GPS::Render()
{
	__super::Render();

	return S_OK;
}

void CFriendly_GPS::SetUp_For_Child()
{
}

CFriendly_GPS* CFriendly_GPS::Create()
{
	CREATE_PIPELINE(CFriendly_GPS);
}

CGameObject* CFriendly_GPS::Clone(void* pArg)
{
	CLONE_PIPELINE(CFriendly_GPS);
}

void CFriendly_GPS::Free()
{
	__super::Free();

	delete this;
}
