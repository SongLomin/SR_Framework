#include "stdafx.h"
#include "Planet_Sun.h"
#include "GameInstance.h"
#include "Math_Utillity.h"
#include "Level_Loading.h"
#include "Dive.h"


CPlanet_Sun::CPlanet_Sun()
{
}

CPlanet_Sun::CPlanet_Sun(const CPlanet_Sun& Prototype)
{
	*this = Prototype;
}

HRESULT CPlanet_Sun::Initialize(void* pArg)
{

	if (FAILED(SetUp_Components()))
		return E_FAIL;
	_float3 StartPos = { 200.f, 100.f, 400.f };
	_tchar* PontText = TEXT("Sun \n 보스 구역 \n [Warring]   \n 보상 : XXX");
	_point PontPos = { (LONG)m_vScreenPos.x + 40, (LONG)m_vScreenPos.y - 10 };
	_float3 MyScale = _float3(150.f, 150.f, 50.f);
	_uint TextureIndex = 3;

	// 레벨 추가 안되있음
	SetUp_Varialbes_For_Child(StartPos, PontText, PontPos, TextureIndex, LEVEL::LEVEL_SUNPLANET, MyScale);

	Set_Alphavalue(100);
	m_pDiveUi = GAMEINSTANCE->Add_GameObject<CDive>(LEVEL_SELECTPLANET, TEXT("Dive"));
	m_pDiveUi->Set_Enable(false);


	return S_OK;
}

void CPlanet_Sun::SetUp_Components_For_Child()
{
}

CPlanet_Sun* CPlanet_Sun::Create()
{
	CREATE_PIPELINE(CPlanet_Sun);
}

CGameObject* CPlanet_Sun::Clone(void* pArg)
{
	CLONE_PIPELINE(CPlanet_Sun);
}

void CPlanet_Sun::Free()
{
	__super::Free();

	delete this;
}
