#include "stdafx.h"
#include "Boss_Name.h"

CBossName::CBossName(const CBossName& Prototype)
{
	*this = Prototype;

}

HRESULT CBossName::Initialize(void* pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	_float fX = 640.f;
	_float fY = 50.f;

	_float fSizeX = 50.0f;
	_float fSizeY = 15.0f;

	Set_Texture_Key(TEXT("Boss_Name"));
	SetUp_Varialbes_For_Child(fX, fY, fSizeX, fSizeY);
	return S_OK;
}

void CBossName::SetUp_Components_For_Child()
{
}


CBossName* CBossName::Create()
{
	CREATE_PIPELINE(CBossName);
}

CGameObject* CBossName::Clone(void* pArg)
{
	CLONE_PIPELINE(CBossName);
}

void CBossName::Free()
{
	__super::Free();

	delete this;
}
