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

	virtual void Change_Level(void* pArg) =0;//������ �ٲ� �� ī�޶� ������� �־���
	virtual HRESULT Complete_Condition() = 0;//������ �ٲ� ���� ���� ����/��->�����ϸ� �Ѿ�Բ�

protected:
	_float		m_fTime = 0.f;
	_bool		m_bCinematic = false;

public:
	virtual void Free() override;

};

END