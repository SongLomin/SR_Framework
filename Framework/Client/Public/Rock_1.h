#pragma once
#include "Client_Defines.h"
#include "Rock.h"


BEGIN(Client)

class CRock_1 final : public CRock
{
private:
	CRock_1();
	CRock_1(const CRock_1& Prototype);
	virtual ~CRock_1() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void LateTick(_float fTimeDelta) override;
	virtual HRESULT Render() override;


public: /* For Event Function */
	virtual void On_Collision_Enter(CCollider* _Other_Collider) override;
	virtual void On_Collision_Stay(CCollider* _Other_Collider) override;
	virtual void On_Collision_Exit(CCollider* _Other_Collider) override;

protected:
	virtual void SetUp_Components_For_Chiled();

public:
	static CRock_1* Create();
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END
