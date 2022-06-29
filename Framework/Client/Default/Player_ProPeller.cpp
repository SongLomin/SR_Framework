#include "stdafx.h"
#include "Player_ProPeller.h"
#include "GameInstance.h"

CPlayer_ProPeller::CPlayer_ProPeller()
{
}

CPlayer_ProPeller::CPlayer_ProPeller(const CPlayer_ProPeller& Prototype)
{
	*this = Prototype;
	//m_szName = L"Ring";
	Add_Component<CTransform>();
}

HRESULT CPlayer_ProPeller::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CPlayer_ProPeller::Initialize(void* pArg)
{

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_pRendererCom = Add_Component<CRenderer>();
	m_pRendererCom->Set_WeakPtr(&m_pRendererCom);

	m_pMeshCom = Add_Component<CMesh_Cube>();
	m_pMeshCom->Set_WeakPtr(&m_pMeshCom);
	m_pMeshCom->Set_Texture(TEXT("Mesh_Cube"), MEMORY_TYPE::MEMORY_STATIC);

	return S_OK;
}

void CPlayer_ProPeller::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	//m_pTransformCom->Go_BackAndForth(8.f, fTimeDelta);
	//m_pTransformCom->Turn(_float3(0.f, 1.f, 0.f), 15.f, fTimeDelta);
	m_pRigidBodyCom->Set_DirVector();
	m_pRigidBodyCom->Add_Dir(CRigid_Body::RIGHT);
}

void CPlayer_ProPeller::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_NONALPHABLEND, this);
}

HRESULT CPlayer_ProPeller::Render()
{
	

	m_pTransformCom->Bind_WorldMatrix();

	//DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);


	__super::Render();

	if (Get_Controller() == CONTROLLER::PLAYER)
		m_pMeshCom->Render_Mesh();



	//DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	return S_OK;
}



inline HRESULT CPlayer_ProPeller::SetUp_Components()
{
	//CGameInstance* pGameInstance = CGameInstance::Get_Instance();

	m_pTransformCom = Get_Component<CTransform>();
	m_pTransformCom->Set_WeakPtr((void**)&m_pTransformCom);

	m_pTransformCom->Set_State(CTransform::STATE::STATE_POSITION, _float3(1.f, 3.5f, 0.f));
	m_pTransformCom->Scaling(_float3(5.f, 0.3f, 0.5f));


	CRigid_Body::RIGIDBODYDESC		RigidBodyDesc;
	RigidBodyDesc.m_fOwnerSpeed = 10.f;
	RigidBodyDesc.m_fOwnerRadSpeed = D3DXToRadian(90.0f);

	RigidBodyDesc.m_fFrictional = 0.05f;
	RigidBodyDesc.m_fRadFrictional = 0.05f;

	m_pRigidBodyCom = Add_Component<CRigid_Body>(&RigidBodyDesc);
	m_pRigidBodyCom->Set_WeakPtr(&m_pRigidBodyCom);
	m_pRigidBodyCom->Link_TransformCom(m_pTransformCom);



	return S_OK;
}



CPlayer_ProPeller* CPlayer_ProPeller::Create()
{
	CREATE_PIPELINE(CPlayer_ProPeller);
}

CGameObject* CPlayer_ProPeller::Clone(void* pArg)
{
	CLONE_PIPELINE(CPlayer_ProPeller);
}

void CPlayer_ProPeller::Free()
{
	__super::Free();

	delete this;
}
