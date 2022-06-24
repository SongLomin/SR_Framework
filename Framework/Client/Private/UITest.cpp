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

	m_pRendererCom = Add_Component<CRenderer>();
	m_pRendererCom->Set_WeakPtr(&m_pRendererCom);


	/*m_pMesh_TestCom = Add_Component<CMesh_Test>();
	m_pMesh_TestCom->Set_WeakPtr(&m_pMesh_TestCom);*/

	m_pMesh_TestCom = Add_Component<CMesh_SongShip>();
	m_pMesh_TestCom->Set_WeakPtr(&m_pMesh_TestCom);

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
	m_pMesh_TestCom->Render_Mesh();
	m_pRendererCom->UnBind_Texture();

	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	return S_OK;
}

HRESULT CUITest::SetUp_Components()
{
	CGameInstance* pGameInstance = CGameInstance::Get_Instance();

	m_pTransformCom = Get_Component<CTransform>();
	m_pTransformCom->Set_WeakPtr((void**)&m_pTransformCom);

	m_pTransformCom->Scaling(_float3(0.1f, 0.1f, 0.1f));





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