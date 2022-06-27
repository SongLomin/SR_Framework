#include "DirectionalLight.h"
#include "GameInstance.h"

CDirectionalLight::CDirectionalLight(const CDirectionalLight& Prototype)
{
    *this = Prototype;
}

HRESULT CDirectionalLight::Initialize_Prototype()
{
    m_ppLightEffect = GAMEINSTANCE->Get_Shader_From_Key(TEXT("DirectionalLight"));

    return S_OK;
}

HRESULT CDirectionalLight::Initialize(void* pArg)
{
    return S_OK;
}

void CDirectionalLight::Tick(_float fTimeDelta)
{
}

void CDirectionalLight::LateTick(_float fTimeDelta)
{
}

CDirectionalLight* CDirectionalLight::Create()
{
    CREATE_PIPELINE(CDirectionalLight);
}

CComponent* CDirectionalLight::Clone(void* pArg)
{
    CLONE_PIPELINE(CDirectionalLight);
}

void CDirectionalLight::Free()
{
    __super::Free();

    delete this;
}

void CDirectionalLight::DrawLight()
{
    ISVALID(m_ppLightEffect, );



}
