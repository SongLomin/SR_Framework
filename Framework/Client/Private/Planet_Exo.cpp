#include "stdafx.h"
#include "Planet_Exo.h"
#include "GameInstance.h"
#include "Math_Utillity.h"
#include "Level_Loading.h"
#include "Dive.h"

CPlanet_Exo::CPlanet_Exo()
{
}

CPlanet_Exo::CPlanet_Exo(const CPlanet_Exo& Prototype)
{
	*this = Prototype;
}

HRESULT CPlanet_Exo::Initialize(void* pArg)
{

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	_float3 StartPos = { -250.f, 150.f, 250.f };
	_tchar* PontText = TEXT("Exo Planet \n 고 위험 구역 \n \n 임무 : 생존 \n 난이도 :『★★★★★』  \n 보상 : XXX");
	_point PontPos = { (LONG)m_vScreenPos.x + 40, (LONG)m_vScreenPos.y - 10 };
	_float3 MyScale = _float3(100.f, 100.f, 50.f);
	_uint TextureIndex = 1;
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(-250.f, 200.f, 250.f));

	m_pDiveUi = GAMEINSTANCE->Add_GameObject<CDive>(LEVEL_SELECTPLANET, TEXT("Dive"));
	m_pDiveUi->Set_Enable(false);


	return S_OK;
}

	SetUp_Varialbes_For_Child(StartPos, PontText, PontPos, TextureIndex, LEVEL::LEVLE_EXOPLANET, MyScale);
void CPlanet_Exo::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	Enter_Planet();
	_float3 MouseEndPos;
	RAY	MouseWorldPos;
	MouseWorldPos = CMath_Utillity::Get_MouseRayInWorldSpace();
	MouseEndPos = MouseWorldPos.Pos + (MouseWorldPos.Dir * MouseWorldPos.fLength);//얘는 왜 있는거임?

}

void CPlanet_Exo::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);


	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_NONALPHABLEND, this);


}

HRESULT CPlanet_Exo::Render()
{

	m_pTransformCom->Bind_WorldMatrix();


	m_pRendererCom->Bind_Texture(1);

	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	DEVICE->SetRenderState(D3DRS_ALPHAREF, 253);
	DEVICE->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	m_pVIBufferCom->Render();

	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	m_pRendererCom->UnBind_Texture();



	return S_OK;
}

void CPlanet_Exo::SetUp_Components_For_Child()
{
}


CPlanet_Exo* CPlanet_Exo::Create()
{
	CREATE_PIPELINE(CPlanet_Exo);
}

CGameObject* CPlanet_Exo::Clone(void* pArg)
{
	CLONE_PIPELINE(CPlanet_Exo);
}

void CPlanet_Exo::Free()
{
	__super::Free();

	delete this;
}
