#include "Camera_Manager.h"
#include "GameInstance.h"

IMPLEMENT_SINGLETON(CCamera_Manager)

CCamera* CCamera_Manager::Get_Camera(const _tchar* _CameraTag)
{
	if (!lstrcmp(_CameraTag, TEXT("")))
	{
		return m_pCurrentCam;
	}

	auto iter = find_if(m_Cams.begin(), m_Cams.end(), CTag_Finder(_CameraTag));

	if (m_Cams.end() == iter)
	{
		return nullptr;
	}

	return iter->second;
}

void CCamera_Manager::Set_Current_Camera(const _tchar* _CameraTag)
{
	CCamera* pCam = Get_Camera(_CameraTag);

	ISVALID(pCam, );

	m_pCurrentCam = pCam;
	m_pCurrentCam->Set_WeakPtr(&m_pCurrentCam);
}

void CCamera_Manager::Add_Shaking(_float _fOffset, _float _fInclination)
{
	m_pCurrentCam->Add_Shaking(_fOffset, _fInclination);
}



void CCamera_Manager::Tick(_float fTimeDelta)
{
	ISVALID(m_pCurrentCam, );


}

void CCamera_Manager::LateTick(_float fTimeDelta)
{
	Clear_Empty_Camera();

	ISVALID(m_pCurrentCam, );

	
	m_pCurrentCam->Bind_PipeLine();
}

void CCamera_Manager::Clear_Empty_Camera()
{
	for (auto iter = m_Cams.begin(); iter != m_Cams.end();)
	{
		if (!iter->second)
		{
			iter = m_Cams.erase(iter);
		}
		
		else
		{
			iter++;
		}
	}
}

void CCamera_Manager::Register_Camera(const _tchar* _CameraTag, CCamera* _CameraCom)
{
	m_Cams.emplace(_CameraTag, _CameraCom);

	auto iter = find_if(m_Cams.begin(), m_Cams.end(), CTag_Finder(_CameraTag));

	if (m_Cams.end() != iter)
	{
		iter->second->Set_WeakPtr(&(iter->second));
	}
}

void CCamera_Manager::Set_Target(CTransform* _Target, const _tchar* _CameraTag)
{
	CCamera* pCam = Get_Camera(_CameraTag);

	ISVALID(pCam, );

	pCam->Set_Target(_Target);
}

void CCamera_Manager::Free()
{
	//전부 참조 포인터라서 Free할 객체가 없다.

	__super::Free();
	
	delete this;
	
}