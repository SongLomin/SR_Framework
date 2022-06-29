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
    HRESULT Remove_By_MemoryType(MEMORY_TYPE _eMemType);

public: /*For Texture*/
    HRESULT Load_Textures(const _tchar* _strKey, const _tchar* pTextureFilePath, TEXTURE_TYPE eType = TEXTURE_TYPE::TYPE_DEFAULT, MEMORY_TYPE eMemType = MEMORY_TYPE::MEMORY_STATIC);
    vector<LPDIRECT3DBASETEXTURE9>* Get_Textures_From_Key(const _tchar* _Str_Key, MEMORY_TYPE _eType = MEMORY_TYPE::MEMORY_END);

private: /*For Texture*/
    map<const _tchar*, vector<LPDIRECT3DBASETEXTURE9>> m_pTextures[(_uint)MEMORY_TYPE::MEMORY_END];
    typedef vector<LPDIRECT3DBASETEXTURE9>		TEXTURES;

public: /*For Shader*/
    HRESULT Load_Shader(const _tchar* _strKey, const _tchar* pShaderFilePath, MEMORY_TYPE eMemType = MEMORY_TYPE::MEMORY_STATIC);
    ID3DXEffect** Get_Shader_From_Key(const _tchar* _Str_Key, MEMORY_TYPE _eType = MEMORY_TYPE::MEMORY_END);
private:
    map<const _tchar*, ID3DXEffect*> m_pShaders[(_uint)MEMORY_TYPE::MEMORY_END];

public:
    virtual void Free() override;
};

END