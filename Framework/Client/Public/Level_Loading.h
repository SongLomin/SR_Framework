#pragma once

/* 로더가 자우너을 로드하는 동안 화면에 뭔가를 보여줄꺼여. */
/* 로더한테 계쏙 물어볼꺼야 끝났냐?? */
/* 어 라고하면 다음레벨로 가자.고 */

#include "Client_Defines.h"
#include "Level.h"

BEGIN(Client)

class CLevel_Loading final : public CLevel
{
public:
	CLevel_Loading();
	virtual ~CLevel_Loading() = default;

public:
	virtual HRESULT Initialize(LEVEL eNextLevel);
	virtual void Tick(_float TimeDelta);
	virtual HRESULT Render();
	virtual void Change_Level(void* pArg) {}
	virtual HRESULT Complete_Condition() { return S_OK; }


private:
	LEVEL			m_eNextLevel = LEVEL_END;
	class CLoader*	m_pLoader = nullptr;

public:
	static CLevel_Loading* Create(LEVEL eNextLevel);
	virtual void Free() override;
};

END