#include "Resource_Manager.h"
#include "GameInstance.h"

IMPLEMENT_SINGLETON(CResource_Manager)

HRESULT CResource_Manager::Add_Texture(const _tchar* _strKey, const _tchar* pTextureFilePath, TEXTURE_TYPE eType, MEMORY_TYPE eMemType)
{
	_tchar		szTextureFullPath[MAX_PATH] = TEXT("");



	for (_uint i = 0; i < 512; ++i)
	{
		LPDIRECT3DBASETEXTURE9		pTexture = nullptr;

		wsprintf(szTextureFullPath, pTextureFilePath, i);
			
		HRESULT		hr = 0;

		switch (eType)
		{
		case TEXTURE_TYPE::TYPE_CUBE:
			hr = D3DXCreateCubeTextureFromFile(DEVICE, szTextureFullPath, (LPDIRECT3DCUBETEXTURE9*)&pTexture);
			break;
		case TEXTURE_TYPE::TYPE_DEFAULT:
			hr = D3DXCreateTextureFromFile(DEVICE, szTextureFullPath, (LPDIRECT3DTEXTURE9*)&pTexture);
			break;
		}

		if (FAILED(hr))
		{
			if (0 == i)
			{
				return E_FAIL;
			}

			else
			{
				return S_OK;
			}
		}

		m_pTextures[(_uint)eMemType][_strKey].push_back(pTexture);
		if (0==_tcscmp(szTextureFullPath, pTextureFilePath))
			break;
	}

	return S_OK;
}

HRESULT CResource_Manager::Remove_By_MemoryType(MEMORY_TYPE _eMemType)
{
	for (auto& pair : m_pTextures[(_uint)_eMemType])
	{
		for (auto& elem : pair.second)
		{
			elem->Release();
		}

		pair.second.clear();
	}

	m_pTextures[(_uint)_eMemType].clear();

	return S_OK;
}

vector<LPDIRECT3DBASETEXTURE9>* CResource_Manager::Get_Textures_From_Key(const _tchar* _Str_Key, MEMORY_TYPE _eType)
{
	if (MEMORY_TYPE::MEMORY_END == _eType)
	{
		auto	iter = find_if(m_pTextures[(_uint)MEMORY_TYPE::MEMORY_STATIC].begin(), m_pTextures[(_uint)MEMORY_TYPE::MEMORY_STATIC].end(), CTag_Finder(_Str_Key));
		
		if (m_pTextures[(_uint)MEMORY_TYPE::MEMORY_STATIC].end() != iter)
		{
			return &(*iter).second;
		}

		iter = find_if(m_pTextures[(_uint)MEMORY_TYPE::MEMORY_DYNAMIC].begin(), m_pTextures[(_uint)MEMORY_TYPE::MEMORY_DYNAMIC].end(), CTag_Finder(_Str_Key));
		
		if (m_pTextures[(_uint)MEMORY_TYPE::MEMORY_DYNAMIC].end() != iter)
		{
			return &(*iter).second;
		}
	}
	else
	{
		auto	iter = find_if(m_pTextures[(_uint)_eType].begin(), m_pTextures[(_uint)_eType].end(), CTag_Finder(_Str_Key));

		if (m_pTextures[(_uint)_eType].end() != iter)
		{
			return &(*iter).second;
		}
	}

	return nullptr;
}

void CResource_Manager::Free()
{
	__super::Free();

	Remove_By_MemoryType(MEMORY_TYPE::MEMORY_DYNAMIC);
	Remove_By_MemoryType(MEMORY_TYPE::MEMORY_STATIC);

	delete this;
}
