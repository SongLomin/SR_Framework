#include "stdafx.h"
#include "AI_HPBar.h"
#include "GameInstance.h"

CAI_HPBar::CAI_HPBar(const CAI_HPBar& Prototype)
{
	*this = Prototype;
}

HRESULT CAI_HPBar::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CAI_HPBar::Initialize(void* pArg)
{
	return S_OK;
}

void CAI_HPBar::Tick(_float fTimeDelta)
{

}

void CAI_HPBar::LateTick(_float fTimeDelta)
{

}

HRESULT CAI_HPBar::Render()
{


	return S_OK;
}

void CAI_HPBar::Update_Hp_Bar(CStatus* pStatus)
{
}

HRESULT CAI_HPBar::SetUp_Components()
{
	return S_OK;
}

CAI_HPBar* CAI_HPBar::Create()
{
	CREATE_PIPELINE(CAI_HPBar);
}

CGameObject* CAI_HPBar::Clone(void* pArg)
{
	CLONE_PIPELINE(CAI_HPBar);
}

void CAI_HPBar::Free()
{
	__super::Free();

	delete this;

}
