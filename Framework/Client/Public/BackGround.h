#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CRenderer;
class CVIBuffer_Rect;
class CTransform;
class CStatus;
class CMesh_Cube;
class CRigid_Body;
class CTargetting;
END

BEGIN(Client)
class CCameraPosin;
class CBackGround final : public CGameObject
{
private:
	CBackGround();
	CBackGround(const CBackGround& Prototype);
	virtual ~CBackGround() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg)override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void LateTick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

public:
	void Set_Targetting();

private:
	CTransform*				m_pTransformCom = nullptr;
	CRenderer*				m_pRendererCom = nullptr;
	CMesh_Cube*				m_pMeshCubeCom = nullptr;
	CStatus*				m_pStatusCom = nullptr;
	CRigid_Body*			m_pRigidBodyCom = nullptr;
	CTargetting*			m_pTargettingCom = nullptr;

private:
	CCameraPosin*           m_pCameraPosin = nullptr;
	static const _tchar*	m_pTag;

	_uint					m_iCurrentCam = 0;

protected: /* 이벤트 함수들 정의 */
	virtual void On_Change_Controller(const CONTROLLER& _IsAI) override;


private: /* 현재 객체에게 필요한 컴포넌트를 복제해온다. */
	HRESULT SetUp_Components();

public:
	static CBackGround* Create();
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END