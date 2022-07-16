#include "stdafx.h"
#include "..\Public\MainApp.h"
#include "GameInstance.h"
#include "Level_Loading.h"
#include <iostream>
#include <cassert>
#include <TextureDrawUI.h>



CMainApp::CMainApp()
	: m_pGameInstance(CGameInstance::Get_Instance())
{
	//Safe_AddRef(m_pGameInstance);
}

HRESULT CMainApp::Initialize()
{
	GRAPHICDESC		GraphicDesc;
	ZeroMemory(&GraphicDesc, sizeof(GRAPHICDESC));

	GraphicDesc.hWnd = g_hWnd;
	GraphicDesc.iWinCX = g_iWinCX;
	GraphicDesc.iWinCY = g_iWinCY;
	GraphicDesc.isWindowMode = true;

	if (FAILED(m_pGameInstance->Initialize_Engine(g_hInst, LEVEL_END, GraphicDesc, &m_pGraphic_Device)))
		return E_FAIL;

	if (FAILED(SetUp_RenderState()))
		return E_FAIL;

	if (FAILED(SetUp_SamplerState()))
		return E_FAIL;

	if (FAILED(Ready_Prototype_Component()))
		return E_FAIL;

	if (FAILED(Open_Level(LEVEL_LOGO)))
		return E_FAIL;

	for (int i = 0; i < LAYERCNT; i++)
	{
		m_pDeferredLayers[i] = static_cast<CTextureDrawUI*>(GAMEINSTANCE->Add_GameObject<CTextureDrawUI>(LEVEL_STATIC, TEXT("RenderTarget")));
		m_pDeferredLayers[i]->Set_Option(
			_float2( //Position
				(g_iWinCX / LAYERCNT) / 2,
				(g_iWinCY / LAYERCNT) / 2 + ((g_iWinCY / LAYERCNT) * i)
			),
			_float2( //Size
				(g_iWinCX / LAYERCNT),
				(g_iWinCY / LAYERCNT)
			), //RenderGroup
			(RENDERGROUP)((_uint)RENDERGROUP::RENDER_NORMAL + i)
		);

		m_pDeferredLayers[i]->Set_Enable(false);
	}

	static_cast<CTextureDrawUI*>(GAMEINSTANCE->Add_GameObject<CTextureDrawUI>(LEVEL_STATIC, TEXT("RenderTarget")))->Set_Option(_float2(g_iWinCX * 0.5, g_iWinCY * 0.5f), _float2(g_iWinCX, g_iWinCY), RENDERGROUP::RENDER_HDR);
	static_cast<CTextureDrawUI*>(GAMEINSTANCE->Add_GameObject<CTextureDrawUI>(LEVEL_STATIC, TEXT("RenderTarget")))->Set_Option(_float2(g_iWinCX * 0.5, g_iWinCY * 0.5f), _float2(g_iWinCX, g_iWinCY), RENDERGROUP::RENDER_BLOOM);
	static_cast<CTextureDrawUI*>(GAMEINSTANCE->Add_GameObject<CTextureDrawUI>(LEVEL_STATIC, TEXT("RenderTarget")))->Set_Option(_float2(g_iWinCX * 0.5, g_iWinCY * 0.5f), _float2(g_iWinCX, g_iWinCY), RENDERGROUP::RENDER_BRIGHTNESS);
	static_cast<CTextureDrawUI*>(GAMEINSTANCE->Add_GameObject<CTextureDrawUI>(LEVEL_STATIC, TEXT("RenderTarget")))->Set_Option(_float2(g_iWinCX * 0.5, g_iWinCY * 0.5f), _float2(g_iWinCX, g_iWinCY), RENDERGROUP::RENDER_POSTPROCCESSING);
	

	return S_OK;
}

void CMainApp::Tick(float fTimeDelta)
{
	if (nullptr == m_pGameInstance)
		return;

	m_pGameInstance->Tick_Engine(fTimeDelta);

	if (GetFocus())
	{
		_point WinSize{ g_iWinCX , g_iWinCY };
		ClientToScreen(g_hWnd, &WinSize);
		RECT ClientRect = { (_long)WinSize.x - g_iWinCX, (_long)WinSize.y - g_iWinCY, (_long)WinSize.x, (_long)WinSize.y };
		ClipCursor(&ClientRect);
	}

	if (KEY_INPUT(KEY::DELETEKEY, KEY_STATE::TAP))
	{
		m_pDeferredLayerEnable = !m_pDeferredLayerEnable;

		for (int i = 0; i < LAYERCNT; i++)
		{
			m_pDeferredLayers[i]->Set_Enable(m_pDeferredLayerEnable);
		}
	}
	
}

HRESULT CMainApp::Render()
{
	if (nullptr == m_pGameInstance)
		return E_FAIL;

	
	m_pGameInstance->Draw_RenderGroup();
	
	

	return S_OK;
}

HRESULT CMainApp::SetUp_RenderState()
{
	m_pGraphic_Device->SetRenderState(D3DRS_LIGHTING, FALSE);
	// m_pGraphic_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);	
	m_pGraphic_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	return S_OK;
}

HRESULT CMainApp::SetUp_SamplerState()
{
	ISVALID(m_pGraphic_Device, E_FAIL);

	//작게 그려지는 경우, 픽셀 선형 보간
	m_pGraphic_Device->SetSamplerState(0, D3DSAMPLERSTATETYPE::D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	//자글자글해지는 것을 보간
	m_pGraphic_Device->SetSamplerState(0, D3DSAMPLERSTATETYPE::D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	//크게 그려지는 경우, 픽셀 선형 보간
	m_pGraphic_Device->SetSamplerState(0, D3DSAMPLERSTATETYPE::D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	//보간의 경우 프레임 드랍을 유발한다.

	return S_OK;
}

HRESULT CMainApp::Open_Level(LEVEL eLevelID)
{
	if (nullptr == m_pGameInstance)
		return E_FAIL;

	CLevel_Loading*		pLevel_Loading = CLevel_Loading::Create(eLevelID);
	if (nullptr == pLevel_Loading)
		return E_FAIL;

	if (FAILED(m_pGameInstance->Open_Level(LEVEL_LOADING, pLevel_Loading)))
		return E_FAIL;

	/* For.Prototype_Component_VIBuffer_Rect*/
	/*if (FAILED(m_pGameInstance->Add_Prototype_Component(typeid(CVIBuffer_Rect).name(),
		CVIBuffer_Rect::Create())))*/
		//return E_FAIL;

	return S_OK;
}

HRESULT CMainApp::Ready_Prototype_Component()
{
	if (nullptr == m_pGameInstance)
		return E_FAIL;

	/* For.Prototype_Component_Renderer */
	//if (FAILED(m_pGameInstance->Add_Prototype(LEVEL_STATIC, typeid(CRenderer).name(),
	//	CRenderer::Create())))
	//	return E_FAIL;

	m_pGameInstance->Add_Prototype_Component(typeid(CRenderer).name(),
		CRenderer::Create());
	//Safe_AddRef(m_pRenderer);

	return S_OK;
}

CMainApp * CMainApp::Create()
{
	CMainApp*		pInstance = new CMainApp();

	if (FAILED(pInstance->Initialize()))
	{
		MessageBox(g_hWnd, TEXT("Failed to Created : CMainApp"), TEXT("System Error"), MB_OK);
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CMainApp::Free()
{		
	CGameInstance::Release_Engine();

	delete this;
}
