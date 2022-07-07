#include "stdafx.h"
#include "AI_TransportShip.h"
#include "GameInstance.h"
#include "Normal_Turret.h"
#include "AI_Friendly.h"

CAI_TransportShip::CAI_TransportShip()
{
}

CAI_TransportShip::CAI_TransportShip(const CAI_TransportShip& Prototype)
{
    *this = Prototype;

    

}

HRESULT CAI_TransportShip::Initialize_Prototype()
{  

    return S_OK;
}

HRESULT CAI_TransportShip::Initialize(void* pArg)
{
	Add_Component<CTransform>();

	SetUp_Components();

    return S_OK;
}

void CAI_TransportShip::Tick(_float fTimeDelta)
{
    __super::Tick(fTimeDelta);
	
	m_fSpawnTime -= fTimeDelta;

	if (m_fSpawnTime < 0.f)
	{
		Spawn_SpaceShip();

		m_fSpawnTime = 10.f;
	}


}

void CAI_TransportShip::LateTick(_float fTimeDelta)
{
    __super::LateTick(fTimeDelta);

	m_pRigidBodyCom->Update_Transform(fTimeDelta);
	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_DEFERRED, this);
}

HRESULT CAI_TransportShip::Render_Begin(ID3DXEffect** Shader)
{
    __super::Render_Begin(Shader);

	m_pTransformCom->Bind_WorldMatrix();

	D3DXHANDLE ColorHandle = (*Shader)->GetParameterByName(0, "Color");
	D3DXHANDLE DiffuseHandle = (*Shader)->GetParameterByName(0, "Diffuse");
	D3DXHANDLE SpecularHandle = (*Shader)->GetParameterByName(0, "Specular");


	float floatArray[3];
	floatArray[0] = 0.8f;
	floatArray[1] = 0.8f;
	floatArray[2] = 0.8f;


	float Specular = 1.f;
	float Diffuse = 1.f;

	(*Shader)->SetFloatArray(ColorHandle, floatArray, 3);
	(*Shader)->SetFloat(DiffuseHandle, Diffuse);
	(*Shader)->SetFloat(SpecularHandle, Specular);

    return S_OK;
}

HRESULT CAI_TransportShip::Render()
{
    __super::Render();

	m_pMeshCom->Render_Mesh();

    return S_OK;
}

void CAI_TransportShip::On_Change_Controller(const CONTROLLER& _IsAI)
{
}

void CAI_TransportShip::On_Collision_Enter(CCollider* _Other_Collider)
{
}

void CAI_TransportShip::On_Collision_Stay(CCollider* _Other_Collider)
{
}

void CAI_TransportShip::On_Collision_Exit(CCollider* _Other_Collider)
{
}

HRESULT CAI_TransportShip::SetUp_Components()
{
    m_pTransformCom = Get_Component<CTransform>();
    m_pTransformCom->Set_WeakPtr(&m_pTransformCom);
    m_pTransformCom->Set_State(CTransform::STATE::STATE_POSITION, _float3(0.f, 0.f, -100.f));
	m_pTransformCom->Scaling(_float3(30.0f, 4.0f, 50.0f));


    m_pRendererCom = Add_Component<CRenderer>();
    m_pRendererCom->Set_WeakPtr(&m_pRendererCom);

    /*m_pTargetingCom = Add_Component<CTargeting>();
    m_pTargetingCom->Set_WeakPtr(&m_pTargetingCom);*/

    m_pMeshCom = Add_Component<CMesh_Cube>();
    m_pMeshCom->Set_WeakPtr(&m_pMeshCom);



#pragma region Status Setting
	CStatus::STATUS		Status;
	Status.fHp = 10.f;
	Status.fAttack = 7.f;
	Status.fArmor = 5.f;

	m_pStatusCom = Add_Component<CStatus>(&Status);
	m_pStatusCom->Set_WeakPtr(&m_pStatusCom);
#pragma endregion Status Setting

#pragma region Rigid_Body Setting
	CRigid_Body::RIGIDBODYDESC		RigidBodyDesc;
	RigidBodyDesc.m_fOwnerSpeed = 4.5f;
	RigidBodyDesc.m_fOwnerAccel = 1.f;
	RigidBodyDesc.m_fOwnerRadSpeed = D3DXToRadian(90.0f);
	RigidBodyDesc.m_fOwnerRadAccel = 0.3f;
	RigidBodyDesc.m_fOwnerJump = 5.f;
	RigidBodyDesc.m_fOwnerJumpScale = 1.f;

	RigidBodyDesc.m_fFrictional = 0.05f;
	RigidBodyDesc.m_fRadFrictional = 0.02f;
	RigidBodyDesc.m_fRadZ = 0.01f;

	RigidBodyDesc.m_fOwnerLiftSpeed = 20.f;
	RigidBodyDesc.m_fOwnerLiftAccel = 0.3f;
	RigidBodyDesc.m_fRadDrag = 1.f;
	RigidBodyDesc.m_fDirDrag = 0.05f;
	m_pRigidBodyCom = Add_Component<CRigid_Body>(&RigidBodyDesc);
	m_pRigidBodyCom->Set_WeakPtr(&m_pRigidBodyCom);
	m_pRigidBodyCom->Link_TransformCom(m_pTransformCom);

#pragma endregion Rigid_Body Setting

#pragma region Collider Setting

	COLLISION_TYPE eCollisionType = COLLISION_TYPE::PLAYER;
	m_pColliderCom = Add_Component<CCollider_Sphere>(&eCollisionType);
	m_pColliderCom->Link_Transform(m_pTransformCom);
	m_pColliderCom->Set_Collider_Size(_float3(1.f, 1.f, 1.f));
	m_pColliderCom->Set_WeakPtr(&m_pColliderCom);


#pragma endregion Collider Setting

#pragma region Posin Setting

	CNormal_Turret* Posin = static_cast<CNormal_Turret*>(GAMEINSTANCE->Add_GameObject<CNormal_Turret>(CURRENT_LEVEL, TEXT("Normal_Turret"), m_pTransformCom));
	Posin->Get_Component<CTransform>()->Set_State(CTransform::STATE::STATE_POSITION, _float3(0.f, 1.f, 0.f));
	m_pMyPosinList.push_back(Posin);
	Posin->Set_WeakPtr(&m_pMyPosinList.back());


#pragma endregion Posin Setting

	m_pStateCom = Add_Component<CState_Move>();
	m_pStateCom->Set_WeakPtr(&m_pStateCom);
	m_pStateCom->Link_RigidBody(m_pRigidBodyCom);
	m_pStateCom->Link_AI_Transform(m_pTransformCom);


	m_pAIControllerCom = Add_Component<CAI_Controller>();
	m_pAIControllerCom->Set_WeakPtr(&m_pAIControllerCom);
	m_pAIControllerCom->Link_Object(this);
	m_pAIControllerCom->Set_Enable(true);
	m_pAIControllerCom->Set_UsableStates({STATE::MOVE_FORWARD});

	Set_Controller(CONTROLLER::AI);


    return S_OK;
}

void CAI_TransportShip::Spawn_SpaceShip()
{
	CGameObject* pAI_Friendly = GAMEINSTANCE->Add_GameObject<CAI_Friendly>(CURRENT_LEVEL, TEXT("AI_Friendly"));
	CTransform* pTransform_Friendly = pAI_Friendly->Get_Component<CTransform>();

	pTransform_Friendly->Set_LocalMatrix(m_pTransformCom->Get_WorldMatrix());
	pTransform_Friendly->Scaling(_float3(1.f, 1.f, 1.f));
	pTransform_Friendly->Add_Position(_float3(0.f, 5.f, -10.f));
	pTransform_Friendly->Update_WorldMatrix();

	CAI_Controller* pController_Friendly = pAI_Friendly->Get_Component<CAI_Controller>();

	//pController_Friendly->Push_Front_Command(STATE::MOVE_LIFT_FRONT);
	pController_Friendly->Push_Front_Command(STATE::MOVE_FORWARD, 6.f);

	

}

CAI_TransportShip* CAI_TransportShip::Create()
{
    CREATE_PIPELINE(CAI_TransportShip);
}

CGameObject* CAI_TransportShip::Clone(void* pArg)
{
    CLONE_PIPELINE(CAI_TransportShip);
}

void CAI_TransportShip::Free()
{
    __super::Free();

    delete this;

}
