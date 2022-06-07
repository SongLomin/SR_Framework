#pragma once



/* 컴포넌트들의 원형을 가지고 있는다. */
#include "Renderer.h"
#include "VIBuffer_Rect.h"

BEGIN(Engine)

class CComponent_Manager final : public CBase
{
	DECLARE_SINGLETON(CComponent_Manager)
public:
	CComponent_Manager();
	virtual ~CComponent_Manager() = default;

public:
	//HRESULT Reserve_Container(_uint iNumLevels);
	HRESULT Add_Prototype(const _char* pPrototypeTag, class CComponent* pPrototype);
	class CComponent* Clone_Component(const _char* pPrototypeTag, void* pArg);


private:
	_uint			m_iNumLevels = 0;

	map<const _char*, class CComponent*>				m_pPrototypes;
	typedef map<const _char*, class CComponent*>		PROTOTYPES;

private:
	class CComponent* Find_Components(const _char* pPrototypeTag);

public:
	virtual void Free() override;
};

END