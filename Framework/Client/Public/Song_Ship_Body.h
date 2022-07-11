#pragma once

#include "Client_Defines.h"
#include "Player.h"

BEGIN(Engine)
class CMesh_SongShip;
class CMesh_Ship1;
class CMesh_Ship6;
END

BEGIN(Client)

class CSong_Ship_Body final : 
	public CPlayer
{
private:
	CSong_Ship_Body();
	CSong_Ship_Body(const CSong_Ship_Body& Prototype);
	virtual ~CSong_Ship_Body() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg)override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void LateTick(_float fTimeDelta) override;
	virtual HRESULT Render_Begin(ID3DXEffect** Shader = nullptr) override;
	virtual HRESULT Render() override;


private:
	//CMesh_SongShip*				m_pMeshCom = nullptr;
	//CMesh_Ship1*                    m_pMeshCom = nullptr;
	CMesh_Ship6* m_pMeshCom = nullptr;



protected: /* For Event Function */
	virtual void On_Change_Controller(const CONTROLLER& _IsAI) override;

public: /* For Event Function */
	virtual void On_Collision_Enter(CCollider* _Other_Collider) override;
	virtual void On_Collision_Stay(CCollider* _Other_Collider) override;
	virtual void On_Collision_Exit(CCollider* _Other_Collider) override;

public:
	virtual void SetUp_Components_For_Child();

public:
	static CSong_Ship_Body* Create();
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END