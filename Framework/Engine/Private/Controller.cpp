#include "Controller.h"
#include "GameInstance.h"
#include "GameObject.h"

CController::CController()
{
}

CController::CController(const CController& Prototype)
{
	*this = Prototype;
}

void CController::Link_Object(CGameObject* _pObject)
{
	m_pMyObject = _pObject;
	WEAK_PTR(m_pMyObject);
}

void CController::Set_Lock(_bool _bLock)
{
	m_bLock = _bLock;
}

_bool CController::Get_Lock()
{
	return	m_bLock;
}



void CController::Free()
{
	__super::Free();

}
