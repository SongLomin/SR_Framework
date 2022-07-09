#include "stdafx.h"
#include "MagmaPlanet_SkyBox.h"
#include "GameInstance.h"


CMagmaPlanet_SkyBox::CMagmaPlanet_SkyBox()
{
}

CMagmaPlanet_SkyBox::CMagmaPlanet_SkyBox(const CMagmaPlanet_SkyBox& Prototype)
{
	*this = Prototype;
}


HRESULT CMagmaPlanet_SkyBox::Initialize(void* pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	_uint TextureIndex = 5;

	SetUp_Varialbes_For_Child(TextureIndex);

	return S_OK;
}

void CMagmaPlanet_SkyBox::SetUp_For_Child()
{
}


CMagmaPlanet_SkyBox* CMagmaPlanet_SkyBox::Create()
{
	CREATE_PIPELINE(CMagmaPlanet_SkyBox);
}

CGameObject* CMagmaPlanet_SkyBox::Clone(void* pArg)
{
	CLONE_PIPELINE(CMagmaPlanet_SkyBox);
}

void CMagmaPlanet_SkyBox::Free()
{
	__super::Free();

	delete this;
}
