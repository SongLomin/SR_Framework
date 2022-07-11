#include "stdafx.h"
#include "Benner.h"
#include "GameInstance.h"

CBenner::CBenner()
{
}

CBenner::CBenner(const CBenner& Prototype)
{
	*this = Prototype;
}

HRESULT CBenner::Initialize(void* pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	_float fX = 640.f;
	_float fY = 80.f;

	_float fSizeX = 180.0f;
	_float fSizeY = 30.0f;

	_uint TextureIndex = 0;
	_uint AlphaValue = 200;

	Set_Texture_Key(TEXT("Benner"));
	SetUp_Varialbes_For_Child(fX, fY, fSizeX, fSizeY, TextureIndex, AlphaValue);

	return S_OK;
}

void CBenner::SetUp_Components_For_Child()
{
}

CBenner* CBenner::Create()
{
	CREATE_PIPELINE(CBenner);
}

CGameObject* CBenner::Clone(void* pArg)
{
	CLONE_PIPELINE(CBenner);
}

void CBenner::Free()
{
	__super::Free();

	delete this;
}

