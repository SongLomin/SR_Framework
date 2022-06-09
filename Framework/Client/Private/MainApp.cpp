#include "stdafx.h"
#include "..\Public\MainApp.h"
#include "GameInstance.h"
#include "Level_Loading.h"
#include <iostream>
#include <cassert>



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

	if (FAILED(m_pGameInstance->Initialize_Engine(LEVEL_END, GraphicDesc, &m_pGraphic_Device)))
		return E_FAIL;

	if (FAILED(SetUp_RenderState()))
		return E_FAIL;

	if (FAILED(Ready_Prototype_Component()))
		return E_FAIL;

	if (FAILED(Open_Level(LEVEL_LOGO)))
		return E_FAIL;

	return S_OK;
}

void CMainApp::Tick(float fTimeDelta)
{
	if (nullptr == m_pGameInstance)
		return;

	m_pGameInstance->Tick_Engine(fTimeDelta);
}

HRESULT CMainApp::Render()
{
	if (nullptr == m_pGameInstance)
		return E_FAIL;

	m_pGameInstance->Render_Begin();
	m_pGameInstance->Draw_RenderGroup();
	m_pGameInstance->Render_Engine();
	m_pGameInstance->Render_End(g_hWnd);

	return S_OK;
}

HRESULT CMainApp::SetUp_RenderState()
{
	m_pGraphic_Device->SetRenderState(D3DRS_LIGHTING, FALSE);
	// m_pGraphic_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);	
	m_pGraphic_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	return S_OK;
}

HRESULT CMainApp::Open_Level(LEVEL eLevelID)
{
	if (nullptr == m_pGameInstance)
		return E_FAIL;

	CLevel_Loading*		pLevel_Loading = CLevel_Loading::Create(m_pGraphic_Device, eLevelID);
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

	/*m_pGameInstance->Add_Prototype_Component(typeid(CRenderer).name(),
		CRenderer::Create());*/
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
	//Safe_Release(m_pRenderer);
	//Safe_Release(m_pGraphic_Device);
	//Safe_Release(m_pGameInstance);		

	CGameInstance::Release_Engine();

	delete this;
}
