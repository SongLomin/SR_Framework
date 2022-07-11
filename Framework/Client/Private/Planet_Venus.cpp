#include "stdafx.h"
#include "Planet_Venus.h"
#include "GameInstance.h"
#include "Math_Utillity.h"
#include "Level_Loading.h"
#include "Dive.h"



CPlanet_Venus::CPlanet_Venus()
{
}

CPlanet_Venus::CPlanet_Venus(const CPlanet_Venus& Prototype)
{
	*this = Prototype;
}

HRESULT CPlanet_Venus::Initialize(void* pArg)
{

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	_float3 StartPos = { 1.f, 100.f, 300.f };
	_tchar* PontText = TEXT("Venus Planet \n 저 위험 구역 \n \n 임무 : 기본 조작 연습 \n 난이도 :『★』  \n 보상 : XXX");
	_point PontPos = { (LONG)m_vScreenPos.x + 40, (LONG)m_vScreenPos.y - 10 };
	_float3 MyScale = _float3(80.f, 80.f, 50.f);
	_uint TextureIndex = 0;

	SetUp_Varialbes_For_Child(StartPos, PontText, PontPos, TextureIndex, LEVEL::LEVEL_VENUSPLANET, MyScale);
	m_pDiveUi = GAMEINSTANCE->Add_GameObject<CDive>(LEVEL_SELECTPLANET, TEXT("Dive"));
	m_pDiveUi->Set_Enable(false);


	return S_OK;
}

void CPlanet_Venus::SetUp_Components_For_Child()
{
}

CPlanet_Venus* CPlanet_Venus::Create()
{
	CREATE_PIPELINE(CPlanet_Venus);
}

CGameObject* CPlanet_Venus::Clone(void* pArg)
{
	CLONE_PIPELINE(CPlanet_Venus);
}

void CPlanet_Venus::Free()
{
	__super::Free();

	delete this;
}
