#include "stdafx.h"
#include "Effect.h"
#include "GameInstance.h"

CEffect::CEffect()
{
}

HRESULT CEffect::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CEffect::Initialize(void* pArg)
{
	return S_OK;
}

void CEffect::Tick(_float fTimeDelta)
{
}

void CEffect::LateTick(_float fTimeDelta)
{
}

HRESULT CEffect::Render_Begin(ID3DXEffect** Shader)
{
	return S_OK;
}

HRESULT CEffect::Render()
{
	return S_OK;
}

HRESULT CEffect::SetUp_Components()
{
	m_pTransformCom = Add_Component<CTransform>();
	WEAK_PTR(m_pTransformCom);
	m_pRendererCom = Add_Component<CRenderer>();
	WEAK_PTR(m_pRendererCom);


	SetUp_Components_For_Child();
	return S_OK;
}



void CEffect::Free()
{
	__super::Free();
}
