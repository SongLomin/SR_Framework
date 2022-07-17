#pragma once
#include "Client_Defines.h"
#include "Level.h"


class CLevel_CharacterSelect : public CLevel
{
public:
	CLevel_CharacterSelect() = default;
	virtual ~CLevel_CharacterSelect() = default;

public:
	virtual HRESULT Initialize();
	virtual void Tick(_float fTimeDelta);
	virtual HRESULT Render();
	virtual void Change_Level(void* pArg, _uint _iNextLevel);
	virtual HRESULT Complete_Condition() { return S_OK; }


private:
	vector<CGameObject*> m_vecShips;
	_int	m_iIndex = 0;

private:
	_float3		m_vMovePos = _float3(0.f,0.f,0.f);//카메라가 이동할 위치



public:
	static CLevel_CharacterSelect* Create();
	virtual void Free() override;


};