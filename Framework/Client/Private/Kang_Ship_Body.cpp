#include "stdafx.h"
#include "Kang_Ship_Body.h"
#include "GameInstance.h"
#include "Normal_Turret.h"
#include "Rocket_Turret.h"
#include "Mesh_KangShip.h"
#include <Lazer_Turret.h>
#include "Trajectory.h"

CKang_Ship_Body::CKang_Ship_Body()
{
}

CKang_Ship_Body::CKang_Ship_Body(const CKang_Ship_Body& Prototype)
{
	*this = Prototype;
}

HRESULT CKang_Ship_Body::Initialize_Prototype()
{
	m_AnchorPosition = _float3(1.4f, 1.f, -0.5f);
	return S_OK;
}

HRESULT CKang_Ship_Body::Initialize(void* pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;


	m_pTrajectorys.push_back(static_cast<CTrajectory*>(GAMEINSTANCE->Add_GameObject<CTrajectory>(LEVEL_STATIC, TEXT("Trajectory"))));
	m_pTrajectorys.back()->Make_TrajectoryNode(200, m_pTransformCom, _float3(5.3f, 1.3f, -15.f));
	WEAK_PTR(m_pTrajectorys.back());
	
	m_pTrajectorys.push_back(static_cast<CTrajectory*>(GAMEINSTANCE->Add_GameObject<CTrajectory>(LEVEL_STATIC, TEXT("Trajectory"))));
	m_pTrajectorys.back()->Make_TrajectoryNode(200, m_pTransformCom, _float3(-5.3f, 1.3f, -15.f));
	WEAK_PTR(m_pTrajectorys.back());

	m_pTrajectorys.push_back(static_cast<CTrajectory*>(GAMEINSTANCE->Add_GameObject<CTrajectory>(LEVEL_STATIC, TEXT("Trajectory"))));
	m_pTrajectorys.back()->Make_TrajectoryNode(200, m_pTransformCom, _float3(20.f, 0.f, -28.f));
	WEAK_PTR(m_pTrajectorys.back());

	m_pTrajectorys.push_back(static_cast<CTrajectory*>(GAMEINSTANCE->Add_GameObject<CTrajectory>(LEVEL_STATIC, TEXT("Trajectory"))));
	m_pTrajectorys.back()->Make_TrajectoryNode(200, m_pTransformCom, _float3(-20.f, 0.f, -28.f));
	WEAK_PTR(m_pTrajectorys.back());



	GAMEINSTANCE->Set_Current_Camera(TEXT("TPS"));

	return S_OK;
}

void CKang_Ship_Body::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
}

void CKang_Ship_Body::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);
}

HRESULT CKang_Ship_Body::Render_Begin(ID3DXEffect** Shader)
{
	m_pTransformCom->Scaling(_float3(2.f, 2.f, 2.f), true);
	m_pTransformCom->Bind_WorldMatrix();

	D3DXHANDLE ColorHandle = (*Shader)->GetParameterByName(0, "Color");

	float floatArray[3];
	floatArray[0] = 0.2f;
	floatArray[1] = 0.5f;
	floatArray[2] = 0.7f;

	(*Shader)->SetFloatArray(ColorHandle, floatArray, 3);

	return S_OK;
}

HRESULT CKang_Ship_Body::Render()
{	
	__super::Render();

	m_pMeshCom->Render_Mesh();

	return S_OK;
}

void CKang_Ship_Body::SetUp_Components_For_Child()
{
	m_pTransformCom->Set_State(CTransform::STATE::STATE_POSITION, _float3(0.f, 1.f, 0.f));

#pragma region Collider Setting
	m_pColliderCom->Set_Collider_Size(_float3(3.f, 0.f, 0.f));

#pragma endregion Collider Setting

#pragma region Mesh Setting

	m_pMeshCom = Add_Component<CMesh_KangShip>();
	m_pMeshCom->Set_WeakPtr(&m_pMeshCom);
	m_pMeshCom->Set_Texture(TEXT("Mesh_Cube"), MEMORY_TYPE::MEMORY_STATIC);

#pragma endregion Mesh Setting

#pragma region Status Setting
	CStatus::STATUS		Status;
	Status.fMaxHp = 30.f;
	Status.fHp = Status.fMaxHp;
	Status.fAttack = 7.f;
	Status.fMaxArmor = 5.f;
	Status.fArmor = Status.fMaxArmor;
	Status.fMaxBooster = 22.f;
	Status.fBooster = Status.fMaxBooster;

	m_pStatusCom = Add_Component<CStatus>(&Status);
	m_pStatusCom->Set_WeakPtr(&m_pStatusCom);
#pragma endregion Status Setting

#pragma region Rigid_Body Setting
	CRigid_Body::RIGIDBODYDESC		RigidBodyDesc;
	RigidBodyDesc.Set_Preset_Kang_Ship();

	m_pRigid_BodyCom = Add_Component<CRigid_Body>(&RigidBodyDesc);
	m_pRigid_BodyCom->Set_WeakPtr(&m_pRigid_BodyCom);
	m_pRigid_BodyCom->Link_TransformCom(m_pTransformCom);

#pragma endregion Rigid_Body Setting

#pragma region Posin Setting

	/*CTurret* Posin = static_cast<CTurret*>(GAMEINSTANCE->Add_GameObject<CNormal_Turret>(LEVEL_STATIC, TEXT("Normal_Turret"), m_pTransformCom));
	Posin->Get_Component<CTransform>()->Set_State(CTransform::STATE::STATE_POSITION, _float3(0.f, 1.f, 0.f));
	m_pMyTurretList.push_back(Posin);
	Posin->Set_WeakPtr(&m_pMyTurretList.back());

	Posin = static_cast<CTurret*>(GAMEINSTANCE->Add_GameObject<CRocket_Turret>(LEVEL_STATIC, TEXT("Normal_Turret"), m_pTransformCom));
	Posin->Get_Component<CTransform>()->Set_State(CTransform::STATE::STATE_POSITION, _float3(-1.f, -1.f, 0.f));
	m_pMyTurretList.push_back(Posin);
	Posin->Set_WeakPtr(&m_pMyTurretList.back());

	Posin = static_cast<CTurret*>(GAMEINSTANCE->Add_GameObject<CRocket_Turret>(LEVEL_STATIC, TEXT("Rocket_Turret"), m_pTransformCom));
	Posin->Get_Component<CTransform>()->Set_State(CTransform::STATE::STATE_POSITION, _float3(1.f, -1.f, 0.f));
	m_pMyTurretList.push_back(Posin);
	Posin->Set_WeakPtr(&m_pMyTurretList.back());*/

	GAMEINSTANCE->Add_GameObject<CLazer_Turret>(LEVEL_STATIC, TEXT("Lazer_Turret"), m_pTransformCom);
	GAMEINSTANCE->Add_GameObject<CLazer_Turret>(LEVEL_STATIC, TEXT("Lazer_Turret"), m_pTransformCom);
	GAMEINSTANCE->Add_GameObject<CLazer_Turret>(LEVEL_STATIC, TEXT("Lazer_Turret"), m_pTransformCom);
	GAMEINSTANCE->Add_GameObject<CLazer_Turret>(LEVEL_STATIC, TEXT("Lazer_Turret"), m_pTransformCom);


#pragma endregion Posin Setting

#pragma region Controller Setting

	m_pAI_ControllerCom->Link_Object(this);
	m_pAI_ControllerCom->Set_Enable(false);


	m_pPlayer_ControllerCom->Link_Object(this);
	m_pPlayer_ControllerCom->Set_Enable(false);

#pragma endregion Controller Setting 

#pragma region State Setting

	m_pStateCom->Link_RigidBody(m_pRigid_BodyCom);
	m_pStateCom->Link_AI_Transform(m_pTransformCom);

#pragma endregion State Setting

	Set_Controller(CONTROLLER::AI);

}

void CKang_Ship_Body::On_Change_Controller(const CONTROLLER& _IsAI)
{
	__super::On_Change_Controller(_IsAI);
}

void CKang_Ship_Body::On_Collision_Enter(CCollider* _Other_Collider)
{
	__super::On_Collision_Enter(_Other_Collider);
}

void CKang_Ship_Body::On_Collision_Stay(CCollider* _Other_Collider)
{
	__super::On_Collision_Stay(_Other_Collider);
}

void CKang_Ship_Body::On_Collision_Exit(CCollider* _Other_Collider)
{
	__super::On_Collision_Exit(_Other_Collider);
}

CKang_Ship_Body* CKang_Ship_Body::Create()
{
	CREATE_PIPELINE(CKang_Ship_Body);
}

CGameObject* CKang_Ship_Body::Clone(void* pArg)
{
	CLONE_PIPELINE(CKang_Ship_Body);
}

void CKang_Ship_Body::Free()
{
	__super::Free();

	delete this;
}
