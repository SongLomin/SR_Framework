#include "Targetting.h"
#include "GameInstance.h"

CTargetting::CTargetting()
{
}

HRESULT CTargetting::Add_Targetting(CGameObject* pObject)
{
	m_pTargetting.push_back(pObject);

	return S_OK;
}

CTargetting* CTargetting::Create()
{
	CREATE_PIPELINE(CTargetting);
}

CComponent* CTargetting::Clone(void* pArg)
{
	CLONE_PIPELINE(CTargetting);
}

void CTargetting::Free()
{
	__super::Free();

	delete this;
}
