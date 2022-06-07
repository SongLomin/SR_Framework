#include "..\Public\GameInstance.h"


IMPLEMENT_SINGLETON(CGameInstance)

CGameInstance::CGameInstance()
	: m_pGraphic_Device(CGraphic_Device::Get_Instance())
	, m_pLevel_Manager(CLevel_Manager::Get_Instance())
	, m_pObject_Manager(CObject_Manager::Get_Instance())
	, m_pComponent_Manager(CComponent_Manager::Get_Instance())
	, m_pRender_Manager(CRender_Manager::Get_Instance())
{
	//Safe_AddRef(m_pComponent_Manager);
	//Safe_AddRef(m_pObject_Manager);
	//Safe_AddRef(m_pLevel_Manager);
	//Safe_AddRef(m_pGraphic_Device);
}

HRESULT CGameInstance::Initialize_Engine(_uint iNumLevels, const GRAPHICDESC& GraphicDesc, LPDIRECT3DDEVICE9* ppOut)
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;	

	/* 그래픽디바이스. */
	if (FAILED(m_pGraphic_Device->InitDevice(GraphicDesc, ppOut)))
		return E_FAIL;

	/* 인풋 디바이스. */

	/* 오브젝트 매니져의 예약. */
	if (FAILED(m_pObject_Manager->Reserve_Container(iNumLevels)))
		return E_FAIL;

	/* 컴포넌트 매니져의 예약. */
	if (FAILED(m_pComponent_Manager->Reserve_Container(iNumLevels)))
		return E_FAIL;

	return S_OK;	
}

HRESULT CGameInstance::Tick_Engine(_float fTimeDelta)
{
	if (nullptr == m_pLevel_Manager)	
		return E_FAIL;

	m_pLevel_Manager->Tick(fTimeDelta);	

	m_pObject_Manager->Tick(fTimeDelta);


	m_pObject_Manager->LateTick(fTimeDelta);

	return S_OK;
}

HRESULT CGameInstance::Render_Engine()
{
	
	if (nullptr == m_pLevel_Manager)
		return E_FAIL;

	m_pLevel_Manager->Render();


	return S_OK;
}

HRESULT CGameInstance::Clear(_uint iLevelID)
{
	if (nullptr == m_pObject_Manager)
		return E_FAIL;

	m_pObject_Manager->Clear(iLevelID);

	return S_OK;
}

void CGameInstance::Render_Begin(void)
{
	if (nullptr == m_pGraphic_Device)
		return;

	return m_pGraphic_Device->Render_Begin();
}

void CGameInstance::Render_End(HWND hWnd)
{
	if (nullptr == m_pGraphic_Device)
		return;

	return m_pGraphic_Device->Render_End(hWnd);
}

LPDIRECT3DDEVICE9* CGameInstance::Get_Device(void)
{
	if (nullptr == m_pGraphic_Device)
		return nullptr;

	return m_pGraphic_Device->Get_Device();
}

HRESULT CGameInstance::Open_Level(_uint iLevelID, CLevel * pLevel)
{
	if (nullptr == m_pLevel_Manager)
		return E_FAIL;

	return m_pLevel_Manager->Open_Level(iLevelID, pLevel);
}

HRESULT CGameInstance::Add_Prototype(const _tchar * pPrototypeTag, CGameObject * pPrototype)
{
	if (nullptr == m_pObject_Manager)
		return E_FAIL;

	return m_pObject_Manager->Add_Prototype(pPrototypeTag, pPrototype);	
}

HRESULT CGameInstance::Add_GameObject(_uint iLevelIndex, const _tchar * pLayerTag, const _tchar * pPrototypeTag, void * pArg)
{
	if (nullptr == m_pObject_Manager)
		return E_FAIL;

	return m_pObject_Manager->Add_GameObject(iLevelIndex, pLayerTag, pPrototypeTag, pArg);
}

HRESULT CGameInstance::Add_Prototype(_uint iLevelIndex, const _tchar * pPrototypeTag, CComponent * pPrototype)
{
	if (nullptr == m_pComponent_Manager)
		return E_FAIL;

	return m_pComponent_Manager->Add_Prototype(iLevelIndex, pPrototypeTag, pPrototype);
	
}

CComponent * CGameInstance::Clone_Component(_uint iLevelIndex, const _tchar * pPrototypeTag, void * pArg)
{
	if (nullptr == m_pComponent_Manager)
		return nullptr;

	return m_pComponent_Manager->Clone_Component(iLevelIndex, pPrototypeTag, pArg);
}

HRESULT CGameInstance::Add_RenderGroup(RENDERGROUP eGroup, CGameObject* pGameObject)
{
	if (nullptr == m_pRender_Manager)
	{
		return E_FAIL;
	}

	return m_pRender_Manager->Add_RenderGroup(eGroup, pGameObject);
}

HRESULT CGameInstance::Draw_RenderGroup()
{
	if (nullptr == m_pRender_Manager)
	{
		return E_FAIL;
	}

	return m_pRender_Manager->Draw_RenderGroup();
}

void CGameInstance::Release_Engine()
{
	CGameInstance::Get_Instance()->Destroy_Instance();

	CObject_Manager::Get_Instance()->Destroy_Instance();

	CComponent_Manager::Get_Instance()->Destroy_Instance();

	CLevel_Manager::Get_Instance()->Destroy_Instance();

	CGraphic_Device::Get_Instance()->Destroy_Instance();

	CRender_Manager::Get_Instance()->Destroy_Instance();

}

void CGameInstance::Free()
{
	//Safe_Release(m_pComponent_Manager);
	//Safe_Release(m_pObject_Manager);
	//Safe_Release(m_pLevel_Manager);
	//Safe_Release(m_pGraphic_Device);

	delete this;
}
