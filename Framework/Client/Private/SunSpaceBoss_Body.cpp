#include "stdafx.h"
#include "SunSpaceBoss_Body.h"
#include "GameInstance.h"
#include "EnemySpace_Body.h"
#include "Enemy_Roller.h"
#include "Enemy_Scourge.h"
#include "Rock_1.h"
#include "Rock_2.h"
#include "Rock_3.h"
#include "Rock_4.h"
#include <BlackHole_Effect.h>
#include <EnemySpawn_Effect.h>

CSunSpaceBoss_Body::CSunSpaceBoss_Body()
{
}

CSunSpaceBoss_Body::CSunSpaceBoss_Body(const CSunSpaceBoss_Body& Prototype)
{
	*this = Prototype;
}

HRESULT CSunSpaceBoss_Body::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CSunSpaceBoss_Body::Initialize(void* pArg)
{
	
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	__super::Initialize(pArg);


	return S_OK;
}

void CSunSpaceBoss_Body::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);


	GAMEINSTANCE->Add_Text(_point{ (LONG)610, (LONG)42 }, D3DCOLOR_ARGB(255, 255, 0, 0), 0.f, TEXT("¿¡´ý °Å´Ï½º"), 0);


	m_fMonsterSpawn -= fTimeDelta;
	if (m_fMonsterSpawn < 0.f)
	{
		Spawn_Monster();

		m_fMonsterSpawn = 18.f;
		if (m_pStatusCom->Get_Status().fHp < m_pStatusCom->Get_Status().fMaxHp / 2.f)
		{
			m_fMonsterSpawn = 9.f;
		}
	}
	Rock_throw(fTimeDelta);


}

void CSunSpaceBoss_Body::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);
	if (m_bSkill)
	{
		m_fRadian -= 140.f;
		m_fSkillTime -= fTimeDelta;
		_float3 vLook = m_pTransformCom->Get_World_State(CTransform::STATE_LOOK);
		_float3 vRight = m_pTransformCom->Get_World_State(CTransform::STATE_RIGHT);
		m_pTransformCom->Turn(vLook, D3DXToRadian(m_fRadian), fTimeDelta * 20.f, true);
		m_pTransformCom->Turn(vRight, D3DXToRadian(m_fRadian), fTimeDelta * 20.f, true);
		if (m_fSkillTime < 0.f)
		{
			m_fSkillTime = 3.f;
			m_bSkill = false;
		}
	}
	else if (!m_bSkill)
	{
		LookAtPlayer();
	}

	m_pRigidBodyCom->Update_Transform(fTimeDelta);
	_float3 vPos = m_pTransformCom->Get_World_State(CTransform::STATE_POSITION);

	if (GAMEINSTANCE->IsIn(&vPos))
		m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_DEFERRED, this);
}

HRESULT CSunSpaceBoss_Body::Render_Begin(ID3DXEffect** Shader)
{
	m_pTransformCom->Scaling(_float3(10.f, 10.f, 10.f), true);
	m_pTransformCom->Bind_WorldMatrix();

	D3DXHANDLE ColorHandle = (*Shader)->GetParameterByName(0, "Color");

	float floatArray[3];
	floatArray[0] = 0.7f;
	floatArray[1] = 0.0f;
	floatArray[2] = 0.7f;

	(*Shader)->SetFloatArray(ColorHandle, floatArray, 3);
	return S_OK;
}

HRESULT CSunSpaceBoss_Body::Render()
{

	__super::Render();
	m_pMeshCom->Render_Mesh();
	return S_OK;
}

void CSunSpaceBoss_Body::Spawn_Monster()
{
	_float3 MyPos = m_pTransformCom->Get_World_State(CTransform::STATE_POSITION);
	for (_uint i = 0; i < 5; ++i)
	{
		_uint MonsterType = rand() % 2 + 1;
		CTransform* pEnemyTransform = nullptr;
		switch (MonsterType)
		{
		case 1:
			pEnemyTransform = GAMEINSTANCE->Add_GameObject<CEnemySpace_Body>(CURRENT_LEVEL, TEXT("EnemySpace_Body"), nullptr, nullptr, true)
				->Get_Component<CTransform>();
			break;

		case 2:
			m_pEnemyTransform = GAMEINSTANCE->Add_GameObject<CEnemy_Scourge>(CURRENT_LEVEL, TEXT("Enemy_Scourge"), nullptr, nullptr, true)
				->Get_Component<CTransform>();
			break;
		}

		
		_float3 SpawnPos{ (_float)(rand() % 300), (_float)(rand() % 300), MyPos.z };
		((CEnemySpawn_Effect*)GAMEINSTANCE->Add_GameObject<CEnemySpawn_Effect>(CURRENT_LEVEL, TEXT("EnemySpawn"), nullptr, nullptr, false))->Set_Pos(SpawnPos);

		
		pEnemyTransform->Set_State(CTransform::STATE_POSITION, SpawnPos);

	}
		m_bSkill = true;
}

void CSunSpaceBoss_Body::Rock_throw(_float fTimeDelta)
{
	_float3 MyPos = m_pTransformCom->Get_World_State(CTransform::STATE_POSITION);
	m_fRockSpawn -= fTimeDelta;
	if (m_fRockSpawn < 0.f)
	{
		m_fRockSpawn = 15.f;
		if (m_pStatusCom->Get_Status().fHp < m_pStatusCom->Get_Status().fMaxHp / 2.f)
		{
			m_fRockSpawn = 7.5f;
		}
		CGameObject* m_pRockObject = nullptr;
		for (_uint i = 0; i < 5; ++i)
		{
			_uint RockType = rand() % 4 + 1;
			switch (RockType)
			{
			case 1:
				m_pRockObject = GAMEINSTANCE->Add_GameObject<CRock_1>(CURRENT_LEVEL, TEXT("Rock_1"), nullptr, nullptr, true);
				break;

			case 2:
				m_pRockObject = GAMEINSTANCE->Add_GameObject<CRock_2>(CURRENT_LEVEL, TEXT("Rock_2"), nullptr, nullptr, true);
				break;

			case 3:
				m_pRockObject = GAMEINSTANCE->Add_GameObject<CRock_3>(CURRENT_LEVEL, TEXT("Rock_3"), nullptr, nullptr, true);
				break;

			case 4:
				m_pRockObject = GAMEINSTANCE->Add_GameObject<CRock_4>(CURRENT_LEVEL, TEXT("Rock_4"), nullptr, nullptr, true);
				break;
			}

			_float3 SpawnPos{ (_float)(rand() % 300), (_float)(rand() % 300), MyPos.z };

			((CBlackHole_Effect*)GAMEINSTANCE->Add_GameObject<CBlackHole_Effect>(CURRENT_LEVEL, TEXT("BlackHole"), nullptr, nullptr, false))->Set_Pos(SpawnPos);

			m_pRockObject->Get_Component<CTransform>()->Set_State(CTransform::STATE_POSITION, SpawnPos);

			CTransform* pPlayerObject = GAMEINSTANCE->Get_Camera(CURRENT_CAMERA)->Get_Transform()->Get_Owner()->Get_Component<CTransform>();

			m_pRockObject->Get_Component<CTransform>()->LookAt(pPlayerObject);
			_float LifeTime = 10.f;

			m_RockObjectList.push_back({ LifeTime,m_pRockObject });
			WEAK_PTR(m_RockObjectList.back().second);
			m_bSkill = true;
		}
	}

	if (!m_RockObjectList.empty())
	{
		m_RockObjectList.sort();
		for (auto& iter = m_RockObjectList.begin(); iter != m_RockObjectList.end();)
		{
			/*if (!iter->second->Get_Enable())
			{
				RETURN_WEAKPTR(iter->second);
				iter = m_RockObjectList.erase(iter);
				continue;
			}*/					
			iter->first -= fTimeDelta;
			if (iter->first < 0.f || !iter->second->Get_Enable())
			{
				RETURN_WEAKPTR(iter->second);
				iter->second->Set_Enable(false);
				iter = m_RockObjectList.erase(iter);
			}
			else
			{
				iter->second->Get_Component<CRigid_Body>()->Add_Dir(CRigid_Body::FRONT);
				++iter;
			}
		}
	}
	
}

void CSunSpaceBoss_Body::EMP()
{
}

void CSunSpaceBoss_Body::LookAtPlayer()
{
	CTransform* pPlayerObject = GAMEINSTANCE->Get_Camera(CURRENT_CAMERA)->Get_Transform()->Get_Owner()->Get_Component<CTransform>();
	WEAK_PTR(pPlayerObject);

	m_pTransformCom->LookAt(pPlayerObject, true);

	RETURN_WEAKPTR(pPlayerObject);
}

void CSunSpaceBoss_Body::SetUp_Components_For_Child()
{
	m_pMeshCom = Add_Component<CMesh_SongShip>();
	WEAK_PTR(m_pMeshCom);

	CStatus::STATUS Status;
	Status.fAttack = 5.f;
	Status.fArmor = 20.f;
	Status.fMaxHp = 500.f;
	Status.fHp = Status.fMaxHp;

	m_pStatusCom = Add_Component<CStatus>(&Status);
	m_pStatusCom->Set_WeakPtr(&m_pStatusCom);

	//m_pStateCom->Link_RigidBody(m_pRigidBodyCom);
	//m_pStateCom->Link_AI_Transform(m_pTransformCom);

	COLLISION_TYPE eBulletCollisionType = COLLISION_TYPE::MONSTER_ATTACK;

	//m_pAIControllerCom->Link_Object(this);
	//m_pAIControllerCom->Set_Enable(false);
	//m_pAIControllerCom->Set_UsableStates(m_pAIControllerCom->Get_States_Preset_AI_Default());


	COLLISION_TYPE eCollisionType = COLLISION_TYPE::MONSTER;
	m_pColliderCom = Add_Component<CCollider_Sphere>(&eCollisionType);
	m_pColliderCom->Link_Transform(m_pTransformCom);
	m_pColliderCom->Set_Collider_Size(_float3(20.f, 20.f, 20.f));
	m_pColliderCom->Set_WeakPtr(&m_pColliderCom);
	Set_Controller(CONTROLLER::AI);

	CRigid_Body::RIGIDBODYDESC		RigidBodyDesc;
	RigidBodyDesc.Set_Preset_Boss_Body();

	m_pRigidBodyCom = Add_Component<CRigid_Body>(&RigidBodyDesc);
	m_pRigidBodyCom->Set_WeakPtr(&m_pRigidBodyCom);
	m_pRigidBodyCom->Link_TransformCom(m_pTransformCom);

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(0.f, 100.f, 800.f));
}

void CSunSpaceBoss_Body::On_Change_Controller(const CONTROLLER& _IsAI)
{
	__super::On_Change_Controller(_IsAI);
}

void CSunSpaceBoss_Body::On_Collision_Enter(CCollider* _Other_Collider)
{
	__super::On_Collision_Enter(_Other_Collider);

	if (Get_Enable() == false)
	{
		
		//((CEnemy_Roller*)GAMEINSTANCE->Add_GameObject<CEnemy_Roller>(CURRENT_LEVEL, TEXT("Enemy_Roller")))
		//	->Get_Component<CTransform>()->Set_State(CTransform::STATE_POSITION,m_pTransformCom->Get_State(CTransform::STATE_POSITION));
	}
}

void CSunSpaceBoss_Body::On_Collision_Stay(CCollider* _Other_Collider)
{
	__super::On_Collision_Stay(_Other_Collider);
}

void CSunSpaceBoss_Body::On_Collision_Exit(CCollider* _Other_Collider)
{
	__super::On_Collision_Exit(_Other_Collider);
}

CSunSpaceBoss_Body* CSunSpaceBoss_Body::Create()
{
	CREATE_PIPELINE(CSunSpaceBoss_Body);
}

CGameObject* CSunSpaceBoss_Body::Clone(void* pArg)
{
	CLONE_PIPELINE(CSunSpaceBoss_Body);
}

void CSunSpaceBoss_Body::Free()
{
	__super::Free();

	delete this;
}
