#include "stdafx.h"
#include "Planet_Magma.h"
#include "GameInstance.h"
#include "Math_Utillity.h"
#include "Level_Loading.h"
#include "Dive.h"

CPlanet_Magma::CPlanet_Magma()
{
}

CPlanet_Magma::CPlanet_Magma(const CPlanet_Magma& Prototype)
{
	*this = Prototype;
}

HRESULT CPlanet_Magma::Initialize(void* pArg)
{

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	_float3 StartPos = { 300.f, 150.f, 200.f };
	_tchar* PontText = TEXT("Magma Planet \n 고 위험 구역 \n 임무 : 제한 시간 내 모든 기체 파괴  \n 난이도 :『★★★★★★』 \n 보상 : XXX");
	_point PontPos = { (LONG)m_vScreenPos.x + 40, (LONG)m_vScreenPos.y - 10 };
	_float3 MyScale = _float3(100.f, 100.f, 50.f);
	_uint TextureIndex = 4;

	SetUp_Varialbes_For_Child(StartPos, PontText, PontPos, TextureIndex, LEVEL::LEVEL_MAGMAPLANET, MyScale);
	m_pDiveUi = GAMEINSTANCE->Add_GameObject<CDive>(LEVEL_SELECTPLANET, TEXT("Dive"));
	m_pDiveUi->Set_Enable(false);


	return S_OK;
}


void CPlanet_Magma::SetUp_Components_For_Child()
{


}
	

CPlanet_Magma* CPlanet_Magma::Create()
{
	CREATE_PIPELINE(CPlanet_Magma);
}

CGameObject* CPlanet_Magma::Clone(void* pArg)
{
	CLONE_PIPELINE(CPlanet_Magma);
}

void CPlanet_Magma::Free()
{

	__super::Free();

	delete this;
}

