#pragma once

#include "State.h"

BEGIN(Engine)

class CTransform;
class CRigid_Body;

class ENGINE_DLL CState_Attack final : public CState
{

private:
	CState_Attack() = default;
	CState_Attack(const CState_Attack& Prototype);
	virtual ~CState_Attack() = default;

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);
	virtual void Tick(_float fTimeDelta) {};
	virtual void LateTick(_float fTimeDelta) {};
	virtual HRESULT Render() { return S_OK; };

public:
	void Attack_Bullet(CGameObject* pBullet, _float fTimeDelta);
	void Attack_Rager(_float fTimeDelta);
	void Attack_Rest(_float fTimeDelta);



public:
	void State_Change(CTransform* pPlayerTransform, _float fTimeDelta);



public:
	static CState_Attack* Create();
	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;

};

END

