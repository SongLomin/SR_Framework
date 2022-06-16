#include "stdafx.h"
#include "..\Public\Monster.h"
#include "GameInstance.h"


CMonster::CMonster(const CMonster& Prototype)
{
	*this = Prototype;
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
	ISVALID(m_pPlayerTransformCom);
	ISVALID(m_pTransformCom);

	m_pTransformCom->Go_Target(m_pPlayerTransformCom, fTimeDelta);
	m_pTransformCom->Go_BackAndForth(2.5, fTimeDelta);

}

void CMonster::LateTick(_float fTimeDelta)
{
	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_NONALPHABLEND, this);
}

HRESULT CMonster::Render()
{
	m_pTransformCom->Bind_WorldMatrix();

	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	m_pRendererCom->Bind_Texture(1);
	m_pVIBufferCom->Render();
	m_pRendererCom->UnBind_Texture();

	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

    return S_OK;
}

HRESULT CMonster::SetUp_Components()
{
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();
	//Safe_AddRef(pGameInstance);

	/* For.Com_Renderer */
	//약포인터: 해당 객체가 삭제되면 약포인터로 선언된 포인터 객체들도 nullptr를 가르킨다.
	//댕글링 포인터를 방지하기 위해 사용한다.
	m_pRendererCom = Add_Component<CRenderer>();

	m_pRendererCom->Set_WeakPtr((void**)&m_pRendererCom);
	m_pRendererCom->Set_Textures_From_Key(TEXT("Test"), MEMORY_TYPE::MEMORY_DYNAMIC);

	m_pVIBufferCom = Add_Component<CVIBuffer_Rect>();
	m_pVIBufferCom->Set_WeakPtr((void**)&m_pVIBufferCom);

	/*CTransform::TRANSFORMDESC		TransformDesc;
	TransformDesc.fSpeedPerSec = 2.5f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);*/

	m_pTransformCom = Get_Component<CTransform>();
	m_pTransformCom->Set_WeakPtr((void**)&m_pTransformCom);
	
	

	//Safe_Release(pGameInstance);
	return S_OK;
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