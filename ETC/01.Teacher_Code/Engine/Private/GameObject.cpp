#include "..\Public\GameObject.h"
#include "GameInstance.h"
#include "Transform.h"

CGameObject::CGameObject(LPDIRECT3DDEVICE9 pGraphic_Device)
	: m_pGraphic_Device(pGraphic_Device)
{
	Safe_AddRef(m_pGraphic_Device);
}

CGameObject::CGameObject(const CGameObject & Prototype)
	: m_pGraphic_Device(Prototype.m_pGraphic_Device)
{
	Safe_AddRef(m_pGraphic_Device);
}

CComponent * CGameObject::Get_Component(const _tchar * pComponentTag)
{
	return Find_Components(pComponentTag);	
}

HRESULT CGameObject::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CGameObject::Initialize(void* pArg)
{
	return S_OK;
}

void CGameObject::Tick(_float fTimeDelta)
{
}

void CGameObject::LateTick(_float fTimeDelta)
{
}

HRESULT CGameObject::Render()
{
	return S_OK;
}

HRESULT CGameObject::Compute_CamDistance(CTransform* pTransform)
{
	CGameInstance*		pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	_float4x4		ViewMatrix;

	m_pGraphic_Device->GetTransform(D3DTS_VIEW, &ViewMatrix);
	D3DXMatrixInverse(&ViewMatrix, nullptr, &ViewMatrix);

	_float3		vCamDir = *(_float3*)&ViewMatrix.m[3][0] - pTransform->Get_State(CTransform::STATE_POSITION);

	m_fCamDistance = D3DXVec3Length(&vCamDir);

	Safe_Release(pGameInstance);

	return S_OK;
}

HRESULT CGameObject::Add_Component(_uint iLevelIndex, const _tchar * pPrototypeTag, const _tchar * pComponentTag, CComponent** ppOut, void * pArg)
{
	if (nullptr != Find_Components(pComponentTag))
		return E_FAIL;

	CGameInstance*		pGameInstance = CGameInstance::Get_Instance();
	Safe_AddRef(pGameInstance);

	CComponent*		pComponent = pGameInstance->Clone_Component(iLevelIndex, pPrototypeTag, pArg);
	if (nullptr == pComponent)
		return E_FAIL;

	m_Components.emplace(pComponentTag, pComponent);

	*ppOut = pComponent;

	Safe_AddRef(pComponent);

	Safe_Release(pGameInstance);
	return S_OK;
}

CComponent * CGameObject::Find_Components(const _tchar * pComponentTag)
{
	auto	iter = find_if(m_Components.begin(), m_Components.end(), CTag_Finder(pComponentTag));

	if (iter == m_Components.end())
		return nullptr;

	return iter->second;
}

void CGameObject::Free()
{
	for (auto& Pair : m_Components)
		Safe_Release(Pair.second);

	m_Components.clear();

	Safe_Release(m_pGraphic_Device);
}
