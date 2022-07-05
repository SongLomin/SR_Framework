#pragma once

#include "Base.h"

BEGIN(Engine)

class ENGINE_DLL CLevel abstract : public CBase
{
protected:
	CLevel();
	virtual ~CLevel() = default;

public:
	virtual HRESULT Initialize();
	virtual void Tick(_float TimeDelta);
	virtual HRESULT Render();

	virtual void Change_Level(void* pArg, _uint _iNextLevel) =0;//������ �ٲ� �� ī�޶� ������� �־���
	virtual HRESULT Complete_Condition() = 0;//������ �ٲ� ���� ���� ����/��->�����ϸ� �Ѿ�Բ�

protected:
	_float		m_fTime = 0.f;
	_float      m_fTextBoxTime = 300.f;

	_bool		m_bCinematic = false;
	_uint		m_iNextLevel = 8;//Level
	

public:
	virtual void Free() override;

};

END