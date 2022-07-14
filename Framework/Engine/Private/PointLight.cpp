#include "PointLight.h"
#include "GameInstance.h"
#include "GameObject.h"

CPointLight::CPointLight(const CPointLight& Prototype)
{
    *this = Prototype;
}

HRESULT CPointLight::Initialize_Prototype()
{
	m_ppLightEffect = GAMEINSTANCE->Get_Shader_From_Key(TEXT("PointLight"));

    return S_OK;
}

HRESULT CPointLight::Initialize(void* pArg)
{
	D3DXCreateSphere(DEVICE, 1, 50, 50, &m_pMesh, 0);

	D3DXVECTOR3 position = D3DXVECTOR3(0.f, 0.f, 5.f);
	D3DXVECTOR3 direction = D3DXVECTOR3(-1.f, -1.f, -1.f);

	m_D3DLight.Type = D3DLIGHTTYPE::D3DLIGHT_POINT;

	m_D3DLight.Ambient = m_Color * 0.5f * m_fColorScale;
	m_D3DLight.Diffuse = m_Color * 0.7f;
	m_D3DLight.Specular = m_Color * 0.9f;

	m_D3DLight.Position = position;
	m_D3DLight.Range = 7.0f;

	m_D3DLight.Attenuation0 = 1.f;
	m_D3DLight.Attenuation1 = 0.7f;
	m_D3DLight.Attenuation2 = 1.8f;
	m_D3DLight.Falloff = 1.f;

    return S_OK;
}

void CPointLight::Tick(_float fTimeDelta)
{
}

void CPointLight::LateTick(_float fTimeDelta)
{
	if (!Get_Enable())
		return;

	if (m_fLifeTime < 0.f)
	{
		Set_Enable(false);
	}

	m_fLifeTime -= fTimeDelta;

	if (!m_bFixed)
		m_D3DLight.Position = m_pOwner->Get_Component<CTransform>()->Get_State(CTransform::STATE_POSITION, true);
	else
		m_D3DLight.Position = _float3(0.f, 0.f, 0.f);
	

	m_D3DLight.Position.x += m_Margin_Position.x;
	m_D3DLight.Position.y += m_Margin_Position.y;
	m_D3DLight.Position.z += m_Margin_Position.z;

	GAMEINSTANCE->Add_Light(this);


}

void CPointLight::Bind_ConstBuffer()
{
	ISVALID(m_ppLightEffect, );

	if (!Get_Enable())
		return;


	m_D3DLight.Ambient = m_Color * 0.5f * m_fColorScale;
	m_D3DLight.Diffuse = m_Color;
	m_D3DLight.Specular = m_Color * 0.6f;


	D3DXHANDLE worldHandle = (*m_ppLightEffect)->GetParameterByName(0, "world");
	D3DXHANDLE projHandle = (*m_ppLightEffect)->GetParameterByName(0, "proj");

	D3DXMATRIX scale, world, proj;
	_float s = m_D3DLight.Range / 1;
	D3DXMatrixScaling(&scale, s, s, s);
	D3DXMatrixTranslation(&world, m_D3DLight.Position.x, m_D3DLight.Position.y, m_D3DLight.Position.z);
	world = scale * world;
	DEVICE->GetTransform(D3DTS_PROJECTION, &proj);

	(*m_ppLightEffect)->SetMatrix(worldHandle, &world);
	(*m_ppLightEffect)->SetMatrix(projHandle, &proj);

	D3DXHANDLE lightAmbientHandle = (*m_ppLightEffect)->GetParameterByName(0, "light_ambient");
	D3DXHANDLE lightDiffuseHandle = (*m_ppLightEffect)->GetParameterByName(0, "light_diffuse");
	D3DXHANDLE lightSpecularHandle = (*m_ppLightEffect)->GetParameterByName(0, "light_specular");

	D3DXHANDLE lightPositionHandle = (*m_ppLightEffect)->GetParameterByName(0, "light_position");
	D3DXHANDLE lightDirectionHandle = (*m_ppLightEffect)->GetParameterByName(0, "light_direction");

	D3DXHANDLE lightRangeHandle = (*m_ppLightEffect)->GetParameterByName(0, "light_range");
	D3DXHANDLE lightFalloffHandle = (*m_ppLightEffect)->GetParameterByName(0, "light_falloff");

	D3DXHANDLE lightAttenuation0Handle = (*m_ppLightEffect)->GetParameterByName(0, "light_attenuation0");
	D3DXHANDLE lightAttenuation1Handle = (*m_ppLightEffect)->GetParameterByName(0, "light_attenuation1");
	D3DXHANDLE lightAttenuation2Handle = (*m_ppLightEffect)->GetParameterByName(0, "light_attenuation2");

	D3DXHANDLE lightThetaHandle = (*m_ppLightEffect)->GetParameterByName(0, "light_theta");
	D3DXHANDLE lightPhiHandle = (*m_ppLightEffect)->GetParameterByName(0, "light_phi");

	float floatArray[3];

	floatArray[0] = m_D3DLight.Ambient.r;
	floatArray[1] = m_D3DLight.Ambient.g;
	floatArray[2] = m_D3DLight.Ambient.b;
	(*m_ppLightEffect)->SetFloatArray(lightAmbientHandle, floatArray, 3);

	floatArray[0] = m_D3DLight.Diffuse.r;
	floatArray[1] = m_D3DLight.Diffuse.g;
	floatArray[2] = m_D3DLight.Diffuse.b;
	(*m_ppLightEffect)->SetFloatArray(lightDiffuseHandle, floatArray, 3);

	floatArray[0] = m_D3DLight.Specular.r;
	floatArray[1] = m_D3DLight.Specular.g;
	floatArray[2] = m_D3DLight.Specular.b;
	(*m_ppLightEffect)->SetFloatArray(lightSpecularHandle, floatArray, 3);

	floatArray[0] = m_D3DLight.Position.x;
	floatArray[1] = m_D3DLight.Position.y;
	floatArray[2] = m_D3DLight.Position.z;
	(*m_ppLightEffect)->SetFloatArray(lightPositionHandle, floatArray, 3);

	floatArray[0] = m_D3DLight.Direction.x;
	floatArray[1] = m_D3DLight.Direction.y;
	floatArray[2] = m_D3DLight.Direction.z;
	(*m_ppLightEffect)->SetFloatArray(lightDirectionHandle, floatArray, 3);

	(*m_ppLightEffect)->SetFloat(lightRangeHandle, m_D3DLight.Range);
	(*m_ppLightEffect)->SetFloat(lightFalloffHandle, m_D3DLight.Falloff);

	(*m_ppLightEffect)->SetFloat(lightAttenuation0Handle, m_D3DLight.Attenuation0);
	(*m_ppLightEffect)->SetFloat(lightAttenuation1Handle, m_D3DLight.Attenuation1);
	(*m_ppLightEffect)->SetFloat(lightAttenuation2Handle, m_D3DLight.Attenuation2);

	(*m_ppLightEffect)->SetFloat(lightThetaHandle, m_D3DLight.Theta);
	(*m_ppLightEffect)->SetFloat(lightPhiHandle, m_D3DLight.Phi);




	D3DXHANDLE hTech = (*m_ppLightEffect)->GetTechniqueByName("StencilCulling");
	(*m_ppLightEffect)->SetTechnique(hTech);

	DEVICE->Clear(0, 0, D3DCLEAR_STENCIL, 0x00000000, 1.0f, 0);

}

void CPointLight::DrawLight()
{
	ISVALID(m_ppLightEffect, );

	if (!Get_Enable())
		return;

	DEVICE->SetFVF(D3DFVF_XYZ | D3DFVF_NORMAL);
	m_pMesh->DrawSubset(0);
}

CPointLight* CPointLight::Create()
{
    CREATE_PIPELINE(CPointLight);
}

CComponent* CPointLight::Clone(void* pArg)
{
    CLONE_PIPELINE(CPointLight);
}

void CPointLight::Free()
{
    __super::Free();

	if (m_pMesh)
	{
		_ulong refcnt = m_pMesh->Release();

		if (refcnt > 0)
		{
			while (refcnt != 0)
			{
				refcnt = m_pMesh->Release();
			}
		}

		m_pMesh = nullptr;
	}

    delete this;

}
