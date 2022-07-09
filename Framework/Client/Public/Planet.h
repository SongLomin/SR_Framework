#pragma once
#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CRenderer;
class CTransform;
class CVIBuffer_Rect;
END

BEGIN(Client)

class CPlanet abstract : public CGameObject
{
protected:
	CPlanet();
	virtual ~CPlanet() = default;

protected:
	void Set_Alphavalue(_uint value) {
		m_iAlphaValue = value;
	}

protected:
	virtual HRESULT Initialize_Prototype() final;
	virtual HRESULT Initialize(void* pArg) PURE;
	virtual void Tick(_float fTimeDelta) final;
	virtual void LateTick(_float fTimeDelta) final;
	virtual HRESULT Render() final;

private:
	CTransform* m_pTransformCom = nullptr;
	CRenderer* m_pRendererCom = nullptr;
	CVIBuffer_Rect* m_pVI_BufferCom = nullptr;

protected:
	_float3 m_vScreenPos;

private:
	_float3 m_vStartPos;
	LEVEL  m_eMyLevel = LEVEL::LEVEL_END;
	_float3 m_vMyWorldPos;
	_float3 m_vMyScale;
	_tchar* m_szPontText = nullptr;
	_point  m_lPontPos;
	_uint m_iTextueIndex;
	_uint m_iAlphaValue = 250;

private:
	_bool m_bLevelChange = false;

	RAY		m_MouseWorldRay;

protected:
	HRESULT SetUp_Components();
	virtual void SetUp_Components_For_Child() PURE;
	void SetUp_Varialbes_For_Child(_float3 _StartPos, _tchar* FontText, _point PontPos, _uint TextureIndex, LEVEL _Level, _float3 Scale = _float3(1.f,1.f,1.f));
	
private:
	void LookAtCamera();
	void Update_Ray();
	void Set_MyWorldPos(_float3 _Pos);
	void Set_ScreenPos();

public:
	virtual void Free() override;
};

END