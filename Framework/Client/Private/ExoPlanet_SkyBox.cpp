#include "stdafx.h"
#include "ExoPlanet_SkyBox.h"
#include "GameInstance.h"


CExoPlanet_SkyBox::CExoPlanet_SkyBox()
{
}

CExoPlanet_SkyBox::CExoPlanet_SkyBox(const CExoPlanet_SkyBox& Prototype)
{
	*this = Prototype;
}


HRESULT CExoPlanet_SkyBox::Initialize(void* pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	_uint TextureIndex = 4;

	SetUp_Varialbes_For_Child(TextureIndex);

	return S_OK;
}

void CExoPlanet_SkyBox::SetUp_For_Child()
{
}


CExoPlanet_SkyBox* CExoPlanet_SkyBox::Create()
{
	CREATE_PIPELINE(CExoPlanet_SkyBox);
}

CGameObject* CExoPlanet_SkyBox::Clone(void* pArg)
{
	CLONE_PIPELINE(CExoPlanet_SkyBox);
}

void CExoPlanet_SkyBox::Free()
{
	__super::Free();

	delete this;
}
