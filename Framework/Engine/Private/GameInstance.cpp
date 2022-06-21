#include "..\Public\GameInstance.h"


IMPLEMENT_SINGLETON(CGameInstance)

CGameInstance::CGameInstance()
	: m_pGraphic_Device(CGraphic_Device::Get_Instance())
	, m_pLevel_Manager(CLevel_Manager::Get_Instance())
	, m_pObject_Manager(CObject_Manager::Get_Instance())
	, m_pComponent_Manager(CComponent_Manager::Get_Instance())
	, m_pRender_Manager(CRender_Manager::Get_Instance())
	, m_pResource_Manager(CResource_Manager::Get_Instance())
	, m_pTime_Manager(CTime_Manager::Get_Instance())
	, m_pInput_Manager(CInput_Manager::Get_Instance())
	, m_pCamera_Manager(CCamera_Manager::Get_Instance())
	, m_pCollision_Manager(CCollision_Manager::Get_Instance())
{
	//Safe_AddRef(m_pComponent_Manager);
	//Safe_AddRef(m_pObject_Manager);
	//Safe_AddRef(m_pLevel_Manager);
	//Safe_AddRef(m_pGraphic_Device);
}

HRESULT CGameInstance::Initialize_Engine(HINSTANCE hInst, _uint iNumLevels, const GRAPHICDESC& GraphicDesc, LPDIRECT3DDEVICE9* ppOut)
{
	m_Graphic_Desc = GraphicDesc;


	if (nullptr == m_pGraphic_Device)
		return E_FAIL;	

	/* 그래픽디바이스. */
	if (FAILED(m_pGraphic_Device->InitDevice(GraphicDesc, ppOut)))
		return E_FAIL;

	/* 인풋 디바이스. */
	if (FAILED(m_pInput_Manager->Initialize(hInst, GraphicDesc.hWnd)))
		return E_FAIL;

	/* 오브젝트 매니져의 예약. */
	if (FAILED(m_pObject_Manager->Reserve_Container(iNumLevels)))
		return E_FAIL;

	/* 컴포넌트 매니져의 예약. */
	//if (FAILED(m_pComponent_Manager->Reserve_Container(iNumLevels)))
	//	return E_FAIL;

	return S_OK;	
}

HRESULT CGameInstance::Tick_Engine(_float fTimeDelta)
{

	m_pInput_Manager->SetUp_DeviceState();

	m_pLevel_Manager->Tick(fTimeDelta);	

	m_pObject_Manager->Tick(fTimeDelta);


	m_pObject_Manager->LateTick(fTimeDelta);

	m_pCamera_Manager->LateTick(fTimeDelta);
	
	m_pInput_Manager->Tick(fTimeDelta);

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

HRESULT CGameInstance::Add_Text(_point _Pos, D3DXCOLOR _Color, _float _CountTime, _tchar* _tString, int _iParamCnt, ...)
{
	if (nullptr == m_pGraphic_Device)
				return E_FAIL;
	
	TEXTINFO Info;
	Info.rcTemp = { _Pos.x, _Pos.y, _Pos.x + 3000, _Pos.y + 3000 };
	Info.color = _Color;

	va_list args;
	va_start(args, _iParamCnt);

	vswprintf(Info.szBuff, MAX_PATH, _tString, args);

	va_end(args);

	return m_pGraphic_Device->Add_Text(Info, _CountTime);
}

HRESULT CGameInstance::Add_Text(_point _Pos, _tchar* _tString, int _iParamCnt, ...)
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;

	TEXTINFO Info;
	Info.rcTemp = { _Pos.x, _Pos.y, _Pos.x + 3000, _Pos.y + 3000 };
	Info.color = D3DCOLOR_ARGB(255, 110, 255, 40);

	va_list args;
	va_start(args, _iParamCnt);

	vswprintf(Info.szBuff, MAX_PATH, _tString, args);

	va_end(args);

	return m_pGraphic_Device->Add_Text(Info, 0.0f);
}

//HRESULT CGameInstance::Add_Text(TEXTINFO* TextInfo, _float CountTime)
//{
//	if (nullptr == m_pGraphic_Device)
//		return E_FAIL;
//
//	return m_pGraphic_Device->Add_Text(TextInfo, CountTime);
//}

HRESULT CGameInstance::Open_Level(_uint iLevelID, CLevel * pLevel)
{
	if (nullptr == m_pLevel_Manager)
		return E_FAIL;

	return m_pLevel_Manager->Open_Level(iLevelID, pLevel);
}

void CGameInstance::Set_CurrentLevelIndex(_uint iLevelID)
{
	m_pLevel_Manager->Set_CurrentLevelIndex(iLevelID);
}

_uint CGameInstance::Get_CurrentLevelIndex()
{
	return m_pLevel_Manager->Get_CurrentLevelIndex();
}

CGameObject* CGameInstance::Get_Player_GameObject()
{
	return m_pObject_Manager->Get_Player();
}

list<CGameObject*>* CGameInstance::Find_Layer(_uint iLevelIndex, const _tchar* pLayerTag)
{
	return m_pObject_Manager->Find_Layer(iLevelIndex, pLayerTag);
}

HRESULT CGameInstance::Add_Prototype_Component(const _char * pPrototypeTag, CComponent * pPrototype)
{
	if (nullptr == m_pComponent_Manager)
		return E_FAIL;

	if (m_pComponent_Manager->Add_Prototype(pPrototypeTag, pPrototype) == nullptr)
		return E_FAIL;

	return S_OK;
}

//CComponent* CGameInstance::Clone_Component(const _char * pPrototypeTag, void * pArg)
//{
//	if (nullptr == m_pComponent_Manager)
//		return nullptr;
//
//	return m_pComponent_Manager->Clone_Component(pPrototypeTag, pArg);
//}

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

HRESULT CGameInstance::Add_Textures(const _tchar* _strKey, const _tchar* pTextureFilePath, TEXTURE_TYPE eType, MEMORY_TYPE eMemType)
{
	return m_pResource_Manager->Add_Texture(_strKey, pTextureFilePath, eType, eMemType);
}

HRESULT CGameInstance::Remove_Textures_By_MemoryType(MEMORY_TYPE _eMemType)
{
	return m_pResource_Manager->Remove_By_MemoryType(_eMemType);
}

vector<LPDIRECT3DBASETEXTURE9>* CGameInstance::Get_Textures_From_Key(const _tchar* _Str_Key, MEMORY_TYPE _eType)
{
	return CResource_Manager::Get_Instance()->Get_Textures_From_Key(_Str_Key, _eType);
}

HRESULT CGameInstance::Add_Timer(_uint eTimer)
{
	if (nullptr == m_pTime_Manager)
		return E_FAIL;

	return m_pTime_Manager->Add_Timer(eTimer);
}

_float CGameInstance::Compute_Timer(_uint eTimer)
{
	if (nullptr == m_pTime_Manager)
		return 0.0f;

	return m_pTime_Manager->Compute_Timer(eTimer);
}

bool CGameInstance::Is_KeyState(KEY _Key, KEY_STATE _KeyState)
{
	if (nullptr == m_pInput_Manager)
		return false;

	return m_pInput_Manager->Get_KeyState(_Key) == _KeyState;
}

_byte CGameInstance::Get_DIMouseKeyState(MOUSEBUTTON eMouseButtonID)
{
	if (nullptr == m_pInput_Manager)
		return 0;

	return m_pInput_Manager->Get_DIMouseKeyState(eMouseButtonID);
}

_long CGameInstance::Get_DIMouseMoveState(MOUSEMOVE eMouseMove)
{
	if (nullptr == m_pInput_Manager)
		return 0;

	return m_pInput_Manager->Get_DIMouseMoveState(eMouseMove);
}

void CGameInstance::Register_Camera(const _tchar* _CameraTag, CCamera* _CameraCom)
{
	m_pCamera_Manager->Register_Camera(_CameraTag, _CameraCom);
}

void CGameInstance::Set_Camera_Target(CTransform* _Target, const _tchar* _CameraTag)
{
	m_pCamera_Manager->Set_Target(_Target, _CameraTag);
}

CCamera* CGameInstance::Get_Camera(const _tchar* _CameraTag)
{
	return m_pCamera_Manager->Get_Camera(_CameraTag);
}

void CGameInstance::Set_Current_Camera(const _tchar* _CameraTag)
{
	m_pCamera_Manager->Set_Current_Camera(_CameraTag);
}

void CGameInstance::Release_Engine()
{
	CObject_Manager::Get_Instance()->Destroy_Instance();

	CComponent_Manager::Get_Instance()->Destroy_Instance();

	CLevel_Manager::Get_Instance()->Destroy_Instance();

	CGraphic_Device::Get_Instance()->Destroy_Instance();

	CRender_Manager::Get_Instance()->Destroy_Instance();

	CResource_Manager::Get_Instance()->Destroy_Instance();

	CTime_Manager::Get_Instance()->Destroy_Instance();

	CInput_Manager::Get_Instance()->Destroy_Instance();

	CGameInstance::Get_Instance()->Destroy_Instance();

	CCamera_Manager::Get_Instance()->Destroy_Instance();

	CCollision_Manager::Get_Instance()->Destroy_Instance();
}

void CGameInstance::Free()
{
	//Safe_Release(m_pComponent_Manager);
	//Safe_Release(m_pObject_Manager);
	//Safe_Release(m_pLevel_Manager);
	//Safe_Release(m_pGraphic_Device);

	delete this;
}
