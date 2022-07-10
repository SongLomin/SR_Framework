#include "stdafx.h"
#include "VenusPlanet_SkyBox.h"
#include "GameInstance.h"


CVenusPlanet_SkyBox::CVenusPlanet_SkyBox()
{
}

CVenusPlanet_SkyBox::CVenusPlanet_SkyBox(const CVenusPlanet_SkyBox& Prototype)
{
	*this = Prototype;
}


HRESULT CVenusPlanet_SkyBox::Initialize(void* pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	_uint TextureIndex = 3;

	SetUp_Varialbes_For_Child(TextureIndex);

	return S_OK;
}

void CVenusPlanet_SkyBox::SetUp_For_Child()
{
}


CVenusPlanet_SkyBox* CVenusPlanet_SkyBox::Create()
{
	CREATE_PIPELINE(CVenusPlanet_SkyBox);
}

CGameObject* CVenusPlanet_SkyBox::Clone(void* pArg)
{
	CLONE_PIPELINE(CVenusPlanet_SkyBox);
}

void CVenusPlanet_SkyBox::Free()
{
	__super::Free();

	delete this;
}
