#include "stdafx.h"
#include "Warring.h"
#include "GameInstance.h"

CWarring::CWarring()
{
}

CWarring::CWarring(const CWarring& Prototype)
{
	*this = Prototype;
}

HRESULT CWarring::Initialize(void* pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	_float fX = 640.f;
	_float fY = 130.f;

	_float fSizeX = 300.0f;
	_float fSizeY = 70.0f;

	_uint TextureIndex = 0;
	_uint AlphaValue = 200;

	Set_Texture_Key(TEXT("Warring"));
	SetUp_Varialbes_For_Child(fX, fY, fSizeX, fSizeY, TextureIndex, AlphaValue);

	return S_OK;
}

void CWarring::SetUp_Components_For_Child()
{
}

CWarring* CWarring::Create()
{
	CREATE_PIPELINE(CWarring);
}

CGameObject* CWarring::Clone(void* pArg)
{
	CLONE_PIPELINE(CWarring);
}

void CWarring::Free()
{
	__super::Free();

	delete this;
}
