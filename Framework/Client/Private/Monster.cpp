#include "stdafx.h"
#include "..\Public\Monster.h"
#include "GameInstance.h"
#include <Math_Utillity.h>



CMonster::CMonster(const CMonster& Prototype)
{
	*this = Prototype;
	Add_Component<CTransform>()->Set_State(CTransform::STATE::STATE_POSITION, _float3(0.f, 1.f, 0.f));
	Set_Controller(CONTROLLER::AI);
}

HRESULT CMonster::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CMonster::Initialize(void* pArg)
{
	SetUp_Components();
	m_pPlayerTransformCom = CGameInstance::Get_Instance()->Get_Player_GameObject()->Get_Component<CTransform>();
	m_pPlayerTransformCom->Set_WeakPtr((void**)&m_pPlayerTransformCom);
	
	return S_OK;
}

void CMonster::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	ISVALID(m_pPlayerTransformCom, );
	ISVALID(m_pTransformCom, );

	m_pTransformCom->Go_Target(m_pPlayerTransformCom, fTimeDelta);
	m_pTransformCom->Go_BackAndForth(2.5, fTimeDelta);

	
	_float3 MyScreenPos;
	CMath_Utillity::WorldToScreen(&m_pTransformCom->Get_State(CTransform::STATE::STATE_POSITION, true), &MyScreenPos);

	GAMEINSTANCE->Add_Text(
		_point{ (long)MyScreenPos.x, (long)MyScreenPos.y },
		D3DCOLOR_ARGB(255, 130, 255, 0),
		0.0f,
		L"HP : %d / 10",
		1,
		(_int)m_pStatusCom->Get_Status().fHp);
}

void CMonster::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_NONALPHABLEND, this);
}

HRESULT CMonster::Render()
{
	m_pTransformCom->Bind_WorldMatrix();
	m_pRendererCom->Bind_Texture(1);

	__super::Render();
	m_pMeshCom->Render_Mesh();

	m_pRendererCom->UnBind_Texture();

	return S_OK;
}

HRESULT CMonster::SetUp_Components()
{
	//CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	//Safe_AddRef(pGameInstance);

	/* For.Com_Renderer */
	//약포인터: 해당 객체가 삭제되면 약포인터로 선언된 포인터 객체들도 nullptr를 가르킨다.
	//댕글링 포인터를 방지하기 위해 사용한다.

	CStatus::STATUS		Status;
	Status.fHp = 10.f;
	Status.fAttack = 7.f;
	Status.fArmor = 5.f;

	m_pStatusCom = Add_Component<CStatus>(&Status);
	m_pStatusCom->Set_WeakPtr(&m_pStatusCom);

	m_pRendererCom = Add_Component<CRenderer>();

	m_pRendererCom->Set_WeakPtr((void**)&m_pRendererCom);
	m_pRendererCom->Set_Textures_From_Key(TEXT("Test"), MEMORY_TYPE::MEMORY_DYNAMIC);


	m_pMeshCom = Add_Component<CMesh_Cube>();
	m_pMeshCom->Set_WeakPtr((void**)&m_pMeshCom);

	/*CTransform::TRANSFORMDESC		TransformDesc;
	TransformDesc.fSpeedPerSec = 2.5f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);*/

	m_pTransformCom = Get_Component<CTransform>();
	m_pTransformCom->Set_WeakPtr((void**)&m_pTransformCom);

	COLLISION_TYPE eCollisionType = COLLISION_TYPE::MONSTER;
	m_pCColliderCom = Add_Component<CCollider_OBB>(&eCollisionType);
	m_pCColliderCom->Set_WeakPtr(&m_pCColliderCom);
	m_pCColliderCom->Link_Transform(m_pTransformCom);
	m_pCColliderCom->Set_Collider_Size(_float3(1.f, 1.f, 1.f));
	

	//Safe_Release(pGameInstance);
	return S_OK;
}

void CMonster::On_Collision_Enter(CCollider* _Other_Collider)
{
	if (_Other_Collider->Get_Collision_Type() == COLLISION_TYPE::PLAYER_ATTACK)
	{
		m_pStatusCom->Add_Status(CStatus::STATUSID::STATUS_HP, -1.f);

		if (m_pStatusCom->Get_Status().fHp <= DBL_EPSILON)
		{
			Set_Dead();
		}
		
	}

}

void CMonster::On_Collision_Stay(CCollider* _Other_Collider)
{
}

void CMonster::On_Collision_Exit(CCollider* _Other_Collider)
{
}

CMonster* CMonster::Create()
{
	CREATE_PIPELINE(CMonster);
}

CGameObject* CMonster::Clone(void* pArg)
{
	CLONE_PIPELINE(CMonster);
}

void CMonster::Free()
{
	__super::Free();

	delete this;
}