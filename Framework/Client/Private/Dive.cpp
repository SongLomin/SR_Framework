#include "stdafx.h"
#include "Dive.h"
#include "GameInstance.h"

CDive::CDive()
{
}

CDive::CDive(const CDive& Prototype)
{
	*this = Prototype;
}

HRESULT CDive::Initialize(void* pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	_float fX = 1130.f;
	_float fY = 160.f;

	_float fSizeX = 100.0f;
	_float fSizeY = 30.0f;

	Set_Texture_Key(TEXT("Dive"));
	SetUp_Varialbes_For_Child(fX, fY, fSizeX, fSizeY);

	return S_OK;
}

void CDive::SetUp_Components_For_Child()
{
}


CDive* CDive::Create()
{
	CREATE_PIPELINE(CDive);
}

CGameObject* CDive::Clone(void* pArg)
{
	CLONE_PIPELINE(CDive);
}

void CDive::Free()
{
	__super::Free();

	delete this;
}
