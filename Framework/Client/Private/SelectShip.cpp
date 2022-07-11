#include "stdafx.h"
#include "SelectShip.h"
#include "GameInstance.h"

CSelectShip::CSelectShip()
{
}

CSelectShip::CSelectShip(const CSelectShip& Prototype)
{
	*this = Prototype;
}

HRESULT CSelectShip::Initialize(void* pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	_float fX = 640.f;
	_float fY = 600.f;

	_float fSizeX = 180.0f;
	_float fSizeY = 30.0f;

	_uint TextureIndex = 0;
	_uint AlphaValue = 200;

	Set_Texture_Key(TEXT("Font_UI"));

	SetUp_Varialbes_For_Child(fX, fY, fSizeX, fSizeY, TextureIndex, AlphaValue);

	return S_OK;
}

void CSelectShip::SetUp_Components_For_Child()
{
}

CSelectShip* CSelectShip::Create()
{
	CREATE_PIPELINE(CSelectShip);
}

CGameObject* CSelectShip::Clone(void* pArg)
{
	CLONE_PIPELINE(CSelectShip);
}

void CSelectShip::Free()
{
	__super::Free();

	delete this;
}