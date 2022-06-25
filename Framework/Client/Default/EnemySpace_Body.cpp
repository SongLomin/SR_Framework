#include "stdafx.h"
#include "EnemySpace_Body.h"
#include "GameInstance.h"
#include "EnemySpace_RightBody.h"
#include "EnemySpace_Posin.h"


CEnemySpace_Body::CEnemySpace_Body(const CEnemySpace_Body& Prototype)
{
	*this = Prototype;
	m_pTransformCom = Add_Component<CTransform>();
	m_pTransformCom->Set_WeakPtr(&m_pTransformCom);
	m_pTransformCom->Set_State(CTransform::STATE::STATE_POSITION, _float3(rand()% 100, rand() % 20, rand() % 100));
	m_pTransformCom->Update_WorldMatrix();
}

HRESULT CEnemySpace_Body::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CEnemySpace_Body::Initialize(void* pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_pPlayerTransformCom = CGameInstance::Get_Instance()->Get_Player_GameObject()->Get_Component<CTransform>();
	m_pPlayerTransformCom->Set_WeakPtr((void**)&m_pPlayerTransformCom);

	

	return S_OK;
}

void CEnemySpace_Body::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);


	ISVALID(m_pTransformCom);


 	m_pStateCom->State_Change(fTimeDelta);
    
}

void CEnemySpace_Body::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);
	m_pRigidBodyCom->Update_Transform(fTimeDelta);
	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_NONALPHABLEND, this);
}

HRESULT CEnemySpace_Body::Render()
{
	__super::Render();

	m_pTransformCom->Bind_WorldMatrix();


	m_pRendererCom->Bind_Texture(1);
	m_pMeshCom->Render_Mesh();
	m_pRendererCom->UnBind_Texture();

	return S_OK;
}

HRESULT CEnemySpace_Body::SetUp_Components()
{


	m_pRendererCom = Add_Component<CRenderer>();

	m_pRendererCom->Set_WeakPtr((void**)&m_pRendererCom);
	m_pRendererCom->Set_Textures_From_Key(TEXT("Test"), MEMORY_TYPE::MEMORY_DYNAMIC);


	m_pMeshCom = Add_Component<CMesh_Cube>();
	m_pMeshCom->Set_WeakPtr((void**)&m_pMeshCom);
	m_pMeshCom->Set_Texture(TEXT("Mesh_Cube"), MEMORY_TYPE::MEMORY_STATIC);

	CRigid_Body::RIGIDBODYDESC		RigidBodyDesc;
	RigidBodyDesc.m_fOwnerSpeed = 10.f;
	RigidBodyDesc.m_fOwnerAccel = 0.1f;
	RigidBodyDesc.m_fOwnerRadSpeed = D3DXToRadian(90.0f);
	RigidBodyDesc.m_fOwnerRadAccel = 0.3f;
	RigidBodyDesc.m_fOwnerJump = 5.f;
	RigidBodyDesc.m_fOwnerJumpScale = 1.f;

	RigidBodyDesc.m_fFrictional = 0.05f;
	RigidBodyDesc.m_fRadFrictional = 0.02f;
	RigidBodyDesc.m_fRadZ = 0.01f;


	RigidBodyDesc.m_fOwnerLiftSpeed = 10.f;
	RigidBodyDesc.m_fOwnerLiftAccel = 0.3f;
	RigidBodyDesc.m_fRadDrag = 1.f;
	RigidBodyDesc.m_fDirDrag = 0.05f;
	RigidBodyDesc.m_fOwnerAccel = 0.1f;

	m_pRigidBodyCom = Add_Component<CRigid_Body>(&RigidBodyDesc);
	m_pRigidBodyCom->Set_WeakPtr(&m_pRigidBodyCom);
	m_pRigidBodyCom->Link_TransformCom(m_pTransformCom);

	
	m_pStateCom = Add_Component<CState_Move>();
	m_pStateCom->Set_WeakPtr((void**)m_pStateCom);
	m_pStateCom->Link_RigidBody(m_pRigidBodyCom);


	GAMEINSTANCE->Add_GameObject<CEnemySpace_RightBody>(CURRENT_LEVEL, TEXT("EnemySpace_RightBody"), m_pTransformCom);

	GAMEINSTANCE->Add_GameObject<CEnemySpace_Posin>(CURRENT_LEVEL, TEXT("EnemySpace_Posin"), m_pTransformCom)
		->Get_Component<CTransform>()->Set_State(CTransform::STATE::STATE_POSITION, _float3(2.f, 1.5f, 0.f));

	GAMEINSTANCE->Add_GameObject<CEnemySpace_Posin>(CURRENT_LEVEL, TEXT("EnemySpace_Posin"), m_pTransformCom)
		->Get_Component<CTransform>()->Set_State(CTransform::STATE::STATE_POSITION, _float3(0.f, 1.5f, 0.f));

	return S_OK;
}


CEnemySpace_Body* CEnemySpace_Body::Create()
{
	CREATE_PIPELINE(CEnemySpace_Body);
}

CGameObject* CEnemySpace_Body::Clone(void* pArg)
{
	CLONE_PIPELINE(CEnemySpace_Body);
}

void CEnemySpace_Body::Free()
{
	__super::Free();

	delete this;
}
