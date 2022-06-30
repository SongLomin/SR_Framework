#pragma once

#include "Base.h"

/* 현재 게임내에 보여줘야할 레벨을 보관한다. */
/* 레벨교체시에 기존 레벨을 삭제한다. */
/* 기존레벨에서 사용했던 객체와 자원(리소스등)을 정리한다. */

BEGIN(Engine)

class CLevel_Manager final : public CBase
{
	DECLARE_SINGLETON(CLevel_Manager)
public:
	CLevel_Manager();
	virtual ~CLevel_Manager() = default;

public:
	HRESULT Open_Level(_uint iLevelID, class CLevel* pLevel);
	
	HRESULT	Register_OpenLevelEvent(_uint iLevelID, CLevel* pLevel);
	HRESULT Call_OpenLevelEvent();
	
	void Set_CurrentLevelIndex(_uint iLevelID);
	_uint Get_CurrentLevelIndex();
	void Tick(_float fTimeDelta);
	HRESULT Render();

private:
	class CLevel*			m_pCurrentLevel = nullptr;
	_uint					m_iCurrentLevelID = 0;
	//인덱스용도만 쓴다.
	_uint					m_iCurrentLevelIndex = 0;
	
	function<HRESULT(_uint, CLevel*)> m_OpenLevelEvent = nullptr;

private:
	_uint					m_iEventLevelID = 0;
	CLevel*					m_pEventLevel = nullptr;
	_bool					m_bEvent = false;


public:
	virtual void Free() override;
};

END