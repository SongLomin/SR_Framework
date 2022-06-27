#include "stdafx.h"
#include "UITest.h"
#include "GameInstance.h"
#include "Math_Utillity.h"

CUITest::CUITest()
{
}

CUITest::CUITest(const CUITest& Prototype)
{
	*this = Prototype;
	Add_Component<CTransform>();
}

HRESULT CUITest::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CUITest::Initialize(void* pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	

	return S_OK;
}

void CUITest::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	


}

void CUITest::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_UI, this);
}

HRESULT CUITest::Render()
{
	__super::Render();

	m_pTransformCom->Bind_WorldMatrix();

	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	m_pRendererCom->Bind_Texture(1);
	m_pVIBufferCom->Render();
	
	m_pRendererCom->UnBind_Texture();

	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	return S_OK;
}

HRESULT CUITest::SetUp_Components()
{
	Add_Component<CTransform>();

	m_pTransformCom = Get_Component<CTransform>();
	m_pTransformCom->Set_WeakPtr(&m_pTransformCom);

	m_pRendererCom = Add_Component<CRenderer>();
	m_pRendererCom->Set_WeakPtr(&m_pRendererCom);
	m_pRendererCom->Set_Textures_From_Key(TEXT("Rock"), MEMORY_TYPE::MEMORY_STATIC);


	m_pVIBufferCom = Add_Component<CVIBuffer_Rect>();
	m_pVIBufferCom->Set_WeakPtr(&m_pVIBufferCom);

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(1.f, 1.f, 1.f));




	return S_OK;
}

CUITest* CUITest::Create()
{
	CREATE_PIPELINE(CUITest);
}

CGameObject* CUITest::Clone(void* pArg)
{
	CLONE_PIPELINE(CUITest);
}

void CUITest::Free()
{
	__super::Free();

	delete this;
}