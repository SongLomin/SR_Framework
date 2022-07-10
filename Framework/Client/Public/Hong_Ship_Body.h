#pragma once
#include "Client_Defines.h"
#include "Player.h"

BEGIN(Engine)
class CMesh_HongShip;
END

BEGIN(Client)

class CHong_Ship_Body
	final : public CPlayer
{
private:
	CHong_Ship_Body();
	CHong_Ship_Body(const CHong_Ship_Body& Prototype);
	virtual ~CHong_Ship_Body() = default;


public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void LateTick(_float fTimeDelta) override;
	virtual HRESULT Render_Begin(ID3DXEffect** Shader = nullptr) override;
	virtual HRESULT Render() override;


public:
	virtual void SetUp_Components_For_Child();

protected: /* For Event Function */
	virtual void On_Change_Controller(const CONTROLLER& _IsAI) override;

public: /* For Event Function */
	virtual void On_Collision_Enter(CCollider* _Other_Collider) override;
	virtual void On_Collision_Stay(CCollider* _Other_Collider) override;
	virtual void On_Collision_Exit(CCollider* _Other_Collider) override;




public:
	static CHong_Ship_Body* Create();
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;

};

END