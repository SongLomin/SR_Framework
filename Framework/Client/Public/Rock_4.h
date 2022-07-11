#pragma once
#include "Client_Defines.h"
#include "BillBoard_Object.h"


BEGIN(Client)

class CRock_4 final : public CBillboard_Object
{
private:
	CRock_4();
	CRock_4(const CRock_4& Prototype);
	virtual ~CRock_4() = default;

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
	static CRock_4* Create();
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END
