#include "SpotLight.h"
#include "GameInstance.h"
#include "GameObject.h"

CSpotLight::CSpotLight(const CSpotLight& Prototype)
{
	*this = Prototype;
}

HRESULT CSpotLight::Initialize_Prototype()
{
	m_ppLightEffect = GAMEINSTANCE->Get_Shader_From_Key(TEXT("SpotLight"));

	return S_OK;
}

HRESULT CSpotLight::Initialize(void* pArg)
{
	D3DXCreateSphere(DEVICE, 1, 50, 50, &m_pMesh, 0);


	m_D3DLight.Type = D3DLIGHTTYPE::D3DLIGHT_SPOT;



	return S_OK;
}

void CSpotLight::Tick(_float fTimeDelta)
{

	if (m_fLifeTime < 0.f)
	{
		Set_Enable(false);
	}

	m_fLifeTime -= fTimeDelta;
}

void CSpotLight::LateTick(_float fTimeDelta)
{
	if (!Get_Enable())
		return;

	CTransform* pOwnerTransform = m_pOwner->Get_Component<CTransform>();

	m_D3DLight.Position = pOwnerTransform->Get_State(CTransform::STATE_POSITION, true);
	
	m_D3DLight.Position.x += m_Margin_Position.x;
	m_D3DLight.Position.y += m_Margin_Position.y;
	m_D3DLight.Position.z += m_Margin_Position.z;

	m_D3DLight.Direction = -1.f*pOwnerTransform->Get_State(CTransform::STATE_LOOK, true);

	GAMEINSTANCE->Add_Light(this);
}

void CSpotLight::Bind_ConstBuffer()
{
	ISVALID(m_ppLightEffect, );

	if (!Get_Enable())
	{
		return;
	}

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

void CSpotLight::DrawLight()
{
	ISVALID(m_ppLightEffect, );

	if (!Get_Enable())
	{
		return;
	}

	DEVICE->SetFVF(D3DFVF_XYZ | D3DFVF_NORMAL);
	m_pMesh->DrawSubset(0);
}

CSpotLight* CSpotLight::Create()
{
	CREATE_PIPELINE(CSpotLight);
}

CComponent* CSpotLight::Clone(void* pArg)
{
	CLONE_PIPELINE(CSpotLight);
}

void CSpotLight::Free()
{
	__super::Free();

	if (m_pMesh)
	{
		m_pMesh->Release();
		m_pMesh = nullptr;
	}

	delete this;
}
