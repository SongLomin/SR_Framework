#include "stdafx.h"
#include "Quest.h"
#include "GameInstance.h"

CQuest::CQuest()
{
}

CQuest::CQuest(const CQuest& Prototype)
{
	*this = Prototype;
}

HRESULT CQuest::Initialize(void* pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	Set_Texture_Key(TEXT("Quest"));

	_float fX = 1380.f;
	_float fY = 80.f;

	_float fSizeX = 160.0f;
	_float fSizeY = 50.0f;

	_float Movement = 0.8f;
	_float EndPos = 1120.f;

	Set_Texture_Key(TEXT("Quest"));
	SetUp_Varialbes_For_Child(fX, fY, fSizeX, fSizeY);
	Moving_UI(MOVE_UI_DIR::MOVE_UI_LEFT, Movement, EndPos);

	return S_OK;
}

void CQuest::SetUp_Components_For_Child()
{
}

CQuest* CQuest::Create()
{
	CREATE_PIPELINE(CQuest);
}

CGameObject* CQuest::Clone(void* pArg)
{
	CLONE_PIPELINE(CQuest);
}

void CQuest::Free()
{
	__super::Free();

	delete this;
}

