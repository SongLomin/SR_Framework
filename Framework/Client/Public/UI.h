#pragma once
#include "stdafx.h"
#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CRenderer;
class CTransform;
class CVIBuffer_Rect;
END


BEGIN(Client)


class CUI abstract : public CGameObject
{
protected:
	CUI();
	virtual ~CUI() = default;

protected:
	// final이 붙은 함수들은 여기서 마지막 호출하겠다는 뜻
	// PURE가 붙은 함수들은 자식클래스에서 무조건 만들어 줘야 한다는 뜻
	virtual HRESULT Initialize_Prototype() final;
	virtual HRESULT Initialize(void* pArg) PURE;
	virtual void Tick(_float fTimeDelta) final;
	virtual void LateTick(_float fTimeDelta) final;
	virtual HRESULT Render() final;

private:
	CRenderer* m_pRendererCom = nullptr;
	CTransform* m_pTransformCom = nullptr;
	CVIBuffer_Rect* m_pVIBufferCom = nullptr;

private:
	_point					m_ptMouse;
	_float4x4				m_ProjMatrix;
	RECT					m_rcRect;
	_bool                   m_bMove = false;

	_uint					m_iTextureIndex;
	_uint					m_iAlphaValue;

private:
	_float	m_fMovement = 0;
	_float  m_fEndPos = 0;
	MOVE_UI_DIR m_eMoveDir = MOVE_UI_DIR::MOVE_UI_END;
private:
	_float					m_fX, m_fY, m_fSizeX, m_fSizeY;

protected:
	HRESULT SetUp_Components();
	virtual void SetUp_Components_For_Child() PURE;
	void SetUp_Varialbes_For_Child(_float _fX, _float _fY, _float _fSizeX, _float _fSizeY, _uint TextureIndex = 0, _uint AlphaValue = 120);
	void Set_Texture_Key(_tchar* _Text, MEMORY_TYPE _MemoryType = MEMORY_TYPE::MEMORY_STATIC);
	void Moving_UI(MOVE_UI_DIR _Dir, _float _movement, _float _EndPos);

		
public:

	virtual void Free() override;
};

END

