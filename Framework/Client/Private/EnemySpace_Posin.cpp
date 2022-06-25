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


	LookAt_Player();

	if (m_fCurTime <= 0)
	{
		CGameObject* Bullet = GAMEINSTANCE->Add_GameObject<CEnemySpace_Bullet>(CURRENT_LEVEL, TEXT("EnemySpace_Bullet"));
		((CEnemySpace_Bullet*)Bullet)->Link_PosinTransform(m_pTransformCom);

		m_fCurTime = m_fMaxTime;
	}
}

void CEnemySpace_Posin::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_NONALPHABLEND, this);
}

HRESULT CEnemySpace_Posin::Render()
{


	m_pTransformCom->Scaling(_float3(0.4f, 0.24f, 1.6f), true);

	m_pTransformCom->Bind_WorldMatrix(D3D_ALL, D3D_ALL);

	__super::Render();
	m_pMeshCom->Render_Mesh();
	m_pRendererCom->UnBind_Texture();

	return S_OK;
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

	m_pPlayerTransformCom = CGameInstance::Get_Instance()->Get_Player_GameObject()->Get_Component<CTransform>();
	m_pPlayerTransformCom->Set_WeakPtr((void**)&m_pPlayerTransformCom);

	return S_OK;
}

void CEnemySpace_Posin::LookAt_Player()
{


	m_pTransformCom->LookAt(m_pPlayerTransformCom, true);
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