#include "..\Public\Texture.h"

CTexture::CTexture(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CComponent(pGraphic_Device)
{
}

CTexture::CTexture(const CTexture & Prototype)
	: CComponent(Prototype)
	, m_Textures(Prototype.m_Textures)
	, m_iNumTextures(Prototype.m_iNumTextures)
{
	for (auto& pTexture : m_Textures)
		Safe_AddRef(pTexture);
}

HRESULT CTexture::Initialize_Prototype(TYPE eType, const _tchar * pTextureFilePath, _uint iNumTextures)
{
	m_Textures.reserve(iNumTextures);

	m_iNumTextures = iNumTextures;

	_tchar		szTextureFullPath[MAX_PATH] = TEXT("");

	for (_uint i = 0; i < m_iNumTextures; ++i)
	{
		LPDIRECT3DBASETEXTURE9		pTexture = nullptr;

		wsprintf(szTextureFullPath, pTextureFilePath, i);

		HRESULT		hr = 0;

		switch (eType)
		{
			/* dds photoshop plugin */
		case TYPE_CUBE:
			hr = D3DXCreateCubeTextureFromFile(m_pGraphic_Device, szTextureFullPath, (LPDIRECT3DCUBETEXTURE9*)&pTexture);
			break;
		case TYPE_DEFAULT:
			hr = D3DXCreateTextureFromFile(m_pGraphic_Device, szTextureFullPath, (LPDIRECT3DTEXTURE9*)&pTexture);
			break;
		}

		if (FAILED(hr))
			return E_FAIL;

		m_Textures.push_back(pTexture);
	}

	return S_OK;
}

HRESULT CTexture::Initialize(void * pArg)
{
	return S_OK;
}

HRESULT CTexture::Bind_Texture(_uint iTextureIndex)
{
	if (iTextureIndex >= m_iNumTextures)
		return E_FAIL;

	m_pGraphic_Device->SetTexture(0, m_Textures[iTextureIndex]);	

	return S_OK;
}

CTexture * CTexture::Create(LPDIRECT3DDEVICE9 pGraphic_Device, TYPE eType, const _tchar * pTextureFilePath, _uint iNumTextures)
{
	CTexture*		pInstance = new CTexture(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype(eType, pTextureFilePath, iNumTextures)))
	{
		MSG_BOX("Failed to Created : CTexture");
		Safe_Release(pInstance);
	}

	return pInstance;
} 

CComponent * CTexture::Clone(void * pArg)
{
	CTexture*		pInstance = new CTexture(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CTexture");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CTexture::Free()
{
	__super::Free();

	for (auto& pTexture : m_Textures)
		Safe_Release(pTexture);

	m_Textures.clear();
}
