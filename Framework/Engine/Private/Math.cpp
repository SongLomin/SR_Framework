#include "Math.h"



CMath::CMath()
{
}

CMath::~CMath()
{
}

HRESULT CMath::WorldToScreen(LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3* pos, D3DXVECTOR3* out)
{
    D3DVIEWPORT9 viewPort;
    D3DXMATRIX view, projection, world;

    pDevice->GetViewport(&viewPort);
    pDevice->GetTransform(D3DTS_VIEW, &view);
    pDevice->GetTransform(D3DTS_PROJECTION, &projection);
    D3DXMatrixIdentity(&world);

    D3DXVec3Project(out, pos, &viewPort, &projection, &view, &world);
    if (out->z < 1) {
        return S_OK;
    }
    
	return E_FAIL;
}

HRESULT CMath::ScreenToWorld(LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3* pos, D3DXVECTOR3* out)
{
    D3DVIEWPORT9 viewPort;
    D3DXMATRIX view, projection;


    pDevice->GetViewport(&viewPort);
    pDevice->GetTransform(D3DTS_VIEW, &view);
    pDevice->GetTransform(D3DTS_PROJECTION, &projection);

    _float3 vProjPos = *pos;

    _float3     vViewPos;
    _float4x4	ProjMatrixInv;

    pDevice->GetTransform(D3DTS_PROJECTION, &ProjMatrixInv);
    D3DXMatrixInverse(&ProjMatrixInv, nullptr, &ProjMatrixInv);
    D3DXVec3TransformCoord(&vViewPos, &vProjPos, &ProjMatrixInv);
   
    _float4x4	ViewMatrixInv;
    pDevice->GetTransform(D3DTS_VIEW, &ViewMatrixInv);
    D3DXMatrixInverse(&ViewMatrixInv, nullptr, &ViewMatrixInv);

    D3DXVec3TransformCoord(out, pos, &ViewMatrixInv);

    return S_OK;
}
