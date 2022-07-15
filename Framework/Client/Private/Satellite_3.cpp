#include "stdafx.h"
#include "Satellite_3.h"
#include "GameInstance.h"
#include "Level_Loading.h"

CSatellite_3::CSatellite_3()
{
}

CSatellite_3::CSatellite_3(const CSatellite_3& Prototype)
{
	*this = Prototype;
}

HRESULT CSatellite_3::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CSatellite_3::Initialize(void* pArg)
{

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	//m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(1500.f,  1200.f, 1700.f));

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(100.f, 100.f, 100.f));

	return S_OK;
}

void CSatellite_3::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
}

void CSatellite_3::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);


	LookAt_Camera();

	if (GAMEINSTANCE->IsIn(&(m_pTransformCom->Get_World_State(CTransform::STATE_POSITION))))
	{
		m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_NONALPHABLEND, this);
	}
}

HRESULT CSatellite_3::Render()
{

	m_pTransformCom->Scaling(_float3(100.f, 100.f, 5.f), true);

	m_pTransformCom->Bind_WorldMatrix();

	
	m_pRendererCom->Bind_Texture(2);

	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	DEVICE->SetRenderState(D3DRS_ALPHAREF, 253);
	DEVICE->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	m_pVIBufferCom->Render();

	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	m_pRendererCom->UnBind_Texture();



	return S_OK;
}




void CSatellite_3::On_Collision_Enter(CCollider* _Other_Collider)
{
	__super::On_Collision_Enter(_Other_Collider);

	if (COLLISION_TYPE::PLAYER == _Other_Collider->Get_Collision_Type())
	{
		GAMEINSTANCE->Add_Text(_point{ (LONG)525, (LONG)400 }, D3DCOLOR_ARGB(255, 0, 204, 255), 1.f, TEXT("우주 정거장을 해킹했습니다!!!!"), 0);


		GAMEINSTANCE->Get_Instance()->Register_OpenLevelEvent(LEVEL_LOADING, CLevel_Loading::Create(LEVEL_SELECTPLANET));
	}
}

void CSatellite_3::On_Collision_Stay(CCollider* _Other_Collider)
{
	__super::On_Collision_Enter(_Other_Collider);
}

void CSatellite_3::On_Collision_Exit(CCollider* _Other_Collider)
{
	__super::On_Collision_Exit(_Other_Collider);
}




HRESULT CSatellite_3::SetUp_Components()
{
	Add_Component<CTransform>();

	m_pTransformCom = Get_Component<CTransform>();
	m_pTransformCom->Set_WeakPtr(&m_pTransformCom);

	m_pRendererCom = Add_Component<CRenderer>();
	m_pRendererCom->Set_WeakPtr(&m_pRendererCom);
	m_pRendererCom->Set_Textures_From_Key(TEXT("Satellite"), MEMORY_TYPE::MEMORY_STATIC);


	m_pVIBufferCom = Add_Component<CVIBuffer_Rect>();
	m_pVIBufferCom->Set_WeakPtr(&m_pVIBufferCom);


	CRigid_Body::RIGIDBODYDESC		RigidBodyDesc;
	RigidBodyDesc.m_fOwnerSpeed = 10.f;
	RigidBodyDesc.m_fOwnerAccel = 0.5f;
	RigidBodyDesc.m_fOwnerRadSpeed = D3DXToRadian(90.0f);
	RigidBodyDesc.m_fOwnerRadAccel = 0.3f;
	RigidBodyDesc.m_fOwnerJump = 5.f;
	RigidBodyDesc.m_fOwnerJumpScale = 1.f;

	RigidBodyDesc.m_fFrictional = 0.01f;
	RigidBodyDesc.m_fRadFrictional = 0.02f;
	RigidBodyDesc.m_fRadZ = 0.01f;


	RigidBodyDesc.m_fOwnerLiftSpeed = 10.f;
	RigidBodyDesc.m_fOwnerLiftAccel = 0.3f;
	RigidBodyDesc.m_fRadDrag = 1.f;
	RigidBodyDesc.m_fDirDrag = 0.05f;
	RigidBodyDesc.m_fOwnerAccel = 0.1f;

	m_pRigidBodyCom = Add_Component<CRigid_Body>(&RigidBodyDesc);
	m_pRigidBodyCom->Link_TransformCom(m_pTransformCom);
	m_pRigidBodyCom->Set_WeakPtr(&m_pRigidBodyCom);
	

	COLLISION_TYPE	eCollisiontype = COLLISION_TYPE::OBJECT;
	m_pColliderCom = Add_Component<CCollider_Sphere>(&eCollisiontype);
	m_pColliderCom->Set_WeakPtr(&m_pColliderCom);
	m_pColliderCom->Link_Transform(m_pTransformCom);
	m_pColliderCom->Set_Collider_Size(_float3(50.f, 50.f, 5.f));

	return S_OK;
}

void CSatellite_3::LookAt_Camera()
{
	_float4x4		ViewMatrix;

	DEVICE->GetTransform(D3DTS_VIEW, &ViewMatrix);
	D3DXMatrixInverse(&ViewMatrix, nullptr, &ViewMatrix);

	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, *(_float3*)&ViewMatrix.m[0][0], true);
	m_pTransformCom->Set_State(CTransform::STATE_UP, *(_float3*)&ViewMatrix.m[1][0], true);
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, *(_float3*)&ViewMatrix.m[2][0], true);
}

CSatellite_3* CSatellite_3::Create()
{
	CREATE_PIPELINE(CSatellite_3);
}

CGameObject* CSatellite_3::Clone(void* pArg)
{
	CLONE_PIPELINE(CSatellite_3);
}

void CSatellite_3::Free()
{
	__super::Free();

	RETURN_WEAKPTR(m_pTransformCom);
	RETURN_WEAKPTR(m_pRendererCom);
	RETURN_WEAKPTR(m_pVIBufferCom);
	RETURN_WEAKPTR(m_pColliderCom);
	RETURN_WEAKPTR(m_pRigidBodyCom);

	delete this;
}
