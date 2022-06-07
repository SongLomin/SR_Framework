#pragma once
#include "Base.h"


BEGIN(Engine)

class CRender_Manager final : public CBase
{
	DECLARE_SINGLETON(CRender_Manager)
public:

	CRender_Manager();
	virtual ~CRender_Manager() = default;

public:
	HRESULT Add_RenderGroup(RENDERGROUP	eGroup, class CGameObject* pGameObject);
	HRESULT Draw_RenderGroup();

private:
	list<class CGameObject*>				m_RenderObjects[(_uint)RENDERGROUP::RENDER_END];
	typedef list<class CGameObject*>		RENDEROBJECTS;

private:


public:
	virtual void Free() override;
};

END
