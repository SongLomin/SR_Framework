#pragma once
#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CRenderer;
class CTransform;
class CMesh_Cube;
END

BEGIN(Client)

class CDummy final :
    public CGameObject
{
private:
    CDummy() = default;
    CDummy(const CDummy& Prototype);
    virtual ~CDummy() = default;

public:
    // CGameObject��(��) ���� ��ӵ�
    virtual HRESULT Initialize_Prototype() override;
    virtual HRESULT Initialize(void* pArg) override;
    virtual void Tick(_float fTimeDelta) override;
    virtual void LateTick(_float fTimeDelta) override;
    virtual HRESULT Render() override;

private:
    CTransform* m_pTransformCom = nullptr;
    CRenderer* m_pRendererCom = nullptr;
    CMesh_Cube* m_pMeshCom = nullptr;

public:
    // CGameObject��(��) ���� ��ӵ�
    static CDummy* Create();
    virtual CGameObject* Clone(void* pArg) override;
    virtual void Free() override;
};

END