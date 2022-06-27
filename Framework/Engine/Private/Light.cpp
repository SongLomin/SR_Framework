#include "Light.h"

CLight::CLight(const CLight& Prototype)
{
	*this = Prototype;
}

ID3DXEffect** CLight::Get_Effect()
{
	return m_ppLightEffect;
}
