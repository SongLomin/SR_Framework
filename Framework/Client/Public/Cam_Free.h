#pragma once
#include "GameObject.h"
#include "Client_Defines.h"

BEGIN(Engine)
class CTransform;
class CCamera;
END

BEGIN(Client)
class CCam_Free :
    public CGameObject
{
private:
    explicit CCam_Free() = default;
    CCam_Free(const CCam_Free& Prototype);
    virtual ~CCam_Free() = default;

public:
    // CGameObject��(��) ���� ��ӵ�
    virtual HRESULT Initialize_Prototype() override;
    virtual HRESULT Initialize(void* pArg) override;
    virtual void Tick(_float fTimeDelta) override;
    virtual void LateTick(_float fTimeDelta) override;
    virtual HRESULT Render() override;

    void    Set_RouteCamera(CCamera* _pCurCamera, _tchar* _NextCameraTag, _float _fTime);

private:
    void    Make_Route();

private:
    CTransform* m_pTransformCom = nullptr;
    CCamera* m_pCameraCom = nullptr;

    //��Ʈ �������� ����
    _tchar* m_NextCameraTag = L"";
    CTransform* m_pNextCameraTransform = nullptr;
    CTransform* m_pCurCameraTransform = nullptr;

    //��� �Ŀ� ������ Ʈ�������� ���� �溤,��ġ��
    _float3     m_vLook;
    _float3     m_vUp;
    _float3     m_vRight;
    _float3     m_vPos;
    
    _float3     m_vdLook;
    _float3     m_vdUp;
    _float3     m_vdRight;
    _float3     m_vdPos;

    _float      m_fTime=0.f;

  

public:
    static CCam_Free* Create();
    virtual CGameObject* Clone(void* pArg) override;
    virtual void Free() override;

};

END
