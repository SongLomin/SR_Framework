#include "stdafx.h"
#include "SelectPlanet_SkyBox.h"
#include "GameInstance.h"


CSelectPlanet_SkyBox::CSelectPlanet_SkyBox()
{
}

CSelectPlanet_SkyBox::CSelectPlanet_SkyBox(const CSelectPlanet_SkyBox& Prototype)
{
	*this = Prototype;
}


HRESULT CSelectPlanet_SkyBox::Initialize(void* pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	_uint TextureIndex = 1;

	SetUp_Varialbes_For_Child(TextureIndex);

	return S_OK;
}

void CSelectPlanet_SkyBox::SetUp_For_Child()
{
}


CSelectPlanet_SkyBox* CSelectPlanet_SkyBox::Create()
{
	CREATE_PIPELINE(CSelectPlanet_SkyBox);
}

CGameObject* CSelectPlanet_SkyBox::Clone(void* pArg)
{
	CLONE_PIPELINE(CSelectPlanet_SkyBox);
}

void CSelectPlanet_SkyBox::Free()
{
	__super::Free();

	delete this;
}
