#include "stdafx.h"
#include "Range.h"
#include "GameInstance.h"

CRange::CRange()
{
}


HRESULT CRange::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CRange::Initialize(void* pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;


	return S_OK;
}

void CRange::Tick(_float fTimeDelta)
{
}

void CRange::LateTick(_float fTimeDelta)
{
}

HRESULT CRange::Render()
{
	return S_OK;
}

HRESULT CRange::SetUp_Components()
{

	return S_OK;
}

CRange* CRange::Create()
{
	CREATE_PIPELINE(CRange);
}

CGameObject* CRange::Clone(void* pArg)
{
	CLONE_PIPELINE(CRange);
}

void CRange::Free()
{
	__super::Free();

	delete this;
}