#pragma once
#include "Client_Defines.h"
#include "GPS.h"

BEGIN(Engine)
END

BEGIN(Client)

class CEnemy_GPS final : CGPS
{
private:
	CEnemy_GPS();
	CEnemy_GPS(const CEnemy_GPS& Prototype);
	virtual ~CEnemy_GPS() = default;



public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void LateTick(_float fTimeDelta) override;
	virtual HRESULT Render() override;


private:
	virtual void SetUp_For_Child();

public:
	static CEnemy_GPS* Create();
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;

};

END