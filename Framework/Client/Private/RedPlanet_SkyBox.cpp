#include "stdafx.h"
#include "RedPlanet_SkyBox.h"
#include "GameInstance.h"


CRedPlanet_SkyBox::CRedPlanet_SkyBox()
{
}

CRedPlanet_SkyBox::CRedPlanet_SkyBox(const CRedPlanet_SkyBox& Prototype)
{
	*this = Prototype;
}


HRESULT CRedPlanet_SkyBox::Initialize(void* pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	_uint TextureIndex = 2;

	SetUp_Varialbes_For_Child(TextureIndex);

	return S_OK;
}

void CRedPlanet_SkyBox::SetUp_For_Child()
{
}


CRedPlanet_SkyBox* CRedPlanet_SkyBox::Create()
{
	CREATE_PIPELINE(CRedPlanet_SkyBox);
}

CGameObject* CRedPlanet_SkyBox::Clone(void* pArg)
{
	CLONE_PIPELINE(CRedPlanet_SkyBox);
}

void CRedPlanet_SkyBox::Free()
{
	__super::Free();

	delete this;
}
