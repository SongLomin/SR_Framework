#include "stdafx.h"
#include "StatusBar.h"
#include "GameInstance.h"



CStatusBar::CStatusBar(const CStatusBar& Prototype)
{
	*this = Prototype;

}

HRESULT CStatusBar::Initialize(void* pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	_float fX = 200.f;
	_float fY = 45.f;

	_float fSizeX = 190.0f;
	_float fSizeY = 35.0f;

	Set_Texture_Key(TEXT("Status"));
	SetUp_Varialbes_For_Child(fX, fY, fSizeX, fSizeY);
	return S_OK;
}

void CStatusBar::SetUp_Components_For_Child()
{
}


CStatusBar* CStatusBar::Create()
{
	CREATE_PIPELINE(CStatusBar);
}

CGameObject* CStatusBar::Clone(void* pArg)
{
	CLONE_PIPELINE(CStatusBar);
}

void CStatusBar::Free()
{
	__super::Free();

	delete this;
}
