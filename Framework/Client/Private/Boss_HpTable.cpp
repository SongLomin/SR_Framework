#include "stdafx.h"
#include "Boss_HpTable.h"

CBossHpTable::CBossHpTable(const CBossHpTable& Prototype)
{
	*this = Prototype;

}

HRESULT CBossHpTable::Initialize(void* pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	_float fX = 640.f;
	_float fY = 85.f;

	_float fSizeX = 400.0f;
	_float fSizeY = 10.0f;

	Set_Texture_Key(TEXT("Boss_HP_Table"));
	SetUp_Varialbes_For_Child(fX, fY, fSizeX, fSizeY);
	return S_OK;
}

void CBossHpTable::SetUp_Components_For_Child()
{
}


CBossHpTable* CBossHpTable::Create()
{
	CREATE_PIPELINE(CBossHpTable);
}

CGameObject* CBossHpTable::Clone(void* pArg)
{
	CLONE_PIPELINE(CBossHpTable);
}

void CBossHpTable::Free()
{
	__super::Free();

	delete this;
}
