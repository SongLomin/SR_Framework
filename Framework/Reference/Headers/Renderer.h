#pragma once

/* 화면에 그려져야할 객체들을 그리는 순서대로 모아서 관리하낟.  */
/* 가지고 있는 객체들의 렌더함수를 호출해주낟. */

#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CRenderer final : public CComponent
{
private:
	CRenderer();
	CRenderer(const CRenderer& Prototype);
	virtual ~CRenderer() = default;
	 
public:
	HRESULT Add_RenderGroup(RENDERGROUP	eGroup, class CGameObject* pGameObject);
	HRESULT Set_Textures_From_Key(const _tchar* _Str_Key, MEMORY_TYPE _eType = MEMORY_TYPE::MEMORY_END);
	HRESULT Bind_Texture(_uint _iIndex);
	HRESULT UnBind_Texture();

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;

public:

private:
	vector<LPDIRECT3DBASETEXTURE9>* m_ppTextures = nullptr;

public:
	static CRenderer* Create();
	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;
};

END