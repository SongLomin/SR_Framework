#include "stdafx.h"
#include "EnemySpace_Posin.h"
#include "GameInstance.h"
#include "Math_Utillity.h"
#include "EnemySpace_Bullet.h"




CEnemySpace_Posin::CEnemySpace_Posin(const CEnemySpace_Posin& Prototype)
{
	*this = Prototype;
	Add_Component<CTransform>();


}

HRESULT CEnemySpace_Posin::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CEnemySpace_Posin::Initialize(void* pArg)
{

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	


	

	m_fCurTime = m_fMaxTime;

	return S_OK;
}

void CEnemySpace_Posin::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	m_fCurTime -= fTimeDelta;


	//LookAt_Player();

	

}

void CEnemySpace_Posin::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	// Å¸°Ù Ã¼Å©
	if (m_pTargetObject)
	{
		_float3 TargetPos = m_pTargetObject->Get_Component<CTransform>()->Get_World_State(CTransform::STATE_POSITION);
		m_pTransformCom->LookAt(TargetPos, true);

		if (m_pTargetObject && m_fCurTime <= 0)
		{
			CGameObject* Bullet = GAMEINSTANCE->Add_GameObject<CEnemySpace_Bullet>(CURRENT_LEVEL, TEXT("EnemySpace_Bullet"));
			((CEnemySpace_Bullet*)Bullet)->Link_PosinTransform(m_pTransformCom);

			m_fCurTime = m_fMaxTime;
		}
	}
	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_NONALPHABLEND, this);
}

HRESULT CEnemySpace_Posin::Render()
{
	m_pTransformCom->Scaling(_float3(0.4f, 0.30f, 1.6f), true);

	m_pTransformCom->Bind_WorldMatrix(D3D_ALL, D3D_ALL);

	__super::Render();
	m_pMeshCom->Render_Mesh();
	m_pRendererCom->UnBind_Texture();

	return S_OK;
}

void CEnemySpace_Posin::Set_Target(CGameObject* _Object)
{

	if (m_pTargetObject != _Object)
	{
		if (m_pTargetObject)
		{
			m_pTargetObject->Return_WeakPtr(&m_pTargetObject);
		}


		m_pTargetObject = _Object;		
	}

	if (nullptr == m_pTargetObject)
	{
		//m_pTransformCom->LookAt(_float3(0.f, 1.f, 0.f), true);
		return;
	}
	else
	{
		m_pTargetObject->Set_WeakPtr(&m_pTargetObject);
	}


	int i = 10;
}





HRESULT CEnemySpace_Posin::SetUp_Components()
{

	m_pRendererCom = Add_Component<CRenderer>();
	m_pRendererCom->Set_WeakPtr(&m_pRendererCom);


	m_pMeshCom = Add_Component<CMesh_Cube>();
	m_pMeshCom->Set_WeakPtr(&m_pMeshCom);
	m_pMeshCom->Set_Texture(TEXT("Mesh_Cube"), MEMORY_TYPE::MEMORY_STATIC);

	m_pTransformCom = Get_Component<CTransform>();
	m_pTransformCom->Set_WeakPtr((void**)&m_pTransformCom);


	return S_OK;
}

void CEnemySpace_Posin::LookAt_Player()
{
	//m_pTransformCom->LookAt(m_pPlayerTransformCom, true);
}



CEnemySpace_Posin* CEnemySpace_Posin::Create()
{
	CREATE_PIPELINE(CEnemySpace_Posin);
}

CGameObject* CEnemySpace_Posin::Clone(void* pArg)
{
	CLONE_PIPELINE(CEnemySpace_Posin);
}

void CEnemySpace_Posin::Free()
{
	__super::Free();

	delete this;
}