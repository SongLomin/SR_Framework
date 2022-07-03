#pragma once
#include "Client_Defines.h"
#include "Player.h"

BEGIN(Engine)
class CMesh_KangShip;
END

BEGIN(Client)

class CKang_Ship_Body
	final : public CPlayer
{
private:
	CKang_Ship_Body();
	CKang_Ship_Body(const CKang_Ship_Body& Prototype);
	virtual ~CKang_Ship_Body() = default;


public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void LateTick(_float fTimeDelta) override;
	virtual HRESULT Render_Begin(ID3DXEffect** Shader = nullptr) override;
	virtual HRESULT Render() override;



private:
	CMesh_KangShip* m_pMeshCom = nullptr;


public:
	virtual void SetUp_Components_For_Child();

protected: /* For Event Function */
	virtual void On_Change_Controller(const CONTROLLER& _IsAI) override;

public: /* For Event Function */
	virtual void On_Collision_Enter(CCollider* _Other_Collider) override;
	virtual void On_Collision_Stay(CCollider* _Other_Collider) override;
	virtual void On_Collision_Exit(CCollider* _Other_Collider) override;




public:
	static CKang_Ship_Body* Create();
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;

};

END