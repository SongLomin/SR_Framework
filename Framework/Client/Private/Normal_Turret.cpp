#include "stdafx.h"
#include "Normal_Turret.h"
#include "GameInstance.h"
#include "Math_Utillity.h"
#include "Normal_Bullet.h"
#include "Fire_PSystem.h"


CNormal_Turret::CNormal_Turret(const CNormal_Turret& Prototype)
{
	*this = Prototype;
}


HRESULT CNormal_Turret::Initialize(void* pArg)
{

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	if (pArg)
		m_eBulletCollisionType = *(COLLISION_TYPE*)pArg;

	float floatArray[3];
	floatArray[0] = 0.2f;
	floatArray[1] = 0.2f;
	floatArray[2] = 0.2f;

	SetUp_Variables_For_Child(0.1f, _float3(0.4f, 0.4f, 3.f), floatArray);

	return S_OK;
}

void CNormal_Turret::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	//m_fPreheatTime -= fTimeDelta;
	
	//m_fPreheatTime = max(1.1f, m_fPreheatTime);
}

void CNormal_Turret::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	

	//if (m_fPreheatTime >= 100.f - DBL_EPSILON)
	//{
	//	//printf("m_fPrehetTime: %f\n",&m_fPreheatTime);
	//}
	//
	//m_pTransformCom->Turn(m_pTransformCom->Get_State(CTransform::STATE_LOOK, true), m_fPreheatTime - 1.1f, 1.f, true);
}



void CNormal_Turret::Command_Fire()
{
	CGameObject* Bullet = GAMEINSTANCE->Add_GameObject<CNormal_Bullet>(CURRENT_LEVEL, TEXT("Normal_Bullet"), nullptr, &m_eBulletCollisionType, true);
	static_cast<CBullet*>(Bullet)->Init_BulletPosition(&Get_Component<CTransform>()->Get_WorldMatrix());
	if (Get_Controller() == CONTROLLER::PLAYER)
	{
		//m_fPreheatTime += TIMEDELTA;
		//m_fPreheatTime *= 1.01f;
		//m_fPreheatTime = min(10.f, m_fPreheatTime);

		GAMEINSTANCE->Add_Shaking(0.1f, 0.05f);
	}
}

void CNormal_Turret::On_EventMessage(void* _Arg)
{
	__super::On_EventMessage(_Arg);

	m_fLerpTime -= TIMEDELTA;

	if (m_fLerpTime < 0.f)
	{
		m_fPreheatTime *= 1.15f;
		m_fLerpTime = 2.f;
	}

	
	
	//m_fPreheatTime = min(100.f, m_fPreheatTime);
}

void CNormal_Turret::SetUp_Components_For_Child()
{
}


CNormal_Turret* CNormal_Turret::Create()
{
	CREATE_PIPELINE(CNormal_Turret);
}

CGameObject* CNormal_Turret::Clone(void* pArg)
{
	CLONE_PIPELINE(CNormal_Turret);
}

void CNormal_Turret::Free()
{
	__super::Free();

	delete this;
}