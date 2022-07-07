#include "stdafx.h"
#include "TextBox.h"
#include "GameInstance.h"

CTextBox::CTextBox()
{
}

CTextBox::CTextBox(const CTextBox& Prototype)
{
	*this = Prototype;
}

HRESULT CTextBox::Initialize(void* pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	_float fX = 630.f;
	_float fY = 620.f;

	_float fSizeX = 250.0f;
	_float fSizeY = 90.0f;

	Set_Texture_Key(TEXT("TextBox_Yang"));
	SetUp_Varialbes_For_Child(fX, fY, fSizeX, fSizeY);

	return S_OK;
}

void CTextBox::SetUp_Components_For_Child()
{
}

CTextBox* CTextBox::Create()
{
	CREATE_PIPELINE(CTextBox);
}

CGameObject* CTextBox::Clone(void* pArg)
{
	CLONE_PIPELINE(CTextBox);
}

void CTextBox::Free()
{
	__super::Free();

	delete this;
}