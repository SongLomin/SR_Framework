#include "stdafx.h"
#include "Enemy_GPS.h"
#include "GameInstance.h"

CEnemy_GPS::CEnemy_GPS()
{
}

CEnemy_GPS::CEnemy_GPS(const CEnemy_GPS& Prototype)
{
	*this = Prototype;
}

HRESULT CEnemy_GPS::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CEnemy_GPS::Initialize(void* pArg)
{
	__super::Initialize(pArg);

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	SetUp_Varialbes_For_Child(GPS_TYPE::GPS_ENEMY, TEXT("GPS_Enemy"));

	return S_OK;
}

void CEnemy_GPS::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
}

void CEnemy_GPS::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);
}

HRESULT CEnemy_GPS::Render()
{

	__super::Render();

	return S_OK;
}

void CEnemy_GPS::SetUp_For_Child()
{
}

CEnemy_GPS* CEnemy_GPS::Create()
{
	CREATE_PIPELINE(CEnemy_GPS);
}

CGameObject* CEnemy_GPS::Clone(void* pArg)
{
	CLONE_PIPELINE(CEnemy_GPS);

}

void CEnemy_GPS::Free()
{
	__super::Free();

	delete this;
}
