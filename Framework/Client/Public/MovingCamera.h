#pragma once
#include "Client_Defines.h"
#include "GameObject.h"


BEGIN(Engine)
class CCamera;
class CTransform;
END

BEGIN(Client)

class CMovingCamera final : public CGameObject
{
public:
	
	typedef struct
	{
		_float fTime;
		_float	fAngle;

		_float3 m_vSpeed;
		_float3 m_vAccel;

		_float  m_fShakeOffset;
		_float  m_fShakeInclination;

		CTransform* m_pStartTransform;
		CTransform* m_pEndTransform;

	}CAMERAROUTE;

private:
	CMovingCamera();
	CMovingCamera(const CMovingCamera& Prototype);
	virtual ~CMovingCamera() = default;

public:
	virtual HRESULT Initialize_Prototype()  override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void LateTick(_float fTimeDelta) override;
	
	virtual HRESULT Render_Begin(ID3DXEffect** Shader = nullptr) override;
	virtual HRESULT Render() override;

public:
	void	Add_Movement(CTransform* _pStartTarget, CTransform* _pEndTarget,CAMERAROUTE _tagRoute);//유동적인 카메라 연출용
	void	Add_Movement(_float _fTime, _float _fAngle,_float3 _vSpeed, _float3 _vAccel, CTransform* _pEndTransform, CTransform* _pStartTransform,_float _fShakeOffSet, _float _fShakeInclination);
	void	Boss_Cinematic(CTransform* _pBossTarget);//이미 만들어져 있는 루트로 그냥 보여줌
	void	Monster_Cinematic(CTransform* _pBossTarget);

private:

private:
	CCamera*		m_pCameraCom;
	CTransform*		m_pTransformCom;

	

	list<CAMERAROUTE>		m_listRoute;
	CAMERAROUTE				m_CameraRoute;
	_bool					m_bFlag = false;;

public:
	static CMovingCamera* Create();
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END