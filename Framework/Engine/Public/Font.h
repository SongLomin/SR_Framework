#pragma once

#include "Base.h"

BEGIN(Engine)

class ENGINE_DLL CFont final : public CBase
{

public:
	CFont();
	virtual ~CFont() = default;

public:
	TEXTINFO Get_Font() {
		return m_tTextInfo;
	}

	_float Get_CountTime() {
		return m_fCountTime;
	}
	
	void Minus_CountTime(_float Time) {
		m_fCountTime -= Time;
	}

public:
	void Set_Param(TEXTINFO* TextInfo, _float CountTime) {
		m_fCountTime = CountTime;
		memcpy(&m_tTextInfo, TextInfo, sizeof(TEXTINFO));
	}

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(TEXTINFO* TextInfo, _float CountTime);



private:
	TEXTINFO					m_tTextInfo;
	_float						m_fCountTime = 0.f;

public:
	static CFont* Create(TEXTINFO* TextInfo, _float CountTime);
	virtual void Free() override;
};

END