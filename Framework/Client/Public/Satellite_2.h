#pragma once
#include "Client_Defines.h"
#include "BillBoard_Object.h"


BEGIN(Client)

class CSatellite_2 final : public CBillboard_Object
{
private:
	CSatellite_2();
	CSatellite_2(const CSatellite_2& Prototype);
	virtual ~CSatellite_2() = default;

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
	static CSatellite_2* Create();
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END