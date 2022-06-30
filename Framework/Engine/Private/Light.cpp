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

void CLight::Set_Preset_PowLight()
{
	m_Color = D3DCOLOR_RGBA(230, 0, 230, 255);
	m_D3DLight.Range = 11.f;

}

void CLight::Set_Preset_SunLight()
{
	m_Color = D3DCOLOR_RGBA(255, 255, 255, 255);
	m_D3DLight.Range = 600.f;
	//m_D3DLight.Falloff = 600.f;
	//m_D3DLight.Phi = 2.f;
	//m_D3DLight.Theta = 1.f;

	m_D3DLight.Attenuation0 = 1.0f;
	m_D3DLight.Attenuation1 = 0.007f;
	m_D3DLight.Attenuation2 = 0.0002f;
}
