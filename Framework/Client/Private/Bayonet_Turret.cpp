#include "stdafx.h"
#include "Bayonet_Turret.h"
#include "GameInstance.h"
#include "Math_Utillity.h"
#include "Normal_Bullet.h"
#include "Fire_PSystem.h"


CBayonet_Turret::CBayonet_Turret(const CBayonet_Turret& Prototype)
{
	*this = Prototype;
}


HRESULT CBayonet_Turret::Initialize(void* pArg)
{

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	if (pArg)
		m_eBulletCollisionType = *(COLLISION_TYPE*)pArg;

	float floatArray[3];
	floatArray[0] = 0.2f;
	floatArray[1] = 0.2f;
	floatArray[2] = 0.9f;

	SetUp_Variables_For_Child(0.1f, _float3(0.2f, 0.2f, 5.f), floatArray);

	return S_OK;
}

void CBayonet_Turret::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	m_fPreheatTime -= fTimeDelta;

	m_fPreheatTime = max(1.1f, m_fPreheatTime);
}

void CBayonet_Turret::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	m_pTransformCom->Turn(m_pTransformCom->Get_State(CTransform::STATE_LOOK, true), m_fPreheatTime - 1.1f, 1.f, true);
}

HRESULT CBayonet_Turret::Render()
{
	m_pMeshTestCom->Render_Mesh();
	return S_OK;
}



void CBayonet_Turret::Command_Fire()
{
	CGameObject* Bullet = GAMEINSTANCE->Add_GameObject<CNormal_Bullet>(CURRENT_LEVEL, TEXT("Normal_Bullet"), nullptr, &m_eBulletCollisionType, true);
	static_cast<CBullet*>(Bullet)->Init_BulletPosition(&Get_Component<CTransform>()->Get_WorldMatrix());
	if (Get_Controller() == CONTROLLER::PLAYER)
	{
		GAMEINSTANCE->Add_Shaking(0.1f, 0.05f);
	}
}

void CBayonet_Turret::On_EventMessage(void* _Arg)
{
	__super::On_EventMessage(_Arg);

	m_fLerpTime -= TIMEDELTA;

	if (m_fLerpTime < 0.f)
	{
		m_fPreheatTime *= 1.15f;
		m_fLerpTime = 2.f;
	}

}

void CBayonet_Turret::SetUp_Components_For_Child()
{
}


CBayonet_Turret* CBayonet_Turret::Create()
{
	CREATE_PIPELINE(CBayonet_Turret);
}

CGameObject* CBayonet_Turret::Clone(void* pArg)
{
	CLONE_PIPELINE(CBayonet_Turret);
}

void CBayonet_Turret::Free()
{
	__super::Free();

	delete this;
}