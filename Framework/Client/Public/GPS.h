#pragma once
#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CRenderer;
class CTransform;
class CVIBuffer_Rect;
END

BEGIN(Client)

class CGPS abstract : public CGameObject
{
protected:
	CGPS();
	virtual ~CGPS() = default;


public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void LateTick(_float fTimeDelta) override;
	virtual HRESULT Render() override;



private:
	CRenderer* m_pRendererCom = nullptr;
	CTransform* m_pTransformCom = nullptr;
	CVIBuffer_Rect* m_pVIBufferCom = nullptr;

	CTransform* m_pCurrentCamera = nullptr;


private:
	_float					m_fX, m_fY, m_fSizeX, m_fSizeY;
	_float4x4				m_ProjMatrix;
	_point					m_ptMouse;
	RECT					m_rcGPSBox;

private:
	GPS_TYPE				m_eType = GPS_TYPE::GPS_END;

protected:
	HRESULT SetUp_Components();
	virtual void SetUp_For_Child() PURE;
	virtual void SetUp_Varialbes_For_Child(GPS_TYPE _Type, _tchar* TextureTag);

private:
	void Enemy_GPS();
	void Friendly_GPS();
	void LookAtCamera();

public:
	virtual void Free() override;
};

END