#include "stdafx.h"
#include "Roket_Bullet.h"
#include "GameInstance.h"
#include "Rocket_PSystem.h"



CRocket_Bullet::CRocket_Bullet()
{
}

CRocket_Bullet::CRocket_Bullet(const CRocket_Bullet& Prototype)
{
	*this = Prototype;

	Add_Component<CTransform>();
}

HRESULT CRocket_Bullet::Initialize_Prototype()
{
	m_fDamage = 10.f;

	return S_OK;
}

HRESULT CRocket_Bullet::Initialize(void* pArg)
{
	COLLISION_TYPE eCollisionType = *(COLLISION_TYPE*)pArg;

	if (FAILED(SetUp_Components(eCollisionType)))
		return E_FAIL;

	return S_OK;
}

void CRocket_Bullet::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	_float3 Light_Look_Dir = -m_pTransformCom->Get_State(CTransform::STATE_LOOK, true);
	D3DXVec3Normalize(&Light_Look_Dir, &Light_Look_Dir);

	m_pLight->Set_LooK_Dir(Light_Look_Dir);
}

void CRocket_Bullet::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);
	m_pRigidBodyCom->Update_Transform(fTimeDelta);
	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_DEFERRED, this);
}

HRESULT CRocket_Bullet::Render_Begin(ID3DXEffect** Shader)
{
	m_pTransformCom->Scaling(_float3(0.3f, 0.3f, 2.0f), true);
	m_pTransformCom->Bind_WorldMatrix();

	D3DXHANDLE ColorHandle = (*Shader)->GetParameterByName(0, "Color");


	float floatArray[3];
	floatArray[0] = 0.2f;
	floatArray[1] = 0.0f;
	floatArray[2] = 0.2f;

	(*Shader)->SetFloatArray(ColorHandle, floatArray, 3);


	return S_OK;
}

HRESULT CRocket_Bullet::Render()
{
	//m_pColliderCom->Debug_Render();
	//m_pPreColliderCom->Debug_Render();



	//DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//m_pRendererCom->Bind_Texture(1);
	__super::Render();
	m_pMeshCom->Render_Mesh();
	//m_pRendererCom->UnBind_Texture();

	//DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	return S_OK;
}

void CRocket_Bullet::Find_Way(_float fTimeDelta)
{
	if (m_fLifeTime < 0.f)
		return;

	


	if (9.3f < m_fLifeTime)//발사 후, 초반 0.5초 동안은 방향 조정연출(?)
	{
		m_pRigidBodyCom->Add_Dir(CRigid_Body::DOWN);
		return;
	}

	else if(9.f > m_fLifeTime)
	{
		if (nullptr == m_pTarget || !m_pTarget->Get_Enable())
		{

			m_pTargetingCom->Make_TargetList_Distance(GAMEINSTANCE->Find_Layer(CURRENT_LEVEL, TEXT("EnemySpace_Body")), m_pTransformCom->Get_World_State(CTransform::STATE_POSITION), 200.f);
			map<_float, CGameObject*>* pMap = m_pTargetingCom->Get_Targetting();
			if (!pMap->empty())
			{
				m_pTarget = pMap->begin()->second;
			}
		}
		if (m_pTarget)
		{
			_float3 fDistance = m_pTransformCom->Get_World_State(CTransform::STATE_POSITION);
			
			_float3 TargetPos =  m_pTarget->Get_Component<CTransform>()->Get_World_State(CTransform::STATE_POSITION);

			fDistance -= TargetPos;

			_float test = D3DXVec3Length(&fDistance);
			
			if (40.f > test)
			{
				m_pTransformCom->LookAt(m_pTarget->Get_Component<CTransform>());
				m_pTransformCom->Go_BackAndForth(1.f, fTimeDelta);
				m_pTransformCom->Update_WorldMatrix();
			}
			else
			{
				_float3 vDir = m_pTarget->Get_Component<CTransform>()->Get_World_State(CTransform::STATE_POSITION) - m_pTransformCom->Get_State(CTransform::STATE_POSITION);
				_float3 vLook = m_pRigidBodyCom->Get_Direction(CRigid_Body::STATE_LOOK);
				D3DXVec3Normalize(&vDir, &vDir);
				D3DXVec3Normalize(&vLook, &vLook);

				_float fDotProduct = D3DXVec3Dot(&vDir, &vLook);
				if (0.f > fDotProduct)
				{
					_float3 fCrossProduct;
					D3DXVec3Cross(&fCrossProduct, &vLook, &vDir);
					_float3 vUp = m_pRigidBodyCom->Get_Direction(CRigid_Body::STATE_UP);
					_float  fDotProduct = D3DXVec3Dot(&fCrossProduct, &vUp);
					if (0.f > fDotProduct)
					{
						m_pRigidBodyCom->Add_Dir(CRigid_Body::LEFT);
					}
					else if (0.f < fDotProduct)
					{
						m_pRigidBodyCom->Add_Dir(CRigid_Body::RIGHT);
					}
				}
				else
				{
					_float3 vVec = fDotProduct * vDir;
					D3DXVec3Normalize(&vVec, &vVec);

					_float3 vProj = vVec + vLook;
					D3DXVec3Normalize(&vProj, &vProj);

					m_pRigidBodyCom->Set_Direction(CRigid_Body::STATE_LOOK, vProj);
				}
			}
		}
	}

	((CRocket_PSystem*)GAMEINSTANCE->Get_ParticleSystem<CRocket_PSystem>(CURRENT_LEVEL, TEXT("Rocket_Particle")))->AddParticle(200 * fTimeDelta, m_pTransformCom);
	m_pRigidBodyCom->Add_Dir(CRigid_Body::FRONT);
}

void CRocket_Bullet::Set_Target(CGameObject* _pTarget)
{
	if (m_pTarget)
	{
		RETURN_WEAKPTR(m_pTarget);
		m_pTarget = nullptr;
	}
	if (_pTarget)
	{
		m_pTarget = _pTarget;
		WEAK_PTR(m_pTarget);
	}
}

void CRocket_Bullet::Init_BulletPosition(_float4x4* _pWorldMat)
{
	__super::Init_BulletPosition(_pWorldMat);

	//m_pTransformCom->Go_BackAndForth(10.f, 1.f);

	m_pTransformCom->Update_WorldMatrix();
	m_pRigidBodyCom->Set_DirVector();
	//m_pRigidBodyCom->Add_Dir(CRigid_Body::FRONT);

}

void CRocket_Bullet::On_Collision_Enter(CCollider* _Other_Collider)
{
	if (_Other_Collider->Get_Collision_Type() == COLLISION_TYPE::MONSTER)
	{
		Set_Enable(false);
	}

}

void CRocket_Bullet::On_Collision_Stay(CCollider* _Other_Collider)
{

}

void CRocket_Bullet::On_Collision_Exit(CCollider* _Other_Collider)
{
}

void CRocket_Bullet::OnTimerEvent(const _uint _iEventIndex)
{
	if (0 == _iEventIndex)
	{
		m_pRigidBodyCom->Add_Dir(CRigid_Body::DOWN);
	}
	else if (1 == _iEventIndex)
	{
		if (nullptr == m_pTarget || !m_pTarget->Get_Enable())
		{

			m_pTargetingCom->Make_TargetList_Distance(GAMEINSTANCE->Find_Layer(CURRENT_LEVEL, TEXT("EnemySpace_Body")), m_pTransformCom->Get_World_State(CTransform::STATE_POSITION), 200.f);
			map<_float, CGameObject*>* pMap = m_pTargetingCom->Get_Targetting();
			if (!pMap->empty())
			{
				m_pTarget = pMap->begin()->second;
			}
		}
		if (m_pTarget)
		{
			
			m_pTransformCom->LookAt(m_pTarget->Get_Component<CTransform>());
		
		}
		m_pTransformCom->Go_BackAndForth(2.f, 1.f);
		m_pTransformCom->Update_WorldMatrix();
	}
}

HRESULT CRocket_Bullet::SetUp_Components_For_Child()
{
	CRigid_Body::RIGIDBODYDESC		RigidBodyDesc;
	RigidBodyDesc.m_fOwnerSpeed = 50.f;
	RigidBodyDesc.m_fOwnerAccel = 1.f;
	RigidBodyDesc.m_fOwnerRadSpeed = D3DXToRadian(120.0f);
	RigidBodyDesc.m_fOwnerRadAccel = 0.3f;
	RigidBodyDesc.m_fOwnerJump = 0.f;
	RigidBodyDesc.m_fOwnerJumpScale = 1.f;

	RigidBodyDesc.m_fFrictional = 0.f;
	RigidBodyDesc.m_fRadFrictional = 0.02f;
	RigidBodyDesc.m_fRadZ = 0.01f;


	RigidBodyDesc.m_fOwnerLiftSpeed = 5.f;
	RigidBodyDesc.m_fOwnerLiftAccel = 1.f;
	RigidBodyDesc.m_fRadDrag = 1.f;
	RigidBodyDesc.m_fDirDrag = 0.05f;

	m_pRigidBodyCom = Add_Component<CRigid_Body>(&RigidBodyDesc);
	m_pRigidBodyCom->Set_WeakPtr(&m_pRigidBodyCom);
	m_pRigidBodyCom->Link_TransformCom(m_pTransformCom);

	m_pMeshCom = Add_Component<CMesh_Test>();
	m_pMeshCom->Set_WeakPtr(&m_pMeshCom);
	m_pMeshCom->Set_Texture(TEXT("Mesh_Cube"), MEMORY_TYPE::MEMORY_STATIC);

	_float3 ColliderSize = m_pTransformCom->Get_Scaled();
	_float3 RenderScale = _float3(0.2f, 0.1f, 0.2f);
	ColliderSize.x *= RenderScale.x;
	ColliderSize.y *= RenderScale.y;
	ColliderSize.z *= RenderScale.z;

	m_pColliderCom->Set_Collider_Size(ColliderSize);

	m_pLight = Add_Component<CSpotLight>();
	WEAK_PTR(m_pLight);
	m_pLight->Set_Light_Variables(D3DXCOLOR(1.f, 0.f, 1.f, 1.f),0.3f,0.5f,0.6f,_float3(0.f,0.f,-2.f), D3DXVECTOR3(-1.f, -1.f, -1.f),
		1.f,1.f,0.7f,1.8f,0.5f,0.05f,0.1f);

	m_pTargetingCom = Add_Component<CTargeting>();//Make_AI_TargetList<- 쫓아가던 타겟이 사라졌을 때만 실행
	WEAK_PTR(m_pTargetingCom);
	m_pTargetingCom->Set_TargetMode(TARGETMODE::TARGET_SINGLE);

	m_fMaxTime = m_fLifeTime = 10.f;

	return S_OK;
}

void CRocket_Bullet::OnEnable(void* _Arg)
{
	__super::OnEnable(_Arg);

	GAMEINSTANCE->Add_TimerEvent(0, this, 1.f, false, false, true);
	GAMEINSTANCE->Add_TimerEvent(1, this, 9.f, false, true, true);
}



CRocket_Bullet* CRocket_Bullet::Create()
{
	CREATE_PIPELINE(CRocket_Bullet);
}

CGameObject* CRocket_Bullet::Clone(void* pArg)
{
	CLONE_PIPELINE(CRocket_Bullet);
}

void CRocket_Bullet::Free()
{
	if (m_pMeshCom)
		m_pMeshCom->Return_WeakPtr(&m_pMeshCom);

	if (m_pRendererCom)
		m_pRendererCom->Return_WeakPtr(&m_pRendererCom);

	RETURN_WEAKPTR(m_pLight);

	__super::Free();

	delete this;
}