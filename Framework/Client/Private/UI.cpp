#include "stdafx.h"
#include "UI.h"
#include "GameInstance.h"


CUI::CUI()
{
}

HRESULT CUI::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CUI::Initialize(void* pArg)
{


	return S_OK;
}

void CUI::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

}

void CUI::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	
}

HRESULT CUI::Render()
{
	__super::Render();

	return S_OK;
}

HRESULT CUI::SetUp_Components()
{

	return S_OK;
}

void CUI::Free()
{
	__super::Free();
}
