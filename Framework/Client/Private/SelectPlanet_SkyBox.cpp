#include "stdafx.h"
#include "SelectPlanet_SkyBox.h"
#include "GameInstance.h"


CSelectPlanet_SkyBox::CSelectPlanet_SkyBox()
{
}

CSelectPlanet_SkyBox::CSelectPlanet_SkyBox(const CSelectPlanet_SkyBox& Prototype)
{
	*this = Prototype;

	Add_Component<CTransform>();
}

HRESULT CSelectPlanet_SkyBox::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CSelectPlanet_SkyBox::Initialize(void* pArg)
{
	if (FAILED(SetUp_Components()))
		return E_FAIL;

	return S_OK;
}

void CSelectPlanet_SkyBox::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);


}

void CSelectPlanet_SkyBox::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	_float4x4		ViewMatrix;
	DEVICE->GetTransform(D3DTS_VIEW, &ViewMatrix);

	D3DXMatrixInverse(&ViewMatrix, nullptr, &ViewMatrix);

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, *(_float3*)&ViewMatrix.m[3][0], true);

	m_pRendererCom->Add_RenderGroup(RENDERGROUP::RENDER_PRIORITY, this);

}

HRESULT CSelectPlanet_SkyBox::Render_Begin(ID3DXEffect** Shader)
{
	m_pTransformCom->Bind_WorldMatrix();

	D3DXHANDLE ColorHandle = (*Shader)->GetParameterByName(0, "Color");
	D3DXHANDLE CameraPosHandle = (*Shader)->GetParameterByName(0, "CameraPosition");
	D3DXHANDLE DiffuseHandle = (*Shader)->GetParameterByName(0, "Diffuse");
	D3DXHANDLE SpecularHandle = (*Shader)->GetParameterByName(0, "Specular");
	D3DXHANDLE CubeTextureHandle = (*Shader)->GetParameterByName(0, "SkyBoxTexture");


	float ColorArray[3];
	ColorArray[0] = 1.f;
	ColorArray[1] = 0.f;
	ColorArray[2] = 0.f;

	_float4x4 CameraPos = GAMEINSTANCE->Get_Camera(CURRENT_CAMERA)->Get_CameraWorldMat();

	float CameraPosArray[3];
	CameraPosArray[0] = CameraPos._41;
	CameraPosArray[1] = CameraPos._42;
	CameraPosArray[2] = CameraPos._43;


	LPDIRECT3DBASETEXTURE9 Texture = m_pRendererCom->Get_Texture(6);

	float Specular = 1.f;
	float Diffuse = 1.f;

	(*Shader)->SetFloatArray(ColorHandle, ColorArray, 3);
	(*Shader)->SetFloatArray(CameraPosHandle, CameraPosArray, 3);
	(*Shader)->SetFloat(DiffuseHandle, Diffuse);
	(*Shader)->SetFloat(SpecularHandle, Specular);
	(*Shader)->SetTexture(CubeTextureHandle, m_pRendererCom->Get_Texture(6));

	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	DEVICE->SetRenderState(D3DRS_ZENABLE, FALSE);
	DEVICE->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	return S_OK;
}

HRESULT CSelectPlanet_SkyBox::Render()
{
	m_pMeshCom->Render_Mesh_From_FVF(VTX::FVF);

	DEVICE->SetRenderState(D3DRS_ZENABLE, TRUE);
	DEVICE->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	/*m_pTransformCom->Bind_WorldMatrix();


	m_pRendererCom->Bind_Texture(6);


	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	DEVICE->SetRenderState(D3DRS_ZENABLE, FALSE);
	DEVICE->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	__super::Render();


	DEVICE->SetRenderState(D3DRS_ZENABLE, TRUE);
	DEVICE->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	m_pRendererCom->UnBind_Texture();*/

	return S_OK;
}

HRESULT CSelectPlanet_SkyBox::SetUp_Components()
{

	m_pTransformCom = Get_Component<CTransform>();
	m_pTransformCom->Set_WeakPtr(&m_pTransformCom);

	m_pRendererCom = Add_Component<CRenderer>();
	m_pRendererCom->Set_WeakPtr(&m_pRendererCom);
	m_pRendererCom->Set_Textures_From_Key(TEXT("Sky_Test"), MEMORY_TYPE::MEMORY_STATIC);

	m_pMeshCom = Add_Component<CMesh_Cube>();
	m_pMeshCom->Set_WeakPtr(&m_pMeshCom);



	return S_OK;
}

CSelectPlanet_SkyBox* CSelectPlanet_SkyBox::Create()
{
	CREATE_PIPELINE(CSelectPlanet_SkyBox);
}

CGameObject* CSelectPlanet_SkyBox::Clone(void* pArg)
{
	CLONE_PIPELINE(CSelectPlanet_SkyBox);
}

void CSelectPlanet_SkyBox::Free()
{
	__super::Free();

	delete this;
}
