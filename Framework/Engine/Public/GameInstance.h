#pragma once

#include "Graphic_Device.h"
#include "Level_Manager.h"
#include "Object_Manager.h"
#include "Component_Manager.h"
#include "Render_Manager.h"
#include "Resource_Manager.h"

/* 1. ���ӳ��� �ʿ��� ��ü(�Ŵ�����)���� ��Ƽ� �����Ѵ�. */
/* 2. Ŭ���̾�Ʈ �����ڰ� �����ϱ����� ��Ʈ�� �������ش�. ��. */
/* 3. ��¥ �ʿ��� �Լ��� Ŭ���׾�Ʈ�����ڿ��� ���������ֳ�. */

BEGIN(Engine)

class ENGINE_DLL CGameInstance final : public CBase
{
public:
	DECLARE_SINGLETON(CGameInstance)
public:
	CGameInstance();
	virtual ~CGameInstance() = default;

public: /* ���� ���̺귲�� ����Ҷ� �ʿ��� �ʱ�ȭ �������� ��ĥ�ž�. */
	HRESULT Initialize_Engine(_uint iNumLevels, const GRAPHICDESC& GraphicDesc, LPDIRECT3DDEVICE9* ppOut);
	HRESULT Tick_Engine(_float fTimeDelta);
	HRESULT Render_Engine();
	HRESULT Clear(_uint iLevelID);

public: /* For.Graphic_Device */	
	void		Render_Begin(void);
	void		Render_End(HWND hWnd = NULL);
	LPDIRECT3DDEVICE9* Get_Device(void);


public: /* For.Level_Manager */
	HRESULT Open_Level(_uint iLevelID, class CLevel* pLevel);

public: /* For.Object_Manager */
	HRESULT Add_Prototype(const _tchar* pPrototypeTag, class CGameObject* pPrototype);
	HRESULT Add_GameObject(_uint iLevelIndex, const _tchar* pLayerTag, const _tchar* pPrototypeTag, void* pArg = nullptr);

public: /* For.Component_Mananger */
	HRESULT Add_Prototype(const _char* pPrototypeTag, class CComponent* pPrototype);
	class CComponent* Clone_Component(const _char* pPrototypeTag, void* pArg = nullptr);

public: /* For.Render_Mananger */
	HRESULT Add_RenderGroup(RENDERGROUP eGroup, class CGameObject* pGameObject);
	HRESULT Draw_RenderGroup();

public: /* For.Resource_Mananger */
	HRESULT Add_Textures(const _tchar * _strKey, const _tchar * pTextureFilePath, TEXTURE_TYPE eType = TEXTURE_TYPE::TYPE_DEFAULT, MEMORY_TYPE eMemType = MEMORY_TYPE::MEMORY_STATIC);
	HRESULT Remove_Textures_By_MemoryType(MEMORY_TYPE _eMemType);
	vector<LPDIRECT3DBASETEXTURE9>* Get_Textures_From_Key(const _tchar * _Str_Key, MEMORY_TYPE _eType = MEMORY_TYPE::MEMORY_END);

private:
	CGraphic_Device*				m_pGraphic_Device = nullptr;
	CLevel_Manager*					m_pLevel_Manager = nullptr;
	CObject_Manager*				m_pObject_Manager = nullptr;
	CComponent_Manager*				m_pComponent_Manager = nullptr;
	CRender_Manager*				m_pRender_Manager = nullptr;
	CResource_Manager*				m_pResource_Manager = nullptr;

public:
	static void Release_Engine();
	virtual void Free() override;
};

END