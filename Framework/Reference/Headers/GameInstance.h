#pragma once

#include "Graphic_Device.h"
#include "Level_Manager.h"
#include "Object_Manager.h"
#include "Component_Manager.h"
#include "Render_Manager.h"
#include "Resource_Manager.h"
#include "Time_Manager.h"
#include "Input_Manager.h"

/* 1. 게임내에 필요한 객체(매니져등)들을 모아서 보관한다. */
/* 2. 클라이언트 개발자가 접근하기좋은 루트를 제공해준다. 나. */
/* 3. 진짜 필요한 함수만 클라잉언트개발자에게 ㅇ오픈해주낟. */

BEGIN(Engine)

class ENGINE_DLL CGameInstance final : public CBase
{
public:
	DECLARE_SINGLETON(CGameInstance)
public:
	CGameInstance();
	virtual ~CGameInstance() = default;

public:
	HRESULT Initialize_Engine(HINSTANCE hInst, _uint iNumLevels, const GRAPHICDESC& GraphicDesc, LPDIRECT3DDEVICE9* ppOut);
	HRESULT Tick_Engine(_float fTimeDelta);
	HRESULT Render_Engine();
	HRESULT Clear(_uint iLevelID);

	HWND	Get_Window_Handle() const { return  m_Graphic_Desc.hWnd; } 
	GRAPHICDESC Get_Graphic_Desc() const { return m_Graphic_Desc; }

public: /* For.Graphic_Device */	
	void		Render_Begin(void);
	void		Render_End(HWND hWnd = NULL);
	LPDIRECT3DDEVICE9* Get_Device(void);
	HRESULT		Add_Text(_point _Pos, D3DXCOLOR _Color, _float _CountTime, _tchar* _tString, int _iParamCnt, ...);
	HRESULT		Add_Text(_point _Pos, _tchar* _tString, int _iParamCnt, ...);

public: /* For.Level_Manager */
	HRESULT Open_Level(_uint iLevelID, class CLevel* pLevel);
	void	Set_CurrentLevelIndex(_uint iLevelID);
	_uint	Get_CurrentLevelIndex();

public: /* For.Object_Manager */
	template <typename T>
	HRESULT Add_Prototype_GameObject()
	{
		if (nullptr == m_pObject_Manager)
			return E_FAIL;

		if (!m_pObject_Manager->Add_Prototype<T>())
			return E_FAIL;

		return S_OK;
	}
	template <typename T>
	CGameObject* Add_GameObject(_uint iLevelIndex, const _tchar* pLayerTag, CTransform* pParent = nullptr, void* pArg = nullptr)
	{
		return m_pObject_Manager->Add_GameObject<T>(iLevelIndex, pLayerTag, pParent, pArg);
	}
	CGameObject* Get_Player_GameObject();


public: /* For.Component_Mananger */
	HRESULT Add_Prototype_Component(const _char* pPrototypeTag, class CComponent* pPrototype);
	template <typename T>
	T* Clone_Component(void* pArg = nullptr)
	{
		if (nullptr == m_pComponent_Manager)
			return nullptr;

		return m_pComponent_Manager->Clone_Component<T>(pArg);
	}

public: /* For.Render_Mananger */
	HRESULT Add_RenderGroup(RENDERGROUP eGroup, class CGameObject* pGameObject);
	HRESULT Draw_RenderGroup();

public: /* For.Resource_Mananger */
	HRESULT Add_Textures(const _tchar * _strKey, const _tchar * pTextureFilePath, TEXTURE_TYPE eType = TEXTURE_TYPE::TYPE_DEFAULT, MEMORY_TYPE eMemType = MEMORY_TYPE::MEMORY_STATIC);
	HRESULT Remove_Textures_By_MemoryType(MEMORY_TYPE _eMemType);
	vector<LPDIRECT3DBASETEXTURE9>* Get_Textures_From_Key(const _tchar * _Str_Key, MEMORY_TYPE _eType = MEMORY_TYPE::MEMORY_END);

public: /* For.Time_Manager */
	HRESULT Add_Timer(_uint eTimer);
	_float Compute_Timer(_uint eTimer);

public: /* For.Input_Manager */
	bool Is_KeyState(KEY _Key, KEY_STATE _KeyState);
	_byte Get_DIMouseKeyState(MOUSEBUTTON eMouseButtonID);
	_long Get_DIMouseMoveState(MOUSEMOVE eMouseMove);


private:
	CGraphic_Device*				m_pGraphic_Device = nullptr;
	CLevel_Manager*					m_pLevel_Manager = nullptr;
	CObject_Manager*				m_pObject_Manager = nullptr;
	CComponent_Manager*				m_pComponent_Manager = nullptr;
	CRender_Manager*				m_pRender_Manager = nullptr;
	CResource_Manager*				m_pResource_Manager = nullptr;
	CTime_Manager*					m_pTime_Manager = nullptr;
	CInput_Manager*					m_pInput_Manager = nullptr;

private:
	GRAPHICDESC						m_Graphic_Desc;

public:
	static void Release_Engine();
	virtual void Free() override;
};

END