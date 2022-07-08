#include "stdafx.h"
#include "BulletCountUI.h"
#include "GameInstance.h"

CBulletCountUI::CBulletCountUI(const CBulletCountUI& Prototype)
{
	*this = Prototype;

}

HRESULT CBulletCountUI::Initialize(void* pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL; 


	_float fX = 1200.f;
	_float fY = 630.f;

	_float fSizeX = 43.0f;
	_float fSizeY = 48.0f;

	Set_Texture_Key(TEXT("EmptyItem"));
	SetUp_Varialbes_For_Child(fX, fY, fSizeX, fSizeY);

	return S_OK;
}


void CBulletCountUI::SetUp_Components_For_Child()
{
}

CBulletCountUI* CBulletCountUI::Create()
{
	CREATE_PIPELINE(CBulletCountUI);
}

CGameObject* CBulletCountUI::Clone(void* pArg)
{
	CLONE_PIPELINE(CBulletCountUI);
}

void CBulletCountUI::Free()
{
	__super::Free();

	delete this;
}