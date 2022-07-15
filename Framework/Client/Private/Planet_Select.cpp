#include "stdafx.h"
#include "Planet_Select.h"
#include "GameInstance.h"
#include "Dive.h"

CPlanet_Select::CPlanet_Select()
{
}

CPlanet_Select::CPlanet_Select(const CPlanet_Select& Prototype)
{
	*this = Prototype;
}

HRESULT CPlanet_Select::Initialize(void* pArg)
{
	__super::Initialize(pArg);

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	_float3 StartPos = { 0.f, 100.f, 400.f };
	_tchar* PontText = TEXT("Earth Planet \n 'F' 키를 눌러 크루즈 드라이브를 사용하세요 ");
	_point PontPos = { (LONG)m_vScreenPos.x + 40, (LONG)m_vScreenPos.y - 10 };
	_float3 MyScale = _float3(100.f, 100.f, 50.f);
	_uint TextureIndex = 5;

	SetUp_Varialbes_For_Child(StartPos, PontText, PontPos, TextureIndex, LEVEL::LEVEL_SELECTPLANET, MyScale);

	m_pDiveUi = GAMEINSTANCE->Add_GameObject<CDive>(LEVEL_SELECTPLANET, TEXT("Dive"));
	m_pDiveUi->Set_Enable(false);
}

void CPlanet_Select::SetUp_Components_For_Child()
{
}

CPlanet_Select* CPlanet_Select::Create()
{
	CREATE_PIPELINE(CPlanet_Select);
}

CGameObject* CPlanet_Select::Clone(void* pArg)
{
	CLONE_PIPELINE(CPlanet_Select);
}

void CPlanet_Select::Free()
{
	__super::Free();

	delete this;
}
