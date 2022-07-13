#pragma once

#include "Client_Defines.h"
#include "Base.h"



BEGIN(Engine)
class CRenderer;
class CGameInstance;

END

BEGIN(Client)
class CTextureDrawUI;

#define LAYERCNT 4
class CMainApp final : public CBase
{

private:
	CMainApp();
	virtual ~CMainApp() = default;
public:
	HRESULT Initialize();	
	void Tick(float fTimeDelta);
	HRESULT Render();

private:
	CGameInstance*			m_pGameInstance = nullptr;
	LPDIRECT3DDEVICE9		m_pGraphic_Device = nullptr;
	CTextureDrawUI*			m_pDeferredLayers[LAYERCNT] = { nullptr };
	_bool					m_pDeferredLayerEnable = false;



private:
	HRESULT SetUp_RenderState();
	HRESULT SetUp_SamplerState();
	HRESULT Open_Level(LEVEL eLevelID);
	HRESULT Ready_Prototype_Component();

public:
	static CMainApp* Create();
	virtual void Free();

};

END