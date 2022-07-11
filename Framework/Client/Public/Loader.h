#pragma once

/* 다음레벨에 필요한 자원을 로드하낟. */

#include "Client_Defines.h"
#include "Base.h"

BEGIN(Client)

class CLoader final : public CBase
{
private:
	CLoader(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual ~CLoader() = default;

public:
	CRITICAL_SECTION Get_CS() const {
		return m_CriticalSection;
	}

	LEVEL Get_NextLevelID() const {
		return m_eNextLevel;
	}

	_bool is_Finished() const {
		return m_isFinished;
	}

	const _tchar* Get_LoadingText() const {
		return m_szLoadingText;
	}

public:
	HRESULT Initialize(LEVEL eNextLevel);
	HRESULT Loading_ForLogoLevel();
	HRESULT Loading_ForCharacterSelect();
	HRESULT Loading_ForRedPlanet();
	HRESULT Loading_ForMagmaPlanet();
	HRESULT Loading_ForVenusPlanet();
	HRESULT Loaidng_ForExoPlanet();
	HRESULT Loading_ForSelectPlanet();
	HRESULT Loading_ForSunPlanet();

private:
	LPDIRECT3DDEVICE9			m_pGraphic_Device = nullptr;
	LEVEL						m_eNextLevel = LEVEL_END;

private:
	HANDLE					m_hThread;
	CRITICAL_SECTION		m_CriticalSection;
	_bool					m_isFinished = false;
	_tchar					m_szLoadingText[MAX_PATH] = TEXT("");

public:

	
public:
	static CLoader* Create(LPDIRECT3DDEVICE9 pGraphic_Device, LEVEL eNextLevel);
	virtual void Free() override;
};

END