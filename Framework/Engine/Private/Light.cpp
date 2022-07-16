#include "Light.h"

CLight::CLight(const CLight& Prototype)
{
	*this = Prototype;
}

ID3DXEffect** CLight::Get_Effect()
{
	return m_ppLightEffect;
}

void CLight::Set_Margin_Position(const _float3& _Position)
{
	m_Margin_Position = _Position;
}

void CLight::Set_LooK_Dir(const _float3& _Look)
{
	m_D3DLight.Direction = _Look;
}

void CLight::Set_LightColorScale(const _float& _ColorScale)
{
	m_fColorScale = _ColorScale;
}

void CLight::Set_LightColor(const D3DXCOLOR& _Color)
{
	m_Color = _Color;
}

void CLight::Set_LightRange(const _float& _Range)
{
	m_D3DLight.Range = _Range;
}

void CLight::Set_D3DLight(const _D3DLIGHT9& _D3DLight)
{
	m_D3DLight = _D3DLight;
}

void CLight::Set_Light_Variables(D3DXCOLOR _Color, _float _lightambient, _float _lightdiffuse, _float _lightspecular,
	_float3 _lightmarginposition, _float3 _lightdirection, _float _lightrange, _float _lightattenuation0, _float _lightattenuation1, _float _lightattenuation2, 
	_float _lightfalloff, _float _lighttheta, _float _lightphi)
{
	m_Color = _Color;
	m_D3DLight.Ambient = _Color*_lightambient;
	m_D3DLight.Diffuse = _Color * _lightdiffuse;
	m_D3DLight.Specular= _Color * _lightspecular;

	m_Margin_Position = _lightmarginposition;
	m_D3DLight.Direction = _lightdirection;
	
	m_D3DLight.Range = _lightrange;
	m_D3DLight.Attenuation0= _lightattenuation0;
	m_D3DLight.Attenuation1 = _lightattenuation1;
	m_D3DLight.Attenuation2 = _lightattenuation2;

	m_D3DLight.Falloff = _lightfalloff;
	m_D3DLight.Theta = _lighttheta;
	m_D3DLight.Phi = _lightphi;

}

void CLight::Set_Preset_PowLight()
{
	m_Color = D3DCOLOR_RGBA(200, 200, 50, 255);
	m_D3DLight.Range = 11.f;
	m_fLifeTime = 0.4f;
	
	m_D3DLight.Attenuation0 = 1.0f;
	m_D3DLight.Attenuation1 = 0.007f;
	m_D3DLight.Attenuation2 = 0.001f;
}

void CLight::Set_Preset_SunLight()
{
	m_Color = D3DCOLOR_RGBA(255, 255, 255, 255);
	m_D3DLight.Range = 600.f;
	//m_D3DLight.Falloff = 600.f;
	//m_D3DLight.Phi = 2.f;
	//m_D3DLight.Theta = 1.f;
	m_fColorScale = 2.f;

	m_D3DLight.Attenuation0 = 1.0f;
	m_D3DLight.Attenuation1 = 0.007f;
	m_D3DLight.Attenuation2 = 0.001f;
}

void CLight::Set_Preset_ItemLight()
{
	m_Margin_Position = _float3(0.f, 10.f, 0.f);
	m_D3DLight.Range = 15.f;
	m_D3DLight.Falloff = 1.f;
	m_D3DLight.Phi = 20;
	m_D3DLight.Theta = 10;

	m_D3DLight.Attenuation0 = 1.0f;
	m_D3DLight.Attenuation1 = 0.007f;
	m_D3DLight.Attenuation2 = 0.001f;


}
