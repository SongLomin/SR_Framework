#include "Lock_Controller.h"

CLock_Controller::CLock_Controller()
{
}

CLock_Controller::CLock_Controller(const CLock_Controller& Prototype)
{
	*this = Prototype;

}

HRESULT CLock_Controller::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CLock_Controller::Initialize(void* pArg)
{
	return S_OK;
}

void CLock_Controller::Tick(_float fTimeDelta)
{
}

void CLock_Controller::LateTick(_float fTimeDelta)
{
}

CLock_Controller* CLock_Controller::Create()
{
	CREATE_PIPELINE(CLock_Controller);
}

CController* CLock_Controller::Clone(void* pArg)
{
	CLONE_PIPELINE(CLock_Controller);
}

void CLock_Controller::Free()
{
	__super::Free();

	delete this;

}
