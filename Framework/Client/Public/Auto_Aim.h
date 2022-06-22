#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CTransform;
class CRenderer;
class CTargetting;
END


BEGIN(Client)

class CAuto_Aim final : public CGameObject
{
private:
	CAuto_Aim();
	CAuto_Aim(const CAuto_Aim& Prototype);
	virtual ~CAuto_Aim() = default;



public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void LateTick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

private: /* 현재 객체에게 필요한 컴포넌트를 복제해온다. */
	HRESULT SetUp_Components();


private:
	CTransform* m_pTransformCom = nullptr;
	CRenderer* m_pRendererCom = nullptr;
	CTargetting* m_pTargettingCom = nullptr;

	POINT m_pt = {};

	bool m_bUse = false;

	list<CGameObject*>* m_pTargetList;
public:
	static CAuto_Aim* Create();
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END