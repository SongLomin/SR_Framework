#include "Math_Utillity.h"
#include "GameInstance.h"


CMath_Utillity::CMath_Utillity()
{
}

CMath_Utillity::~CMath_Utillity()
{
}

HRESULT CMath_Utillity::WorldToScreen(D3DXVECTOR3* pos, D3DXVECTOR3* out)
{
    D3DVIEWPORT9 viewPort;
    D3DXMATRIX view, projection, world;

    DEVICE->GetViewport(&viewPort);
    DEVICE->GetTransform(D3DTS_VIEW, &view);
    DEVICE->GetTransform(D3DTS_PROJECTION, &projection);
    D3DXMatrixIdentity(&world);

    D3DXVec3Project(out, pos, &viewPort, &projection, &view, &world);
    if (out->z < 1) {
        return S_OK;
    }
    
	return E_FAIL;
}

HRESULT CMath_Utillity::ScreenToWorld(D3DXVECTOR3* pos, D3DXVECTOR3* out)
{
    D3DVIEWPORT9 viewPort;
    D3DXMATRIX view, projection;


    DEVICE->GetViewport(&viewPort);
    DEVICE->GetTransform(D3DTS_VIEW, &view);
    DEVICE->GetTransform(D3DTS_PROJECTION, &projection);

    _float3 vProjPos = *pos;

    _float3     vViewPos;
    _float4x4	ProjMatrixInv;

    DEVICE->GetTransform(D3DTS_PROJECTION, &ProjMatrixInv);
    D3DXMatrixInverse(&ProjMatrixInv, nullptr, &ProjMatrixInv);
    D3DXVec3TransformCoord(&vViewPos, &vProjPos, &ProjMatrixInv);
   
    _float4x4	ViewMatrixInv;
    DEVICE->GetTransform(D3DTS_VIEW, &ViewMatrixInv);
    D3DXMatrixInverse(&ViewMatrixInv, nullptr, &ViewMatrixInv);

    D3DXVec3TransformCoord(out, pos, &ViewMatrixInv);

    return S_OK;
}
