#include "DirectionalLight.h"
#include "GameInstance.h"

CDirectionalLight::CDirectionalLight(const CDirectionalLight& Prototype)
{
    *this = Prototype;
	m_ppLightEffect = GAMEINSTANCE->Get_Shader_From_Key(TEXT("DirectionalLight"));
}

HRESULT CDirectionalLight::Initialize_Prototype()
{
    

    return S_OK;
}

HRESULT CDirectionalLight::Initialize(void* pArg)
{
	/* prepare screen quad vertex buffer */
	DEVICE->CreateVertexBuffer(
		6 * sizeof(VTX),
		0,
		D3DFVF_XYZ,
		D3DPOOL_MANAGED,
		&vb,
		0
	);

	/* screen quad coordinates

	-1,1	        1,1
	 v0             v1
	  +-------------+
	  |             |
	  |    screen   |
	  |             |
	  +-------------+
	 v2             v3
	-1,-1          1,-1

	*/
	VTX v0 = {
		-1, 1, 0
	};
	VTX v1 = {
		1, 1, 0
	};
	VTX v2 = {
		-1, -1, 0
	};
	VTX v3 = {
		1, -1, 0
	};

	/* fill into buffer */
	VTX* vertices;
	vb->Lock(0, 0, (void**)&vertices, 0);
	
	vertices[0] = v0;
	vertices[1] = v1;
	vertices[2] = v2;
	vertices[3] = v1;
	vertices[4] = v3;
	vertices[5] = v2;

	vb->Unlock();

	D3DXCOLOR color = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);       // white
	D3DXVECTOR3 position = D3DXVECTOR3(0.f, 0.f, 5.f);
	D3DXVECTOR3 direction = D3DXVECTOR3(-1.f, -1.f, -1.f);
	D3DXVec3Normalize(&direction, &direction);

	m_D3DLight.Type = D3DLIGHTTYPE::D3DLIGHT_DIRECTIONAL;

	m_D3DLight.Ambient = color * 0.5f;
	m_D3DLight.Diffuse = color;
	m_D3DLight.Specular = color * 0.9f;

	m_D3DLight.Direction = direction;

    return S_OK;
}

void CDirectionalLight::Tick(_float fTimeDelta)
{
}

void CDirectionalLight::LateTick(_float fTimeDelta)
{
	GAMEINSTANCE->Add_Light(this);
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

void CDirectionalLight::Bind_ConstBuffer()
{
    ISVALID(m_ppLightEffect, );

	D3DXHANDLE lightAmbientHandle = (*m_ppLightEffect)->GetParameterByName(0, "light_ambient");
	D3DXHANDLE lightDiffuseHandle = (*m_ppLightEffect)->GetParameterByName(0, "light_diffuse");
	D3DXHANDLE lightSpecularHandle = (*m_ppLightEffect)->GetParameterByName(0, "light_specular");


	D3DXHANDLE lightDirectionHandle = (*m_ppLightEffect)->GetParameterByName(0, "light_direction");


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


	floatArray[0] = m_D3DLight.Direction.x;
	floatArray[1] = m_D3DLight.Direction.y;
	floatArray[2] = m_D3DLight.Direction.z;
	(*m_ppLightEffect)->SetFloatArray(lightDirectionHandle, floatArray, 3);


    D3DXHANDLE hTech = (*m_ppLightEffect)->GetTechniqueByName("Plain");
    (*m_ppLightEffect)->SetTechnique(hTech);
	

}

void CDirectionalLight::DrawLight()
{
    ISVALID(m_ppLightEffect, );

	DEVICE->SetRenderState(D3DRS_ZWRITEENABLE, false);
	DEVICE->SetStreamSource(0, vb, 0, sizeof(VTX));
	DEVICE->SetFVF(D3DFVF_XYZ);
	DEVICE->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
	DEVICE->SetRenderState(D3DRS_ZWRITEENABLE, true);
}
