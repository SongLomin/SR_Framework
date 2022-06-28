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
	m_pObject = _pObject;
	WEAK_PTR(m_pObject);
}



void CController::Free()
{
	__super::Free();

}
