#pragma once
#include "Base.h"

BEGIN(Engine)

class CResource_Manager final :
    public CBase
{
    DECLARE_SINGLETON(CResource_Manager)
    
public:
    CResource_Manager() = default;
    virtual ~CResource_Manager() = default;

public:
    HRESULT Add_Texture(const _tchar* _strKey, const _tchar* pTextureFilePath, TEXTURE_TYPE eType = TEXTURE_TYPE::TYPE_DEFAULT, MEMORY_TYPE eMemType = MEMORY_TYPE::MEMORY_STATIC);
    HRESULT Remove_By_MemoryType(MEMORY_TYPE _eMemType);
    vector<LPDIRECT3DBASETEXTURE9>* Get_Textures_From_Key(const _tchar* _Str_Key, MEMORY_TYPE _eType = MEMORY_TYPE::MEMORY_END);


private:
    map<const _tchar*, vector<LPDIRECT3DBASETEXTURE9>> m_pTextures[(_uint)MEMORY_TYPE::MEMORY_END];
    typedef vector<LPDIRECT3DBASETEXTURE9>		TEXTURES;

public:
    virtual void Free() override;
};

END