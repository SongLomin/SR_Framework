#include "stdafx.h"
#include "BulletUI.h"
#include "GameInstance.h"

CBulletUI::CBulletUI(const CBulletUI& Prototype)
{
	*this = Prototype;
	/*	if (KEY_INPUT(KEY::LBUTTON, KEY_STATE::TAP))
		{
			m_pRendererCom->Set_Textures_From_Key(TEXT("MainWeapon"), MEMORY_TYPE::MEMORY_STATIC);
		}

		if (KEY_INPUT(KEY::RBUTTON, KEY_STATE::TAP))
		{
			m_pRendererCom->Set_Textures_From_Key(TEXT("SubWeapon"), MEMORY_TYPE::MEMORY_STATIC);
		}*/
}

HRESULT CBulletUI::Initialize(void* pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	

	_float fX = 80.f;
	_float fY = 630.f;

	_float fSizeX = 43.0f;
	_float fSizeY = 50.0f;

	Set_Texture_Key(TEXT("MainWeapon"));
	SetUp_Varialbes_For_Child(fX, fY, fSizeX, fSizeY);

	return S_OK;
}

void CBulletUI::SetUp_Components_For_Child()
{
}

CBulletUI* CBulletUI::Create()
{
	CREATE_PIPELINE(CBulletUI);
}

CGameObject* CBulletUI::Clone(void* pArg)
{
	CLONE_PIPELINE(CBulletUI);
}

void CBulletUI::Free()
{
	__super::Free();

	delete this;
}

