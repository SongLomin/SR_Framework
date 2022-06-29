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

void CLight::Set_LightRange(const _float& _Range)
{
	m_D3DLight.Range = _Range;
}

void CLight::Set_D3DLight(const _D3DLIGHT9& _D3DLight)
{
	m_D3DLight = _D3DLight;
}
