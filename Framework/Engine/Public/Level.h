#pragma once

#include "Base.h"
#include "GameObject.h"

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
	_bool       m_bEventCheck[20] = { false };

	_uint       m_iFontiX = 1360;
	_uint       m_iFontiXCount = 1470;
	_uint       m_iEnemyCount = 0;

	_uint		m_iNextLevel = 8;

protected:
	CGameObject* m_pTextBoxObject = nullptr;
	CGameObject* m_pQuestBoxObject = nullptr;
	CGameObject* m_pTagetObject = nullptr;
	

public:
	virtual void Free() override;

};

END